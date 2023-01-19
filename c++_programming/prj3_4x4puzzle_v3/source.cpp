#include <iostream>
#include <fstream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() �Լ� ���
#include <conio.h>	 //getch()�� kbhit() �Լ� ���
#include <ctime>	 //clock() �Լ� ���

using namespace std;

#define ESC 27	 // ���� ����
#define LEFT 75	 // ���� ȭ��ǥ Ű ASCII��
#define RIGHT 77 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 80	 // �Ʒ� ȭ��ǥ Ű ASCII��
#define UP 72	 // ���� ȭ��ǥ Ű ASCII��

#define MDIM 4			// 4x4 ������� ũ��
#define PDIM 7			// 7x7 ������ ũ��
#define PNUM MDIM *MDIM // �׸�ĭ�� ��

// ���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ����
#define MAP_STARTX 15
#define MAP_STARTY 3

// �̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ����
#define SCORE_STARTX 34
#define SCORE_STARTY 36

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
	puzzleGame();																// default ������: Ŭ���� ��ü �ʱ�ȭ �Լ�, �ʿ�ÿ� �Ű������� �߰���
	~puzzleGame();																// �Ҹ���: Ŭ���� ��ü�� �Ҹ����� �����Ҵ��� ������ ���� ��ü�� ������ ���� ����
	friend ostream &operator<<(ostream &outputStream, const puzzleGame &gmBot); // gameDrawd ����Լ� ��ſ� << ������ �����ε��� ���� ����Ͻÿ�.
	void puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k) const;		// �ϳ��� ������ �׸��� ����Լ�
	void puzzleMove(int moveKey);												// ���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
	void shuffle(int num);														// ���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
	void getCommand(void);														// ��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
																				//  ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
																				// �ʿ�ÿ� �Ű����� ���ڸ� �߰��� �� ����
	int getAction(void) const { return action; };								// �����Լ����� action�� ���� �д´�.
	int solvable(void);															// Ǯ �� �ִ� �������� �Ǻ��ϴ� �Լ�
	void setCTime(clock_t ct) { cTime = ct; };									// cTime���� �ζ��� �Լ�
	void setSTime(clock_t st) { sTime = st; };									// sTime���� �ζ��� �Լ�

private:
	int (*numPat)[PDIM][PDIM];
	int **map;

	int action;
	int x, y;	   // ��ĭ�� ��ġ
	int moveNum;   // �̵�ȸ��
	clock_t sTime; // ���� �ð�
	clock_t cTime; // ���� �ð�
};

void gotoXY(int x, int y); // �ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
int getDirectKey();

int main(void)
{
	puzzleGame gameBot;

	gameBot.shuffle(50); // 50�� ���´�
	gameBot.setCTime(clock());
	gameBot.setSTime(clock()); // �����ϱ��� �ð� �ʱ�ȭ
	cout << gameBot;		   // ���� ȭ�� ���
	gameBot.getCommand();	   // �Է�, ���� �ϼ� ���� Ȯ��

	while (gameBot.getAction()) // action�� Stop�̸� �ݺ����� ����ȴ�.
	{
		gameBot.puzzleMove(gameBot.getAction()); // �Էµ� Ű�� ���� ������ �ű��.
		gameBot.setCTime(clock());				 // ���� �ð��� �����Ѵ�.
		cout << gameBot;						 // ȭ�����
		gameBot.getCommand();					 // �Է�, ���� �ϼ� ���� Ȯ��
	}

	system("cls");	 // ȭ���� �ѹ� �����.
	cout << gameBot; // ȭ�� ���
	gotoXY(SCORE_STARTX + 20, SCORE_STARTY);
	cout << "The game is over!!" << endl
		 << endl
		 << endl; // �ȳ����� ����Ѵ�.
}

ostream &operator<<(ostream &outputStream, const puzzleGame &gmBot)
{ // gameDrawd ����Լ� ��ſ� << ������ �����ε��� ���� ����Ͻÿ�.
	gotoXY(SCORE_STARTX, SCORE_STARTY);
	cout << "  �̵� ȸ��: " << gmBot.moveNum << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY + 1);
	cout.setf(ios::fixed);
	cout.precision(1);
	cout << "  �ҿ� �ð�: " << (gmBot.cTime - gmBot.sTime) / 1000.0 << "��" << endl;
	cout.unsetf(ios::fixed);
	// �̵� ȸ�� ���, �ҿ�ð� �Ҽ��� ù° �ڸ����� ���

	gotoXY(MAP_STARTX + 20, MAP_STARTY);
	cout << "   Fifteen Puzzle" << endl; // ���� ���

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			gmBot.puzzleDraw(gmBot.numPat, MAP_STARTX + (j * 15), MAP_STARTY + (i * 8) + 1, gmBot.map[i][j]);
	// puzzleDraw �Լ� ȣ���� ���� ���.

	return outputStream;
}

