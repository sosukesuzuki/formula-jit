#!/bin/bash

EXECUTABLE="./build/formula"

tests=(
    "1 + 1=2"
    "2 * 3=6"
    "4 / 2=2"
    "5 - 3=2"
    "10 + 20 * 3=70"
    "(1 + 2) * 3=9"
    "6 / 3 + 2=4"
    "7 * (3 + 2)=35"
    "1 + 1 - 1=1"
    "100 / 10 * 2=20"
    "((1 + 2) * (3 + 4)) - (5 / (6 - 7))=26"
    "3 * (4 + 5) - 6 / (7 - 8)=33"
    "10 - (2 + 3) * (4 - 5)=15"
    "6 / (1 + 2) * (3 + 4) - 8=6"
    "(7 - 3) * (2 + 2) / (4 - 2)=8"
    "12 / (3 * (2 + 1)) + 4=5.33333"
    "(3 + 2) * (4 - 1) / (5 - 3)=7.5"
    "18 / (2 + 1) - (6 - 3) * 2=0"
    "(9 - 4) * (3 + 2) / (7 - 5)=12.5"
    "20 - (5 * (2 + 1)) + 3=8"
    "(15 / 3) + (2 * 5) - 4=11"
    "25 / (5 - 2) * (3 + 1)=33.3333"
    "(8 + 2) / (5 - 3) * 4=20"
    "30 - (10 / (5 - 2)) * 2=23.333"
    "(2 * 3) + (4 / (1 + 1)) - 5=3"
    "12 / (3 - 1) * (6 - 4)=12"
    "(7 + 5) / (3 - 1) - 4=2"
    "28 / (7 - 3) * (5 + 1)=42"
    "(16 / 4) + (9 - 3) * 2=16"
    "32 / (4 * (2 - 1)) + 6=14"
)

echo "Expression                          | Expected | Actual (No JIT) | P/F (No JIT) | Actual (JIT) | P/F (JIT)"
echo "------------------------------------|----------|-----------------|--------------|--------------|-----------"

for test in "${tests[@]}"; do
    IFS='=' read -r expression expected <<< "$test"
    
    actual_no_jit=$(echo "$expression" | $EXECUTABLE)
    
    actual_jit=$(echo "$expression" | $EXECUTABLE --useJIT)
    
    if [ "$actual_no_jit" == "$expected" ]; then
        result_no_jit="P"
    else
        result_no_jit="F"
    fi
    
    if [ "$actual_jit" == "$expected" ]; then
        result_jit="P"
    else
        result_jit="F"
    fi
    
    printf "%-35s | %-8s | %-15s | %-12s | %-13s | %s\n" "$expression" "$expected" "$actual_no_jit" "$result_no_jit" "$actual_jit" "$result_jit"

    if [ "$result_no_jit" == "F" ] || [ "$result_jit" == "F" ]; then
        exit 1
    fi
done