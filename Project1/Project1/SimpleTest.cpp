#include "SimpleTest.h"



SimpleTest::SimpleTest()
{
	for (int i = 1; i < SIZE + 2; i++)
	{
		maze[0][i] = -1;
		maze[i][0] = -1;
		maze[SIZE + 1][i] = -1;
		maze[i][SIZE + 1] = -1;
	}
	srand(unsigned(time(NULL)));
}


SimpleTest::~SimpleTest()
{
}

void SimpleTest::SetLevel(int t)
{
	level = t;
}

void SimpleTest::Build()
{
	x = SIZE, y = SIZE;
	for (int i = 1; i < SIZE+1; i++)
	{
		for (int j = 1; j < SIZE+1; j++)
		{
			maze[i][j] = -1;
		}
	}
	switch (level)
	{
	case 0:
		for (int i = 1; i < SIZE; i++)
		{
			maze[i][i] = (SIZE - i) + (SIZE - i);
			maze[i][i + 1] = (SIZE - i) + (SIZE - i - 1);
		}
		break;
	case 1:
		for (int i = 1; i < SIZE + 1; i++)
		{
			maze[1][i] = (SIZE - 1) + (SIZE - i);
			maze[i][SIZE] = (SIZE - i) + (SIZE - SIZE);
		}
		break;
	case 2:
		for (int i = 1; i < SIZE + 1; i++)
		{
			maze[i][1] = (SIZE - i) + (SIZE - 1);
			maze[SIZE][i] = (SIZE - SIZE) + (SIZE - i);
		}
		break;
	}
	maze[SIZE][SIZE] = 0;
}

void SimpleTest::PrintMaze()
{
	for (int i = 0; i < SIZE + 2; i++)
	{
		std::cout << i;
		for (int j = 0; j < SIZE + 2; j++)
		{
			if (maze[i][j] == -1)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << maze[i][j];
			}
		}
		std::cout << std::endl;
	}
}

bool SimpleTest::Move(int way)
{
	switch (way)
	{
	case 0:
		if (SimulationMove(x - 1, y))
		{
			x--;
			return true;
		}
		break;
	case 1:
		if (SimulationMove(x, y - 1))
		{
			y--;
			return true;
		}
		break;
	case 2:
		if (SimulationMove(x - 1, y - 1))
		{
			x--;
			y--;
			return true;
		}
		break;
	}
	return false;
}

int SimpleTest::GetInformation(char S, int M_X, int M_Y)
{
	switch (S)
	{
	case 'A':
		if (M_X - 1 >= 0 || M_Y - 1 >= 0)
		{
			return maze[M_X - 1][M_Y-1];
		}
		else
		{
			return -1;
		}
		break;
	case 'B':
		if (M_X - 1 >= 0 || M_Y >= 0)
		{
			return maze[M_X - 1][M_Y];
		}
		else
		{
			return -1;
		}
		break;
	case 'C':
		if (M_X >= 0 || M_Y - 1 >= 0)
		{
			return maze[M_X][M_Y - 1];
		}
		else
		{
			return -1;
		}
		break;
	case 'D':
		if (M_X >= 0 && M_Y >= 0)
		{
			return maze[M_X][M_Y];
		}
		else
		{
			return -1;
		}
		break;
	}
}

bool SimpleTest::SimulationMove(int S_x, int S_y)
{
	if (maze[S_x][S_y] != -1)
	{
		return true;
	}
	return false;
}
