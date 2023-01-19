#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() 함수 사용
#include <conio.h>	 //getch()와 kbhit() 함수 사용
#include <ctime>	 //clock() 함수 사용

using namespace std;

#define ESC 27	 // 게임 종료
#define LEFT 75	 // 왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80	 // 아래 화살표 키 ASCII값
#define UP 72	 // 위쪽 화살표 키 ASCII값

#define MDIM 4 // 4x4 퍼즐맵의 크기
#define PDIM 7 // 7x7 퍼즐의 크기

// 게임 Map 그리기 시작 위치: 필요하다면 출력 위치를 조정할 수 있음
#define MAP_STARTX 20
#define MAP_STARTY 2

// 이동 회수 및 소요시간 출력 위치: 필요하다면 출력 위치를 조정할 수 있음
#define SCORE_STARTX 20
#define SCORE_STARTY 30

static int numPat[16][7][7] =
	{
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 0, 0, 0, 0, 2,
		 2, 0, 0, 0, 0, 0, 2,
		 2, 0, 0, 0, 0, 0, 2, // 빈칸
		 2, 0, 0, 0, 0, 0, 2,
		 2, 0, 0, 0, 0, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 0, 1, 0, 0, 2,
		 2, 0, 0, 1, 0, 0, 2,
		 2, 0, 0, 1, 0, 0, 2, // 1
		 2, 0, 0, 1, 0, 0, 2,
		 2, 0, 0, 1, 0, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2, // 2
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 1, 0, 0, 0, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 3
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 4
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 1, 0, 0, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 5
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 0, 0, 0, 2,
		 2, 0, 1, 0, 0, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 6
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2, // 7
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 8
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 1, 1, 1, 0, 2,
		 2, 0, 1, 0, 1, 0, 2,
		 2, 0, 1, 1, 1, 0, 2, // 9
		 2, 0, 0, 0, 1, 0, 2,
		 2, 0, 0, 0, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 1, 0, 1, 0, 1, 2,
		 2, 1, 0, 1, 0, 1, 2, // 10
		 2, 1, 0, 1, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 0, 1, 0, 2,
		 2, 1, 0, 0, 1, 0, 2,
		 2, 1, 0, 0, 1, 0, 2, // 11
		 2, 1, 0, 0, 1, 0, 2,
		 2, 1, 0, 0, 1, 0, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 1, 0, 0, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2, // 12
		 2, 1, 0, 1, 0, 0, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 1, 0, 0, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2, // 13
		 2, 1, 0, 0, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 1, 0, 1, 2,
		 2, 1, 0, 1, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2, // 14
		 2, 1, 0, 0, 0, 1, 2,
		 2, 1, 0, 0, 0, 1, 2,
		 2, 2, 2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2, 2, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 1, 0, 1, 0, 0, 2,
		 2, 1, 0, 1, 1, 1, 2, // 15
		 2, 1, 0, 0, 0, 1, 2,
		 2, 1, 0, 1, 1, 1, 2,
		 2, 2, 2, 2, 2, 2, 2}};

enum COMMAND
{
	Stop = 0,
	Left,
	Right,
	Down,
	Up,
	Non
};

class puzzleGame
{
public:
	puzzleGame(void);												// 초기화 함수; 필요시에 매개변수를 추가함
	void gameDraw(void);											// 퍼즐로 구성되는 게임 맵과 반복회수, 시간 출력함수; MAP_STARTX, MAP_STARTY 상수를 참조해서 항상 고정 위치(gotoXY함수 사용에 출력필요시에 매개변수를 추가함
	void puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k); // 하나의 퍼즐을 그리는 멤버함수
	void puzzleMove(int moveKey);									// 퍼즐 이동시키는 멤버 함수; 필요시에 매개변수 추가함
	void shuffle(int num);											// 퍼즐 맵 초기화; 50회 무작위 이동, 필요시에 인자 추가 할 수 있음
	void getCommand(void);											// 키값에 따라 명령어를 디코딩하는 멤버 함수
	int getAction(void) { return action; };
	void setsTime(clock_t time) { sTime = time; };
	int solvable(void);

