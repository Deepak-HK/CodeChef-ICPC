#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned int uint;

struct Planets
{
	uint P1, P2;
};

uint PlanetID(uint, uint, uint);
uint ShortestPath(Planets *, uint, uint, uint, uint, uint);

int main()
{
	uint N, M, U, P1, P2, i, j, SObj = 0;
	int Q;

	cin>>N>>M>>Q;

	uint **Tunnels = new uint *[N-1];
	for(i=0; i < N-1; i++)
	{
		Tunnels[i] = new uint [2];

	}
	uint **Teleports = new uint *[M];
	for(i=0; i < M; i++)
	{
		Teleports[i] = new uint [4];
	}

	uint **Queries = new uint *[Q];
	for(i=0; i < Q; i++)
	{
		Queries[i] = new uint [4];
	}

	uint *PathLength = new uint [Q];

	for(i=0; i < N-1; i++)
	{
		for(j=0; j < 2; j++)
		{
			cin>>Tunnels[i][j];
		}
	}

	for(i=0; i < M; i++)
	{
		for(j=0; j < 4; j++)
		{
			cin>>Teleports[i][j];
		}
	}

	for(i=0; i < Q; i++)
	{
		for(j=0; j < 4; j++)
		{
			cin>>Queries[i][j];
		}
	}

	U = 0;
	for(i=0; i < Q; i++)
	{
		for(j=1; j < 4; j+=2)
		{
			if(Queries[i][j] > U)
			{
				U = Queries[i][j];
			}
		}
	}
	for(i=0; i < M; i++)
	{
		for(j=1; j < 4; j+=2)
		{
			if(Teleports[i][j] > U)
			{
				U = Teleports[i][j];
			}
		}
	}

	Planets *obj;
	obj = new Planets [((N-1)*U)+M];

	for(i=0; i < N-1; i++)
	{
		for(j=0; j < N*U; j+=N)
		{
			obj[SObj].P1 = Tunnels[i][0] - 1 + j;
			obj[SObj].P2 = Tunnels[i][1] - 1 + j;
			SObj++;
		}
	}

	for(i=0; i < M; i++)
	{
		P1 = PlanetID(Teleports[i][0], Teleports[i][1] , N);
		P2 = PlanetID(Teleports[i][2], Teleports[i][3] , N);
		obj[SObj].P1 = P1-1;
		obj[SObj].P2 = P2-1;
		SObj++;
	}

	for(i=0; i < Q; i++)
	{
		P1 = PlanetID(Queries[i][0], Queries[i][1], N);
		P2 = PlanetID(Queries[i][2], Queries[i][3], N);
		PathLength[i] = ShortestPath(obj, P1, P2, N, U, SObj);
	}

	for(i=0; i < Q; i++)
	{
		if(PathLength[i] >= 200001)
		{
			cout<<"impossible\n";
		}
		else cout<<PathLength[i]<<"\n";
	}

	delete [] obj;
	delete [] Teleports;
	delete [] Tunnels;
	delete [] Queries;
	delete [] PathLength;
	return 0;
}

uint PlanetID(uint P, uint U, uint N)
{
	return (((U-1) * N) + P);
}

uint ShortestPath(Planets *obj, uint P1, uint P2, uint N, uint U, uint SObj)
{
	uint i, flag = 0;
	for(i=0; i < SObj; i++)
	{
		if((obj[i].P1 == P1-1 && obj[i].P2 == P2-1) || (obj[i].P2 == P1-1 && obj[i].P1 == P2-1))
		{
			flag = 1;
			break;
		}
	}

	if(flag == 1)
	{
		return 1;
	}
	else
	{

		uint j, x, k=0, L1, L2, V, A = P1-1, VS = N*U, W;

		uint *Labels = new uint [N*U];
		uint *PL = new uint [N*U];
		uint *Vertex = new uint [N*U];
		for(i=0; i < VS; i++)
		{
			Vertex[i] = i;
		}
		for(i=0; i < VS; i++)
		{
			if(Vertex[i] == P1-1)
			{
				for(j=i; j< VS-1; j++)
				{
					Vertex[j] = Vertex[j+1];
				}
				--VS;
			}
		}

		for(i=0; i < N*U; i++)
		{
			Labels[i] = 200001;
		}
		Labels[A] = 0;
		PL[k] = A;
		k++;

		for(x=0; x < (N*U - 1); x++)
		{
			for(i=0; i < VS; i++)
			{
				flag = 0;
				V = Vertex[i];
				L1 = Labels[V];
				L2 = Labels[A];
				for(j=0; j < SObj; j++)
				{
					if((obj[j].P1 == V && obj[j].P2 == A) || (obj[j].P1 == A && obj[j].P2 == V))
					{
						flag = 1;
						break;
					}
				}
				if(flag == 1)
				{
					W = L2 + 1;
				}
				else W = L2 + 200001;
				Labels[V] = min(L1, W);
			}

			V = 200001;

			for(i=0; i < N*U; i++)
			{
				flag = 0;
				if(i != P1-1)
				{
					for(j=0; j < k; j++)
					{
						if(i == PL[j])
						{
							flag = 1;
							break;
						}
					}
					if((flag == 0) && (Labels[i] < V))
					{
						V = Labels[i];
						A = i;
					}
				}
			}
			PL[k] = A;
			k++;

			for(i=0; i < VS; i++)
			{
				if(Vertex[i] == A)
				{
					for(j=i; j < (VS - 1); j++)
					{
						Vertex[j] = Vertex[j+1];
					}
					VS--;
				}
			}
		}
		return Labels[P2-1];
		delete [] Vertex;
		delete [] Labels;
		delete [] PL;
	}
}
