#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetCursorConsolePosition() �Լ� ���
#include <conio.h> //getch()�� kbhit() �Լ� ���
#include <ctime> //clock() �Լ� ���
#include <stdlib.h>
#include <time.h>


#define ESC 27 //���� ����
#define LEFT 75 //���� ȭ��ǥ Ű ASCII��
#define RIGHT 77 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 80 //�Ʒ� ȭ��ǥ Ű ASCII��
#define UP 72 //���� ȭ��ǥ Ű ASCII��

#define DIM 4 //4x4 ������� ũ��

static int x, y; //��ĭ�� ��ġ
static int moveNum; //�̵�ȸ��
static clock_t sTime; //���� �ð�

					  //���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define MAP_STARTX 16 
#define MAP_STARTY 2

					  //�̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define SCORE_STARTX 45
#define SCORE_STARTY 21

using namespace std;

int getDirectKey(void)//����Ű ȹ�� �Լ�
{
	return _getch() == 224 ? _getch() : 0;
}

int getAction(int(*map)[DIM])//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ // ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
{
	int i = 0;

	for (i = 0; i < 15; i++)
		if (*(map[0] + i) != i + 1)
			break;

	if (i == 15)
		return 0;

	switch (getDirectKey()) {
	case ESC:
		return 0;
	case LEFT:
		return LEFT;
	case RIGHT:
		return RIGHT;
	case DOWN:
		return DOWN;
	case UP:
		return UP;
	default:
		return 1;
	}
}

int main()
{
	while (1)
	{
		int a = 0;
		a = getDirectKey();		
		printf("%c, %d\n", a, a);
	}
	return 0;
}

void gotoXY(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void init(int(*map)[4]) //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
{
	for (int i = 0; i < 15; i++)
		*(map[0] + i) = i + 1;

	map[3][3] = '*';
}
void gameDraw(int(*map)[4]) // ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�; MAP_STARTX, MAP_STARTY ����� �����ؼ� �׻� ���� ��ġ(gotoXY�Լ� ��뿡 ����ʿ�ÿ� �Ű������� �߰���
{
	gotoXY(MAP_STARTX, MAP_STARTY);
	cout << "      Fifteen Puzzle";

	for (int i = 0; i < 4; i++)
	{
		gotoXY(MAP_STARTX, MAP_STARTY + i + 1);
		for (int j = 0; j < 4; j++)
		{
			if(map[i][j]=='*')
				cout << (char)map[i][j] << "\t";
			else
				cout << map[i][j] << "\t";
		}
	}
	gotoXY(SCORE_STARTX, SCORE_STARTY);
	cout << "�̵� Ƚ�� : " << moveNum;
	gotoXY(SCORE_STARTX, SCORE_STARTY+1);
	cout << "�ҿ� �ð� : " << clock() - sTime<<endl<<endl;
}
void shuffle(int num, int(*map)[4])
{
	int numcheck[DIM*DIM];
	int random = 0;

	for (int k = 0; k < num; k++)
	{
		srand(time(NULL));
		
		for (int i = 0; i < DIM*DIM; i++)
			numcheck[i] = 1;

		for (int i = 0; i < DIM; i++)
			for (int j = 0; j < DIM; j++)
				while (1){
					if ((numcheck[random = (rand() % (DIM*DIM))]) != 0){
						if (random == 15) {
							x = j;
							y = i;
							map[i][j] = '*';
						}else
							map[i][j] = random+1;
						numcheck[random] = 0;
						break;
					}
				}

		gameDraw(map);
		Sleep(100);
	}
}