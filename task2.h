#pragma once
#include "stdafx.h"
typedef struct {
	int x;	//一个单位长度为两个px
	int y;
}Point2;

void drawLine(Point2 p0, Point2 p1, COLORREF color);
void task2();
