#!/bin/bash
set -e

function echo_title {
    echo -e "\e[36m## $1 ##\e[0m"
}


echo_title "build logger"
./logger.sh

echo_title "build sample"
g++ --std=c++17 -o consume_produce main.cpp -lpthread -I spdlog/include

echo_title "run sample"
./consume_produce