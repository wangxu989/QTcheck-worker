#!/bin/bash
for i in  `ls | grep .c`
do
    cp $i ./qrencodecpp/$i
done
