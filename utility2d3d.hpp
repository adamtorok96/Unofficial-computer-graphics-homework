#pragma once

#ifndef UTILITY_2D_3D
#define UTILITY_2D_3D

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <opencv2/opencv.hpp>

#ifndef __linux__
#include "getline.h"
#endif

void drawTextToCenter(cv::Mat &img, const char *text);
GLuint createTextureFromFile(const char *filename);

#endif