#include "cursor.h"

#define P 5 //한 게임에서 가능한 동시 배팅 수 설정

#define SPACE 32
#define ENTER  13
#define ESC   27
#define UP   0x48
#define DOWN  0x50
#define LEFT  0x4b
#define RIGHT  0x4d

//─│┌┐┘└├┬┤┴┼０１２３４５６７８９


//베팅
int insert(int m) {

	int coin = 0;

	printf("베팅할 금액을 설정해 주십시오. : ");
	scanf("%d", &coin);

	if (coin > m) {
		while (1) {
			gotoxy(0, 23);
			printf("금액을 초과했습니다. 다시 설정해 주십시오. : ");
			scanf("%d", &coin);
			if (coin <= m) break;
		}
	}

	return coin;
}

//배당 계산
int dot(int x, int y) {

	int a;

	if (x % 4 == 1 && y % 2 == 0) {
		a = 1;
	}
	else if (x % 4 == 1) {
		a = 2;
	}
	else if (y % 2 == 0) {
		a = 3;
	}
	else {
		a = 4;
	}

	return a;
}

//배당 계산
int cal(int a[4], int x, int y) {

	int s, d;

	d = dot(x, y);

	switch (d) {
	case 1: a[0] = ((x - 2) / 4 * 3 + (y - 1) / 2 + 1); a[1] = ((x - 2) / 4 * 3 + (y + 1) / 2 + 1); a[2] = ((x + 2) / 4 * 3 + (y - 1) / 2 + 1); a[3] = ((x + 2) / 4 * 3 + (y + 1) / 2 + 1); s = 9; break;
	case 2: a[0] = ((x - 2) / 4 * 3 + y / 2 + 1); a[1] = ((x + 2) / 4 * 3 + y / 2 + 1); a[2] = a[3] = 0; s = 18; break;
	case 3: a[0] = (x / 4 * 3 + (y - 1) / 2 + 1); a[1] = (x / 4 * 3 + (y + 1) / 2 + 1); a[2] = a[3] = 0; s = 18; break;
	case 4: a[0] = (x / 4 * 3 + y / 2 + 1); a[1] = a[2] = a[3] = 0; s = 36; break;
	default: break;
	}

	return s;
}

//선택한 수 표시
int dis(int a[4], int x, int y) {

	int i;
	int scale = 0;

	scale = cal(a, x, y);

	gotoxy(15, 12);
	for (i = 0; i < 4; i++) {
		printf("%2d   ", a[i]);
	}
	printf("\n");

	return scale;
}

//선택한 수 저장
void save(int a[4], int b[][7], int s, int db) {

	int i;

	for (i = 0; i < 4; i++) {
		b[db][i] = a[i];
	}
	b[db][4] = s;
}

