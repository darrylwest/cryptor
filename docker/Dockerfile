#
#
#
FROM debian:bookworm

LABEL maintainer="darryl.west" version="2024.12.14"

RUN apt-get update && apt-get install -y \
    make binutils autoconf automake autotools-dev libtool pkg-config cmake \
    build-essential gcc g++ uuid-dev clang curl wget jq vim neovim git-core procps \
    libcxxopts-dev libssl-dev libspdlog-dev zlib1g-dev libbrotli-dev brotli

RUN useradd --create-home cryptor

ADD install.tgz /

WORKDIR /home/cryptor

CMD [ "/usr/local/bin/cryptor", "--base /home/cryptor/www", "--port 29200" ]
# CMD [ "/usr/bin/sleep", "600d" ]
