#pragma once
#ifndef MYHEADER_H
#define MYHEADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <sstream>
#include <../irrKlang/irrKlang.h>
using namespace irrklang;

using namespace std;

const float arrowMoveStep = 3.0f;
const float powerMultiplier = 5.0f;
const float fps = 30.0f; 


#define M_PI ((float)3.141592654f)
#define PI2	((float)6.283185308f)
#define EPSILON2 (float)(1E-2)
#define EPSILON3 (float)(1E-3)
#define EPSILON4 (float)(1E-4)
#define EPSILON5 (float)(1E-5)
#define EPSILON6 (float)(1E-6)
#define DEGREES_TO_RADIANS(ang) ((ang)*M_PI / 180.0)
#define RADIANS_TO_DEGREES(rads) ((rads)*180.0 / M_PI)
#define YROTATE_CEIL ((float)40.0f)
#define BALL_RADIUS ((float)0.02f)
#define CUP_RADIUS ((float)0.05f)
#define GRAVITY ((float)-5.0f)
#define FRICTION ((float)1.1f)
#define CAMERA_DISTANCE ((float)0.70f)
#define BUTTON_OFFSET_HEIGHT ((float)50.0f)
#define BUTTON_OFFSET_WIDTH ((float)400.0f)





static bool caseInsensitiveCompare(std::string a, std::string b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }

    return true;
}
#endif