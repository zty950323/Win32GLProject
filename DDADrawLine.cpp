#include "stdafx.h"
#include "DDADrawLine.h"
#include "..\packages\nupengl.core.0.1.0.1\build\native\include\GL\glew.h"
#include "..\packages\nupengl.core.0.1.0.1\build\native\include\GL\freeglut.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#define random(a,b) (rand() % (b - a + 1) + a)
float xs = 0.0;
float ys = 0.0;
float xe = 0.0;
float ye = 0.0;
DDADrawLine::DDADrawLine()
{
}


DDADrawLine::~DDADrawLine()
{
}
// 实现DDA画线显示过程
// author: 赵天宇
// date : 2018/03/09
void lineSegement() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
//	DDADrawLine::LineDDA(xs, ys, xe, ye);
	DDADrawLine::MPDrawLine(xs, ys, xe, ye);
	glEnd();
	glFlush();
}
// 实现DDA画线算法测试
// author: 赵天宇
// date : 2018/03/09
void DDADrawLine::DDATest(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	using namespace std;
//	cout << "输入线段起始和终点坐标（范围 0 - 500， 0 - 500）：";
//	cin >> xs >> ys >> xe >> ye;
	srand((unsigned)time(NULL));
	xs = random(0, 500);
	ys = random(0, 500);
	xe = random(0, 500);
	ye = random(0, 500);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Middle Point Draw Line");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500, 0.0, 500.0);
	glutDisplayFunc(DDADrawLine::display);
	DDADrawLine::myInit();
//	DDADrawLine::MPDrawLine(xs, ye, xe, ys);
	glutMainLoop();
}
// 实现DDA算法。存在缺陷的一个算法实现。
// author: 赵天宇
// date : 2018/03/09
void DDADrawLine::LineDDA(int x0, int y0, int x1, int y1)
{
	float x = 0.0;
	float y = 0.0;
	float m = 0.0;
	// 添加增量，实现增量思想
	float dx = x1 - x0;
	float dy = y1 - y0;
	if (dx != 0)
	{
		m = dy / dx;
		if (m <= 1 && m >= -1)
		{
			y = y0;
			for (x = x0; x <= x1; x++)
			{
				glVertex2i(x, int(y + 0.5));
				y += m;
			}
		}
		if (m > 1 || m < -1)
		{
			m = 1 / m;
			x = x0;
			for (y = y0; y <= y1; y++)
			{
				glVertex2i(int(x + 0.5), y);
				x += m;
			}
		}
	}
	else 
	{
		int x = x0;
		int y = 0;
		y = (y0 <= y1) ? y0 : y1;
		int d = fabs((double)(y0 - y1));
		while (d >= 0)
		{
			glVertex2i(x, y);
			y++;
			d--;
		}
	}
}

void DDADrawLine::DDALine(int xa, int ya, int xb, int yb)
{
	GLfloat delta_x, delta_y, x, y;
	int dx, dy, steps;
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx)>abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	delta_x = (GLfloat)dx / (GLfloat)steps;
	delta_y = (GLfloat)dy / (GLfloat)steps;
	x = xa;
	y = ya;
//	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	for (int i = 1; i <= steps; i++)
	{
		x += delta_x;
		y += delta_y;
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
		glEnd();
	}
}

void DDADrawLine::GLTest(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Hello OpenGL");

	glutMainLoop();
}
#pragma  MPDrawLine // 中点画线算法
// 存在缺陷的中点画线算法
void DDADrawLine::MPDrawLine(int x0, int y0, int x1, int y1)
{
	int a, b, dt1, dt2, d, x, y;
	a = y0 - y1;
	b = x1 - x0;
	d = a + a + b; //为了避免小数，这里取2倍 不写成2*a + b的原因是防止乘法
	dt1 = a + b + a + b;
	dt2 = a + a;
	x = x0;
	y = y0;
	// 绘制起点
//	glColor3f(1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	// 绘制整条线
	while (x < x1)
	{
		if (d < 0)
		{
			x++;
			y++;
			d += dt1;
		}
		else
		{
			x++;
			d += dt2;
		}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}
}
// 中点绘制直线的测试方法
void DDADrawLine::MPDrawLineTest(int argc, char **argv)
{

}

void DDADrawLine::MPLineDraw(int x0, int y0, int x1, int y1)
{
	int x = x0, y = y0;
	int a = y0 - y1;
	int b = x1 - x0;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	int d, d1, d2;
	if (-a <= b) // 斜率绝对值 <= 1
	{
		d = a + a + b;
		d1 = a + a;
		d2 = a + a + b + b;
		while (x != x1)
		{
			if (d < 0)
			{
				y += cy;
				d += d2;
			}
			else
			{
				d += d1;
			}
			x += cx;
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
		}
	}
	else // 斜率绝对值 > 1
	{
		d = a + b + b;
		d1 = b + b;
		d2 = a + a + b + b;
		if (d < 0)
		{
			d += d1;
		}
		else
		{
			x += cx;
			d += d2;
		}
		y += cy;
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}
}

void DDADrawLine::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

								   /*----------------------------------------*/
								   /*  viewport stuff                        */
								   /*----------------------------------------*/
								   /* set up a viewport in the screen window */
								   /* args to glViewport are left, bottom, width, height */
	glViewport(0, 0, 500, 500);
	/* NB: default viewport has same coords as in myinit, */
	/* so this could be omitted: */

	
//	DDADrawLine::DDALine(xs, ys, xe, ye);
//	DDADrawLine::DDALine(0, 500, 500, 0);
//	DDADrawLine::MPDrawLine(50, 80, 400, 160);
//	DDADrawLine::MPLineDraw(xs, ys, xe, ye);
//	DDADrawLine::MPLineDraw(0, 500, 500, 0);
	DDADrawLine::BreasehamDrawLine(xs, ys, xe, ye);
	DDADrawLine::BreasehamDrawLine(0, 0, 500, 500);
	DDADrawLine::BreasehamDrawLine(0, 500, 500, 0);
	/* and flush that buffer to the screen */
	glFlush();
}

void DDADrawLine::myInit(void)
{

	/* attributes */

	glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
	glColor3f(1.0, 0.0, 0.0); /* draw in red */

							  /* set up viewing: */
							  /* 500 x 500 window with origin lower left */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void DDADrawLine::Swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void DDADrawLine::BreasehamDrawLine(int x0, int y0, int x1, int y1)
{
	int iTag = 0;
	int dx, dy, tx, ty, inc1, inc2, d, curx, cury;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	glEnd();
	if (x0 == x1 && y0 == y1)
	{
		return;
	}
	dy = abs(y1 - y0);
	dx = abs(x1 - x0);
	if (dx < dy)
	{
		iTag = 1;
		Swap(x0, x1);
		Swap(x1, y1);
		Swap(dx, dy);
	}
	tx = ((x1 - x0) > 0) ? 1 : -1;
	ty = ((y1 - y0) > 0) ? 1 : -1;
	curx = x0; 
	cury = y0;
	inc1 = 2 * dy;
	inc2 = 2 * (dy - dx);
	d = inc1 - dx;
	while (curx != x1)
	{
		curx += tx;
		if (d < 0)
		{
			d += inc1;
		}
		else
		{
			cury += ty;
			d += inc2;
		}
		if (iTag)
		{
			glBegin(GL_POINTS);
			glVertex2i(cury, curx);
			glEnd();
		}
		else
		{
			glBegin(GL_POINTS);
			glVertex2i(curx, cury);
			glEnd();
		}
	}
}

