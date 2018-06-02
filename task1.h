#pragma once
#include "stdafx.h"
#define PI 3.1415926535

typedef struct {
	int pos_x;
	int pos_y;
} Point;

void fill(Point seed, COLORREF borderColor, COLORREF fillColor, COLORREF background, int screenw, int screenh);

void task1();

