#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() �Լ� ���
#include <conio.h>	 //getch()�� kbhit() �Լ� ���
#include <ctime>	 //clock() �Լ� ���

using namespace std;

#define ESC 27	 // ���� ����
#define LEFT 75	 // ���� ȭ��ǥ Ű ASCII��
#define RIGHT 77 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 80	 // �Ʒ� ȭ��ǥ Ű ASCII��
#define UP 72	 // ���� ȭ��ǥ Ű ASCII��

#define MDIM 4 // 4x4 ������� ũ��
#define PDIM 7 // 7x7 ������ ũ��

// ���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ����
#define MAP_STARTX 15
#define MAP_STARTY 3

// �̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ����
#define SCORE_STARTX 34
#define SCORE_STARTY 36

static int numPat[16][7][7] =
	{
		{2, 2, 2, 2, 2, 2, 2,
		 2, 0, 0, 0, 0, 0, 2,
		 2, 0, 0, 0, 0, 0, 2,
		 2, 0, 0, 0, 0, 0, 2, // ��ĭ
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
}; // ����Ű�� ����, ����Ʈ�� ���ڵ�

class puzzleGame
{
public:
	puzzleGame(void);	 // �ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
	void gameDraw(void); // ����� �����Ǵ� ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�
						 // MAP_STARTX, MAP_STARTY ����� ����
						 // �׻� ���� ��ġ(gotoXY�Լ� ���)�� ��� �ʿ�ÿ� �Ű������� �߰�
	void puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k); // �ϳ��� ������ �׸��� ����Լ�
	void puzzleMove(int moveKey);									// ���� �̵���Ű�� ��� �Լ�; �ʿ�ÿ� �Ű����� �߰���
	void shuffle(int num);											// ���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
	void getCommand(void);											// Ű���� ���� ��ɾ ���ڵ��ϴ� ��� �Լ�
	int getAction(void) { return action; };							// private ��� ���� action�� class �ۿ��� ��� ���� �Լ�
	void setsTime(double time) { sTime = time; };					// ���� �Լ����� ���� ���� �ð����� sTime�� �ʱ�ȭ�ϴ� �ζ��� �Լ�
	int solvable(void);												// Ǯ �� �ִ� �������� �Ǻ��ϴ� �Լ�

private:
	int map[MDIM][MDIM]; // ���� �迭
	int action;			 // � �ൿ�� �������� ����. (Stop, Left, Right, Down, Up, Non)
	int x, y;			 // ��ĭ�� ��ġ
	int moveNum;		 // �̵�ȸ��
	clock_t sTime;		 // ���� �ð�
	clock_t cTime;		 // ���� �ð�
};

void gotoXY(int x, int y); // �ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
int getDirectKey();

int main(void)
{
	puzzleGame gameBot;		   // class��ü ����
	int action = 0;			   // ���� ����
	gameBot.shuffle(50);	   // ���ϴ� Ƚ����ŭ ������ ���´�.
	gameBot.setsTime(clock()); // �ҿ�ð� ����� ���� ������ ���� �ð��� ����صд�.
	while (1)
	{
		gameBot.getCommand();		  // ������ �˻��ϰų� Ű���� �Է��� ���ؾ �ൿ�� �������� action�� �����Ѵ�.
		action = gameBot.getAction(); // class private�� action���� �ҷ��´�.

		if (action == Stop) // ������ ���߰ų� ESCŰ�� �Է¹��� ��� �����Ѵ�.
			break;
		else
			gameBot.puzzleMove(action); // �Է¹��� �������� ������ �̵���Ų��.

		gameBot.gameDraw(); // �ٽ� ���� �����Ѵ�.
	}

	system("cls");			   // ȭ���� �ѹ� �����.
	gameBot.setsTime(clock()); // �ð��� �ʱ�ȭ�Ѵ�.
	gameBot.gameDraw();
	gotoXY(SCORE_STARTX + 20, SCORE_STARTY);
	cout << "The game is over!!" << endl
		 << endl
		 << endl; // �ȳ����� ����Ѵ�.

	return 0;
}

