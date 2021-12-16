#!/bin/bash
set -e

. title.sh

if [ ! -d spdlog ]; then
    git clone https://github.com/gabime/spdlog.git
fi

. title.sh

# build optional
# cd spdlog
# mkdir -p build
# cd build
# cmake .. && make -j

echo_title "build spd sample"
g++ --std=c++17 -o consume_produce_spd bench_spd.cpp -lpthread -I spdlog/include

echo_title "run sample spd"
./consume_produce_spd 1>/dev/null
