#ifndef CALC_H
#define CALC_H

#include <math.h>

#include "rocket.h"

typedef struct Calc Calc;

struct Calc {
  Rocket* rocket;

  // m: masa seca en kg
  double m;

  // f: fineza del cohete
  double f;

  // SF: factor de forma
  double SF;

  // vH: velocidad de apertura del paracaidas en m/s
  double vH;

  // Cs: velocidad del sonido en m/s
  double Cs;

  // M: numero de mach
  double M;

  // h: altura de lanzamiento en m
  double h;

  // Alt: altitud de lanzamiento en m
  double Alt;

  // H: Apogeo absoluto en m
  double H;

  // pH: densidad del aire en apogeo absoluta en kg/m3
  double pH;

  // u0: velocidad del aire Ns/m2
  double u0;

  // Re: numero de Reynolds
  double Re;

  // Cf: coeficiente de friccion
  double Cf;

  // Dfb: fuerza de arrastre en N
  double Dfb;

  // CdS0: superficie de arrastre efectiva en m2
  double CdS0;

  // v1: velocidad terminal del paracaidas en m/s
  double v1;
};

typedef struct CalcParams CalcParams;

struct CalcParams {
  double vH;
  double Cs;
  double h;
  double Alt;
  double pH;
  double u0;
  double v1;
};

Calc* buildCalc(Rocket *rocket, CalcParams params);

void calcStrategy(Calc *calc);

void calcDryMass(Calc *calc);
void calcFinesse(Calc *calc);
void calcFormFactor(Calc *calc);
void calcMachNumber(Calc *calc);
void calcAbsoluteApogee(Calc *calc);
void calcReynoldsNumber(Calc *calc);
void calcFrictionCoefficient(Calc *calc);
void calcDragForce(Calc *calc);
void calcEffectiveDragSurface(Calc *calc);

#endif
