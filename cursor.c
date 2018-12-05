
#include "cursor.h"

// 
// ----------------------------------------------------------------------------------------------------
// �Լ� ���� ����  : ���� ȭ���� �����Ͽ� ����ϵ��� �ϼ��� 


void gotoxy(int x, int y)		// Ŀ���� x,y��ǥ�� �̵�
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int wherex()					// Ŀ���� x ��ǥ�� ����
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.X;
}

int wherey()					// Ŀ���� y��ǥ�� ����
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.Y;
}

void setcursortype(int cur_t)	// Ŀ�� �����
{
	CONSOLE_CURSOR_INFO ccInfo;

	if (cur_t == 0)		// NOCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = FALSE;
	}
	else if (cur_t == 1)	// SOLIDCURSOR
	{
		ccInfo.dwSize = 100;
		ccInfo.bVisible = TRUE;
	}
	else				// NORMALCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = TRUE;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ccInfo);
}

BOOL gettext(int left, int top, int right, int bottom, void *destin)    // ���� �����ϱ�
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return ReadConsoleOutput(hConsole, destin, coordBufSize, coordBufCoord, &region);
}

BOOL puttext(int left, int top, int right, int bottom, void *source)    // ������ ���� �ǵ�����
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return WriteConsoleOutput(hConsole, source, coordBufSize, coordBufCoord, &region);
}

int getscr(int x, int y)    // x, y ��ǥ ������ �ƽ�Ű�ڵ带 ����
{
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Char.AsciiChar;
}

int getattr(int x, int y)   // x, y ��ǥ ������ �Ӽ�(����)�� ����
{
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Attributes;
}

int getcolor(int x, int y)	// ���� ���� ���� getcolor(���ڻ�);
{
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf);
}

int getbkcolor(int x, int y)	// ��� ���� ���� getcolor(����);
{
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf0) >> 4;
}

void textattr(int color)		// ���� ���� : textattr(���ڻ�|����<<4)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(color));
}

void setcolor(int textcolor)    // ���� ���� ���� setcolor(���ڻ�);
{
	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = textcolor | (attr & 0xf0);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));

}

void setbkcolor(int color)        // ��� ���� ���� setbkcolor(����);
{
	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = (attr & 0xf) | (color << 4);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));

}




void getcolorname(int color, char *buf)
{
	//  assert(color>=0&&color<=15);
	switch (color)
	{
	case 0:     strcpy(buf, "BLACK");           break;
	case 1:     strcpy(buf, "BLUE");            break;
	case 2:     strcpy(buf, "GREEN");           break;
	case 3:     strcpy(buf, "CYAN");            break;
	case 4:     strcpy(buf, "RED");             break;
	case 5:     strcpy(buf, "MAGENTA");         break;
	case 6:     strcpy(buf, "BROWN");           break;
	case 7:     strcpy(buf, "LIGHTGRAY");       break;
	case 8:     strcpy(buf, "DARKGRAY");        break;
	case 9:     strcpy(buf, "LIGHTBLUE");       break;
	case 10:    strcpy(buf, "LIGHTGREEN");      break;
	case 11:    strcpy(buf, "LIGHTCYAN");       break;
	case 12:    strcpy(buf, "LIGHTRED");        break;
	case 13:    strcpy(buf, "LIGHTMAGENTA");    break;
	case 14:    strcpy(buf, "YELLOW");          break;
	default:    strcpy(buf, "WHITE");           break;
	}
}

void checkIt(int x, int y)
{
	int ch, f, b;
	char name_f[20];
	char name_b[20];

	ch = getscr(x, y);
	gotoxy(0, 14);
	f = getcolor(x, y);
	b = getbkcolor(x, y);

	getcolorname(f, name_f);
	getcolorname(b, name_b);
	setcolor(LIGHTGRAY | BLACK << 4);

	printf("position : %3d, %3d\n", x, y);
	printf("char : %c,  ascii : %3d\n", ch, ch);
	printf("text color is ");

	setcolor(WHITE);        setbkcolor(f);      printf("%s", name_f);

	setcolor(LIGHTGRAY);    setbkcolor(BLACK);  printf("and background color is ");

	setcolor(WHITE);        setbkcolor(b);      printf("%s", name_b);

	setcolor(LIGHTGRAY);    setbkcolor(BLACK);  printf("               ");
	gotoxy(x, y);
}



int getkey()
{
	int ch;
	if ((ch = getch()) == 0xE0)
		ch = getch();
	return ch;
}