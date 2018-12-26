#!/usr/bin/env bash

# POSIX albo C, obie opcje uzalezniaja nas od stref czasowych
LC_ALL=POSIX

# Reprezentacja dnia tygonia jako 1..7
TODAY=`date +%u`

# Pozostale dni tygodnia do weekendu
REMAINING=`expr 5 - $TODAY`

# Jesli jest SB lub ND
if [ $TODAY -gt 5 ]; then
    echo "Yes! You can chill now."
else
    # Jesli nie, wyswietlamy ile pozostalo dni do weekendu
    echo "Nope. But it will be in ${REMAINING} days!"
fi
