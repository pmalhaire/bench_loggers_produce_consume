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
...
## run sample spd ##
[2021-12-12 21:52:44.670] [consume] [info] Consume one 999995
[2021-12-12 21:52:44.670] [consume] [info] Consume one 999996
[2021-12-12 21:52:44.670] [consume] [info] Consume one 999997
[2021-12-12 21:52:44.670] [consume] [info] Consume one 999998
[2021-12-12 21:52:44.670] [consume] [info] Consume one 999999
[2021-12-12 21:52:44.670] [main] [info] let the CPU rest a bit
[2021-12-12 21:52:45.670] [main] [info] produce consume log spd only main
[2021-12-12 21:52:46.240] [main] [info] stdio messages consumed:1000000 in 9.237613856s rate:108253.06357122534msg/s
[2021-12-12 21:52:46.240] [main] [info] spd all messages consumed:1000000 in 7.250905824s rate:137913.80336096336msg/s
[2021-12-12 21:52:46.240] [main] [info] spd main only messages consumed:1000000 in 0.569752775s rate:1755147.2215295485msg/s
## run sample fmt ##
21:52:56.629561 main_fmt.cpp:73  INF[consume] Consume one 43684
21:52:56.629565 main_fmt.cpp:73  INF[consume] Consume one 43685
21:52:56.629566 main_fmt.cpp:73  INF[consume] Consume one 43686
21:52:56.629566 main_fmt.cpp:73  INF[consume] Consume one 43687
21:52:56.629567 main_fmt.cpp:73  INF[consume] Consume one 43688
21:52:57.258628 main_fmt.cpp:134 INF[main  ] let the CPU rest a bit
21:52:58.258711 main_fmt.cpp:137 INF[main  ] produce consume log fmt only main
21:52:58.757748 main_fmt.cpp:145 INF[main  ] stdio messages consumed:1000000 in 9.298271486s rate:107546.87056682052msg/s
21:52:58.757750 main_fmt.cpp:148 INF[main  ] fmt all messages consumed:1000000 in 0.706428345s rate:1415571.7378526197msg/s
21:52:58.757750 main_fmt.cpp:151 INF[main  ] fmt main only messages consumed:1000000 in 0.499038544s rate:2003853.233428799msg/s
```
