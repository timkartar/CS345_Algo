#!/bin/bash
rm hist
for i in $(seq 1000)
do
#./input.sh 1000 > input
./incr_loop < input >> hist
done
#seq 10 10 3000 > tmp1
#paste tmp1 tmp > loop_data
