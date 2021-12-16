#!/bin/bash
set -e

. title.sh

if [ ! -d easyloggingpp ]; then
    git clone https://github.com/amrayn/easyloggingpp.git
fi

echo_title "build easyloggingpp sample"
g++ --std=c++17 -o consume_produce_easy -D ELPP_THREAD_SAFE easyloggingpp/src/easylogging++.cc bench_easy.cpp -lpthread -I easyloggingpp/src

echo_title "run sample easyloggingpp"
./consume_produce_easy 1>/dev/null
