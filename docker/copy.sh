#!/usr/bin/env bash
# dpw@alamo
# 2024-01-19 18:01:34
#

set -eu

docker cp ../.ssh/id_rsa cryptor-service:/home/cryptor/.ssh/
docker cp ../.ssh/id_rsa.pub cryptor-service:/home/cryptor/.ssh/

