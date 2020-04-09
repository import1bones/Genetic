#include "ANN.h"

ANN::ANN()
{
	srand(unsigned(time(NULL)));
	Inital();
	GA();
	PrintANN();
}


ANN::~ANN()
{

}

void ANN::Inital()
{
	float mid;
	for (int i = 0; i < INDIVIDUAL_MAX_SIZE; i++)
	{
		for (int j = 0; j < CHROMOSOME_MAX_SIZE; j++)
		{
			mid = rand() % 512+1;
			if (rand()%2)
			{
				Sum[i].Weight_1[j] = mid / 100;
			}
			else
			{
				Sum[i].Weight_1[j] = mid / 100 * -1;
			}
		}
		Sum[i].Offset = rand() % 100 / 10;
		
	}
}

void ANN::GA()
{
	int Sept,level;
	bool live;
	for (int i = 0; i < TIME; i++)
	{
		//if (i % 10)
		//{
		//	level = 0;
		//	DEMO.SetLevel(level);
		//}
		level = 1;
		DEMO.SetLevel(level);

		for ( now = 0; now < INDIVIDUAL_MAX_SIZE; now++)
		{
			Sum[now].Fitness = 0;
			DEMO.Build();
			do
			{
				Sept=ChooseSept(Activition(Hidden(0)), Activition(Hidden(1)), Activition(Hidden(2)));
				if (Sept != 3)
				{
					if (DEMO.Move(Sept))
					{
						live = true;
						Sum[now].Fitness++;
						if (Sum[now].Fitness >= 100)
						{
							Sum[now].Fitness = (Sum[now].Fitness - 99)*(Sum[now].Fitness - 99) + 100;
						}

					}
					else
					{
						live = false;
					}
				}
				else
				{
					live = false;
					Sum[now].Fitness--;
				}
			} while (live);
		death:
			;
		}
		count(i);
		Compete();
		Hybridize();
		if (i % 100 == 0)
		{
			save();
			std::cout << "Hybridize:" << hyb << std::endl;
			hyb = 0;
		}
	}
	PrintANN();
}

float ANN::Hidden(int Sept)
{
	float R_Value = 0;
	switch (Sept)
	{
	case 0:
		Chromosome[0] = DEMO.GetInformation('A', DEMO.x - 1, DEMO.y);
		Chromosome[1] = DEMO.GetInformation('B', DEMO.x - 1, DEMO.y);
		Chromosome[2] = DEMO.GetInformation('C', DEMO.x - 1, DEMO.y);
		Chromosome[3] = DEMO.GetInformation('D', DEMO.x - 1, DEMO.y);
		break;
	case 1:
		Chromosome[0] = DEMO.GetInformation('A', DEMO.x, DEMO.y - 1);
		Chromosome[1] = DEMO.GetInformation('B', DEMO.x, DEMO.y - 1);
		Chromosome[2] = DEMO.GetInformation('C', DEMO.x, DEMO.y - 1);
		Chromosome[3] = DEMO.GetInformation('D', DEMO.x, DEMO.y - 1);
		break;
	case 2:
		Chromosome[0] = DEMO.GetInformation('A', DEMO.x - 1, DEMO.y - 1);
		Chromosome[1] = DEMO.GetInformation('B', DEMO.x - 1, DEMO.y - 1);
		Chromosome[2] = DEMO.GetInformation('C', DEMO.x - 1, DEMO.y - 1);
		Chromosome[3] = DEMO.GetInformation('D', DEMO.x - 1, DEMO.y - 1);
		break;
	}
	R_Value = Calculate();
	return R_Value;
}

float ANN::Activition(float s)
{
	if (s > 0)
	{
		s = s * s;
	}
	else
	{
		s = 0;
	}
	return s;
}

