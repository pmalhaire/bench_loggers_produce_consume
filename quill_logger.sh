#!/bin/bash
set -e

if [ ! -d quill ]; then
    git clone https://github.com/odygrd/quill.git
fi

# build optional
cd quill
mkdir -p build
cd build
cmake .. && make -j
