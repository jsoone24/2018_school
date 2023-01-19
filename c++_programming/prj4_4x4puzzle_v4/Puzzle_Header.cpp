#include <conio.h> //getch()�� kbhit() �Լ� ���
#include <fstream>
#include <windows.h>	   //GetStdHandle(), Sleep(), SetConsoleCursorPosition() �Լ� ���
#include "Puzzle_Header.h" //�и�������

ostream &operator<<(ostream &outputStream, const puzzleGame &gmBot) // gameDrawd ����Լ� ��ſ� << ������ �����ε��� ���� ����Ͻÿ�.
{
	namedWindow("Puzzle_Game", CV_WINDOW_AUTOSIZE); // â �̸� ������ ����

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			gmBot.puzzleDraw(gmBot.Pmap, gmBot.Num16, MAP_STARTX + 95 * j, MAP_STARTY + 95 * i, gmBot.map[i][j]);
	// puzzleDraw �Լ� ȣ���� ���� ���.

	float timeing = (gmBot.cTime - gmBot.sTime) / 1000.00, temp; // �ҿ�ð� ���

	string time = gmBot.Point2(to_string(timeing)); // ���ڸ� �� ���� ��µǰ� �޺κ��� �ڸ�
	string move = to_string(gmBot.moveNum);
	// putText�Լ� ������� �ð��� string������ �ٲ۴�.

	Size timetext = getTextSize(time, 0, 1, 2, 0);
	Size movetext = getTextSize(move, 0, 1, 2, 0);
	Point timepoint, movepoint;

	movepoint.x = 185 - movetext.width / 2;
	movepoint.y = 690;
	timepoint.x = 415 - timetext.width / 2;
	timepoint.y = 690;
	// �ð��� �̵�Ƚ���� ���� �Ʒ����Ͱ��ƴ� �߰�������µǰ� �ϱ����� �ؽ�Ʈũ�⸦ ��� �߰����� �����.

	rectangle(gmBot.Pmap, Point(97, 655), Point(270, 700), Scalar(160, 173, 187), -1);
	rectangle(gmBot.Pmap, Point(327, 653), Point(500, 700), Scalar(160, 173, 187), -1);
	// �̵�Ƚ���� �ð� ��½� �̹����� �ߺ��Ǿ� ��µǴ� ������ �߻��ϴµ� �̸� �����ϱ� ����
	// ��ø�Ǵ� �κп� ����ؼ� ���� ���� ������ ä���� �簢���� �׸���.

	putText(gmBot.Pmap, time, timepoint, 0, 1, Scalar(255, 255, 255), 2, LINE_AA);
	putText(gmBot.Pmap, move, movepoint, 0, 1, Scalar(255, 255, 255), 2, LINE_AA);
	// ������ ��ġ�� �ð��� �̵�Ƚ���� ����Ѵ�.

	imshow("Puzzle_Game", gmBot.Pmap);
	waitKey(100);
	// �̹����� â�� ǥ���ϸ� ���̰� �ϱ����� 0.1���� ���ð��� �ο��Ѵ�.

	return outputStream;
}

puzzleGame::puzzleGame()
{
	Pmap = imread("./Map.png", CV_LOAD_IMAGE_COLOR);
	// ��濡 ���� ������ Mat���� Pmap�� �����Ѵ�.

	Puzzle_num = imread("./Num.png", CV_LOAD_IMAGE_COLOR);
	Rect temp;
	int num = 0;
	// Draw circles on the detected faces
	for (int i = 0; i < PNUM / 4; i++)
	{
		for (int j = 0; j < PNUM / 4; j++)
		{
			temp.x = FSTARTX + (FSIZE + 20) * j;
			temp.y = FSTARTY + (FSIZE + 20) * i;
			temp.width = FSIZE;
			temp.height = FSIZE;
			resize(Puzzle_num(temp).clone(), Num16[num++], Size(Psize, Psize));
		}
	}
	// ���ڿ� ���� ������ Mat���� Puzzle_num�� �����Ѵ�.
	// �ҷ��� �̹������� �簢���� ������ �����ϰ� ������ ���ڵ��� Num16�迭�� �����Ѵ�.

	map = new int *[MDIM]; // ������ �����͸� �����Ҵ� �Ѵ�.

	for (int i = 0; i < MDIM; i++)
		map[i] = new int[MDIM]; // ������ �����͸� �����Ҵ��Ѵ�.

	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			map[i][j] = i * 4 + j;
	// ���� �� �����Ҵ� �� �� �Ҵ�
	x = MDIM - 1;
	y = MDIM - 1;
	// ���� ���� 1,2,3,~ ,MDIM*MDIM-1,0�� ������ �ʱ�ȭ ��Ű�� ��ĭ�� ��ġ�� ���������� �ʱ�ȭ��Ų��.
	sTime = 0.00; // ���۽ð��� �ʱ�ȭ ��Ų��.
	moveNum = 0;  // �̵� ȸ���� �ʱ�ȭ��Ų��.

	// ���� �ʱ�ȭ �ڵ� �ۼ�
}

