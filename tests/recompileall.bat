@echo off
gcc -o FIFO FIFO.c -Wno-overflow
gcc -o LRU LRU.c -Wno-overflow
gcc -o OPR OPR.c -Wno-overflow
gcc -o "Belady's anomaly" "Belady's anomaly.c" -Wno-overflow
