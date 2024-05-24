#!/bin/bash

BUILD_TYPE="Release"

if [ "$1" == "--debug" ]; then
  BUILD_TYPE="Debug"
fi

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

make
