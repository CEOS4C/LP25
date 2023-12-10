#!/bin/bash

exists() {
  if [ -e "$1" ]; then
    echo "Le chemin $1 existe."
  else
    echo "Le chemin $1 n'existe pas."
  fi
}

usage() {
  echo "Usage: $0 <chemin>"
  echo "Exemple: $0 /home/ceos4c/Documents/UTBM/TC03/LP25/TP"
}

if [ $# -lt 1 ]; then
  echo "Erreur : Aucun argument passé au script."
  usage
  exit 1
fi

exists "$1"


