#!/usr/bin/env bash
# dpw@alamo
# 2024-01-19 18:01:34
#

set -eu

# docker cp ../.ssh/cert.pem cryptor-service:/home/cryptor/.ssh/
# docker cp ../.ssh/key.pem cryptor-service:/home/cryptor/.ssh/

# docker cp /usr/local/include/ansi_colors.hpp cryptor-service:/usr/local/include/
# docker cp /usr/local/include/httplib.h cryptor-service:/usr/local/include/

docker cp ~/.ssh/id_rsa cryptor-service:/home/cryptor/.ssh/
docker cp ~/.ssh/id_rsa.pub cryptor-service:/home/cryptor/.ssh/


