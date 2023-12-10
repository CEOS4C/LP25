#!/bin/bash

OPTION=""

if [ "$(basename "$0")" == "InvTriUser.sh" ]; then
  OPTION=-r
fi

sort $OPTION /etc/passwd | cut -d ':' -f 1