puzzleGame::puzzleGame()
{

	int num = 1, temp;
	ifstream fin;

	numPat = new int[PNUM][PDIM][PDIM];
	fin.open("./NumberPattern.txt"); // "NumberPattern.txt" ������ ������Ʈ ������ ��ġ�ؾ� ��
	if (fin.fail())
	{
		cout << "���� ���� ������ �� �� �����ϴ�!\n";
		exit(1);
	}

	for (int p = 0; p < PNUM; p++)
		for (int i = 0; i < PDIM; i++)
			for (int j = 0; j < PDIM; j++)
			{
				fin >> temp;
				numPat[p][i][j] = temp;
			}

	map = new int *[MDIM]; // ������ �����͸� �����Ҵ� �Ѵ�.

	for (int i = 0; i < MDIM; i++)
		map[i] = new int[MDIM]; // ������ �����͸� �����Ҵ��Ѵ�.

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			map[i][j] = i * 4 + j + 1;
	// ���� �� �����Ҵ� �� �� �Ҵ�
	map[MDIM - 1][MDIM - 1] = 0;
	x = MDIM - 1;
	y = MDIM - 1;
	// ���� ���� 1,2,3,~ ,MDIM*MDIM-1,0�� ������ �ʱ�ȭ ��Ű�� ��ĭ�� ��ġ�� ���������� �ʱ�ȭ��Ų��.
	sTime = 0;	 // ���۽ð��� �ʱ�ȭ ��Ų��.
	moveNum = 0; // �̵� ȸ���� �ʱ�ȭ��Ų��.

	// ���� �ʱ�ȭ �ڵ� �ۼ�
}

puzzleGame::~puzzleGame()
{
	for (int i = 0; i < MDIM; i++)
		delete[] map[i]; // �迭 �����͸� �ʱ�ȭ�Ѵ�.

	delete[] map;	 // �迭 �����͸� �ʱ�ȭ�Ѵ�.
	delete[] numPat; // ������ �迭�� �ʱ�ȭ �Ѵ�.
}

void puzzleGame::puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k) const
{ // 7*7�� ���� ���¿�, �Է��� ��ġ, �Է��� ���ڸ� �Է¹޴´�.
	for (int i = 0; i < PDIM; i++)
	{
		gotoXY(x, y + i);
		for (int j = 0; j < PDIM; j++)
		{
			if (puzzle[k][i][j] == 0)
				cout << "  ";
			else if (puzzle[k][i][j] == 1)
				cout << "��";
			else
				cout << "��";
		}
	} // ���� ������ ��翡 ���� ��ȣ�� �ٸ��� ����Ѵ�.
}

void puzzleGame::puzzleMove(int moveKey)
{
	int temp = 0;

	switch (moveKey) // getcommand�� ���� �Է¹��� Ű���� ������ ������ �����δ�.
	{
	case Left:
		if (x >= 1)
		{ // ���� ó���� ���� ��ĭ�� ��ġ�� ���� ����� �ʵ��� �Ѵ�.
			temp = map[y][x];
			map[y][x] = map[y][x - 1];
			map[y][x - 1] = temp;
			x--;
			moveNum++; // ������ �̵��߱� ������ �̵� Ƚ���� 1���Ѵ�.
		}
		break;

	case Right:
		if (x <= 2)
		{
			temp = map[y][x];
			map[y][x] = map[y][x + 1];
			map[y][x + 1] = temp;
			x++;
			moveNum++; // ������ �̵��߱� ������ �̵� Ƚ���� 1���Ѵ�.
		}
		break;

	case Up:
		if (y >= 1)
		{
			temp = map[y][x];
			map[y][x] = map[y - 1][x];
			map[y - 1][x] = temp;
			y--;
			moveNum++; // ������ �̵��߱� ������ �̵� Ƚ���� 1���Ѵ�.
		}
		break;

	case Down:
		if (y <= 2)
		{
			temp = map[y][x];
			map[y][x] = map[y + 1][x];
			map[y + 1][x] = temp;
			y++;
			moveNum++; // ������ �̵��߱� ������ �̵� Ƚ���� 1���Ѵ�.
		}
		break;

	default:
		break; // �ƹ��͵� �ƴϸ� �׳� switch�� Ż���Ѵ�.
	}
}

void puzzleGame::getCommand(void)
{
	bool Flag = FALSE; // ������ ���߾������� Ȯ���Ѵ�.

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
		{
			if ((map[i][j] != i * 4 + j + 1) && (i * j < (MDIM - 1) * (MDIM - 1)))
			{
				Flag = TRUE;
			}
		} // �߰��� Ʋ�� �κ��� �߻��ϸ� Flag�� TRUE�� �����ȴ�.
	if (Flag == FALSE)
		action = Stop; // ������ �� ������ action �� Stop���� �Ѵ�.

	if (action != Stop) // ������ ���߾����� ���� ��� Ű����� Ű�� �Է¹޴´�.
		switch (getDirectKey())
		{ // getDirectKey �Լ��� ���� Ű�� �Է¹ް� ��ɾ ���ڵ��� action�� �����Ѵ�.
		case ESC:
			action = Stop;
			moveNum = 0;
			sTime = cTime = 0; // �ð��� �̵�Ƚ���� �ʱ�ȭ�Ѵ�.
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
			break; // ����Ű�� ESCŰ���� �ٸ�Ű�� �ԷµǸ� NON�� �����Ѵ�.
		}
}

