#!/usr/bin/env bash

# Tresc plikow jako zmienne
BODY="tresc.txt"
SUBJECT="Swietna oferta, polecam"
ADDRESSES="adresy.txt"

# Tworzymy tablice z otrzymanych wynikow
ATTACHMENTS=(spec*.pdf)

# Kazdy plik z tablicy zamieniamy na flage -a + string z nazwa pliku
declare -a ATTS
for ATT in "${ATTACHMENTS[@]}"; do
    ATTS+=("-A" "$ATT")
done

# Dla kazej linijki z pliku z adresami wysylamy maila
# i wypisujemy komende na stdout
while read ADDRESS; do
    COMMAND="mail -s \"$SUBJECT\" ${ATTS[@]} $ADDRESS < $BODY"
    echo $COMMAND
    eval $COMMAND
done <$ADDRESSES
