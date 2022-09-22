#!/usr/bin/env bash

for ((i = 0; i <= 4; ++i))
do
    for ((j = 0; j <= i; ++j))
    do
        echo "$i $j"
        cat `ls path_hgp_hrr_${i}_${j}_*.txt` | ../../build/src/hgphrr/hgphrr_code_gen
    done
done