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
[2021-12-12 11:14:23.201] [main] [info] start
[2021-12-12 11:14:23.201] [main] [info] produce consume log all
...
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999990
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999991
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999992
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999993
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999994
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999995
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999996
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999997
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999998
[2021-12-12 11:12:22.259] [consume] [info] Consuming one 999999
[2021-12-12 11:12:22.282] [main] [info] consumed:1000000
[2021-12-12 11:12:22.283] [main] [info] consumed:1000000 in 23.04178842s rate:43399.40901167254msg/s
[2021-12-12 11:12:22.283] [main] [info] produce consume log only main
[2021-12-12 11:12:22.283] [main] [info] wait for end
[2021-12-12 11:12:22.383] [main] [info] consumed:169148
[2021-12-12 11:12:22.383] [main] [info] wait for end
[2021-12-12 11:12:22.483] [main] [info] consumed:336470
[2021-12-12 11:12:22.483] [main] [info] wait for end
[2021-12-12 11:12:22.583] [main] [info] consumed:501987
[2021-12-12 11:12:22.583] [main] [info] wait for end
[2021-12-12 11:12:22.683] [main] [info] consumed:673707
[2021-12-12 11:12:22.683] [main] [info] wait for end
[2021-12-12 11:12:22.783] [main] [info] consumed:844528
[2021-12-12 11:12:22.783] [main] [info] wait for end
[2021-12-12 11:12:22.883] [main] [info] consumed:1000000
[2021-12-12 11:12:22.883] [main] [info] consumed:1000000 in 0.600766358s rate:1664540.6099786966msg/s
```
