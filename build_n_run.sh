#!/bin/bash
set -e

function echo_title {
    echo -e "\e[36m## $1 ##\e[0m"
}


echo_title "build loggers"
./spd_logger.sh
./fmt_logger.sh

echo_title "build spd sample"
g++ --std=c++17 -o consume_produce_spd main_spd.cpp -lpthread -I spdlog/include

echo_title "build fmt sample"
g++ --std=c++17 -o consume_produce_fmt main_fmt.cpp -lpthread -I fmtlog

echo_title "run sample spd"
./consume_produce_spd | tail -n 10
echo_title "run sample fmt"
./consume_produce_fmt | tail -n 10
