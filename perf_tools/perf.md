#perf tips

```bash
#perf record -F 99 -a -g -- sleep 60

perf record -F 99 -p 3140 -g -- sleep 60
perf script > out.perf
 
./stackcollapse-perf.pl perf.out > out.folded

./flamegraph.pl out.folded > mysql.svg
```