#!/bin/sh

if [ -f $1.c ] ; then
  echo "Creating $1.h from $1.c"

  cd ../perfect
  make

  if [ ! -f ../src/lookupa.o ] ; then
    cp lookupa.o ../src
  fi
  
  hlist < ../src/$1.c | perfect -mn

  rm -f hhlist*
  make hhlist

  cat phash.c  > ../src/$1.h

  echo "static ub4 codes[]={" >> ../src/$1.h

  hhlist < ../src/$1.c | sort >> ../src/$1.h

  echo "/*      */ 0x00000000 };" >> ../src/$1.h

  echo "#define code(s) codes[phash(s,strlen(s))]" >> ../src/$1.h

  cd ../src
  echo "$1.h created"
  echo
else
  echo "File '$1.c' not found"
fi
