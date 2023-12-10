#!/bin/bash

read -p "Entrez le nom du fichier :" file_name

if [ ! -e "$file_name" ]; then
    echo "Le fichier 'file_name' n'existe pas."
       exit 1
fi

file_type=$(file -b "$file_name")

if [ -f "$file_name" ]; then
    file_permissions=$(stat -c "%A" "$file_name")
    echo "Type de fichier : $file_type"
    echo "Droits sur le fichier : $file_permissions"
else
    echo "Type de fichier : $file_type"
fi

