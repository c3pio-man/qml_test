#!/bin/sh

mkdir output-linux
cd output-linux

$FRSCSDK_DIR/../local/qt5/bin/qmake PLATFORM=linux ../qml_test.pro
make -j 8
make install

cd ..