private:
	int map[MDIM][MDIM];
	int action;
	int x, y;	   // 빈칸의 위치
	int moveNum;   // 이동회수
	clock_t sTime; // 시작 시간
	clock_t cTime; // 현재 시간
};

void gotoXY(int x, int y); // 콘솔 화면에서 커서를 특정 위치로 이동
int getDirectKey();

int main(void)
{
	puzzleGame gameBot;
	int action = 0;
	gameBot.shuffle(50);
	gameBot.setsTime(clock()); // 소요시간 계산을 위해 게임의 시작 시간을 기록해둔다.

	while (1)
	{
		gameBot.gameDraw();
		gameBot.getCommand();
		action = gameBot.getAction();
		// gameBot.puzzleMove();
	}

	cout << "The game is over!!" << endl;
	return 0;
}

puzzleGame::puzzleGame()
{
	for (int i = 0; i < MDIM * MDIM; i++) // 맵의 값을 1,2,3,~의 순서로 초기화 시킨다.
		*(map[0] + i) = i;
	x = 0;
	y = 0;
	sTime = 0;	 // 시작시간을 초기화 시킨다.
	moveNum = 0; // 이동 회수를 초기화시킨다.

	// 게임 초기화 코드 작성
}

void puzzleGame::puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k)
{
	for (int i = 0; i < PDIM; i++)
	{
		gotoXY(x, y + i);
		for (int j = 0; j < PDIM; j++)
		{
			if (puzzle[k][i][j] == 0)
				cout << "  ";
			else if (puzzle[k][i][j] == 1)
				cout << "□";
			else
				cout << "■";
		}
	}
}

void puzzleGame::gameDraw(void)
{
	gotoXY(MAP_STARTX, MAP_STARTY);
	cout << "   Fifteen Puzzle" << endl;

	for (int i = 0; i < MDIM; i++)
	{
		gotoXY(MAP_STARTX, MAP_STARTY + i * 7 + 1);
		for (int j = 0; j < MDIM; j++)
		{
			puzzleDraw(numPat, MAP_STARTX + j * 7 + 1, MAP_STARTY + i * 7 + 1, map[i][j]);
			// 여기서 puzzleDraw 함수 호출함
		}
	}

	cout << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY);
	cout << "  이동 회수: " << moveNum << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY + 1);
	cTime = clock();
	cout << "  소요 시간: " << (cTime - sTime) / 1000.0 << "초" << endl;
}

void puzzleGame::puzzleMove(int moveKey)
{
	int temp = 0;

	switch (action) // 키보드에서 입력받은 키보드 값을 바탕으로 배열의 값을 바꾼다.
	{
	case LEFT:
		if (x >= 1)
		{ // 예외 처리를 통해 만약 '*'의 위치가 판을 벗어나지 않도록 한다.
			temp = map[y][x];
			map[y][x] = map[y][x - 1];
			map[y][x - 1] = temp;
			x--;
		}
		break;

	case RIGHT:
		if (x <= 2)
		{
			temp = map[y][x];
			map[y][x] = map[y][x + 1];
			map[y][x + 1] = temp;
			x++;
		}
		break;

	case UP:
		if (y >= 1)
		{
			temp = map[y][x];
			map[y][x] = map[y - 1][x];
			map[y - 1][x] = temp;
			y--;
		}
		break;

	case DOWN:
		if (y <= 2)
		{
			temp = map[y][x];
			map[y][x] = map[y + 1][x];
			map[y + 1][x] = temp;
			y++;
		}
		break;

	default:
		break; // 아무것도 아니면 그냥 switch를 탈출한다.
	}
}

void puzzleGame::getCommand(void)
{
	switch (getDirectKey())
	{ // 키를 입력받는 함수를 통해 키를 입력받고 키에 따라 값을 리턴한다.
	case ESC:
		action = Stop;
		break;
	case LEFT:
		action = Left;
		break;
	case RIGHT:
		action = Right;
		break;
	case DOWN:
		action = Down;
		break;
	case UP:
		action = Up;
		break;
	default:
		action = Non;
		break; // 방향키나 ESC키말고 다른키가 입력되면 1을 리턴한다.
	}
}

