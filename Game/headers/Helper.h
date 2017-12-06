//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_HELPER_H
#define SHOOTER_HELPER_H

class Helper{
public:
    static int calculateAngle(float x1, float y1, float x2, float y2);
    static float degreesToRadians(double degrees);
    static int distance(float x1, float y1, float x2, float y2);
    static int correctAngle(int angle);
    static float radiansToDegrees(double radians);
};



#endif //SHOOTER_HELPER_H
