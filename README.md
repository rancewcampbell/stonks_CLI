# Stonks CLI

## Description

With all the recent buzz on the stock market, I was getting tired of constantly checking specific stocks online. This inspired me to create this little commandline tool to get stock quotes instantly. All you need is an API key to the [Finnhub](https://finnhub.io/) financial API and you are on your way! By default the program can take up to 5 stock tickers. This is to avoid too many API requests. This has only been tested on Linux, but should work on any Linux/Unix machine with minimal tweaking. Feel free to take this and make it your own!

![](./stonks_CLI.gif)

## Installation Instructions

- Clone repo

- `cd/stonks_CLI`

- Make sure the `CC` variable in *Makefile* is your C compiler (*gcc* by default)

- Make sure the `BINPATH` variable in *Makefile* is the path to your `/bin` directory

- Run `make install`

- If you don't want to install in `/bin`, run `make` to build in local directory


## Usage

- Set a `FINNHUB_API_KEY` environment variable to your Finnhub API key. Here's a [post](https://unix.stackexchange.com/questions/117467/how-to-permanently-set-environmental-variables) to explain how to do this if you forgot.

- Run `stonks <ticker>` where the ticker is any valid stock ticker symbol.

- Use a `-p` flag to enable a refresh every 10 seconds: `stonks -p <ticker>`

## Dependancies

- libCURL C library
- pthreads C library
- C compiler (set in *Makefile*)
- [Finnhub](https://finnhub.io/) API key (free for developers)

## Troubleshooting

- Sometimes the compiler can't find the libcurl headers. If this is the case for you (as it was for me), following the instructions on the [CURL](https://curl.se/libcurl/c/libcurl-tutorial.html) website should tell you how to fix this. Depending on your system this might require you having to update the `#include` for `curl.h`.

## License

Copyright 2021 Rance Campbell

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.