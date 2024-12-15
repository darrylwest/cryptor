#!/usr/bin/env bash
# dpw@piedmont
# 2023-09-21 21:21:52
#

set -eu

# make sure the id_rsa keys are copied first... 
git clone git@github.com:darrylwest/cryptor.git

[ -x .cargo/bin/cargo ] || {
    curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh -s -- -y
    cargo install lsd

    # don't these for c++ development...
    # cargo install just
    # cargo install ripgrep
}

exit $?

