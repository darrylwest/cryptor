#!/bin/sh
# darwest@ebay.com <darryl.west>
# 2024.01.19
#

export NAME="cryptor-service"

# -v "$PWD":/home/dpw/

# config-data

docker run -it -d -u cryptor \
    --publish 29200:29200 \
    --hostname=cryptor \
    --name $NAME  \
    "darrylwest/$NAME:latest"

