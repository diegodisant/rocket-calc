#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "rocket.h"
#include "calc.h"

int main() {
  printBanner();

  RocketParams rocketParams = {
    2.4,  // L
    0.134,   // D
    0.128,  // DInt
    48.2,  // mC
    6.38,  // mP
  };
  Rocket *rocket = buildRocket(rocketParams);

  CalcParams calcParams = {
    20.2,       // vH
    332.529,     // Cs
    2994,        // h
    2000,        // Alt
    1.00649,     // pH
    0.0000174645,// u0
    5.54,           // v1
    0.8,         // Cd
    0.014,       // S
    2.5,         // n
    0.49,        // X1
    1.7,         // Cx
    10,           // Nc
    1000,        // Csc
    222,         // Css
    0.0272,      // mcs
    0.00967,     // mcc
    0.281,       // mco
    3.36,       // mp
    6750,        // Fmax
    90,          // Mr
    0.128,       // Dremp
    4.92,        // mmsp
    0.01,        // Thi
    62.27,      // aparacaidas
    0.33,        // posi
  };
  Calc *calc = buildCalc(rocket, calcParams);

  calcStrategy(calc);

  free(calc);
  free(rocket);

  return 0;
}
