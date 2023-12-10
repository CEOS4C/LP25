#!/bin/bash

afficher_aide() {
  echo "Utilisation : $0 [OPTIONS]"
  echo "Options :"
  echo "  -h, --help                Affiche l'aide et arrête le script."
  echo "  -v                        Affiche les opérations effectuées lors de la sauvegarde."
  echo "  --source <source_dir>     Spécifie le répertoire source (obligatoire)."
  echo "  --destination <dest_dir>  Spécifie le répertoire cible (obligatoire)."
  echo "  --dry-run                 Affiche les opérations sans les effectuer (comme -v)."
  echo "  --log-file [fichier]      Journalise les opérations dans un fichier (par défaut : journal.log)."
}

fichier_journal="journal.log"

simulation=false

options=$(getopt -o hv --long help,source:,destination:,dry-run,log-file:: -n "$0" -- "$@")
if [ $? -ne 0 ]; then
  afficher_aide
  exit 1
fi

eval set -- "$options"

while true; do
  case "$1" in
    -h|--help)
      afficher_aide
      exit 0
      ;;
    -v)
      verbose=true
      shift
      ;;
    --source)
      source_directory="$2"
      shift 2
      ;;
    --destination)
      destination_directory="$2"
      shift 2
      ;;
    --dry-run)
      simulation=true
      shift
      ;;
    --log-file)
      case "$2" in
        "")
          fichier_journal="journal.log"
          shift 2
          ;;
        *)
          fichier_journal="$2"
          shift 2
          ;;
      esac
      ;;
    --)
      shift
      break
      ;;
  esac
done

if [ -z "$source_directory" ] || [ -z "$destination_directory" ]; then
  echo "Les répertoires source et destination sont obligatoires. Utilisez -h pour obtenir de l'aide."
  exit 1
fi

if [ ! -d "$source_directory" ]; then
  echo "Le chemin source n'est pas un répertoire valide."
  exit 1
fi

if [ ! -d "$destination_directory" ]; then
  echo "Le chemin cible n'est pas un répertoire valide."
  exit 1
fi

copier_fichier_si_necessaire() {
  source_file="$1"
  target_file="$2"

  if [ -e "$target_file" ]; then
    if [ "$source_file" -nt "$target_file" ]; then
      md5_source=$(md5sum "$source_file" | awk '{print $1}')
      md5_target=$(md5sum "$target_file" | awk '{print $1}')

      if [ "$md5_source" != "$md5_target" ]; then
        if [ "$simulation" = true ]; then
          echo "Simulation : Copier $source_file vers $target_file"
        else
          cp "$source_file" "$target_file"
          echo "Copié $source_file vers $target_file"
        fi
      fi
    fi
  else
    if [ "$simulation" = true ]; then
      echo "Simulation : Copier $source_file vers $target_file"
    else
      cp "$source_file" "$target_file"
      echo "Copié $source_file vers $target_file"
    fi
  fi
}

find "$source_directory" -type d | while read -r source_dir; do
  dossier_source="$source_dir"
  relatif_dir="${dossier_source#$source_directory/}"
  dossier_cible="$destination_directory/$relatif_dir"

  if [ ! -d "$dossier_cible" ]; then
    if [ "$simulation" = true ]; then
      echo "Simulation : Créer le répertoire $dossier_cible"
    else
      mkdir -p "$dossier_cible"
      echo "Créé le répertoire $dossier_cible"
    fi
  fi
done

find "$source_directory" -type f | while read -r source_file; do
  fichier_source="$source_file"
  fichier_relatif="${fichier_source#$source_directory/}"
  fichier_cible="$destination_directory/$fichier_relatif"
  copier_fichier_si_necessaire "$fichier_source" "$fichier_cible"
done

if [ -n "$fichier_journal" ]; then
  if [ "$simulation" = true ]; then
    echo "Simulation : Journalisation des opérations dans $fichier_journal"
  else
    echo "Journalisation des opérations dans $fichier_journal"
    history | grep -v "$0" >> "$fichier_journal"
  fi
fi

echo "Sauvegarde terminée."

