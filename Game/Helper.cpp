//
// Created by Ahmad Rahimi on 11/21/17.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include "Helper.h"

int Helper::calculateAngle(float x1, float y1, float x2, float y2) {
    float angle = atan2(y1 - y2, x1 - x2);
    return static_cast<int>(angle * 180 / M_PI);
}

float Helper::degreesToRadians(double degrees) {
    return float(degrees / 180*M_PI);
}

int Helper::distance(float x1, float y1, float x2, float y2) {
    return int(abs(hypot(x1 - x2, y1 - y2)));
}

int Helper::correctAngle(int angle) {
    if (angle > 90){
        return (angle - 90);
    }else {
        return (angle + 270);
    }
}

float Helper::radiansToDegrees(double radians) {
    return radians * 180/M_PI;
}