puzzleGame::puzzleGame()
{
	for (int i = 0; i < MDIM * MDIM; i++)
		*(map[0] + i) = i + 1;
	map[MDIM - 1][MDIM - 1] = 0;
	x = MDIM - 1;
	y = MDIM - 1;
	// ���� ���� 1,2,3,~ ,MDIM*MDIM-1,0�� ������ �ʱ�ȭ ��Ű�� ��ĭ�� ��ġ�� ���������� �ʱ�ȭ��Ų��.
	sTime = 0;	 // ���۽ð��� �ʱ�ȭ ��Ų��.
	moveNum = 0; // �̵� ȸ���� �ʱ�ȭ��Ų��.

	// ���� �ʱ�ȭ �ڵ� �ۼ�
}

void puzzleGame::puzzleDraw(int puzzle[][PDIM][PDIM], int x, int y, int k)
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

void puzzleGame::gameDraw(void)
{
	gotoXY(SCORE_STARTX, SCORE_STARTY);
	cout << "  �̵� ȸ��: " << moveNum << endl;
	gotoXY(SCORE_STARTX, SCORE_STARTY + 1);
	cout.setf(ios::fixed);
	cout.precision(1);
	cTime = clock();
	cout << "  �ҿ� �ð�: " << (cTime - sTime) / 1000.0 << "��" << endl;
	cout.unsetf(ios::fixed);
	// �̵� ȸ�� ���, �ҿ�ð� �Ҽ��� ù° �ڸ����� ���

	gotoXY(MAP_STARTX + 20, MAP_STARTY);
	cout << "   Fifteen Puzzle" << endl; // ���� ���

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			puzzleDraw(numPat, MAP_STARTX + (j * 15), MAP_STARTY + (i * 8) + 1, map[i][j]);
	// puzzleDraw �Լ� ȣ���� ���� ���.
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
	int i = 0; // ���� ���� ��� ���ϱ� ���� �ӽú����� �����س��´�.

	while (1)
	{
		if (*(map[0] + i) != i + 1) // ���� ���� ������� �þ�� ���� ���Ͽ� ���� �߰��� Ʋ���� ������ Ż���Ѵ�.
			break;
		else if (i == MDIM * MDIM - 2)
		{				   // ���� �迭�� ũ���� ������ ���� DIM*DIM-2 �� �����ϸ� ����� �����ϰ� Ż��
			action = Stop; // ���� �ൿ�� �����ϰ� �� action�� Stop���� �ʱ�ȭ��Ų��.
			moveNum = 0;   // ���� �ൿ�� �����ϱ⶧���� �̵� ȸ���� �ʱ�ȭ ��Ų��.
			break;
		}
		i++;
	}
	if (action != Stop) // ������ ���߾����� ���� ��� Ű����� Ű�� �Է¹޴´�.
		switch (getDirectKey())
		{ // getDirectKey �Լ��� ���� Ű�� �Է¹ް� ��ɾ ���ڵ��� action�� �����Ѵ�.
		case ESC:
			action = Stop;
			moveNum = 0;
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
		sTime = clock(); // ���� ���� ���� �ð��� ��� �ʱ�ȭ ���������ν� �ð��� 0���� ���̵��� �Ѵ�.
		gameDraw();		 // ���� ���Ž�Ų��.
		Sleep(100);		 // �� ������ ���̵��� ���ð��� �ش�.
	}
}

int puzzleGame::solvable(void) // �������� �迭�� ������ Ǯ���ִ��� �Ǻ��ϴ� �Լ�
{
	int inv_count = 0, k = 0, temp; // ������ ���� �迭 ���� ���� ���� ����

	if (x != MDIM - 1 || y != MDIM - 1) // ���� ��ĭ�� ��ġ�� �� �Ʒ� �� ���������� �̵���Ų��.
	{
		temp = map[MDIM - 1][MDIM - 1];
		map[MDIM - 1][MDIM - 1] = 0;
		map[y][x] = temp;
		y = MDIM - 1;
		x = MDIM - 1;
	}

	for (int i = 0; i < MDIM * MDIM - 2; i++) // ������ ������ �Ϸķ� ������Ű�� ������ ���� ���� ����.
		for (int j = i + 1; j < MDIM * MDIM - 1; j++)
			if (*(map[0] + i) > *(map[0] + j))
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