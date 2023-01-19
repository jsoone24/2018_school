#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() 함수 사용
#include <conio.h> //getch()와 kbhit() 함수 사용
#include <ctime> //clock() 함수 사용

using namespace std;

#define ESC 27 //게임 종료
#define LEFT 75 //왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80 //아래 화살표 키 ASCII값
#define UP 72 //위쪽 화살표 키 ASCII값

#define MDIM 4 //4x4 퍼즐맵의 크기
#define PDIM 7 //7x7 퍼즐의 크기


//게임 Map 그리기 시작 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define MAP_STARTX 20 
#define MAP_STARTY 2

//이동 회수 및 소요시간 출력 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define SCORE_STARTX 20
#define SCORE_STARTY 30

static int numPat[16][7][7]=
{
{2,2,2,2,2,2,2,
 2,0,0,0,0,0,2,
 2,0,0,0,0,0,2,
 2,0,0,0,0,0,2,
 2,0,0,0,0,0,2,
 2,0,0,0,0,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,0,1,0,0,2,
 2,0,0,1,0,0,2,
 2,0,0,1,0,0,2,
 2,0,0,1,0,0,2,
 2,0,0,1,0,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,1,1,1,0,2,
 2,0,1,0,0,0,2,
 2,0,1,1,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,1,1,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,0,1,0,2,
 2,0,1,0,1,0,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,0,0,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,1,0,0,0,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,1,1,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,0,0,0,2,
 2,0,1,0,0,0,2,
 2,0,1,1,1,0,2,
 2,0,1,0,1,0,2,
 2,0,1,1,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,0,0,1,0,2,
 2,0,0,0,1,0,2,
 2,0,0,0,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,1,0,1,0,2,
 2,0,1,1,1,0,2,
 2,0,1,0,1,0,2,
 2,0,1,1,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,0,1,1,1,0,2,
 2,0,1,0,1,0,2,
 2,0,1,1,1,0,2,
 2,0,0,0,1,0,2,
 2,0,0,0,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,1,1,1,2,
 2,1,0,1,0,1,2,
 2,1,0,1,0,1,2,
 2,1,0,1,0,1,2,
 2,1,0,1,1,1,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,0,1,0,2,
 2,1,0,0,1,0,2,
 2,1,0,0,1,0,2,
 2,1,0,0,1,0,2,
 2,1,0,0,1,0,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,1,1,1,2,
 2,1,0,0,0,1,2,
 2,1,0,1,1,1,2,
 2,1,0,1,0,0,2,
 2,1,0,1,1,1,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,1,1,1,2,
 2,1,0,0,0,1,2,
 2,1,0,1,1,1,2,
 2,1,0,0,0,1,2,
 2,1,0,1,1,1,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,1,0,1,2,
 2,1,0,1,0,1,2,
 2,1,0,1,1,1,2,
 2,1,0,0,0,1,2,
 2,1,0,0,0,1,2,
 2,2,2,2,2,2,2},
{2,2,2,2,2,2,2,
 2,1,0,1,1,1,2,
 2,1,0,1,0,0,2,
 2,1,0,1,1,1,2,
 2,1,0,0,0,1,2,
 2,1,0,1,1,1,2,
 2,2,2,2,2,2,2}
};

enum COMMAND {Stop=0, Left, Right, Down, Up, Non};

class puzzleGame
{
public:
	    
		puzzleGame(void); //초기화 함수; 필요시에 매개변수를 추가함
		void gameDraw(void); // 퍼즐로 구성되는 게임 맵과 반복회수, 시간 출력함수; MAP_STARTX, MAP_STARTY 상수를 참조해서 항상 고정 위치(gotoXY함수 사용에 출력필요시에 매개변수를 추가함
		void puzzleDraw(int (*puzzle)[PDIM], int x, int y);// 하나의 퍼즐을 그리는 멤버함수
		void puzzleMove(int moveKey); //퍼즐 이동시키는 멤버 함수; 필요시에 매개변수 추가함
		void shuffle(int num);//퍼즐 맵 초기화; 50회 무작위 이동, 필요시에 인자 추가 할 수 있음
		void getCommand(void);//키값에 따라 명령어를 디코딩하는 멤버 함수
		int getAction(void)	{ return action;};
private:
	   int map[MDIM][MDIM];
       int action;
	   int x,y; //빈칸의 위치
	   int moveNum; //이동회수
	   clock_t sTime; //시작 시간
	   clock_t cTime; //시작 시간
};

void gotoXY(int x, int y); //콘솔 화면에서 커서를 특정 위치로 이동
int getDirectKey();

int main(void)
{
	puzzleGame gameBot;
	gameBot.shuffle(50);
	gameBot.gameDraw();
	gameBot.getCommand();
    while(gameBot.getAction())
	{
	  gameBot.puzzleMove(gameBot.getAction());
	  gameBot.gameDraw(); 
	  gameBot.getCommand();
	}

	cout << "The game is over!!" << endl;
	return 0;
}

puzzleGame::puzzleGame()
{

	//게임 초기화 코드 작성
	
}


void puzzleGame::puzzleDraw(int (*puzzle)[PDIM], int x, int y)
{
	for(int i=0;i< PDIM ; i++)
	{
	  gotoXY(x,y+i);
	  for(int j=0; j< PDIM; j++)
		{
			if(puzzle[i][j] == 0)
				cout << "  ";
			else if(puzzle[i][j] == 1)
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
	
	for(int i=0; i< MDIM; i++)
	{   
		for(int j=0; j< MDIM; j++)
		{

			//여기서 puzzleDraw 함수 호출함

		}
	}

	cout << endl;
	gotoXY(  SCORE_STARTX, SCORE_STARTY);
	cout << "  이동 회수: " << moveNum << endl;
	gotoXY(  SCORE_STARTX, SCORE_STARTY+1);
	cTime = clock();
	cout << "  소요 시간: " << (cTime-sTime)/1000.0 << "초" << endl;
}



void puzzleGame::puzzleMove(int moveKey)
{
	~
    ~
	~
}

void puzzleGame::getCommand(void)
{
	~
	~
	~
}

//콘솔 화면에서 커서를 특정 위치로 이동
void gotoXY(int x, int y) 
{
 COORD Pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


int getDirectKey()
{
	char key=Non;
    if(_kbhit()!= 0) //키보드를 눌렀는지 확인함
	{
	  //특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값은 224값을 발생하고 두번째 값은 특수키에 따라 다름
	  //특수 키를 확인하기 위해 2번의 getch()함수를 호출해야 함
		key = getch();
		if(key==224) key=_getch();
	}
	return key;
} 
