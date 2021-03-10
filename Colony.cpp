#include <iostream>
#include <cmath>
#include <random>

#include "Colony.h"

double dist(point first, point second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

