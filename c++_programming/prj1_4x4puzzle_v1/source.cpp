#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetCursorConsolePosition() �Լ� ���
#include <conio.h> //_getch()�� kbhit() �Լ� ���
#include <ctime> //clock() �Լ� ���
#include <stdlib.h> //ȭ���� ������ ����� �Լ� system("cls") ���

//��� �����
#define ESC 27 //���� ����
#define LEFT 75 //���� ȭ��ǥ Ű ASCII��
#define RIGHT 77 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 80 //�Ʒ� ȭ��ǥ Ű ASCII��
#define UP 72 //���� ȭ��ǥ Ű ASCII��
#define DIM 4 //4x4 ������� ũ��

//���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define MAP_STARTX 24
#define MAP_STARTY 9

//�̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define SCORE_STARTX 45
#define SCORE_STARTY 21

static int x, y; //��ĭ�� ��ġ
static int moveNum; //�̵�ȸ��
static clock_t sTime; //���� �ð�

//���� ���� ���� �ȳ� ǥ�� ��ġ����
static int indentx = 11+MAP_STARTX; 
static int indenty = 10+MAP_STARTY;

using namespace std;

//�Լ� �����
void gotoXY(short x, short y); //�ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void init(int(*gotmap)[DIM]); //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
void gameDraw(int (*gotmap)[DIM]); // ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�; MAP_STARTX, MAP_STARTY ����� ������
				//�׻� ���� ��ġ(gotoXY�Լ� ��뿡 ����ʿ�ÿ� �Ű������� �߰���
				//                ȭ�� ��� ����
				//                Fifteen Puzzle
				//                  1  2  9  3
				//                  6  8  7  4
				//                  10    5  15
				//                  13 14 12 11
				//
				//                  �̵� ȸ��: 10ȸ
				//                  �ҿ� �ð�: 15.2��

void puzzleMove(int action, int(*gotmap)[DIM]); //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
void shuffle(int num, int(*gotmap)[DIM]);//���� �� �ʱ�ȭ; 50ȸ ������ �̵�
int getAction(int (*gotmap)[DIM]);//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
								  // ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
int getDirectKey(); //����Ű ȹ�� �Լ�
void print_time_and_movenum(void); //������ ���۵� �� �ú��ʿ� ������ ȸ�� ǥ���ϴ� �Լ�
int solvable(int(*gotmap)[DIM]); //������ ������ Ǯ���ִ��� �Ǵ��ϴ� �Լ�

