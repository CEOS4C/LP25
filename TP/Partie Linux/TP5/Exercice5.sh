#!/bin/bash

repertoire_racine="/home/ceos4c/Documents/UTBM/TC03/LP25/TP/tp5 scripts/Photos"

declare -a repertoires

trouver_fichiers_multiples() {
  local repertoire="$1"
  local fichiers=()
  local doublons_trouves=0 
  while IFS= read -r -d '' fichier; do
    fichiers+=("$fichier")
  done < <(find "$repertoire" -type f -print0)
  
  local nombre_fichiers="${#fichiers[@]}"
  
  for ((i=0; i<nombre_fichiers-1; i++)); do
    for ((j=i+1; j<nombre_fichiers; j++)); do
      fichier1="${fichiers[i]}"
      fichier2="${fichiers[j]}"
      
      if [ "$(md5sum "$fichier1" | awk '{print $1}')" == "$(md5sum "$fichier2" | awk '{print $1}')" ]; then
        echo "Fichier en double trouvé :"
        echo "1. $fichier1"
        echo "2. $fichier2"
       
        nouveau_fichier2="${fichier2}_duplicate"
        
        ln -s "$fichier1" "$nouveau_fichier2"
        doublons_trouves=1 
      fi
    done
  done

  if [ $doublons_trouves -eq 1 ]; then
    echo "Opération réussie : Des fichiers en double ont été trouvés et des liens symboliques ont été créés."
  else
    echo "Aucun fichier en double trouvé dans le répertoire : $repertoire"
  fi
}

while IFS= read -r -d '' dossier; do
  repertoires+=("$dossier")
done < <(find "$repertoire_racine" -type d -print0)

for dossier in "${repertoires[@]}"; do
  trouver_fichiers_multiples "$dossier"
done

