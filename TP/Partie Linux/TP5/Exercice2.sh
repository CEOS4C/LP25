#!/bin/bash

echo "Nombre d'arguments : $#"

echo "Liste des arguments dans l'ordre :"
for arg in "$@"; do
  echo "$arg"
done

echo "Liste des arguments dans l'ordre inverse :"
args=("$@")
for ((i=${#args[@]}-1; i>=0; i--)); do
  echo "${args[i]}"
done

