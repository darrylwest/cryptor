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

Encrypted files or passwords are not saved by the backend service, and always stay safely in the browser.  Encrypted
messages are saved in your downloads folder on the device running the application.  It is also important to note 
that the passphrase never leaves the browser, so it cannot be hacked by man-in-the-middle attacks.  
Hosting the service on your private network also reduces the risk of phishing attacks.

You can preview the hosted web app [here](https://darrylwest.github.io/cryptor/).

## Installation Instructions

### Docker

The easiest way to run Cryptor service without having to compile is by running the pre-compiled Docker image.  
It requires running [Docker](https://hub.docker.com/) on your local machine, but this is easy on mac or windows.

See the Docker folder for shell scripts to run the container: `./run.sh` then point your browser to [the app](https://localhost:29200).
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
* [ ] spdlog (compiled with make install)
* [ ] openssl@3
* [ ] cpp-httplib
* [ ] clang-format (optional)

Here is an install script that should work on Debian 12 or Umbutu 22:

```bash
sudo apt-get update && apt-get upgrade -y \
    && apt-get install -y libspdlog-dev libcxxopts-dev libcpp-httplib-dev openssl spdlog cxxopts
```

## Basic Use

The server requires cert.pem and key.pem files to enable TLS.  You can create them using openssl.

### Build the application

Easiest way to build the application is to run the `mk` shell script like this:

`./mk init build`

### Run the application

After a successful build, you can run the application like this:

'./build/cryptor --base $root/html

Or, like this: `./mk run`

### Run Unit & Integration Test

After a successful build, you can run the unit and integration tests like this:

'''bash
./build/unit
./build/integration
'''

Or, like this: `./mk test`

## Reporting Issues

A list of issues is available in the crypto repo.  Feel free to add any issues you find, 
or any suggestions for enhancements.

###### 2024.12.16 | dpw
