#pragma once

#ifndef Puzzle_Header
#define Puzzle_Header

#include <iostream>
#include <ctime> //clock() �Լ� ���
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

#define FSIZE 120  // ���� �׸� �ϳ� ũ��
#define FSTARTX 30 // ���� �׸� ���� ��ġ x
#define FSTARTY 30 // ���� �׸� ���� ��ġ y
#define Psize 82   // �����Ǿ�� �� ������ ũ��

#define ESC 27		  // ���� ����
#define LEFT 2424832  // ���� ȭ��ǥ Ű ASCII��
#define RIGHT 2555904 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 2621440  // �Ʒ� ȭ��ǥ Ű ASCII��
#define UP 2490368	  // ���� ȭ��ǥ Ű ASCII��

#define MDIM 4			// 4x4 ������� ũ��
#define PDIM 7			// 7x7 ������ ũ��
#define PNUM MDIM *MDIM // �׸�ĭ�� ��

// ���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ����
#define MAP_STARTX 117
#define MAP_STARTY 206

enum COMMAND
{
	Stop = 0,
	Left,
	Right,
	Down,
	Up,
	Non
};
// action �� ���� ���� ����

class puzzleGame
{
public:
	puzzleGame();																 // default ������: Ŭ���� ��ü �ʱ�ȭ �Լ�, �ʿ�ÿ� �Ű������� �߰���
	~puzzleGame();																 // �Ҹ���: Ŭ���� ��ü�� �Ҹ����� �����Ҵ��� ������ ���� ��ü�� ������ ���� ����
	friend ostream &operator<<(ostream &outputStream, const puzzleGame &gmBot);	 // gameDrawd ����Լ� ��ſ� << ������ �����ε��� ���� ����Ͻÿ�.
	void puzzleDraw(Mat Mapping, const Mat Puzzle[], int x, int y, int k) const; // �ϳ��� ������ �׸��� ����Լ�
	void puzzleMove(int moveKey);												 // ���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
	void shuffle(int num);														 // ���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
	void getCommand(void);														 // ��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
																				 //  ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
																				 // �ʿ�ÿ� �Ű����� ���ڸ� �߰��� �� ����
	int getAction(void) const { return action; };								 // �����Լ����� action�� ���� �д´�.
	int solvable(void);															 // Ǯ �� �ִ� �������� �Ǻ��ϴ� �Լ�
	void setCTime(clock_t ct) { cTime = ct; };									 // cTime���� �ζ��� �Լ�
	void setSTime(clock_t st) { sTime = st; };									 // sTime���� �ζ��� �Լ�
	string Point2(string nums) const;											 // �Ҽ��� ���ڸ����� ����ϱ����� �Լ�
	Mat getPmap() { return this->Pmap; };										 // �����Լ����� Pmap�� �θ��� �ʿ��� �Լ�
private:
	Mat Puzzle_num, Pmap; // ���� ��ü �� ���� Puzzle_num, ��ü ���� ���� Pmap
	Mat Num16[PNUM];	  // 1~15, ��ĭ�� �����ϱ� ���� Num[16] �迭
	int **map;			  // map �����Ҵ����� ����

	int action;	   // ������ ���� ����
	int x, y;	   // ��ĭ�� ��ġ
	int moveNum;   // �̵�ȸ��
	clock_t sTime; // ���� �ð�
	clock_t cTime; // ���� �ð�
};
#endif // !Puzzle_Header
