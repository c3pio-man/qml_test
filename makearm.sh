#!/bin/bash
. ../../env_set.sh >/dev/null
export FRSCSDK_DIR=$TOOLCHAIN_PATH
export PB_SYSROOT=$TOOLCHAIN_PATH/$TOOLCHAIN_PREFIX/sysroot/

mkdir -p output-arm
cd output-arm

$TOOLCHAIN_PATH/$TOOLCHAIN_PREFIX/sysroot/usr/qt5/bin/qmake PLATFORM=arm CONFIG+=debug ../qml_test.pro || exit 1
make -j ${PB_CPU_COUNT:-1} || exit 1

cd ..
