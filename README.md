# Cryptor Web App

## Overview

The Cryptor Web App and service enable encryption and decryption of sensitive private messages.  The service is 
designed to run on a local, private network although it is safe to run in a public hosted environment.  

Encrypted files are note saved by the backend service, but to the downloads folder of the device running the 
browser application.  Also important to note that the password never leaves the browser.  Hosting the service
locally reduces the risk of phishing attacts.

## Installation Instructions

### Docker

The easies way to run the service without having to compile is by running the pre-compiled docker image.  It
does require running docker.


### Mac (Intel and ATOM)

* [ ] Intel: macOS Sonoma Version 14.6
* [ ] Silicon: macOS Sequoia Version 15.1
* [ ] brew
* [ ] cmake
* [ ] clang++ Apple clang version 16.0.0 (clang-1600.0.26.4)
* [ ] spdlog
* [ ] openssl@3
* [ ] cpp-httplib
* [ ] clang-format (optional)

### Linux

* [ ] g++ version 11.
* [ ] cmake
* [ ] spdlog (complied with make install)
* [ ] openssl@3
* [ ] cpp-httplib

## Basic Use

The server requires cert.pem and key.pem files to enable TLS.  You can create them using openssl.

### Run the applicaton

_TBD_

### Run the unit tests

_TBD_

## Reporting Issues

A list of issues is available in the crypto repo.

###### 2024.12.14 | dpw
