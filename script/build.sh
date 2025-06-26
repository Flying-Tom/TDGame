#!/bin/bash

# clean previous build
rm -rf build && mkdir -p build

# prepare lib
ln -s "${QT_ROOT_DIR}"/lib build/

# build
cmake -B build . -D CMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# if macos, deploy and codesign
if [[ "$OSTYPE" == "darwin"* ]]; then
  macdeployqt build/TDGame.app
  codesign --force --deep --sign - build/TDGame.app
fi
