#pragma once
#include<iostream>
#include<time.h>
#include<fstream>
#define SIZE 100
class SimpleTest
{
public:
	SimpleTest();
	~SimpleTest();
	void SetLevel(int t);
	void Build();
	void PrintMaze();
	bool Move(int way);
	int GetInformation(char S, int M_X, int M_Y);
	int x, y;
private:
	bool SimulationMove(int S_x, int S_y);
	int level;
	int maze[SIZE + 2][SIZE + 2];
};

