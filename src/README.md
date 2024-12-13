# Cryptor Server


### Shutdown Hook

curl -k -XDELETE https://<host>:<port>/shutdown

or on the local dev machine, `make shutdown`

## cpp-httplib

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
* [x] add unit.cpp with cli and help
* [ ] implement tests with httplib https client
* [ ] refactor main to move all the service stuff to service.hpp
* [ ] move the project to the starter template
* [ ] error handling
* [ ] refactor repo to put server at top level and html below


###### 2024.12.12 | dpw
