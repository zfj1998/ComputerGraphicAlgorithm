#include "stdafx.h"
#include "task1.h"

//四通道扫描线种子填充算法
void fill(Point seed, COLORREF borderColor, COLORREF fillColor, COLORREF background, int screenw, int screenh) {
	int x_min;		//一轮扫描后当前行的左边界
	int x_max;		//一轮扫描后当前行的右边界
	std::vector<Point> stack;	//关键栈
	stack.push_back(seed);	//将种子压栈

	while (!stack.empty()) {	//开始填充

		Sleep(1);

		Point point = stack.back(); //弹出栈顶的点
		stack.pop_back();

		int x = point.pos_x;
		int y = point.pos_y;	//获得该点坐标
		while (getpixel(x, y) != borderColor && x < screenw) { //向右填充
			putpixel(x, y, fillColor);
			x++;
		}
		x_max = x - 1;	//更新扫描线右边界

		x = point.pos_x - 1;
		while (getpixel(x, y) != borderColor && x > 0) {	//向左填充
			putpixel(x, y, fillColor);
			x--;
		}
		x_min = x + 1;	//更新扫描线左边界

		bool fillBlock;	//用于判断下一区间是否需要填充
						//向上扫描
		if (y > 1 && y < screenh) {
			x = x_min;
			y = y - 1;
			while (x < x_max) {
				fillBlock = false;
				//找到需要填充的小区间的右端点
				while (getpixel(x, y) == background && x < x_max) {
					fillBlock = true;
					x++;
				}
				if (fillBlock) {	//小区间右端点入栈
					Point upRight;
					upRight.pos_x = x;
					upRight.pos_y = y;
					stack.push_back(upRight);
				}
				//跳过不用填充的部分
				while (getpixel(x, y) != background && x < x_max) {
					x++;
				}
			}

			//向下扫描
			x = x_min;
			y = y + 2;
			while (x < x_max) {
				fillBlock = false;
				//找到需要填充的小区间的右端点
				while (getpixel(x, y) == background && x < x_max) {
					fillBlock = true;
					x++;
				}
				if (fillBlock) {	//小区间右端点入栈
					Point downRight;
					downRight.pos_x = x;
					downRight.pos_y = y;
					stack.push_back(downRight);
				}
				//跳过不用填充的部分
				while (getpixel(x, y) != background && x < x_max) {
					x++;
				}
			}
		}
	}
}


void task1()
{
	initgraph(400, 300);   // 创建绘图窗口
	POINT pts[5];	// 定义数组，保存五角星的五个顶点坐标

	// 计算五角星的五个顶点坐标
	double a = PI / 2;
	for (int i = 0; i < 5; i++)
	{
		pts[i].x = int(200 + cos(a) * 100);
		pts[i].y = int(150 - sin(a) * 100);
		a += PI * 4 / 5;
	}

	// 设置填充模式为 WINDING (详见 EasyX 帮助手册)
	setpolyfillmode(WINDING);
	// 设置填充颜色为红色
	setfillcolor(RED);
	// 绘制五角星(无边框)
	solidpolygon(pts, 5);


	MOUSEMSG m;		// 定义鼠标消息

	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// 如果点左键的同时按下了 Ctrl 键
			if (m.mkCtrl) {
				COLORREF borderColor = RED;
				COLORREF fillColor = BLACK;
				COLORREF background = WHITE;
				Point seed;
				seed.pos_x = m.x;
				seed.pos_y = m.y;
				fill(seed, borderColor, fillColor, background, 400, 300);
			}
			else {
				COLORREF borderColor = RED;
				COLORREF fillColor = WHITE;
				COLORREF background = BLACK;
				Point seed;
				seed.pos_x = m.x;
				seed.pos_y = m.y;
				fill(seed, borderColor, fillColor, background, 400, 300);
			}
			break;
		}
	}
}