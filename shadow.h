#ifndef SHADOW_SHADOW_H_H
#define SHADOW_SHADOW_H_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// MsWindows-on ez is kell
#include <windows.h>
#pragma warning(disable: 4996)
#endif // Win32 platform


#include "GameControl.h"
#include "ImageProcessor.h"
#include "Avatar.h"
#include "CrawlerScroll.h"

using namespace std;

GameControl gameController;
ImageProcessor imageProcessor;
Avatar interceptor(&gameController, &imageProcessor);
CrawlerScroll crawler(&gameController);

void display(void);
void idle();
void reshape(int w, int h);
void init(void);
void keyboard (unsigned char key, int x, int y);

#endif //SHADOW_SHADOW_H_H