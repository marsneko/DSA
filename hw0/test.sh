#!/bin/zsh

clang main.c
i=0

while [ $i -le 50 ]
  do
    echo 'input : '
    ./a.out `cat gcd/${i}.in`
    echo 'output : '
    cat gcd/${i}.out
    echo ""
    i=`expr $i + 1 `
  done