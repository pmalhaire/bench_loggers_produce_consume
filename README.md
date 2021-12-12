# Sample code for produce consume with spdlog sinks

creates 2 threads and a syncronized queue

references :

https://levelup.gitconnected.com/producer-consumer-problem-using-condition-variable-in-c-6c4d96efcbbc
https://stackoverflow.com/a/9396587/3562282

## run the code

./build_n_run.sh

### expected output

```
## build logger ##
-- Build spdlog: 1.9.2
-- Build type: Release
-- Generating example(s)
-- Generating install
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pierrot/dev/stereolabs/consumer_producer/spdlog/build
Consolidate compiler generated dependencies of target spdlog
[ 80%] Built target spdlog
Consolidate compiler generated dependencies of target example
[100%] Built target example
## build sample ##
## run sample ##
...
2021-12-12 10:45:50.582] [consume] [info] Consuming one 999986
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999987
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999988
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999989
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999990
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999991
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999992
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999993
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999994
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999995
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999996
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999997
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999998
[2021-12-12 10:45:50.582] [consume] [info] Consuming one 999999
[2021-12-12 10:45:50.680] [main] [info] consumed:1000000
[2021-12-12 10:45:50.680] [main] [info] consumed:1000000 in 27.813137931s rate:35954.23150314222msg/s

```