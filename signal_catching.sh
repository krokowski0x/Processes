#!/usr/bin/env bash

trap onSignalCaught 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

onSignalCaught() {
    echo "Signal Caught!"
}

while sleep 1;
do
    echo "Hello! PID: $$"
done
