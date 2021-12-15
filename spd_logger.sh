#!/bin/bash
set -e

if [ ! -d spdlog ]; then
    git clone https://github.com/gabime/spdlog.git
fi

# build optional
# cd spdlog
# mkdir -p build
# cd build
# cmake .. && make -j
