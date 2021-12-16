#!/bin/bash
set -e

. title.sh


echo_title "test loggers"
./bench_spd.sh
./bench_fmt.sh
./bench_easy.sh
./bench_quill.sh
./bench_g3log.sh