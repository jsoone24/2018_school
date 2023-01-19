#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetCursorConsolePosition() 함수 사용
#include <conio.h> //getch()와 kbhit() 함수 사용
#include <ctime> //clock() 함수 사용
#include <stdlib.h>
#include <time.h>


#define ESC 27 //게임 종료
#define LEFT 75 //왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80 //아래 화살표 키 ASCII값
#define UP 72 //위쪽 화살표 키 ASCII값

#define DIM 4 //4x4 퍼즐맵의 크기

static int x, y; //빈칸의 위치
static int moveNum; //이동회수
static clock_t sTime; //시작 시간

					  //게임 Map 그리기 시작 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define MAP_STARTX 16 
#define MAP_STARTY 2

					  //이동 회수 및 소요시간 출력 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define SCORE_STARTX 45
#define SCORE_STARTY 21

using namespace std;

int getDirectKey(void)//방향키 획득 함수
{
	return _getch() == 224 ? _getch() : 0;
}

int getAction(int(*map)[DIM])//모든 퍼즐이 제 위치에 있거나 ESC키가 눌러졌으면 정수 0을 반환 // 방향키를 눌렀을 때는 해당 키값을 반환(LEFT, RIGHT, DOWN, UP)
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

void init(int(*map)[4]) //초기화 함수; 필요시에 매개변수를 추가함
{
	for (int i = 0; i < 15; i++)
		*(map[0] + i) = i + 1;

	map[3][3] = '*';
}
void gameDraw(int(*map)[4]) // 게임 맵과 반복회수, 시간 출력함수; MAP_STARTX, MAP_STARTY 상수를 참조해서 항상 고정 위치(gotoXY함수 사용에 출력필요시에 매개변수를 추가함
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
	cout << "이동 횟수 : " << moveNum;
	gotoXY(SCORE_STARTX, SCORE_STARTY+1);
	cout << "소요 시간 : " << clock() - sTime<<endl<<endl;
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