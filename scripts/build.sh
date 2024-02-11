#!/bin/bash

ARDUINO_BOARD=avr.nano
ARDUINO_PROGRAMMER=avr.arduinoasisp
SERIAL_PORT=/dev/ttyACM0

cmake -S . -B build/release -DCMAKE_TOOLCHAIN_FILE=/usr/share/arduino-cmake-toolchain-git/Arduino-toolchain.cmake -DARDUINO_BOARD=$ARDUINO_BOARD -DARDUINO_PROGRAMMER=$ARDUINO_PROGRAMMER

cd build/release

make -j12 SERIAL_PORT=$SERIAL_PORT CONFIRM=1 program-vat_filler
