#include "stdafx.h"
#include "task2.h"

//Bresenham画线算法，因为x、y都是2的倍数，故计算过程中都做截半处理
void drawLine(Point2 p0, Point2 p1, COLORREF color) {
	Point2 t;	//用作交换
	if (p1.x < p0.x) { //p1.x一定大于p0.x，即实现了从左往右画
		t = p0;
		p0 = p1;
		p1 = t;
	}
	int deltaX = p1.x - p0.x;
	int deltaY = p1.y - p0.y;
	//当斜率为无穷大时
	if (deltaX == 0) {
		if (p1.y < p0.y) {	//p1.y要比p0.y大
			t = p0;
			p0 = p1;
			p1 = t;
		}
		int loops = (p1.y - p0.y) / 2 - 1;
		int x0 = p0.x;
		int y0 = p0.y;
		putpixel(x0, y0, color);
		for (int i = 0; i < loops; i++) {
			y0 += 2;
			putpixel(x0, y0, color);
		}
	}
	else {
		double k = double(deltaY) / deltaX;
		if (k >= 0 && k <= 1) {	//斜率大于0小于1
			int loops = (p1.x - p0.x) / 2 - 1;
			int e = 0;
			int x0 = p0.x;
			int y0 = p0.y;
			int x1 = p0.x;
			int y1 = p0.y;
			putpixel(x0, y0, color);
			for (int i = 0; i < loops; i++) {
				if (i == 0) {
					e = deltaY - deltaX / 2;
				} else {
					e = e + deltaY - deltaX * (y1 - y0) / 2;
				}
				if (e >= 0) {
					x0 = x1;
					y0 = y1;
					x1 += 2;
					y1 += 2;
				} else {
					x0 = x1;
					y0 = y1;
					x1 += 2;
				}
				putpixel(x1, y1, color);
			}
		}
		else if (k > 1) {	//斜率大于1
			int loops = (p1.y - p0.y) / 2 - 1;
			int e = 0;
			int x0 = p0.x;
			int y0 = p0.y;
			int x1 = p0.x;
			int y1 = p0.y;
			putpixel(x0, y0, color);
			for (int i = 0; i < loops; i++) {
				if (i == 0) {
					e = deltaX - deltaY / 2;
				} else {
					e = e + deltaX - deltaY * (x1 - x0) / 2;
				}
				if (e >= 0) {
					x0 = x1;
					y0 = y1;
					x1 += 2;
					y1 += 2;
				} else {
					x0 = x1;
					y0 = y1;
					y1 += 2;
				}
				putpixel(x1, y1, color);
			}
		} else if (k>-1 && k<0) {	//斜率大于-1小于0
			int loops = (p1.x - p0.x) / 2 - 1;
			int e = 0;
			int x0 = p0.x;
			int y0 = p0.y;
			int x1 = p0.x;
			int y1 = p0.y;
			putpixel(x0, y0, color);
			for (int i = 0; i < loops; i++) {
				if (i == 0) {
					e = -deltaY - deltaX / 2;
				}
				else {
					e = e - deltaY - deltaX * (y0 - y1) / 2;
				}
				if (e >= 0) {
					x0 = x1;
					y0 = y1;
					x1 += 2;
					y1 -= 2;
				}
				else {
					x0 = x1;
					y0 = y1;
					x1 += 2;
				}
				putpixel(x1, y1, color);
			}
		} else if (k <= -1) {	//斜率小于-1
			int loops = (p0.y - p1.y) / 2 - 1;
			int e = 0;
			int x0 = p0.x;
			int y0 = p0.y;
			int x1 = p0.x;
			int y1 = p0.y;
			putpixel(x0, y0, color);
			for (int i = 0; i < loops; i++) {
				if (i == 0) {
					e = deltaX + deltaY / 2;
				}
				else {
					e = e + deltaX + deltaY * (x1 - x0) / 2;
				}
				if (e >= 0) {
					x0 = x1;
					y0 = y1;
					x1 += 2;
					y1 -= 2;
				}
				else {
					x0 = x1;
					y0 = y1;
					y1 -= 2;
				}
				putpixel(x1, y1, color);
			}
		}
	}
}

void task2() {
	initgraph(1200, 800);   // 创建绘图窗口

	//画600*400的网格
	setlinecolor(WHITE);
	for (int i=0; i<1200; i=i+2) {
		line(i, 0, i, 800);
	}
	for (int i=0; i<800; i=i+2) {            
		line(0, i, 1200, i);
	}
	
	MOUSEMSG m;		// 定义鼠标消息

	bool oneClick = false;	//判断鼠标点击次数
	Point2 anchor;	//鼠标第一次点击位置作为锚点
	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			Point2 pos;
			if (m.x%2==0) {
				pos.x = m.x;
			} else {
				pos.x = m.x - 1;
			} if (m.y % 2 == 0) {
				pos.y = m.y;
			} else {
				pos.y = m.y - 1;
			}
			setfillcolor(RED);
			solidcircle(pos.x, pos.y, 4);
			if (oneClick) {
				drawLine(pos,anchor,RED);
				oneClick = false;
			} else {
				anchor = pos;
				oneClick = true;
			}
			break;
		}
	}
}
