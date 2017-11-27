#!/bin/bash
entries=($(shuf -i 0-100000 -n $1))
echo "${entries[@]}" > temp
sed 's/ /\n/g' temp > temp11

entries=($(shuf -i 0-9999 -n $1))
echo "${entries[@]}" > temp
sed 's/ /\n/g' temp > temp12

paste -d '.' temp11 temp12 > temp1


entries=($(shuf -i 0-100000 -n $1))
echo "${entries[@]}" > temp
sed 's/ /\n/g' temp > temp11

entries=($(shuf -i 0-9999 -n $1))
echo "${entries[@]}" > temp
sed 's/ /\n/g' temp > temp12

paste -d '.' temp11 temp12 > temp2

echo $1 #> input
paste temp1 temp2 #>> input

rm temp
rm temp11
rm temp12
rm temp1
rm temp2
#entries=($(shuf -i 0-149 -n 15))
#echo "${entries[@]}"
