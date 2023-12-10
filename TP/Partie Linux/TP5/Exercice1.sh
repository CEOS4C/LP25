#!/bin/bash

current_directory=$(pwd)
echo "Répertoire courant : $current_directory"

if [ -n "$1" ]; then
  directory="$1"
else
  directory="."
fi

if [ -d "$directory" ]; then
  ls "$directory"
else
  echo "Le répertoire spécifié n'existe pas."
fi