float ANN::Calculate()
{
	float R_V = 0;
	for (int j = 0; j < CHROMOSOME_MAX_SIZE; j++)
	{
		R_V += Chromosome[j] * Sum[now].Weight_1[j];
	}
	R_V += Sum[now].Offset;
	return R_V;
}

int ANN::ChooseSept(float Sept_0, float Sept_1, float Sept_2)
{
	if (Sept_0 > Sept_1&&Sept_0 > Sept_2)
	{
		return 0;
	}
	else if (Sept_1 > Sept_0&&Sept_1 > Sept_2)
	{
		return 1;
	}
	else if(Sept_2 > Sept_0&&Sept_2 > Sept_1)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

void ANN::Compete()
{
	Individual mid;
	for (int i = 0; i < INDIVIDUAL_MAX_SIZE; i++)
	{
		for (int j = INDIVIDUAL_MAX_SIZE - 1; j > i + 1; j--)

		{
			if (Sum[j].Fitness > Sum[j - 1].Fitness)
			{
				mid = Sum[j];
				Sum[j] = Sum[j - 1];
				Sum[j - 1] = mid;
			}
		}
	}
	for (int i = 0; i < INDIVIDUAL_G_SIZE; i++)
	{
		Sum[i].Live++;
	}
}

void ANN::Hybridize()
{
	int father, mather = 0;
	int nature;
	for (int i = INDIVIDUAL_G_SIZE; i < INDIVIDUAL_MAX_SIZE; i++)
	{
		Sum[i].Live = 0;
		father = rand() % INDIVIDUAL_G_SIZE;
		mather = rand() % INDIVIDUAL_G_SIZE;
		for (int j = 0; j < CHROMOSOME_MAX_SIZE; j++)
		{
			nature = rand() % 100;
			if (nature <= 50)
			{
				Sum[i].Weight_1[j] = Sum[father].Weight_1[j];
				if (nature < (Sum[father].Mutation/10))
				{
					if (nature % 2 == 0)
					{
						Sum[i].Weight_1[j] += (nature % 10)/10;
					}
					else
					{
						Sum[i].Weight_1[j] -= (nature % 10) / 10;
					}
					if (Sum[father].Mutation < 50)
					{
						Sum[father].Mutation += nature % 10;
					}
					hyb++;
				}
			}
			else
			{
				Sum[i].Weight_1[j] = Sum[mather].Weight_1[j];
				if (nature > 99-(Sum[mather].Mutation/10))
				{
					if (nature % 2 == 0)
					{
						Sum[i].Weight_1[j] += (nature % 10)/10;
					}
					else
					{
						Sum[i].Weight_1[j] -= (nature % 10) / 10;

					}
					if (Sum[mather].Mutation < 50)
					{
						Sum[mather].Mutation += nature % 10;
					}
					hyb++;
				}
			}
		}
	}
}

void ANN::count(int t)
{
	times[t] = 0;
	live[t] = 0;
	for (int i = 0; i < INDIVIDUAL_MAX_SIZE; i++)
	{
		times[t] += Sum[i].Fitness;
		live[t] += Sum[i].Live;
	}
	std::cout << t <<" Best: "<<Sum[0].Fitness<< " Fitness: " << times[t] << " live: " << live[t] << std::endl;

}

void ANN::save()
{
	std::ofstream outfile("individual.dat");
	for (int i = 0; i < INDIVIDUAL_G_SIZE; i++)
	{
		for (int j = 0; j < CHROMOSOME_MAX_SIZE; j++)
		{
			outfile << Sum[i].Weight_1[j] << " ";
		}
		outfile << Sum[i].Offset << std::endl;
	}
}

void ANN::PrintANN()
{
	for (int i = 0; i < INDIVIDUAL_G_SIZE; i++)
	{
		std::cout << i << " ";
		for (int j = 0; j < CHROMOSOME_MAX_SIZE; j++)
		{
			std::cout << Sum[i].Weight_1[j] << " ";
		}
		std::cout << std::endl;
	}
}


