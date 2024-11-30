#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

#define M_PI 3.14159265358979323846
#define GRAVITY_ACCELERATION 9.81

Calc* buildCalc(Rocket *rocket, CalcParams params) {
  Calc *calc = (Calc *) malloc(sizeof(Calc));

  calc->rocket = rocket;
  calc->vH = params.vH;
  calc->Cs = params.Cs;
  calc->h = params.h;
  calc->Alt = params.Alt;
  calc->pH = params.pH;
  calc->u0 = params.u0;
  calc->v1 = params.v1;

  printf("vH: %f m/s, Velocidad de Apertura del Paracaidas\n", calc->vH);
  printf("Cs: %f m/s, Velocidad del Sonido\n", calc->Cs);
  printf("h: %f m, Altura de Lanzamiento\n", calc->h);
  printf("Alt: %f m, Altitud de Lanzamiento\n", calc->Alt);
  printf("pH: %f kg/m3, Densidad del Aire en Apogeo Absoluto\n", calc->pH);
  printf("u0: %.15f Ns/m2, Velocidad del Aire\n", calc->u0);
  printf("v1: %f m/s, Velocidad Terminal del Paracaidas\n", calc->v1);

  return calc;
}

void calcStrategy(Calc *calc) {
  calcDryMass(calc);
  calcFinesse(calc);
  calcFormFactor(calc);
  calcMachNumber(calc);
  calcAbsoluteApogee(calc);
  calcReynoldsNumber(calc);
  calcFrictionCoefficient(calc);
  calcDragForce(calc);
  calcEffectiveDragSurface(calc);

  return;
}

void calcDryMass(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->m = r->mC - r->mP;

  printf("m: %f kg, Masa Seca\n", calc->m);

  return;
}

void calcFinesse(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->f = r->L / r->D;

  printf("f: %f, Fineza del Cohete\n", calc->f);

  return;
}

void calcFormFactor(Calc *calc) {
  calc->SF = 1 + (60 / pow(calc->f, 3)) + (0.0025 * calc->f);

  printf("SF: %f, Factor de Forma\n", calc->SF);

  return;
}

void calcMachNumber(Calc *calc) {
  calc->M = calc->vH / calc->Cs;

  printf("M: %f, Numero de Mach\n", calc->M);

  return;
}

void calcAbsoluteApogee(Calc *calc) {
  calc->H = calc->h + calc->Alt;

  printf("H: %f m, Apogeo Absoluto\n", calc->H);

  return;
}

void calcReynoldsNumber(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Re = (calc->pH * calc->vH * r->D) / calc->u0;

  printf("Re: %f, Numero de Reynolds\n", calc->Re);

  return;
}

void calcFrictionCoefficient(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Cf = 0.45 * pow(log10(calc->Re * r->D), -2.58) * pow(1 + (0.144 * pow(calc->M, 2)), -0.65);

  printf("Cf: %f, Coeficiente de Friccion\n", calc->Cf);

  return;
}

void calcDragForce(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Dfb = (0.5 * calc->pH) * M_PI * r->L * r->D * pow(calc->vH, 2) * calc->Cf * calc->SF;

  printf("Dfb: %f N, Fuerza de Arrastre\n", calc->Dfb);

  return;
}

void calcEffectiveDragSurface(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->CdS0 = ((2 * calc->m * GRAVITY_ACCELERATION) + calc->Dfb) / (calc->pH * pow(calc->v1, 2));

  printf("CdS0: %f m2, Superficie de Arrastre Efectiva\n", calc->CdS0);

  return;
}
