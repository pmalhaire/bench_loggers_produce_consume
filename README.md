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
[2021-12-12 11:14:23.201] [main] [info] produce consume log stdio
...
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999982
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999983
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999984
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999985
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999986
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999987
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999988
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999989
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999990
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999991
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999992
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999993
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999994
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999995
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999996
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999997
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999998
[2021-12-12 11:53:38.420] [consume] [info] Consume one 999999
[2021-12-12 11:53:38.420] [main] [info] let the CPU rest a bit
[2021-12-12 11:53:39.420] [main] [info] produce consume log spd only main
[2021-12-12 11:53:40.155] [main] [info] stdio messages consumed:1000000 in 12.298761884s rate:81308.99755860335msg/s
[2021-12-12 11:53:40.155] [main] [info] spd all messages consumed:1000000 in 23.336102621s rate:42852.05701401514msg/s
[2021-12-12 11:53:40.155] [main] [info] spd main only messages consumed:1000000 in 0.734630114s rate:1361229.251214714msg/s
```
