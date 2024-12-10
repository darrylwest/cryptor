# Cryptor Server

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

### Linux

* [ ] g++ version 11.
* [ ] spdlog (complied with make instll)
* [ ] openssl@3

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


###### 2024.12.10 | dpw
