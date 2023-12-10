#!/bin/bash

options=$(getopt -o h --long help,source:,destination:,dry-run,log-file:: -n "$0" -- "$@")

if [ $? -ne 0 ]; then
  echo "Utilisation : $0 [-h] [--source source] [--destination destination] [--dry-run] [--log-file [fichier]] [--] [arguments...]"
  exit 1
fi

eval set -- "$options"

source_dir=""
destination_dir=""
log_file=""
dry_run=false

while true; do
  case "$1" in
    -h|--help)
      echo "Option -h activée (sans paramètre)"
      shift
      ;;
    --source)
      source_dir="$2"
      echo "Option --source activée avec le paramètre : $source_dir"
      shift 2
      ;;
    --destination)
      destination_dir="$2"
      echo "Option --destination activée avec le paramètre : $destination_dir"
      shift 2
      ;;
    --dry-run)
      dry_run=true
      echo "Option --dry-run activée (sans paramètre)"
      shift
      ;;
    --log-file)
      case "$2" in
        "")
          log_file=""
          echo "Option --log-file activée (paramètre optionnel non spécifié)"
          shift 2
          ;;
        *)
          log_file="$2"
          echo "Option --log-file activée avec le paramètre : $log_file"
          shift 2
          ;;
      esac
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

echo "Source : $source_dir"
echo "Destination : $destination_dir"
echo "Dry Run : $dry_run"
echo "Log File : $log_file"

echo "Arguments restants : $@"
