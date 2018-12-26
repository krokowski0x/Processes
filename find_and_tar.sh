#!/usr/bin/env bash

# Jesli cos pojdzie nie tak, wyswietlamy krotki manual
usage() {
    printf "
    Usage: $0 [-n <Integer>] [-m <String>] [-a <File>]
    E.g:   $0 -n 5 -m '*.pdf' -a out.tar\n\n"
}

# Jesli mamy jakies zmienne srodowiskowe, inicjalizujemy nimi opcje
n=$NUM_DAYS || null
m=$FILE_NAMES || null
a=$TAR_NAME || null

# Przetwarzanie argumentow za pomoca getopta
while getopts "n:m:a:" option; do
    case "${option}" in
        n)
            n=${OPTARG}
            ;;
        m)
            m=${OPTARG}
            ;;
        a)
            a=${OPTARG}
            ;;
        h|*)
            usage
            exit
            ;;
    esac
done
shift $((OPTIND-1))

# Jesli zmienne i argumenty nie zostaly podane, prosimy o nie tutaj
if [ -z "${n}" ]; then
    echo -n "Enter days since modified:"
    read n
elif [ -z "${m}" ]; then
    echo -n "Enter files' wildcard:"
    read m
elif [ -z "${a}" ]; then
    echo "Enter tar filename:"
    read a
fi

# Ostateczne wywolanie komendy wypisujemy na stdout
set -x

# Wywolujemy pipe tar'a i find'a ze zmiennymi
find $HOME -name "$m" -mtime -$n | xargs tar -zcvf $a
