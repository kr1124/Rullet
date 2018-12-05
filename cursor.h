#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
enum color_info
{
	BLACK,			// ������
	BLUE,			// �Ķ���
	GREEN,			// ���
	CYAN,			// �ϴû�
	RED,			// ������
	MAGENTA,		// ��ȫ��
	BROWN,			// ����
	LIGHTGRAY,		// ��ȸ��
	DARKGRAY,		// ��ȸ��
	LIGHTBLUE,		// ���Ķ�
	LIGHTGREEN,		// ���λ�
	LIGHTCYAN,		// ���ϴû�
	LIGHTRED,		// ������
	LIGHTMAGENTA,	// ����ȫ
	YELLOW,			// ���
	WHITE,			// ���
};

enum cursor_info
{
	NOCURSOR,       // Ŀ�� �������
	SOLIDCURSOR,    // ū Ŀ��
	NORMALCURSOR,   // �Ϲ� Ŀ��
};
//------------------------------------------//

//------------------------------------------
// key

#define ESC			27
#define BS			0xe
#define TAB			0xf
#define ENTER		13
#define SPACE		0x20
#define HOME		0x47
#define END			0x4f
#define PGUP		0x49
#define PGDN		0x51
#define INS			0x52
#define DEL			0x53

#define UP		0x48
#define DOWN		0x50
#define LEFT		0x4b
#define RIGHT		0x4d
#define LSHIFT		0x2a
#define RSHIFT		0x36
#define CTRL		0x1d
#define ALT			0x38

#define F1			0x3b
#define F2			0x3c
#define F3			0x3d
#define F4			0x3e
#define F5			0x3f
#define F6			0x40
#define F7			0x41
#define F8			0x42
#define F9			0x43
#define F10			0x44
#define F11			0x57
#define F12			0x58
//-----------------------------------------------//

#define delay(n)        Sleep(n)                    // n/1000�� �ð��� ����
#define randomize()     srand((unsigned)time(NULL)) // ���� �߻��� �ʱ�ȭ
#define random(n)       (rand() % (n))              // 0~n������ ���� �߻�
#define clrscr()        system("cls")               // ȭ���� ��� �����.

extern void gotoxy(int, int);                       // Ŀ���� x,y��ǥ�� �̵�
extern int wherex();                                // Ŀ���� x ��ǥ�� ����
extern int wherey();                                // Ŀ���� y��ǥ�� ����

extern void setcursortype(int);	                    // Ŀ�� �����

extern BOOL gettext(int, int, int, int, void *);    // ���� �����ϱ�
extern BOOL puttext(int, int, int, int, void *);    // ������ ���� �ǵ�����

extern int getscr(int, int);                        // x, y ��ǥ ������ �ƽ�Ű�ڵ带 ����
extern int getattr(int, int);                       // x, y ��ǥ ������ �Ӽ�(����)�� ����

extern int getcolor(int, int);	                    // ���� ���� ���� getcolor(���ڻ�);
extern int getbkcolor(int, int);                    // ��� ���� ���� getcolor(����);

extern void setcolor(int);                          // ���� ���� ���� setcolor(���ڻ�);
extern void setbkcolor(int);                        // ��� ���� ���� setbkcolor(����);

extern void textattr(int);	                        // ���� ���� : textattr(���ڻ�|����<<4)


// �Լ� �� ��ȣ��� ���Ǳ��� �� : ����ο� ���� �����δ� �ٸ� ȭ�Ϸ� �����մϴ�.