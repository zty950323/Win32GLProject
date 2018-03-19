#pragma once
class DDADrawLine
{
public:
	DDADrawLine();
	~DDADrawLine();
	static void DDATest(int argc, char **argv);
	static void LineDDA(int x0, int y0, int x1, int y1);
	//************************************
	// Method:    DDALine
	// FullName:  DDADrawLine::DDALine
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: int xa
	// Parameter: int ya
	// Parameter: int xb
	// Parameter: int yb
	//************************************
	static void DDALine(int xa, int ya, int xb, int yb);
	static void GLTest(int argc, char **argv);
	// �е㻭���㷨��ģ��/���Ƚϣ�
	//************************************
	// Method:    MPDrawLine - ����ȱ�� �� ֻ�ܻ����ϵ���
	// FullName:  DDADrawLine::MPDrawLine
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: int x0
	// Parameter: int y0
	// Parameter: int x1
	// Parameter: int y1
	//************************************
	static void MPDrawLine(int x0, int y0, int x1, int y1);
	// �е����ֱ�ߵĲ��Է���
	//************************************
	// Method:    MPDrawLineTest
	// FullName:  DDADrawLine::MPDrawLineTest
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: int argc
	// Parameter: char * * argv
	//************************************
	static void MPDrawLineTest(int argc, char **argv);
	//************************************
	// Method:    MPLineDraw
	// FullName:  DDADrawLine::MPLineDraw
	// Access:    public static 
	// Returns:   void
	// Qualifier:
	// Parameter: int x0
	// Parameter: int y0
	// Parameter: int x1
	// Parameter: int y1
	//************************************
	static void MPLineDraw(int x0, int y0, int x1, int y1);
	static void display(void);
	static void myInit(void);
	static void Swap(int &a, int &b);
	static void BreasehamDrawLine(int x0, int y0, int x1, int y1);
#if 0
	// �����ݽṹ
	struct Point
	{
		GLfloat x;
		GLfloat y;
	};
#endif
};