void puzzleGame::shuffle(int num)
{
	int numcheck[MDIM * MDIM]; // 배열의 값이 중복되었는지 체크하기위한 맵과 동일한 크기의 배열을 생성한다.
	int random = 0;			   // 생성된 난수를 저장해 놓는 변수이다.

	srand(time(NULL)); // 난수의 시드 값을 바꾸어 줌으로써 난수 생성을 한다.

	for (int k = 0; k < num; k++)
	{
		while (1)
		{
			for (int i = 0; i < MDIM * MDIM; i++)
				numcheck[i] = 1; // 난수 설정하기전에 중복체크 배열을 사용되기 전 상태인 '1'로 초기화 시킨다.

			for (int i = 0; i < MDIM; i++)
				for (int j = 0; j < MDIM; j++)
					while (1)
					{
						if ((numcheck[random = (rand() % (MDIM * MDIM))]) != 0)
						{
							if (random == 0)
							{		   // 만약 난수의 값이 빈칸의 좌표인 0이라면 그의 배열 좌표를 저장한다.
								x = j; //'*'의 위치를 저장하기 위해 전역변수 x,y에 2차원 배열의 좌표를 저장한다.
								y = i;
							}
							map[i][j] = random;
							numcheck[random] = 0;
							break;
						} // 생성된 난수가 사용되지 않은 난수이면 사용 표시를 하고 배열에 저장하며 루프를 탈출한다.
					}	  // 난수가 사용 전이면 numcheck에 1의 형태로, 후면 0의 형태로 저장된다.

			if (solvable() == 1) // 퍼즐을 풀지 못하는 경우로 섞일 수 있다. 풀 수 있는지 판별하여
				break;			 // 풀 수 있으면 1을 리턴하며 풀지못하면 0을 리턴하고 다시 섞는다.
		}
		sTime = clock(); // 섞을 때는 시작 시간을 계속 초기화 시켜줌으로써 시간이 0으로 보이도록 한다.
		gameDraw();		 // 맵을 갱신시킨다.
		Sleep(100);		 // 맵 변경이 보이도록 대기시간을 준다.
	}
}

int puzzleGame::solvable(void) // 무작위로 배열된 퍼즐이 풀수있는지 판별하는 함수
{
	int inv_count = 0, k = 0, temp; // 반전된 숫자 배열 세는 변수 등을 선언

	if (x != MDIM - 1 || y != MDIM - 1) // 먼저 '*'표의 위치를 맨 아래 맨 오른쪽으로 이동시킨다.
	{
		temp = map[MDIM - 1][MDIM - 1];
		map[MDIM - 1][MDIM - 1] = 0;
		map[y][x] = temp;
		y = MDIM - 1;
		x = MDIM - 1;
	}

	for (int i = 0; i < MDIM * MDIM - 2; i++) // 섞여진 수들을 일렬로 나열시키고 반전된 수의 수를 샌다.
		for (int j = i + 1; j < MDIM * MDIM - 1; j++)
			if (*(map[0] + i) > *(map[0] + j))
				inv_count++;

	if (inv_count % 2 == 1) // 만약 반전된 수의 수가 홀수 개이면 풀 수 없는 퍼즐이며 0을 리턴한다.
		return 0;
	else
		return 1; // 짝수 개이면 풀 수 있는 퍼즐이며 1을 리턴한다.
}

// 콘솔 화면에서 커서를 특정 위치로 이동
void gotoXY(short x, short y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int getDirectKey()
{
	char key = Non;

	if (_kbhit() != 0) // 키보드를 눌렀는지 확인함
	{
		// 특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값은 224값을 발생하고 두번째 값은 특수키에 따라 다름
		// 특수 키를 확인하기 위해 2번의 getch()함수를 호출해야 함
		key = _getch();
		if (key == 224)
			key = _getch();
	}

	return key;
}