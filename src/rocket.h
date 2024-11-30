#ifndef ROCKET_H
#define ROCKET_H

typedef struct Rocket Rocket;

struct Rocket {
  // L: longitud del cohete en m
  double L;

  // D: diametro del cohete en m
  double D;

  // mC: masa del cohete en kg (openrocket)
  double mC;

  // mP: masa del propelente en kg (openrocket)
  double mP;
};

typedef struct RocketParams RocketParams;

struct RocketParams {
  double L;
  double D;
  double mC;
  double mP;
};

Rocket* buildRocket(RocketParams params);
#endif
