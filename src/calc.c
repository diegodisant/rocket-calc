#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

#define M_PI 3.14159265358979323846
#define GRAVITY_ACCELERATION 9.806
#define FIXED_PRESSURE 89631.8
#define SCALAR_FACTOR 1000

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
  calc->Cd = params.Cd;
  calc->S = params.S;
  calc->n = params.n;
  calc->X1 = params.X1;
  calc->Cx = params.Cx;
  calc->Nc = params.Nc;
  calc->Csc = params.Csc;
  calc->Css = params.Css;
  calc->mcs = params.mcs;
  calc->mcc = params.mcc;
  calc->mco = params.mco;
  calc->mp = params.mp;
  calc->Fmax = params.Fmax;
  calc->Mr = params.Mr;
  calc->Dremp = params.Dremp;
  calc->mmsp = params.mmsp;
  calc->Thi = params.Thi;
  calc->aparacaidas = params.aparacaidas;
  calc->posi = params.posi;

  printf("vH: %f m/s, Velocidad de Apertura del Paracaidas\n", calc->vH);
  printf("Cs: %f m/s, Velocidad del Sonido\n", calc->Cs);
  printf("h: %f m, Altura de Lanzamiento\n", calc->h);
  printf("Alt: %f m, Altitud de Lanzamiento\n", calc->Alt);
  printf("pH: %f kg/m3, Densidad del Aire en Apogeo Absoluto\n", calc->pH);
  printf("u0: %.15f Ns/m2, Velocidad del Aire\n", calc->u0);
  printf("v1: %f m/s, Velocidad Terminal del Paracaidas\n", calc->v1);
  printf("Cd: %f, Coeficiente de Propiedades del Paracaidas\n", calc->Cd);
  printf("S: %f m2, Superficie del Paracaidas\n", calc->S);
  printf("n: %f, Factor de Paracaidas\n", calc->n);
  printf("X1: %f, Factor de Reduccion de Fuerza de Apertura\n", calc->X1);
  printf("Cx: %f, Coeficiente de Fuerza de Apertura\n", calc->Cx);
  printf("Nc: %f, Numero de Cuerdas de Suspension\n", calc->Nc);
  printf("Csc: %f N, Carga Segura de la Cuerda de Choque\n", calc->Csc);
  printf("Css: %f N, Carga Segura de las Cuerdas de Suspension\n", calc->Css);
  printf("mcs: %f kg, Masa de la Cuerda de Suspension\n", calc->mcs);
  printf("mcc: %f kg, Masa de la Cuerda de Choque\n", calc->mcc);
  printf("mco: %f kg, Masa del Cono\n", calc->mco);
  printf("mp: %f kg, Masa del Paracaidas\n", calc->mp);
  printf("Fmax: %f N, Empuje Maximo del Motor\n", calc->Fmax);
  printf("Mr: %f MPa, Resistencia del Material\n", calc->Mr);
  printf("Dremp: %f mm, Diametro del Retenedor de Empuje\n", calc->Dremp);
  printf("mmsp: %f kg, Masa del Motor sin Propelente\n", calc->mmsp);
  printf("Thi: %f mm, Espesor del Retenedor Inferior\n", calc->Thi);
  printf("aparacaidas: %f m/s2, Aceleracion de Apertura de Paracaidas\n", calc->aparacaidas);
  printf("posi: %f, Relacion de Poasson para el Retenedor\n", calc->posi);

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
  calcParachuteNominalSurface(calc);
  calcParachuteNominalDiameter(calc);
  calcSuspesionRopeLength(calc);
  calcShockRopeLength(calc);
  calcParachuteInflateTime(calc);
  calcBalisticParameter(calc);
  calcApertureForce(calc);
  calcSuspensionRopesApertureForce(calc);
  calcShockRopeSecurityFactor(calc);
  calcSuspensionRopeSecurityFactor(calc);
  calcDeploymentForce(calc);
  calcDeploymentMass(calc);
  calcDeploymentForceMassRatio(calc);
  calcPushRetainerEffort(calc);
  calcPushRetainerThickness(calc);
  calcInferiorRetainerEffort(calc);
  calcInferiorRetainerSecurityFactor(calc);

  return;
}

void calcDryMass(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->m = r->mC - r->mP;

  printf("(c) m: %f kg, Masa Seca\n", calc->m);

  return;
}

void calcFinesse(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->f = r->L / r->D;

  printf("(c) f: %f, Fineza del Cohete\n", calc->f);

  return;
}

void calcFormFactor(Calc *calc) {
  calc->SF = 1 + (60 / pow(calc->f, 3)) + (0.0025 * calc->f);

  printf("(c) SF: %f, Factor de Forma\n", calc->SF);

  return;
}

void calcMachNumber(Calc *calc) {
  calc->M = calc->vH / calc->Cs;

  printf("(c) M: %f, Numero de Mach\n", calc->M);

  return;
}

void calcAbsoluteApogee(Calc *calc) {
  calc->H = calc->h + calc->Alt;

  printf("(c) H: %f m, Apogeo Absoluto\n", calc->H);

  return;
}

void calcReynoldsNumber(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Re = (calc->pH * calc->vH * r->D) / calc->u0;

  printf("(c) Re: %f, Numero de Reynolds\n", calc->Re);

  return;
}

void calcFrictionCoefficient(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Cf = 0.45 * pow(log10(calc->Re * r->D), -2.58) * pow(1 + (0.144 * pow(calc->M, 2)), -0.65);

  printf("(c) Cf: %f, Coeficiente de Friccion\n", calc->Cf);

  return;
}

