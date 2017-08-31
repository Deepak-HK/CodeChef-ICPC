#include<iostream>
#include "clear.h"
using namespace std;

int PlanetID(int, int, int);

int main()
{
	int Planets, Teleports, Queries, Planet_ID_1, Planet_ID_2, Universe_Num, Planet_Num, Path_1, Path_2, i, j;
	cin>>Planets>>Teleports>>Queries;

	//Dynamic memory allocation of Matrix
	long **Matrix = new long *[Planets * Planets];
	for(i=0; i < Planets * Planets; i++)
	{
		Matrix[i] = new long [Planets * Planets];
	}

	//Initializing Matrix elements to 0
	for(i=0; i < Planets * Planets; i++)
	{
		for(j=0; j < Planets * Planets; j++)
		{
			Matrix[i][j] = 0;
		}
	}

	//Intra-universe tunnels
	for(i=0; i < Planets - 1; i++)
	{
		cin>>Path_1>>Path_2;
		for(j=0; j < Planets * Planets; j += Planets)
		{
			Matrix[Path_1 - 1 + j][Path_2 - 1 + j] = 1;
			Matrix[Path_2 - 1 + j][Path_1 - 1 + j] = 1;
		}
	}

	//Inter-universe teleports
	for(i=0; i < Teleports; i++)
	{
		cin>>Planet_Num>>Universe_Num;
		Planet_ID_1 = PlanetID(Planet_Num, Universe_Num, Planets);
		cin>>Planet_Num>>Universe_Num;
		Planet_ID_2 = PlanetID(Planet_Num, Universe_Num, Planets);
		Matrix[Planet_ID_1 - 1][Planet_ID_2 - 1] = 1;
		Matrix[Planet_ID_2 - 1][Planet_ID_1 - 1] = 1;
	}

	for(i=0; i < Planets * Planets; i++)
	{
		cout<<endl<<endl;
		for(j=0; j < Planets * Planets; j++)
		{
			cout<<"\t"<<Matrix[i][j];
		}
	}

	return 0;
}

int PlanetID(int Planet_Num, int Universe_Num, int Planets)
{
	int Planet_ID;
	Planet_ID = ((Universe_Num - 1) * Planets) + Planet_Num;
	return Planet_ID;
}
