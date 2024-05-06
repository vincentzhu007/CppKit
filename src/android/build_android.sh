#!/bin/bash

readonly BUILD_DIR=build_android

function do_build() {
  local android_ndk=$1
  local android_toolchain="${android_ndk}/build/cmake/android.toolchain.cmake"

  if [ -d ${BUILD_DIR} ]; then
    rm -rf ${BUILD_DIR} # clean build dir
    echo "Cleaned build dir."
  fi

  echo "Start to build..."
  cmake -DCMAKE_BUILD_TYPE:STRING=Release \
        -DCMAKE_TOOLCHAIN_FILE="${android_toolchain}" \
        -DANDROID_NDK="${android_ndk}" \
        -DANDROID_PLATFORM=android-26 \
        -DANDROID_ABI=arm64-v8a \
        -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
        -DCMAKE_SYSTEM_NAME=Android \
        -DCMAKE_SYSTEM_VERSION=26 \
        -G "Unix Makefiles" -S . -B ${BUILD_DIR}

  # Run make.
  cmake --build ${BUILD_DIR} --config Release -j 4
}

function main() {
  if [ x"$ANDROID_NDK" == 'x' ]; then
    echo "Can't build Android, please set env ANDROID_NDK."
    exit 1
  fi

  do_build $ANDROID_NDK
}

main $@
