#include "stdafx.h"
#include "task2.h"

//Bresenham�����㷨����Ϊx��y����2�ı������ʼ�������ж����ذ봦��
void drawLine(Point2 p0, Point2 p1, COLORREF color) {
	Point2 t;	//��������
	if (p1.x < p0.x) { //p1.xһ������p0.x����ʵ���˴������һ�
		t = p0;
		p0 = p1;
		p1 = t;
	}
	int deltaX = p1.x - p0.x;
	int deltaY = p1.y - p0.y;
	//��б��Ϊ�����ʱ
	if (deltaX == 0) {
		if (p1.y < p0.y) {	//p1.yҪ��p0.y��
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
		if (k >= 0 && k <= 1) {	//б�ʴ���0С��1
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
		else if (k > 1) {	//б�ʴ���1
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
		} else if (k>-1 && k<0) {	//б�ʴ���-1С��0
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
		} else if (k <= -1) {	//б��С��-1
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
	initgraph(1200, 800);   // ������ͼ����

	//��600*400������
	setlinecolor(WHITE);
	for (int i=0; i<1200; i=i+2) {
		line(i, 0, i, 800);
	}
	for (int i=0; i<800; i=i+2) {            
		line(0, i, 1200, i);
	}
	
	MOUSEMSG m;		// ���������Ϣ

	bool oneClick = false;	//�ж����������
	Point2 anchor;	//����һ�ε��λ����Ϊê��
	while (true)
	{
		// ��ȡһ�������Ϣ
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
