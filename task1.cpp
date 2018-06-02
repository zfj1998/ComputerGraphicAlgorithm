#include "stdafx.h"
#include "task1.h"

//��ͨ��ɨ������������㷨
void fill(Point seed, COLORREF borderColor, COLORREF fillColor, COLORREF background, int screenw, int screenh) {
	int x_min;		//һ��ɨ���ǰ�е���߽�
	int x_max;		//һ��ɨ���ǰ�е��ұ߽�
	std::vector<Point> stack;	//�ؼ�ջ
	stack.push_back(seed);	//������ѹջ

	while (!stack.empty()) {	//��ʼ���

		Sleep(1);

		Point point = stack.back(); //����ջ���ĵ�
		stack.pop_back();

		int x = point.pos_x;
		int y = point.pos_y;	//��øõ�����
		while (getpixel(x, y) != borderColor && x < screenw) { //�������
			putpixel(x, y, fillColor);
			x++;
		}
		x_max = x - 1;	//����ɨ�����ұ߽�

		x = point.pos_x - 1;
		while (getpixel(x, y) != borderColor && x > 0) {	//�������
			putpixel(x, y, fillColor);
			x--;
		}
		x_min = x + 1;	//����ɨ������߽�

		bool fillBlock;	//�����ж���һ�����Ƿ���Ҫ���
						//����ɨ��
		if (y > 1 && y < screenh) {
			x = x_min;
			y = y - 1;
			while (x < x_max) {
				fillBlock = false;
				//�ҵ���Ҫ����С������Ҷ˵�
				while (getpixel(x, y) == background && x < x_max) {
					fillBlock = true;
					x++;
				}
				if (fillBlock) {	//С�����Ҷ˵���ջ
					Point upRight;
					upRight.pos_x = x;
					upRight.pos_y = y;
					stack.push_back(upRight);
				}
				//�����������Ĳ���
				while (getpixel(x, y) != background && x < x_max) {
					x++;
				}
			}

			//����ɨ��
			x = x_min;
			y = y + 2;
			while (x < x_max) {
				fillBlock = false;
				//�ҵ���Ҫ����С������Ҷ˵�
				while (getpixel(x, y) == background && x < x_max) {
					fillBlock = true;
					x++;
				}
				if (fillBlock) {	//С�����Ҷ˵���ջ
					Point downRight;
					downRight.pos_x = x;
					downRight.pos_y = y;
					stack.push_back(downRight);
				}
				//�����������Ĳ���
				while (getpixel(x, y) != background && x < x_max) {
					x++;
				}
			}
		}
	}
}


void task1()
{
	initgraph(400, 300);   // ������ͼ����
	POINT pts[5];	// �������飬��������ǵ������������

	// ��������ǵ������������
	double a = PI / 2;
	for (int i = 0; i < 5; i++)
	{
		pts[i].x = int(200 + cos(a) * 100);
		pts[i].y = int(150 - sin(a) * 100);
		a += PI * 4 / 5;
	}

	// �������ģʽΪ WINDING (��� EasyX �����ֲ�)
	setpolyfillmode(WINDING);
	// ���������ɫΪ��ɫ
	setfillcolor(RED);
	// ���������(�ޱ߿�)
	solidpolygon(pts, 5);


	MOUSEMSG m;		// ���������Ϣ

	while (true)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();

		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			// ����������ͬʱ������ Ctrl ��
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