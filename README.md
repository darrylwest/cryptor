# Cryptor Web App

```
_______________________________________________________________________________________

 ______                    __                _______                    __
|      |.----.--.--.-----.|  |_.-----.----. |     __|.-----.----.--.--.|__|.----.-----.
|   ---||   _|  |  |  _  ||   _|  _  |   _| |__     ||  -__|   _|  |  ||  ||  __|  -__|
|______||__| |___  |   __||____|_____|__|   |_______||_____|__|  \___/ |__||____|_____|
             |_____|__|
_______________________________________________________________________________________
```

## Overview

The Cryptor Web App and service enable encryption and decryption of sensitive private messages.  The service is 
designed to run on a local, private network although it is safe to run in a public hosted environment.  

Encrypted files are note saved by the backend service, but to the downloads folder of the device running the 
browser application.  Also important to note that the password never leaves the browser.  Hosting the service
locally reduces the risk of phishing attacts.

You can preview the hosted web app [here](https://darrylwest.github.io/cryptor/).

## Installation Instructions

### Docker

The easiest way to run Cryptor service without having to compile is by running the pre-compiled docker image.  It
does require running [docker](https://hub.docker.com/).

See the docker folder for shell scipts to run the container: `./run.sh` then point your browser to [the app](https://localhost:29200).
It's also possible to attach to the container, run the post-install script and modify the html or server source (NOTE: you need github access for this).


### Mac (Intel & Apple Silicon)

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

* [ ] g++ version 11 or 12.
* [ ] cmake
* [ ] spdlog (complied with make install)
* [ ] openssl@3
* [ ] cpp-httplib
* [ ] clang-format (optional)

Here is an install script that should work on Debian 12 or Umbutu 22:

```
sudo apt-get update && apt-get upgrade -y \
    && apt-get install -y libspdlog-dev libcxxopts-dev libcpp-httplib-dev openssl spdlog cxxopts
```

## Basic Use

The server requires cert.pem and key.pem files to enable TLS.  You can create them using openssl.

### Build the application

Easiest way to build the applicaton is to run the `mk` shell script like this:

`./mk init build`

### Run the applicaton

After a successfule build, you can run the application like this:

'./build/cryptor --base $root/html

Or, like this: `./mk run`

### Run Unit & Integration Test

After a successfule build, you can run the unit and integration tests like this:

'''
./build/unit
./build/integration
'''

Or, like this: `./mk test`

## Reporting Issues

A list of issues is available in the crypto repo.

###### 2024.12.15 | dpw
