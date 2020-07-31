#perf tips

```bash
#perf record -F 99 -a -g -- sleep 60

perf record -F 99 -p 3140 -g -m 2 -- sleep 60
perf script > perf.out
 
./stackcollapse-perf.pl perf.out > out.folded

./flamegraph.pl out.folded > mysql.svg
```


#2.errors

```cpp
sudo  perf record -F 99 -a  -g  -p 118521 -- sleep 30
Warning:
PID/TID switch overriding SYSTEMPermission error mapping pages.
Consider increasing /proc/sys/kernel/perf_event_mlock_kb,
or try again with a smaller value of -m/--mmap_pages.
(current value: -1)
sleep: Terminated
增加参数： -m 2后解决

sudo  perf record -F 99 -a  -g  -m 2 -p 118521 -- sleep 30
```