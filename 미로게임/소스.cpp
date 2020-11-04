#include <iostream>
#include <conio.h>
using namespace std;

/*
0: ��
1: ��
2: ������
3: ������
4: ��ź

*/
struct _tagPoint
{
	int x;
	int y;

};
typedef _tagPoint POINT; // type�� ������
typedef _tagPoint* PPOINT;
void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pstartpos, PPOINT pEndpos)
	{
	pstartpos->x = 0;
	pstartpos->y = 0;

	pEndpos->x = 19;
	pEndpos->y = 19;

	*pPlayerPos = *pstartpos;
	strcpy_s(Maze[0], "1110000000000000000");
	strcpy_s(Maze[1], "0011111111100000000");
	strcpy_s(Maze[2], "0010010000011111110");
	strcpy_s(Maze[3], "0110010000000000010");
	strcpy_s(Maze[4], "0110011110000011110");
	strcpy_s(Maze[5], "0110000001111100000");
	strcpy_s(Maze[6], "0110000001000000000");
	strcpy_s(Maze[7], "0110000001000000000");
	strcpy_s(Maze[8], "0010000001000000000");
	strcpy_s(Maze[9], "0010000001111111000");
	strcpy_s(Maze[10],"0111111111000000000");
	strcpy_s(Maze[11], "000100011000000000");
	strcpy_s(Maze[12], "001100000111000000");
	strcpy_s(Maze[13], "000110000001111100");
	strcpy_s(Maze[14], "0011111000001000000");
	strcpy_s(Maze[15], "0010000000001000000");
	strcpy_s(Maze[16], "0010000011111110000");
	strcpy_s(Maze[17], "0011111110001000000");
	strcpy_s(Maze[18], "0010000000001110000");
	strcpy_s(Maze[19], "2110000000001111113");


	}
void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "��";
			else if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "��";
			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";
		}
		cout << endl;
	}
}
void Moveup(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y - 1 >= 0)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0'
			&& Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4')
		{
			--pPlayerPos->y;
		}

	}
}
void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y + 1 < 20)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y+1][pPlayerPos->x] != '0' && Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4')
		{
			++pPlayerPos->y;
		}

	}
}
void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x + 1 < 20)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayerPos-> y][pPlayerPos->x+1] != '0' && Maze[pPlayerPos->y ][pPlayerPos->x+1] != '4')
		{
			++pPlayerPos->x;
		}

	}
}
void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x - 1 < 20)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y][pPlayerPos->x -1] != '0' && Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4')
		{
			--pPlayerPos->x;
		}

	}
}
void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cinput)
{
	switch (cinput)
	{
	case'w':
	case 'W':
		Moveup(Maze, pPlayerPos);
		break;
	case's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;



	}
}
//������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21],const PPOINT pPlayer,PPOINT pBombArr, int*pBombCount)
{
	if (*pBombCount == 5)
		return;
	for (int i = 0; i < *pBombCount; ++i)
	{
	
		if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y)
			return;
	}
	pBombArr[*pBombCount] = *pPlayer;
	++(*pBombCount);
	Maze[pPlayer->y][pPlayer->x] = '4';
	

}
void Fire(char Maze[21][21],PPOINT pPlayer,PPOINT pBombArr, int *pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
		//�÷��̾ ��ź�� �¾��� �� ���������� ������.
		if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y)
		{
			pPlayer->x = 0;
			pPlayer->y = 0;
		}
		if (pBombArr[i].y-1>=0)
		{
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
	}
		if (pBombArr[i].y+1 <20)
		{
		
			if (Maze[pBombArr[i].y +1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y +1][pBombArr[i].x] = '1';
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		if (pBombArr[i].x - 1 >= 0)
		{
			
			if (Maze[pBombArr[i].y ][pBombArr[i].x-1] == '0')
				Maze[pBombArr[i].y ][pBombArr[i].x-1] = '1';
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		if (pBombArr[i].x + 1< 20)
		{

			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
	}
	*pBombCount = 0;
}

int main() {

	//20x20 �̷θ� ������ش�.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	int iBombCount = 0;
	

	POINT tBombPos[5];
	// �̷θ� �����Ѵ�.

	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	//�̷θ� ����Ѵ�
	while (true)
	{
		system("cls");
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�." << endl;
			break;
		}
		cout << "t: ��ź��ġ u: ��ź ��Ʈ����" << endl;
		cout << "w: �� s: �Ʒ� a: ���� d: ������ q: ����: ";
		char cinput = _getch();
		if (cinput == 'q' || cinput == 'Q')
			break;
		else if (cinput == 't' || cinput == 'T')
		{
			CreateBomb(strMaze, &tPlayerPos,tBombPos, &iBombCount);
		
		}
		else if (cinput == 'u' || cinput == 'U')
		{
			Fire(strMaze, &tPlayerPos, tBombPos, &iBombCount);

		}
		MovePlayer(strMaze, &tPlayerPos, cinput);
	}
	return 0;
}