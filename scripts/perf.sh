#!/bin/bash

output_file="build/performance_results.csv"

echo "repeated,no_JIT,JIT" > $output_file

for ((i=1; i<=10000000; i*=10)); do
    no_jit_time=$(hyperfine --warmup 3 --runs 5 "./build/formula ./build/test-formula --repeated=$i" --export-csv temp_no_jit.csv)
    no_jit_mean=$(awk -F, 'NR==2 {print $2}' temp_no_jit.csv)
    
    jit_time=$(hyperfine --warmup 3 --runs 5 "./build/formula ./build/test-formula --useJIT --repeated=$i" --export-csv temp_jit.csv)
    jit_mean=$(awk -F, 'NR==2 {print $2}' temp_jit.csv)
    
    echo "$i,$no_jit_mean,$jit_mean" >> $output_file
done

rm temp_no_jit.csv temp_jit.csv
