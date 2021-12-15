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
[2021-12-15 08:31:23.672] [consume] [info] Consume one 999995
[2021-12-15 08:31:23.672] [consume] [info] Consume one 999996
[2021-12-15 08:31:23.672] [consume] [info] Consume one 999997
[2021-12-15 08:31:23.672] [consume] [info] Consume one 999998
[2021-12-15 08:31:23.672] [consume] [info] Consume one 999999
[2021-12-15 08:31:23.673] [main] [info] let the CPU rest a bit
[2021-12-15 08:31:24.673] [main] [info] produce consume log spd only main
[2021-12-15 08:31:25.419] [main] [info] stdio messages consumed:1000000 in 9.53895104s rate:104833.32976620457msg/s
[2021-12-15 08:31:25.419] [main] [info] spd all messages consumed:1000000 in 8.908479259s rate:112252.6046170817msg/s
[2021-12-15 08:31:25.419] [main] [info] spd main only messages consumed:1000000 in 0.746523631s rate:1339542.3245483304msg/s
## run sample fmt ##
08:31:35.828373 main_fmt.cpp:73  INF[consume] Consume one 43684
08:31:35.828374 main_fmt.cpp:73  INF[consume] Consume one 43685
08:31:35.828375 main_fmt.cpp:73  INF[consume] Consume one 43686
08:31:35.828376 main_fmt.cpp:73  INF[consume] Consume one 43687
08:31:35.828376 main_fmt.cpp:73  INF[consume] Consume one 43688
08:31:36.424603 main_fmt.cpp:134 INF[main  ] let the CPU rest a bit
08:31:37.424731 main_fmt.cpp:137 INF[main  ] produce consume log fmt only main
08:31:38.050238 main_fmt.cpp:145 INF[main  ] stdio messages consumed:1000000 in 9.29825253s rate:107547.08981860703msg/s
08:31:38.050240 main_fmt.cpp:148 INF[main  ] fmt all messages consumed:1000000 in 0.693208817s rate:1442566.7641212358msg/s
08:31:38.050241 main_fmt.cpp:151 INF[main  ] fmt main only messages consumed:1000000 in 0.625498893s rate:1598723.8525776258msg/s
## run sample easy ##
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999993
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999994
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999995
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999996
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999997
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999998
2021-12-15 08:33:10,965 INFO [default] consume:Consume one 999999
Main:stdio messages consumed:1000000 in 9.39358s rate:106456msg/s
Main:easy_all messages consumed:1000000 in 41.0912s rate:24336.1msg/s
Main:easy_main_only messages consumed:1000000 in 40.1452s rate:24909.6msg/s
## run sample quill ##
17:54:40.420492937 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999993
17:54:40.420493120 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999994
17:54:40.420493303 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999995
17:54:40.420493490 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999996
17:54:40.420493672 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999997
17:54:40.420493855 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999998
17:54:40.420494123 [483038] main_quill.cpp:73            LOG_INFO      consume      - Consume one 999999
17:54:41.420658188 [482799] main_quill.cpp:161           LOG_INFO      root         - stdio messages consumed:1000000 in 7.89300005s rate:126694.53866277373msg/s
17:54:41.420659240 [482799] main_quill.cpp:164           LOG_INFO      root         - quill messages consumed:1000000 in 0.325476963s rate:3072414.0682116416msg/s
```