void calcDragForce(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Dfb = (0.5 * calc->pH) * M_PI * r->L * r->D * pow(calc->vH, 2) * calc->Cf * calc->SF;

  printf("(c) Dfb: %f N, Fuerza de Arrastre\n", calc->Dfb);

  return;
}

void calcEffectiveDragSurface(Calc *calc) {
  calc->CdS0 = ((2 * calc->m * GRAVITY_ACCELERATION) + calc->Dfb) / (calc->pH * pow(calc->v1, 2));

  printf("(c) CdS0: %f m2, Superficie de Arrastre Efectiva\n", calc->CdS0);

  return;
}

void calcParachuteNominalSurface(Calc *calc) {
  calc->S0 = calc->CdS0 / calc->Cd;

  printf("(c) S0: %f m2, Superficie Nominal del Paracaidas\n", calc->S0);

  return;
}

void calcParachuteNominalDiameter(Calc *calc) {
  calc->D0 = sqrt((4 * calc->S0) / M_PI);

  printf("(c) D0: %f m, Diametro Nominal del Paracaidas\n", calc->D0);

  return;
}

void calcSuspesionRopeLength(Calc *calc) {
  calc->Ls = 2.25 * (calc->D0 + (calc->S * calc->D0));

  printf("(c) Ls: %f m, Longitud de las Cuerdas de Suspension\n", calc->Ls);

  return;
}

void calcShockRopeLength(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->Lcc = 2.5 * r->L;

  printf("(c) Lcc: %f m, Longitud de la Cuerda de Choque\n", calc->Lcc);

  return;
}

void calcParachuteInflateTime(Calc *calc) {
  calc->tf = (calc->n * calc->D0) / (0.85 * calc->vH);

  printf("(c) tf: %f s, Tiempo de Inflado del Paracaidas\n", calc->tf);

  return;
}

void calcBalisticParameter(Calc *calc) {
  calc->A = (2 * calc->m * GRAVITY_ACCELERATION) / (calc->CdS0 * calc->pH * GRAVITY_ACCELERATION * calc->vH * calc->tf);

  printf("(c) A: %f, Parametro Balistico\n", calc->A);

  return;
}

void calcApertureForce(Calc *calc) {
  calc->Fx = calc->CdS0 * (0.5 * calc->pH * pow(calc->vH, 2)) * calc->Cx * calc->X1;

  printf("(c) Fx: %f N, Fuerza de Apertura\n", calc->Fx);

  return;
}

void calcSuspensionRopesApertureForce(Calc *calc) {
  calc->Fxc = calc->Fx / calc->Nc;

  printf("(c) Fxc: %f N, Fuerza de Apertura de las Cuerdas de Suspension\n", calc->Fxc);

  return;
}

void calcShockRopeSecurityFactor(Calc *calc) {
  calc->FS = calc->Csc / calc->Fx;

  printf("(c) FS: %f, Factor de Seguridad de la Cuerda de Choque\n", calc->FS);

  return;
}

void calcSuspensionRopeSecurityFactor(Calc *calc) {
  calc->FSS = calc->Css / calc->Fxc;

  printf("(c) FSS: %fs, Factor de Seguridad de las Cuerdas de Suspension\n", calc->FSS);

  return;
}

void calcDeploymentForce(Calc *calc) {
  Rocket *r = calc->rocket;

  calc->F = FIXED_PRESSURE * (0.25 * M_PI * pow(r->DInt, 2));

  printf("(c) F: %f N, Fuerza de Despliegue\n", calc->F);

  return;
}

void calcDeploymentMass(Calc *calc) {
  calc->md = (calc->mcs + calc->mcc + calc->mco + calc->mp);

  printf("(c) md: %f kg, Masa de Despliegue\n", calc->md);

  return;
}

void calcDeploymentForceMassRatio(Calc *calc) {
  calc->Fratio = calc->F / (calc->md * GRAVITY_ACCELERATION);

  printf("(c) Fratio: %f, Relacion de Fuerza de Despliegue/Masa a Desplegar\n", calc->Fratio);

  return;
}

void calcPushRetainerEffort(Calc *calc) {
  Rocket *r = calc->rocket;\

  calc->Wemp = calc->Fmax / (0.25 * M_PI * pow(r->DInt * SCALAR_FACTOR, 2));

  printf("(c) Wemp: %f Mpa, Esfuerzo Maximo del Retenedor de Empuje\n", calc->Wemp);

  return;
}

void calcPushRetainerThickness(Calc *calc) {
  calc->Thp = sqrt((3 * calc->Wemp) * (pow(calc->Dremp * SCALAR_FACTOR, 2)) / (4 * calc->Mr)) * 2;

  printf("(c) Thp: %f mm, Espesor del Retenedor de Empuje\n", calc->Thp);

  return;
}

void calcInferiorRetainerEffort(Calc *calc) {
  calc->Winf = ((calc->mmsp * calc->aparacaidas) / pow(calc->Thi * SCALAR_FACTOR, 2))*(1 + calc->posi)*(0.485 * (log((calc->Dremp * SCALAR_FACTOR) / (calc->Thi * SCALAR_FACTOR))) + 0.52);

  printf("(c) Winf: %f Mpa, Esfuerzo Maximo del Retenedor Inferior\n", calc->Winf);

  return;
}

void calcInferiorRetainerSecurityFactor(Calc *calc) {
  calc->RIFS = calc->Mr / calc->Winf;

  printf("(c) RIFS: %f, Factor de Seguridad para el Retenedor Inferior\n", calc->RIFS);

  return;
}
