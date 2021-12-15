#!/bin/bash
set -e

if [ ! -d fmtlog ]; then
    git clone https://github.com/MengRao/fmtlog.git
    cd fmtlog
    git submodule init
    git submodule update
    cd -
fi

# build logger optional
# cd fmtlog
# ./build.sh