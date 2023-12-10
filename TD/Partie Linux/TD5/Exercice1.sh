#!/bin/bash

options=$(getopt -o ho::s: --long help,output::,string: -n "$0" -- "$@")

if [ $? -ne 0 ]; then
  echo "Utilisation : $0 [-h] [-o [paramètre]] [-s paramètre] [--] [arguments...]"
  exit 1
fi

eval set -- "$options"

while true; do
  case "$1" in
    -h|--help)
      echo "Option -h activée (sans paramètre)"
      shift
      ;;
    -o|--output)
      case "$2" in
        "")
          echo "Option -o activée (paramètre optionnel non spécifié)"
          shift 2
          ;;
        *)
          echo "Option -o activée avec le paramètre : $2"
          shift 2
          ;;
      esac
      ;;
    -s|--string)
      echo "Option -s activée avec le paramètre : $2"
      shift 2
      ;;
    --)
      shift
      break
      ;;
    *)
      echo "Option inconnue : $1"
      exit 1
      ;;
  esac
done

echo "Arguments restants : $@"
