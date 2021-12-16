#!/bin/bash
set -e

. title.sh

if [ ! -d quill ]; then
    git clone https://github.com/odygrd/quill.git
fi

echo_title "build g3log lib"
cd quill
mkdir -p build
cd build
cmake .. && make -j > /dev/null
cd ../..

echo_title "build quill sample"
g++ --std=c++14 -o consume_produce_quill bench_quill.cpp -lpthread -I quill/quill/include -Lquill/build/quill -lquill

echo_title "run sample quill"
./consume_produce_quill 1>/dev/null