#!/bin/bash
for i in  `ls | grep .h`
do
    cp $i ./qrencodeh/$i
done
