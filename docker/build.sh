#!/bin/sh
# dpw@oakland.local
# 2024.01.19
#

set -eu

[ `uname` == "Darwin" ] && {
    echo "Don't build on osx.  build on debian linux"
    exit 1
}

export VERSION=$( date +"%y.%m.%d" )
export NAME="cryptor-service"
export DOCKER_REPO=darrylwest
export IMAGE="$DOCKER_REPO/$NAME"

# TODO: copy ../html/index.html to home/cryptor/www/

cp ../.ssh/*.pem home/cryptor/.ssh/

file="install.tgz"
tar czvf $file home/ usr/local/

docker build \
    -t $IMAGE:$VERSION \
    -t $IMAGE:latest . 

echo "docker push $IMAGE:$VERSION"
