#!/bin/bash
set -e

. title.sh

if [ ! -d g3log ]; then
    git clone https://github.com/KjellKod/g3log.git
fi

echo_title "build g3log lib"
cd g3log
mkdir -p build
cd build
cmake -DG3_SHARED_LIB=OFF -DCMAKE_INSTALL_PREFIX=$PWD/../install .. > /dev/null
cmake --build . --target install > /dev/null
cd ../..

echo_title "build g3log sample"
g++ --std=c++17 -o consume_produce_g3log bench_g3log.cpp -lpthread -I g3log/install/include -Lg3log/install/lib -lg3log

echo_title "run sample g3log"
./consume_produce_g3log 1>/dev/null