int main(void)
{
	int map[DIM][DIM]; //�� ũ�⸦ ����
	int action = 1; //Ű������ ���� �޴� ����

	init(map); //�� ó�� ���� �ʱ�ȭ ��Ų��
	gameDraw(map); //���� �׸��� �Լ��� ȣ���Ѵ�.
	Sleep(1000); //�ʱ������ ���� �����ֱ� ���� 1�ʰ� �����.
	gotoXY(indentx,indenty); //"���� ��" �ȳ� ǥ�ø� ���� Ŀ���� ��ǥ�� �̵��Ѵ�.
	cout << "���� ��";
	shuffle(50, map); //���ڷ� 50�� �Ѱ� 50�� ���̰Բ� �Ѵ�.
	
	gotoXY(indentx, indenty); //�ȳ�ǥ�ø� ���� �̵��Ѵ�.
	cout << "���� �Ϸ�"; //�ȳ� �޽��� ���
	gotoXY(indentx,indenty); //����
	cout << "���� ����!"; //����

	sTime = clock(); // �ҿ�ð� ����� ���� ������ ���� �ð��� ����صд�.

	while (1) {
		action = getAction(map); // ������ Ǯ�ȴ��� �Ǻ��ϰ� Ű�� �Է¹޴´�.
		if (action == 2) { //������ ���߾��� �� �׿� ���� �ȳ��� �ϸ� ������ Ż���Ѵ�.
			system("cls");
			gameDraw(map);
			gotoXY(indentx, indenty);
			cout << "���� �ϼ�!";
			break;
		}
		else if (action == 1) {
			gotoXY(MAP_STARTX, indenty); //�߸��� Ű�� �Է¹����� �׿� ���� �ȳ��� ǥ���Ѵ�.
			cout << "����Ű Ȥ�� ESCŰ�� �Է��ϼ���!";
		}
		else if (action == 0) {//ESCŰ�� �Է¹޾����� �ȳ��ϸ� �����Ѵ�.
			system("cls");
			gameDraw(map);
			gotoXY(indentx, indenty);
			cout << "���� ����!";
			break;
		}
		else {
			puzzleMove(action, map); //�Է¹��� �������� ������ �̵���Ų��.
			moveNum++; //������ �̵��߱� ������ �̵� Ƚ���� 1���Ѵ�.
		}
		gameDraw(map); //�ٽ� ���� �����Ѵ�.
	}

	Sleep(1000); //ȭ���� ��������� ����� ���ð��� �ش�.
	system("cls"); //�ܼ�ȭ���� �ʱ�ȭ��Ų��.
	init(map); //�迭�� �ð�, �̵� Ƚ���� �ʱ�ȭ ��Ų��.
	gameDraw(map); //���� �����Ѵ�.
	gotoXY(indentx, indenty); //�������� �ȳ� �޽����� ǥ���ϱ����� �̵��Ѵ�.
	cout << "���� ����\n\n\n\n\n\n\n\n\n\n" ;
	
	return 0;
}

//�ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void gotoXY(short x, short y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �׿� �Լ����� ������

void init(int(*gotmap)[DIM]) //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
{
	for (int i = 0; i < DIM*DIM; i++) // ���� ���� 1,2,3,~�� ������ �ʱ�ȭ ��Ų��. 
		*(gotmap[0] + i) = i;

	sTime = clock(); //���۽ð��� �ʱ�ȭ ��Ų��.
	moveNum = 0; //�̵� ȸ���� �ʱ�ȭ��Ų��.
}

void gameDraw(int(*gotmap)[DIM]) // ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�; MAP_STARTX, MAP_STARTY ����� �����ؼ�
{								//�׻� ���� ��ġ(gotoXY�Լ� ��뿡 ����ʿ�ÿ� �Ű������� �߰���
	gotoXY(MAP_STARTX + 7, MAP_STARTY); //������ �̸��� ����ϱ� ���� �̵��Ѵ�.
	cout << "Fifteen Puzzle";

	for (int i = 0; i < DIM; i++) //�迭�� ����� ������ ����Ѵ�.
	{
		gotoXY(MAP_STARTX, MAP_STARTY + 2 + i * 2); //������ 2ĭ���� ����Ѵ�.
		for (int j = 0; j < DIM; j++)
		{
			if (gotmap[i][j] == 0) //���� ó���� ���� 0�� �ڸ��� ���� ��ȣ'*�� ����Ѵ�.
				cout << '*' << "\t";//0�� ���� '*'�� ����Ѵ�.
			else
				cout << gotmap[i][j] << "\t"; //�Ϲ� ������ ���ڸ� ����Ѵ�.
		}
	}
	print_time_and_movenum(); //�ҿ�� �ð��� �̵�Ƚ���� ����Ѵ�.
}

