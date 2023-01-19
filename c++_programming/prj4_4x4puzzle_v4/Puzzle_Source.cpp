#include "Puzzle_Header.h"
// �и������ϵ� ��������� include�Ѵ�.

int main(void)
{
	puzzleGame gameBot;

	gameBot.shuffle(50); // 50�� ���´�

	gameBot.setCTime(clock());
	gameBot.setSTime(clock());
	// �����ϱ��� �ð� �ʱ�ȭ

	cout << gameBot;	  // ���� ȭ�� ���
	gameBot.getCommand(); // �Է�, ���� �ϼ� ���� Ȯ��

	while (gameBot.getAction()) // action�� Stop�̸� �ݺ����� ����ȴ�.
	{
		gameBot.puzzleMove(gameBot.getAction()); // �Էµ� Ű�� ���� ������ �ű��.
		gameBot.setCTime(clock());				 // ���� �ð��� �����Ѵ�.
		cout << gameBot;						 // ȭ�����
		gameBot.getCommand();					 // �Է�, ���� �ϼ� ���� Ȯ��
	}
	rectangle(gameBot.getPmap(), Point(240, 140), Point(600, 0), Scalar(239, 248, 250), -1);
	putText(gameBot.getPmap(), "Game Over!", Point(250, 130), 0, 1, Scalar(101, 110, 119), 4, LINE_AA);
	// ���� �ϼ� Ȥ�� ���� ����� ȭ�� ���� ��ܿ� "Game Over!" �ؽ�Ʈ �Է� �ߺ���� ���� ���� �簢�� �׸�
	cout << gameBot; // �ؽ�Ʈ�� �Էµ� ȭ�� ���
	waitKey(0);		 // Ű�� �Է� ���� ������ ����Ѵ�.

	return 0;
}