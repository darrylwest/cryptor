# Cryptor Server

## Basic Use

### License

_TBD_

### Shutdown Hook

curl -k -XDELETE https://<host>:<port>/shutdown

or on the local dev machine, `make shutdown`

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
* [ ] brew to install clang-format

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
* [x] replace the cert/key file define with attrs in Config; 
* [x] add CLI --cert <file> --key <file>
* [ ] add unit.cpp with cli and help
* [ ] implement tests with httplib https client
* [ ] refactor main to move all the service stuff to service.hpp
* [ ] move the project to the starter template
* [ ] error handling
* [ ] refactor repo to put server at top level and html below


###### 2024.12.10 | dpw