//UI표시
void ui(int x, int y, int scale, int a[4], int b[][7], int db, int m) {

	int i, j;

	gotoxy(0, 10);
	printf("방향키로 이동, SPACE BAR로 베팅, ENTER로 롤, ESC로 종료\n");
	printf("현재 위치      x: %d  y: %d \n", x, y);
	printf("선택한 수 : \n");
	printf("배당 : X %2d  \n", scale);
	printf("현재 보유 금액 : %d", m);

	gotoxy(0, 0);
	printf("┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");
	printf("│ 01│ 04│ 07│ 10│ 13│ 16│ 19│ 22│ 25│ 28│ 31│ 34│\n");
	printf("├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
	printf("│ 02│ 05│ 08│ 11│ 14│ 17│ 20│ 23│ 26│ 29│ 32│ 35│\n");
	printf("├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n");
	printf("│ 03│ 06│ 09│ 12│ 15│ 18│ 21│ 24│ 27│ 30│ 33│ 36│\n");
	printf("└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");

	gotoxy(60, 0);
	printf("현재 베팅 정보\n");
	gotoxy(60, 1);
	printf("┌───────────────┬──────┬─────┬────────┐\n");
	gotoxy(60, 2);
	printf("│   베팅한 숫자 │ 액수 │ 배당│   상금 │\n");
	gotoxy(60, 3);
	printf("├───┬───┬───┬───┼──────┼─────┼────────┤\n");

	//─│┌┐┘└├┬┤┴┼０１２３４５６７８９

	for (i = 0; i < db; i++) {
		gotoxy(60, i + 4);
		for (j = 0; j < 4; j++) {
			if (b[i][j] == 0) {
				printf("│   ");
			}
			else {
				printf("│ %2d", b[i][j]);
			}
		}
		printf("│ %5d│  %2d │ %7d│", b[i][4], b[i][5], b[i][6]);
		//gotoxy(60, i + 5);
		//printf("├───┼───┼───┼───┼──────┼─────┤"); 
	}
	gotoxy(60, i + 4);
	printf("└───┴───┴───┴───┴──────┴─────┴────────┘\n");
}


/*int roll(int r[38]) {

	int i, j, k, n;

	srand((unsigned)time(NULL));

	k = rand() % 38; //룰렛 시작 수
	n = rand() % 38; //나온 수

	for (i = 0; i < 10; i++) {
		gotoxy(0, 20);
		for (j = 0; j < 10; j++) {
			printf("%2d   ", r[(k + i + j)%38]);
		}
		Sleep(2 * i * i* i);
		//system("cls");
	}

	return n;
}*/


//ENTER 입력 시, 룰렛을 돌리는 함수
int roll() {

	int r[38] = { 0, 2, 14, 35, 23, 4, 16, 33, 21, 6, 18, 31, 19, 8, 12, 20, 25, 10, 27, 50, 1, 13, 36, 24, 3, 15, 34, 22, 5, 17, 32, 29, 7, 11, 30, 26, 9, 28 }; //룰렛 순서
	int x[38] = {
	   90,90,88,86,84,80,76,72,67,62,57,52,48,43,39,36,33,32,30,30,30,32,34,37,40,44,48,53,58,63,68,73,77,81,84,87,89,90
	};
	int y[38] = {
	   14,12,10,8,7,6,4,3,2,1,1,2,3,4,6,7,8,10,12,14,16,18,20,22,23,24,25,26,27,27,26,25,24,23,21,19,18,16
	};
	int random = 0;
	int i, j;
	int speed = 40;
	int flag = 0;
	int count = 0;

	srand((unsigned)time(NULL));

	for (i = 0; i < 38; i++) {
		gotoxy(x[i], y[i]);
		printf("%2d", r[i]);
	}
	random = rand() % 38;

	while (1) {

		for (j = 1; j < 39; j++) {
			if (j != 0) {
				gotoxy(x[j - 1], y[j - 1]);
				setbkcolor(BLACK);
				printf("%2d", r[j - 1]);
			}
			if (j != 38) {
				gotoxy(x[j], y[j]);
				setbkcolor(LIGHTMAGENTA);
				printf("%2d", r[j]);

			}
			else if (j == 38) {
				gotoxy(x[0], y[0]);
				setbkcolor(LIGHTMAGENTA);
				printf("%2d", r[0]);
			}

			if (flag) {
				if (count == 1 && random == r[j % 38]) break;
				if (count < 1) {
					speed += 10;
					if (random == r[j % 38]) count++;
				}
			}


			_sleep(speed);
		}

		if (GetAsyncKeyState(VK_SPACE)) {
			flag = 1;
		}
		if (count == 1 && random == r[j % 38]) break;
	}
	setbkcolor(BLACK);

	return random;
}

//roll에서 나온 수를 비교하는 함수
int result(int d, int b[][7], int db) {

	int i, j, k, m, n, o;
	k = m = n = o = 0;

	for (i = 0; i < db; i++) {
		for (j = 0; j < 4; j++) {
			if (d == b[i][j]) {
				k = 1;
				m = i;
				n = j;
			}
		}
	}

	gotoxy(0, 23);
	if (k == 1) {
		printf("당첨되었습니다! 상금은 %d입니다!", b[m][6]);
		o = b[m][n];
	}
	else {
		printf("아쉽게도 당첨되지 못했습니다.");
	}

	return o;
}

//초기 금액 설정
int m_input() {

	int i;

	printf("금액을 설정해 주십시오. : ");
	scanf("%d", &i);

	return i;
}

int reset(int b[][7], int db) {

	int i, j;

	for (i = 0; i < db; i++) {
		for (j = 0; j < 7; j++) {
			b[i][j] = 0;
		}
	}

	return 0;
}

void main() {

	//int r[38] = { 0, 2, 14, 35, 23, 4, 16, 33, 21, 6, 18, 31, 19, 8, 12, 20, 25, 10, 27, 50, 1, 13, 36, 24, 3, 15, 34, 22, 5, 17, 32, 29, 7, 11, 30, 26, 9, 28 }; //룰렛 순서
	int a[4] = { 0 }; //선택한 수
	int b[P][7] = { 0 }; //베팅한 수 및 베팅(b[][4]), 배당(b[][5]), 상금(b[][6])
	char c;
	int x, y, i;
	int bet = 0;
	int scale = 0; //배당
	int money = 10000; //자금
	int d = 0; // 걸린 수
	int db = 0; //베팅 표시 카운터
	x = 3;
	y = 1;
	i = 0;

	money = m_input();

	system("cls");

	while (1) {

		ui(x, y, scale, a, b, db, money);

		gotoxy(x, y);
		c = getkey();

		if (c == ESC) {
			gotoxy(0, 24);
			break;
		}

		switch (c) {
		case LEFT:  x -= 2; scale = dis(a, x, y);    break;
		case RIGHT: x += 2; scale = dis(a, x, y);    break;
		case UP:    y--; scale = dis(a, x, y);    break;
		case DOWN:  y++; scale = dis(a, x, y);    break;
		case ENTER:

			system("cls");

			d = roll();

			gotoxy(0, 22);
			printf("나온 숫자는 %d입니다!!!!!", d);

			money += result(d, b, db);

			printf("게임을 계속하려면 ");
			system("pause");
			//getchar();

			db = reset(b, db);

			system("cls");

			break;
		case SPACE:
			scale = dis(a, x, y);
			save(a, b, scale, db);

			gotoxy(0, 23);
			bet = insert(money);

			money -= bet;

			b[db][4] = bet;
			b[db][5] = scale;
			b[db][6] = bet * scale;

			db += 1;

			system("cls");

			break;
		default:  break;
		}

		if (x < 3) {
			x = 3;
		}
		if (x > 47) {
			x = 47;
		}
		if (y < 1) {
			y = 1;
		}
		if (y > 5) {
			y = 5;
		}

		gotoxy(x, y);

		x = wherex();
		y = wherey();

	}
}