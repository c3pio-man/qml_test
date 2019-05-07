#!/bin/bash
. ../../env_set.sh >/dev/null
export FRSCSDK_DIR=$TOOLCHAIN_PATH
#export PB_SYSROOT=$TOOLCHAIN_PATH/$TOOLCHAIN_PREFIX/sysroot/
export PB_SDK_DIR=$PB_TOOLCHAIN_PATH
mkdir -p output-linux
cd output-linux

$TOOLCHAIN_PATH/local/qt5/bin/qmake PLATFORM=linux CONFIG+=debug ../qml_test.pro || exit 1
make -j ${PB_CPU_COUNT:-1} || exit 1

cd ..
