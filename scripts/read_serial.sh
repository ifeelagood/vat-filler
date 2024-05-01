#!/bin/bash

BAUD=115200
PORT=/dev/ttyUSB0

# set port baud and shit
stty $BAUD -F $PORT raw -echo

cat $PORT

# one could save to a file by piping read_serial.sh | tee file.csv