puzzleGame::~puzzleGame()
{
	for (int i = 0; i < MDIM; i++)
		delete[] map[i]; // �迭 �����͸� �ʱ�ȭ�Ѵ�.

	delete[] map; // �迭 �����͸� �ʱ�ȭ�Ѵ�.
}

void puzzleGame::puzzleDraw(Mat Mapping, const Mat Puzzle[], int x, int y, int k) const
{ // ���ڰ� �׷��� �̹����� ���� �̹���, �Է��� ��ġ, �Է��� ���ڸ� �Է¹޴´�.
	Mat imageROI = Mapping(Rect(x, y, Psize, Psize));
	// ���� ROI ����
	// Rect�� �簢�� ���� ����
	// x, y�� ���� ���� ũ���� x��ǥ, y��ǥ ��������
	// Psize�� ���� �ϳ� �̹����� ���� ���� ũ��

	Puzzle[k].copyTo(imageROI);
	// ������ ���ɿ����� ���� �ϳ� �̹����� �����Ͽ� ���δ�.
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
			if ((map[i][j] != i * 4 + j) && (i * j < (MDIM - 1) * (MDIM - 1)))
			{
				Flag = TRUE;
			}
		} // �߰��� Ʋ�� �κ��� �߻��ϸ� Flag�� TRUE�� �����ȴ�.
	if (Flag == FALSE)
		action = Stop; // ������ �� ������ action �� Stop���� �Ѵ�.

	if (action != Stop)
	{ // ������ ���߾����� ���� ��� Ű����� Ű�� �Է¹޴´�.
		switch (cvWaitKey(0))
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
}

void puzzleGame::shuffle(int num)
{
	int numcheck[MDIM * MDIM]; // �迭�� ���� �ߺ��Ǿ����� üũ�ϱ����� �ʰ� ������ ũ���� �迭�� �����Ѵ�.
	int random = 0;			   // ������ ������ ������ ���� �����̴�.

	srand(time(NULL)); // ������ �õ� ���� �ٲپ� �����ν� ���� ������ �Ѵ�.

	putText(Pmap, "Shuffling...", Point(250, 130), 0, 1, Scalar(101, 110, 119), 4, LINE_AA);
	// ���� �ִٴ� �ȳ����� ����Ѵ�.

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
							if (random == 15)
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
		cTime = sTime = 0.00; // ���� ���� ���� �ð��� ��� �ʱ�ȭ ���������ν� �ð��� 0���� ���̵��� �Ѵ�.
		cout << *this;		  // ���� Ŭ������ ����ϱ� ���� this�����͸� ����Ѵ�.
		Sleep(100);			  // �� ������ ���̵��� ���ð��� �ش�.
	}
	rectangle(Pmap, Point(240, 140), Point(600, 0), Scalar(239, 248, 250), -1);
	putText(Pmap, "Start!", Point(250, 130), 0, 1, Scalar(101, 110, 119), 4, LINE_AA);
	// �����϶�� �ȳ������� ����ϸ� ������ �ߺ������ �������� ���� ������ ���� �簢���� �׸���.
}

int puzzleGame::solvable(void) // �������� �迭�� ������ Ǯ���ִ��� �Ǻ��ϴ� �Լ�
{
	int inv_count = 0, k = 0, temp, t_arr[MDIM * MDIM]; // ������ ���� �迭 ���� ���� ���� ����

	if (x != MDIM - 1 || y != MDIM - 1) // ���� ��ĭ�� ��ġ�� �� �Ʒ� �� ���������� �̵���Ų��.
	{
		temp = map[MDIM - 1][MDIM - 1];
		map[MDIM - 1][MDIM - 1] = MDIM * MDIM - 1;
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
	// ������ �迭���� ���� ���������� ���ϸ� ������ ���� ���� ����.

	if (inv_count % 2 == 1) // ���� ������ ���� ���� Ȧ�� ���̸� Ǯ �� ���� �����̸� 0�� �����Ѵ�.
		return 0;
	else
		return 1; // ¦�� ���̸� Ǯ �� �ִ� �����̸� 1�� �����Ѵ�.
}

string puzzleGame::Point2(string nums) const
{				 // �Ҽ��� ���ڸ����� ����ϱ� ���� �Լ��̴�.
	string temp; // �ӽ� string temp�� �����Ѵ�.
	temp = nums.substr(0, nums.find(".") + 3);
	// ���ڿ�����.find�� ���� .�� ��ġ�� ã�� .substr�� ���� 0��° �ε������� .���� 3���� ���ڿ���
	// ����ϸ� �Ҽ��� ���ڸ����� ����ϰ� �ȴ�. �̸� temp�� ������ temp�� �����Ѵ�.
	return temp;
}