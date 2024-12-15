#!/usr/bin/env bash
# dpw@alamo
# 2024-01-19 18:01:34
#

set -eu

# docker cp ../.ssh/cert.pem cryptor-service:/home/cryptor/.ssh/
# docker cp ../.ssh/key.pem cryptor-service:/home/cryptor/.ssh/

docker cp /usr/local/include/ansi_colors.hpp config-service:/usr/local/include/
docker cp /usr/local/include/httplib.h config-service:/usr/local/include/

docker cp ~/.ssh/id_rsa config-service:/home/dpw/.ssh/
docker cp ~/.ssh/id_rsa.pub config-service:/home/dpw/.ssh/


