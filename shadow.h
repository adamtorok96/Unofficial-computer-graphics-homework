#ifndef SHADOW_SHADOW_H_H
#define SHADOW_SHADOW_H_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// MsWindows-on ez is kell
#include <windows.h>
#pragma warning(disable: 4996)
#endif // Win32 platform

#include "utility2d3d.hpp"

#include "GameControl.h"

static GameControl gameController;

#include "ImageProcessor.h"

static ImageProcessor imageProcessor;

#include "CrawlerScroll.h"
#include "Avatar.h"

using namespace std;


static Avatar interceptor;
static CrawlerScroll crawler;


void display(void);
void idle();
void reshape(int w, int h);
void init(void);
void keyboard (unsigned char key, int x, int y);

#endif //SHADOW_SHADOW_H_H
