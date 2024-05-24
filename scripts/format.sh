#!/bin/bash

SRC_DIR="src"

find "$SRC_DIR" -path "$SRC_DIR/external" -prune -o \( -name '*.cpp' -o -name '*.h' \) -print0 | xargs -0 clang-format -i
