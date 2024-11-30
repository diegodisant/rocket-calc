#include <stdio.h>
#include "utils.h"
#include "rocket.h"
#include "calc.h"

int main() {
  //printBanner();

  RocketParams rocketParams = {
    0.924,  // L
    0.05,   // D
    1.555,  // mC
    0.183   // mP
  };
  Rocket *rocket = buildRocket(rocketParams);

  CalcParams calcParams = {
    18,          // vH
    327.794,     // Cs
    1333,        // h
    1864,        // Alt
    0.9308,      // pH
    0.000017065, // u0
    5,           // v1
    0.8,         // Cd
    0.07,        // S
    2.5,         // n
    0.49,        // X1
    1.7,         // Cx
    8,           // Nc
    1000,        // Csc
    222          // Css
  };
  Calc *calc = buildCalc(rocket, calcParams);

  calcStrategy(calc);

  return 0;
}
