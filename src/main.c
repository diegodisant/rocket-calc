#include <stdio.h>
#include "utils.h"
#include "rocket.h"
#include "calc.h"

int main() {
  printBanner();

  // L, D, mC, mP
  RocketParams rocketParams = {0.924, 0.05, 1.555, 0.183};
  Rocket *rocket = buildRocket(rocketParams);

  // vH, Cs, h, Alt, pH, u0, v1
  CalcParams CalcParams = {18, 327.794, 1333, 1864, 0.890823, 0.000017065, 5};
  Calc *calc = buildCalc(rocket, CalcParams);

  calcStrategy(calc);

  return 0;
}