void puzzleMove(int action,int(*gotmap)[DIM]) //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
{
	int temp = 0; //���� ��ȯ�ϱ� ���� �ӽ÷� ������ ���� ����

	switch (action) //Ű���忡�� �Է¹��� Ű���� ���� �������� �迭�� ���� �ٲ۴�.
	{
	case LEFT:
		if (x >= 1) { //���� ó���� ���� ���� '*'�� ��ġ�� ���� ����� �ʵ��� �Ѵ�.
			temp = gotmap[y][x];
			gotmap[y][x] = gotmap[y][x - 1];
			gotmap[y][x - 1] = temp;
			x--;
		}
		break;

	case RIGHT:
		if (x <= 2) {
			temp = gotmap[y][x];
			gotmap[y][x] = gotmap[y][x + 1];
			gotmap[y][x + 1] = temp;
			x++;
		}
		break;

	case UP:
		if (y >= 1) {
			temp = gotmap[y][x];
			gotmap[y][x] = gotmap[y-1][x];
			gotmap[y-1][x] = temp;
			y--;
		}
		break;

	case DOWN:
		if (y <= 2) {
			temp = gotmap[y][x];
			gotmap[y][x] = gotmap[y+1][x];
			gotmap[y+1][x] = temp;
			y++;
		}
		break;

	default:
		break; //�ƹ��͵� �ƴϸ� �׳� switch�� Ż���Ѵ�.
	}
}

void shuffle(int num, int(*gotmap)[DIM])
{
	int numcheck[DIM*DIM]; //�迭�� ���� �ߺ��Ǿ����� üũ�ϱ����� �ʰ� ������ ũ���� �迭�� �����Ѵ�.
	int random = 0; //������ ������ ������ ���� �����̴�.

	srand(time(NULL)); //������ �õ� ���� �ٲپ� �����ν� ���� ������ �Ѵ�.

	for (int k = 0; k < num; k++)
	{
		while (1) {
			for (int i = 0; i < DIM*DIM; i++)
				numcheck[i] = 1; //���� �����ϱ����� �ߺ�üũ �迭�� ���Ǳ� �� ������ '1'�� �ʱ�ȭ ��Ų��.

			for (int i = 0; i < DIM; i++)
				for (int j = 0; j < DIM; j++)
					while (1) {
						if ((numcheck[random = (rand() % (DIM*DIM))]) != 0) {
							if (random == 0) { //���� ������ ���� '*'�� ��ǥ�� 9�̶�� ���� �迭 ��ǥ�� �����Ѵ�.
								x = j; //'*'�� ��ġ�� �����ϱ� ���� �������� x,y�� 2���� �迭�� ��ǥ�� �����Ѵ�.
								y = i;
							}
							gotmap[i][j] = random;
							numcheck[random] = 0;
							break;
						} //������ ������ ������ ���� �����̸� ��� ǥ�ø� �ϰ� �迭�� �����ϸ� ������ Ż���Ѵ�.
					}	  // ������ ��� ���̸� numcheck�� 1�� ���·�, �ĸ� 0�� ���·� ����ȴ�.

			if (solvable(gotmap) == 1) //������ Ǯ�� ���ϴ� ���� ���� �� �ִ�. Ǯ �� �ִ��� �Ǻ��Ͽ�
				break;				   //Ǯ �� ������ 1�� �����ϸ� Ǯ�����ϸ� 0�� �����ϰ� �ٽ� ���´�.
		}
		sTime = clock(); //���� ���� ���� �ð��� ��� �ʱ�ȭ ���������ν� �ð��� 0���� ���̵��� �Ѵ�.
		gameDraw(gotmap); //���� ���Ž�Ų��.
		Sleep(100); //�� ������ ���̵��� ���ð��� �ش�.
	}
}

int getAction(int(*gotmap)[DIM]) //��� ������ �� ��ġ�� ������ 2�� ESCŰ�� ���������� ���� 0�� ��ȯ 
{								// ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
	int i = 0; //���� ���� ��� ���ϱ� ���� �ӽú����� �����س��´�.

	while(1){
		if (*(gotmap[0] + i) != i + 1) //���� ���� ������� �þ�� ���� ���Ͽ� ���� �߰��� Ʋ���� ������ Ż���Ѵ�.
			break;
		else if(i == DIM*DIM - 2) //���� ������� �þ�� ���� �迭�� ũ���� ������ ���� DIM*DIM-2 �� �����ϸ� 2�� �����Ѵ�.
			return 2; 
		i++;
	}

	switch (getDirectKey()) { //Ű�� �Է¹޴� �Լ��� ���� Ű�� �Է¹ް� Ű�� ���� ���� �����Ѵ�.
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
		return 1; // ����Ű�� ESCŰ���� �ٸ�Ű�� �ԷµǸ� 1�� �����Ѵ�.
	}
}

