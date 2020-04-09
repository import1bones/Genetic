#pragma once
#include"SimpleTest.h"
#define CHROMOSOME_MAX_SIZE 4
#define INDIVIDUAL_MAX_SIZE 100000
#define INDIVIDUAL_G_SIZE 1000
#define TIME 10000
struct Individual
{
	bool UseChromosome[CHROMOSOME_MAX_SIZE];
	int Fitness=0;
	int Live = 0;
	int Mutation = 16;
	float Weight_1[CHROMOSOME_MAX_SIZE];
	float Offset;
};
class ANN
{
public:
	ANN();
	~ANN();
private:
	void Inital();
	void GA();
	float Hidden(int Sept);
	float Activition(float s);
	float Calculate();
	int ChooseSept(float Sept_0, float Sept_1, float Sept_2);
	int Chromosome[CHROMOSOME_MAX_SIZE]; 
	void Compete();
	void Hybridize();
	void count(int t);
	void save();
	void PrintANN();

	Individual Sum[INDIVIDUAL_MAX_SIZE];
	SimpleTest DEMO;
	long int times[TIME];
	long int live[TIME];
	int hyb=0;
	int now;
};

