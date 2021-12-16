#!/bin/bash
set -e

. title.sh

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

echo_title "build fmt sample"
g++ --std=c++17 -o consume_produce_fmt -I fmtlog bench_fmt.cpp -lpthread

echo_title "run sample fmt"
./consume_produce_fmt 1>/dev/null
