# Sample code for produce consume with spdlog sinks

creates 2 threads and a syncronized queue

references :

https://levelup.gitconnected.com/producer-consumer-problem-using-condition-variable-in-c-6c4d96efcbbc
https://stackoverflow.com/a/9396587/3562282

## run the code

./build_n_run.sh

### expected output

```
## test loggers ##
## build spd sample ##
## run sample spd ##
produce consume log stdio
let the CPU rest a bit
produce consume log all
let the CPU rest a bit
produce consume log none
stdio messages consumed:1000000 in 3.07113s rate:325613msg/s
spd:all messages consumed:1000000 in 2.3247s rate:430163msg/s
spd:none messages consumed:1000000 in 0.457773s rate:2.18449e+06msg/s
## build fmt sample ##
## run sample fmt ##
produce consume log stdio
let the CPU rest a bit
produce consume log all
let the CPU rest a bit
produce consume log none
stdio messages consumed:1000000 in 3.07598s rate:325100msg/s
fmt:all messages consumed:1000000 in 0.38591s rate:2.59128e+06msg/s
fmt:none messages consumed:1000000 in 0.273145s rate:3.66106e+06msg/s
## build easyloggingpp sample ##
## run sample easyloggingpp ##
produce consume log stdio
let the CPU rest a bit
produce consume log all
let the CPU rest a bit
produce consume log none
stdio messages consumed:1000000 in 3.13727s rate:318749msg/s
easyloggercpp:all messages consumed:1000000 in 30.4753s rate:32813.4msg/s
easyloggercpp:none messages consumed:1000000 in 29.7973s rate:33560.1msg/s
## build g3log lib ##
-- Build Type: Release
-- Quill Version: 1.6.3
-- QUILL_NO_EXCEPTIONS: OFF
-- QUILL_USE_BOUNDED_QUEUE: OFF
-- QUILL_FMT_EXTERNAL: OFF
-- QUILL_NO_THREAD_NAME_SUPPORT: OFF
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pierrot/dev/stereolabs/consumer_producer/quill/build
## build quill sample ##
## run sample quill ##
produce consume log stdio
let the CPU rest a bit
produce consume log all
let the CPU rest a bit
produce consume log none
stdio messages consumed:1000000 in 3.37326s rate:296449msg/s
quill:all messages consumed:1000000 in 0.407442s rate:2.45434e+06msg/s
quill:none messages consumed:1000000 in 0.350607s rate:2.8522e+06msg/s
## build g3log lib ##
CMAKE_INSTALL_PREFIX: /home/pierrot/dev/stereolabs/consumer_producer/g3log/install
Install rpath location: /home/pierrot/dev/stereolabs/consumer_producer/g3log/install
## build g3log sample ##
## run sample g3log ##
produce consume log stdio
let the CPU rest a bit
produce consume log all
let the CPU rest a bit
produce consume log none
stdio messages consumed:1000000 in 3.04937s rate:327937msg/s
g3log:all messages consumed:1000000 in 2.19713s rate:455138msg/s
g3log:none messages consumed:1000000 in 2.13178s rate:469092msg/s```
