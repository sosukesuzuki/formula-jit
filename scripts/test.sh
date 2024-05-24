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
)

echo "Expression       | Expected Result | Actual Result (No JIT) | Pass/Fail (No JIT) | Actual Result (JIT) | Pass/Fail (JIT)"
echo "-----------------|-----------------|------------------------|---------------------|---------------------|---------------"

for test in "${tests[@]}"; do
    IFS='=' read -r expression expected <<< "$test"
    
    actual_no_jit=$(echo "$expression" | $EXECUTABLE)
    
    actual_jit=$(echo "$expression" | $EXECUTABLE --useJIT)
    
    if [ "$actual_no_jit" == "$expected" ]; then
        result_no_jit="Pass"
    else
        result_no_jit="Fail"
    fi
    
    if [ "$actual_jit" == "$expected" ]; then
        result_jit="Pass"
    else
        result_jit="Fail"
    fi
    
    printf "%-16s | %-15s | %-22s | %-19s | %-19s | %s\n" "$expression" "$expected" "$actual_no_jit" "$result_no_jit" "$actual_jit" "$result_jit"
done
