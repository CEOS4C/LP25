#!/bin/bash

generate_password() {
  local length="$1"
  local password=""
  local characters="$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $length | head -n 1)"

  echo "$characters"
}

if [ -n "$1" ]; then
  length="$1"
else
  length=16
fi

password=$(generate_password "$length")

echo "Mot de passe aléatoire de $length caractères : $password"

