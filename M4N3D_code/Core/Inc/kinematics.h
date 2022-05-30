#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "control.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

double deg2rad(double deg);
double rad2deg(double rad);
uint16_t rad2srv(double rad);
uint16_t deg2srv(double deg);
double srv2rad(uint16_t srv);
double srv2deg(uint16_t srv);

bool KS_calc_IK(double x, double y, double z);
void KS_calc_FK();

#endif
