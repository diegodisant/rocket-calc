#!/bin/sh

gcc \
  ./src/utils.c \
  ./src/rocket.c \
  ./src/calc.c \
  ./src/main.c \
  -o rocketcalc \
  -lm \
  -O3

./rocketcalc
