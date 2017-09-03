#include<iostream>
#include<climits>
#include<algorithm>
using namespace std;

unsigned long PlanetID(unsigned long, unsigned long, unsigned long);
unsigned long ShortestPath(unsigned long **, unsigned long, unsigned long, unsigned long, unsigned long);
//unsigned long MinLabel(unsigned long, unsigned long, unsigned long);

int main()
{
	unsigned long N, M, U, P1, P2, i, j;
	unsigned long Q;

	cin>>N>>M>>Q;

	//Tunnels input
	unsigned long **Tunnels = new unsigned long *[N-1]();
	for(i=0; i < N-1; i++)
	{
		Tunnels[i] = new unsigned long [2]();
	}
	for(i=0; i < N-1; i++)
	{
		for(j=0; j < 2; j++)
		{
			cin>>Tunnels[i][j];
		}
	}


	//Teleports input
	unsigned long **Teleports = new unsigned long *[M]();
	for(i=0; i < M; i++)
	{
		Teleports[i] = new unsigned long [4]();
	}
	for(i=0; i < M; i++)
	{
		for(j=0; j < 4; j++)
		{
			cin>>Teleports[i][j];
		}
	}

	//Queries input
	unsigned long **Queries = new unsigned long *[Q]();
	for(i=0; i < Q; i++)
	{
		Queries[i] = new unsigned long [4]();
	}
	for(i=0; i < Q; i++)
	{
		for(j=0; j < 4; j++)
		{
			cin>>Queries[i][j];
		}
	}

	//Determining max number of universes from Queries and Teleports
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

	//Creating adjacency matrix
	unsigned long **Matrix = new unsigned long *[N*U]();
	for(i=0; i < N*U; i++)
	{
		Matrix[i] = new unsigned long [N*U]();
	}


	for(i=0; i < N*U; i++)
	{
		for(j=0; j < N*U; j++)
		{
			Matrix[i][j] = LONG_MAX;
		}
	}

	//Intra-universe inter-planetary tunnels
	for(i=0; i < N-1; i++)
	{
		for(j=0; j < N*U; j+=N)
		{
			Matrix[Tunnels[i][0] - 1 + j][Tunnels[i][1] - 1 + j] = 1;
			Matrix[Tunnels[i][1] - 1 + j][Tunnels[i][0] - 1 + j] = 1;
		}
	}

	//Inter-universe teleports
	for(i=0; i < M; i++)
	{
		P1 = PlanetID(Teleports[i][0], Teleports[i][1] , N);
		P2 = PlanetID(Teleports[i][2], Teleports[i][3] , N);
		Matrix[P1-1][P2-1] = 1;
		Matrix[P2-1][P1-1] = 1;
	}

	/*for(i=0; i < N*U; i++)
	{
		cout<<"\n\n";
		for(j=0; j < N*U; j++)
		{
			cout<<"\t"<<Matrix[i][j];
		}
	}
	cout<<endl;*/

	unsigned long *PathLength = new unsigned long [Q]();

	//Determining shortest path length
	for(i=0; i < Q; i++)
	{
		P1 = PlanetID(Queries[i][0], Queries[i][1], N);
		P2 = PlanetID(Queries[i][2], Queries[i][3], N);
		PathLength[i] = ShortestPath(Matrix, P1, P2, N, U);
	}

	for(i=0; i < Q; i++)
	{
		if(PathLength[i] >= LONG_MAX) cout<<"\nIMPOSSIBLE";
		else cout<<PathLength[i]<<"\n";
	}

	return 0;
}

unsigned long PlanetID(unsigned long P, unsigned long U, unsigned long N)
{
	unsigned long Planet_No=0;
	Planet_No = ((U-1) * N) + P;
	return Planet_No;
}

unsigned long ShortestPath(unsigned long **Matrix, unsigned long P1, unsigned long P2, unsigned long N, unsigned long U)
{
	unsigned long PathLength=0;
	static unsigned long x = N*U;

	if(Matrix[P1-1][P2-1] == 1)
	{
		PathLength++;
	}
	else
	{
		unsigned long i, j, flag=0, k=0, L1, L2, A, V = P1-1;

		//Labels array
		unsigned long *L = new unsigned long [N*U]();

		//Permanent labels array
		unsigned long *P = new unsigned long [N*U]();

		//Vertex array
		unsigned long *T = new unsigned long [N*U]();
		for(i=0; i < x; i++)
		{
			T[i] = i;
		}
		for(i=0; i < x; i++)
		{
			if(T[i] == P1-1)
			{
				for(j=i; j<x-1; j++)
				{
					T[j] = T[j+1];
				}
				--x;
			}
		}

		for(i=0; i < N*U; i++)
		{
			L[i] = LONG_MAX;
		}
		L[V] = 0;
		P[k] = V;
		k++;

		LOOP:
		j=0;
		while(j < x)
		{
			L2 = L[V];
			L1 = L[T[j]];
			for(i=j; i<x-1; i++)
			{
				T[i] = T[i+1];
			}
			--x;


			for(j=0; j < k; j++)
			{
				cout<<"\nT["<<x<<"] = "<<T[x]<<" P["<<j<<"] = "<<P[j];
				if(T[x] != P[j])
				{

					L1 = L[x];
					A = x;
					cout<<"\nA = "<<A;
					L[A] = min(L1, L2 + Matrix[V][A]);
					//L[A] = MinLabel(L1, L2, Matrix[V][A]);
				}
				else break;
			}
			++j;
		}

		L1 = LONG_MAX;
		for(i=0; i < N*U; i++)
		{
			cout<<"\nL["<<i<<"] = "<<L[i];
			if(i == P1-1) continue;
			else if(L[i] < L1)
			{
				L1 = L[i];
				V = i;
			}
		}
		cout<<"\nV = "<<V<<endl;
		P[k] = V;
		k++;
		x=0;
		cout<<string(20, '*')<<endl;
		if(k <=N*U) goto LOOP;
		else PathLength = L[P2-1];
	}

	return PathLength;
}

/*unsigned long MinLabel(unsigned long L1, unsigned long L2, unsigned long W)
{
	unsigned long var1, var2, min;
	var1 = L1;
	var2 = L2+W;
	min = var1;
	cout<<"\nvar1 = "<<var1;
	cout<<"\nvar2 = "<<var2;

	if(var2 < min) min = var2;
	cout<<"\nmin = "<<min;
	return min;
}*/
