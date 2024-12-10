# Cryptor Server

## Basic Use

### License

_TBD_

### Shutdown Hook

curl -k -XDELETE https://<host>:<port>/shutdown

## cpp-httplib


## Installation Instructions

The server requires cert.pem and key.pem files.

### Mac (Intel and ATOM)

* [ ] Intel: macOS Sonoma Version 14.6
* [ ] ATOM: macOS Sequoia Version 15.1
* [ ] brew (to install openssl@3)
* [ ] clang++ Apple clang version 16.0.0 (clang-1600.0.26.4)
* [ ] spdlog
* [ ] openssl@3
* [ ] cpp-httplib

### Linux

* [ ] g++ version 11.
* [ ] spdlog (complied with make install)
* [ ] openssl@3
* [ ] cpp-httplib

## To Do

* [x] reformat cpp code for 4 spaces
* [x] add version.hpp
* [x] add cli.hpp with help and implement cxxopts
* [x] add spdlog 
* [x] fix logging to use spdlog
* [x] add a shutdown uri /shutdown (delete method)
* [x] remove brew from makefile for linux
* [ ] add unit.hpp with help
* [ ] replace the cert/key file define with attrs in Config; add to CLI --cert <file> --key <file>
* [ ] cmake? use AI to generate based on text from Makefile and cryptor.cpp
* [ ] error handling
* [ ] refactor repo to put server at top level and html below


###### 2024.12.10 | dpw
