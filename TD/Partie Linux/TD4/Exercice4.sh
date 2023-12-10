#!/bin/bash

function usage() {
  echo "Usage: $1 SOURCE DESTINATION"
}

if (( $# != 2 )); then
  usage $0
  exit 1
fi

if ! [ -d $1 ]; then
  usage $0
  echo "SOURCE must be a directory"
  exit 1
fi

if ! [ -d $2 ]; then
  usage $0
  echo "DESTINATION must be a directory"
  exit 1
fi

if [ "${2:${#2}-1}" == "/" ]; then
  DST_DIR="${2:0:${#2}-1}"
else
  DST_DIR="$2"
fi

if [ "${2:0:1}" != "/" ]; then
  DST_DIR=$PWD/$DST_DIR
fi

echo "Backup to $DST_DIR"

function create_if_not_exists() {
  if ! [ -d $2/$1 ]; then
    if [ "$1" != "." ]; then
      echo "Create $2/$1"
      mkdir -p $2/$1
    fi
  fi
}

IFS=$'\n'
cd $1

# Go through directories
for f in `find . -type d -print`; do
  create_if_not_exists $f $DST_DIR
done

# Go through files
for f in `find . -type f -print`; do
  if ! [ -f $DST_DIR/$f ]; then
    echo "copy $f to $DST_DIR/$f"
    cp $f $DST_DIR/$f
  else
    SAVE_DATE=`stat -c %Y $DST_DIR/$f`
    SRC_DATE=`stat -c %Y $f`
    if (( $SAVE_DATE != $SRC_DATE )); then
      SRC_MD5=`md5sum $f`
      DST_MD5=`md5sum $DST_DIR/$f`
      if [ "${SRC_MD5:0:32}" != "${DST_MD5:0:32}" ]; then
        echo "copy $f to $DST_DIR/$f"
        cp $f $DST_DIR/$f
      fi
    fi
  fi
done

cd -
unset IFS
