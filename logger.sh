#!/bin/bash
set -e

if [ ! -d spdlog ]; then
    git clone https://github.com/gabime/spdlog.git
fi

cd spdlog
mkdir -p build
cd build
cmake .. && make -j
