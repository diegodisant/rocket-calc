#include <stdio.h>
#include <stdlib.h>

#include "rocket.h"

Rocket* buildRocket(RocketParams params) {
  Rocket *rocket = (Rocket *) malloc(sizeof(Rocket));

  rocket->L = params.L;
  rocket->D = params.D;
  rocket->DInt = params.DInt;
  rocket->mC = params.mC;
  rocket->mP = params.mP;

  printf("L: %f m, Longitud del Cohete\n", rocket->L);
  printf("D: %f m, Diametro del Cohete\n", rocket->D);
  printf("DInt: %f m, Diametro Interno del Cohete\n", rocket->DInt);
  printf("mC: %f kg, Masa del Cohete\n", rocket->mC);
  printf("mP: %f kg, Masa del Propelente\n", rocket->mP);

  return rocket;
}
