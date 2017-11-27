#!/bin/bash
rm tmp00
for i in $(seq 100 100 3000)
do
./input.sh $i > input1
./incr < input1 >> tmp00
done
seq 100 100 3000 > tmp10
paste tmp10 tmp00 > incr_data
