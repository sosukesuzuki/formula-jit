#!/bin/bash

SRC_DIR="src"

find "$SRC_DIR" \( -name '*.cpp' -o -name '*.h' \) -print0 | xargs -0 clang-format -i