int getDirectKey(void)//����Ű ȹ�� �Լ�
{
	int input = _getch(); //input ������ ���� �Էµ� Ű ���� �����Ѵ�.

	if (input == 224) //����Ű�� ù 1����Ʈ�� 224�� ���� ������ �̷� ����Ű������ �Ǻ��Ѵ�.
		return _getch(); //����Ű�� 2����Ʈ �̹Ƿ� ������ 1����Ʈ�� �ƽ�Ű �ڵ� ���� �����Ѵ�.
	else if (input == 27) //ESC�� �ƽ�Ű �ڵ� ���� �Է¹����� ESC�� �ƽ�Ű �ڵ� ���� �����Ѵ�.
		return ESC;
	else
		return 1; // ESC�� ����Ű �̿��� Ű�� �Է� ������ 1�� �����Ѵ�.
}

void print_time_and_movenum(void) //�̵� Ƚ���� �ҿ�ð��� ����ϴ� �Լ�
{
	double time_flowed = (double)(clock() - sTime) / 1000; //���� �帥 �ð��� double���·� �Ҽ������� �����Ѵ�.
	int s = time_flowed, m = s / 60, h = m / 60; //�� �� �� ������ �ð��� ������.

	gotoXY(SCORE_STARTX, SCORE_STARTY); //�̵� Ƚ���� �ҿ� �ð��� ����ϴ� ��ǥ�� �̵��Ͽ� ������ ����Ѵ�.
	cout << "�̵� Ƚ�� : " << moveNum << "ȸ";
	gotoXY(SCORE_STARTX, SCORE_STARTY + 1);
	cout << "�ҿ� �ð� : ";

	if (h > 0) //1�ð��� �Ѿ�� �� �� �� ��� ����Ѵ�.
		cout << h << "�ð� " << m << "�� ";
	else if (m > 0)  //1�к��� ���� �帣�� 1�ð����� ���� �帣�� �� �ʸ� ����Ѵ�. 
		cout << m << "�� ";
	else {}  //���� ��쿡 �ش����� ������ �׳� ����Ѵ�.

	//�Ҽ��� ù° �ڸ����� �ҿ�ð� �ʸ� ����Ѵ�.
	cout.setf(ios::fixed);
	cout.precision(1);
	cout << (double)(s % 60 + (time_flowed - s)) << "��" << endl;
	cout.unsetf(ios::fixed);
}

int solvable(int(*gotmap)[DIM]) //�������� �迭�� ������ Ǯ���ִ��� �Ǻ��ϴ� �Լ� 
{
	int inv_count = 0, k = 0,temp; //������ ���� �迭 ���� ���� ���� ����
	
	if (x != DIM - 1 || y != DIM - 1) //���� '*'ǥ�� ��ġ�� �� �Ʒ� �� ���������� �̵���Ų��.
	{
		temp = gotmap[DIM-1][DIM-1];
		gotmap[DIM - 1][DIM - 1] = 0;
		gotmap[y][x] = temp;
		y = DIM - 1;
		x = DIM - 1;
	}

	for (int i = 0; i < DIM* DIM - 2; i++) //������ ������ �Ϸķ� ������Ű�� ������ ���� ���� ����.
		for (int j = i + 1; j < DIM * DIM-1; j++)
			if (*(gotmap[0] + i) > *(gotmap[0] + j))
				inv_count++;

	if (inv_count % 2 == 1) //���� ������ ���� ���� Ȧ�� ���̸� Ǯ �� ���� �����̸� 0�� �����Ѵ�.
		return 0;
	else
		return 1; //¦�� ���̸� Ǯ �� �ִ� �����̸� 1�� �����Ѵ�.
}