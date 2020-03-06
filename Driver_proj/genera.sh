#! /bin/sh -e
cmake -G Xcode \
  -D CMAKE_CXX_COMPILER=../build/llvm-install/bin/clang++  \
  -D CMAKE_C_COMPILER=../build/llvm-install/bin/clang \
  -D OCLINT_BUILD_DIR=../build/oclint-core \
  -D OCLINT_SOURCE_DIR=../oclint-core \
  -D OCLINT_METRICS_SOURCE_DIR=../oclint-metrics \
  -D OCLINT_METRICS_BUILD_DIR=../build/oclint-metrics \
  -D LLVM_ROOT=../build/llvm-install/ ../oclint-driver