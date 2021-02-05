#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BWHT    "\e[1;37m"
#define CLEAR   "\e[1;1H\e[2J"


typedef struct {
  char *ptr;
  size_t len;
} CURLdata;

typedef struct {
    char *curr;
    char *high;
    char *low;
} QUOTE;

typedef char URL[256];

/* initialize the struct needed to receive the GET request */
void init_CURLdata(CURLdata *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

/* CURL provides format for write functions in their documentation */
size_t writefunc(void *ptr, size_t size, size_t nmemb, CURLdata *data)
{
  size_t new_len = data->len + size*nmemb;
  data->ptr = realloc(data->ptr, new_len+1);
  if (data->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(data->ptr + data->len, ptr, size*nmemb);
  data->ptr[new_len] = '\0';
  data->len = new_len;

  return size*nmemb;
}

/* removes chars from beginning of string. */
void delchar(char *str, int num_delete)
{
    int len = strlen(str) - num_delete;
    if ((num_delete) <= strlen(str)) {
        memmove(&str[0], &str[num_delete], len);
        str[len] = '\0';
    }
}

/* construct necessary URL for API GET quote request. */
void buildURL(URL *base_url, char *symbol, char *API, int API_len) {
    strncat(*base_url, "quote?symbol=", 14);
    strncat(*base_url, symbol, 10);
    strncat(*base_url, "&token=", 8);
    strncat(*base_url, API, API_len);
}

/* use CURL library to get quote data and save in CURLdata struct */
void getQuote(CURL *curl, CURLcode res, URL *url, CURLdata *data) {
    curl_easy_setopt(curl, CURLOPT_URL, *url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);
    res = curl_easy_perform(curl);
}

/* API returns JSON formatted data. parseQuote splits on commas and
   deletes the leading chars to get just the price for each field */
void parseQuote(QUOTE *quote, CURLdata *data) {
    quote->curr = strtok(data->ptr, ",");
    quote->high = strtok(NULL, ",");
    quote->low = strtok(NULL, ",");

    delchar(quote->curr, 5);
    delchar(quote->high, 4);
    delchar(quote->low, 4);
}

void printQuote(char *symbol, QUOTE *quote) {
    printf(CLEAR);
    printf("Quote for ");
    printf(BWHT "%s\n" RESET, symbol);
    printf("Current price:\t");
    printf(GREEN "$%s\n" RESET, quote->curr);
    printf("Daily High:\t");
    printf(YELLOW "$%s\n" RESET, quote->high);
    printf("Daily Low:\t");
    printf(RED "$%s\n\n" RESET, quote->low);
}

int main(int argc, char *argv[]) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    CURLdata data;
    QUOTE quote;
    URL base_url = "https://finnhub.io/api/v1/";
    char *API = getenv("FINNHUB_API_KEY");
    size_t API_len = strlen(API);
    char *symbol = argv[1];

    /* check if user entered everything properly */
    if (argc < 2) {
        fprintf(stderr, "I need a stock symbol\n");
        return EXIT_FAILURE;
    } else if (!API) {
        fprintf(stderr, "Set your FINNHUB_API_KEY env var");
        return EXIT_FAILURE;
    } 
    
    /* make sure curl initializes properly */
    if (!curl) {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }

    init_CURLdata(&data);

    buildURL(&base_url, symbol, API, API_len);
    getQuote(curl, res, &base_url, &data);
    parseQuote(&quote, &data);
    printQuote(symbol, &quote);

    free(data.ptr);

    curl_easy_cleanup(curl);

    return EXIT_SUCCESS;
}