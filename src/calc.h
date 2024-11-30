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

  // Cd: coeficiente de propiedades del paracaidas
  double Cd;

  // S0: superficie nominal del paracaidas en m2
  double S0;

  // D0: diametro nominal del paracaidas en m
  double D0;

  // Ls: longitud de las cuerdas de supension suspencion en m
  double Ls;

  // S: superficie del paracaidas en m2
  double S;

  // Lcc: longitud de la cuerda de choque en m
  double Lcc;

  // n: factor de paracaidas (tabla de parametro balistico)
  double n;

  // tg: tiempo de inflado del paracaidas en ss
  double tf;

  // A: parametro balisitico
  double A;

  // X1: factor de reduccion de fuerza de apertura (tabla de parametro balistico)
  double X1;

  // C1: coeficiente de fuerza de apertura (tabla de propiedades de paracaidas)
  double Cx;

  // Fx: fuerza de apertura en N
  double Fx;

  // Nc: numero de cuerdas de suspension
  double Nc;

  // Fxc: fuerza de apertura de las cuerdas de suspension en N
  double Fxc;

  // Csc: carga segura de la cuerda de choque en N
  double Csc;

  // FS: factor de seguridad de la cuerda de choque
  double FS;

  // Css; carga segura de las cuerdas de suspension en N
  double Css;

  // FSS: factor de seguridad de las cuerdas de suspension
  double FSS;
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
  double Cd;
  double S;
  double n;
  double X1;
  double Cx;
  double Nc;
  double Csc;
  double Css;
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
void calcParachuteNominalSurface(Calc *calc);
void calcParachuteNominalDiameter(Calc *calc);
void calcSuspesionRopeLength(Calc *calc);
void calcShockRopeLength(Calc *calc);
void calcParachuteInflateTime(Calc *calc);
void calcBalisticParameter(Calc *calc);
void calcApertureForce(Calc *calc);
void calcSuspensionRopesApertureForce(Calc *calc);
void calcShockRopeSecurityFactor(Calc *calc);
void calcSuspensionRopeSecurityFactor(Calc *calc);

#endif
