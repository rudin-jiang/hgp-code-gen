#!/usr/bin/env bash

for ((i = 0; i <= 4; ++i))
do
    for ((j = 0; j <= i; ++j))
    do
        echo "$i $j"
        echo "$i $j" | ../../build/src/hgpvrr/hgpvrr_path_gen_random
    done
done