void puzzleGame::shuffle(int num)
{
	int numcheck[MDIM * MDIM]; // �迭�� ���� �ߺ��Ǿ����� üũ�ϱ����� �ʰ� ������ ũ���� �迭�� �����Ѵ�.
	int random = 0;			   // ������ ������ ������ ���� �����̴�.

	srand(time(NULL)); // ������ �õ� ���� �ٲپ� �����ν� ���� ������ �Ѵ�.

	for (int k = 0; k < num; k++)
	{
		while (1)
		{
			for (int i = 0; i < MDIM * MDIM; i++)
				numcheck[i] = 1; // ���� �����ϱ����� �ߺ�üũ �迭�� ���Ǳ� �� ������ '1'�� �ʱ�ȭ ��Ų��.

			for (int i = 0; i < MDIM; i++)
				for (int j = 0; j < MDIM; j++)
					while (1)
					{
						if ((numcheck[random = (rand() % (MDIM * MDIM))]) != 0)
						{
							if (random == 0)
							{		   // ���� ������ ���� ��ĭ�� ��ǥ�� 0�̶�� ���� �迭 ��ǥ�� �����Ѵ�.
								x = j; // ��ĭ�� ��ġ�� �����ϱ� ���� ��� ���� x,y�� 2���� �迭�� ��ǥ�� �����Ѵ�.
								y = i;
							}
							map[i][j] = random;
							numcheck[random] = 0;
							break;
						} // ������ ������ ������ ���� �����̸� ��� ǥ�ø� �ϰ� �迭�� �����ϸ� ������ Ż���Ѵ�.
					}	  // ������ ��� ���̸� numcheck�� 1�� ���·�, �ĸ� 0�� ���·� ����ȴ�.

			if (solvable() == 1) // ������ Ǯ�� ���ϴ� ���� ���� �� �ִ�. Ǯ �� �ִ��� �Ǻ��Ͽ�
				break;			 // Ǯ �� ������ 1�� �����ϸ� Ǯ�����ϸ� 0�� �����ϰ� �ٽ� ���´�.
		}
		cTime = sTime = 0; // ���� ���� ���� �ð��� ��� �ʱ�ȭ ���������ν� �ð��� 0���� ���̵��� �Ѵ�.
		cout << *this;
		Sleep(100); // �� ������ ���̵��� ���ð��� �ش�.
	}
}

int puzzleGame::solvable(void) // �������� �迭�� ������ Ǯ���ִ��� �Ǻ��ϴ� �Լ�
{
	int inv_count = 0, k = 0, temp, t_arr[MDIM * MDIM]; // ������ ���� �迭 ���� ���� ���� ����

	if (x != MDIM - 1 || y != MDIM - 1) // ���� ��ĭ�� ��ġ�� �� �Ʒ� �� ���������� �̵���Ų��.
	{
		temp = map[MDIM - 1][MDIM - 1];
		map[MDIM - 1][MDIM - 1] = 0;
		map[y][x] = temp;
		y = MDIM - 1;
		x = MDIM - 1;
	}

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			t_arr[i * 4 + j] = map[i][j];
	// �迭�� ���ڵ��� ���ϱ� ���� ���� ũ���� ������ �迭�� �����Ѵ�.

	for (int i = 0; i < MDIM * MDIM - 2; i++)
		for (int j = i + 1; j < MDIM * MDIM - 1; j++)
			if (t_arr[i] > t_arr[j])
				inv_count++;

	if (inv_count % 2 == 1) // ���� ������ ���� ���� Ȧ�� ���̸� Ǯ �� ���� �����̸� 0�� �����Ѵ�.
		return 0;
	else
		return 1; // ¦�� ���̸� Ǯ �� �ִ� �����̸� 1�� �����Ѵ�.
}

// �ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void gotoXY(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int getDirectKey()
{
	char key = Non;
	while (1)
	{					   // Ű���尡 �������� ������ Ż���Ѵ�.
		if (_kbhit() != 0) // Ű���带 �������� Ȯ����
		{
			// Ư�� Ű�� ������ �� ���ۿ� 2Byte�� �߻���, ù��° ���� 224���� �߻��ϰ� �ι�° ���� Ư��Ű�� ���� �ٸ�
			// Ư�� Ű�� Ȯ���ϱ� ���� 2���� getch()�Լ��� ȣ���ؾ� ��
			key = _getch();
			if (key == 224)
				key = _getch();
			break;
		}
	}
	return key;
}