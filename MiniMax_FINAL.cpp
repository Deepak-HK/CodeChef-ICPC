#include<iostream>
using namespace std;

int IsNice(long **, int);

int main()
{
    int order, i, j;
    int changes;

    cin>>order;

    long **Matrix = new long *[order]; //Allocating memory for columns

    for(i=0; i < order; i++)
    {
    	Matrix[i] = new long [order]; //Allocating memory for rows
    }

    for(i=0; i < order; i++)
    {
        for(j=0; j < order; j++)
        {
            cin>>Matrix[i][j];
        }
    }

    changes = IsNice(Matrix, order);

    for(i=0; i < order; i++) delete [] Matrix[i];

    delete [] Matrix;

    cout<<changes;

    return 0;
}

int IsNice(long **Matrix, int order)
{
    long RowMin[order], ColumnMax[order], R_Max, C_Min;
    int Var, i, j, count, Counts[order];

    for(i=0; i < order; i++)
    {
        Var = Matrix[i][0];
        for(j=0; j < order; j++)
        {
            if(Matrix[i][j] < Var) Var = Matrix[i][j];
        }
        RowMin[i] = Var;
    }

    for(i=0; i < order; i++)
    {
        Var = 0;
        for(j=0; j < order; j++)
        {
            if(Matrix[j][i] > Var) Var = Matrix[j][i];
        }
        ColumnMax[i] = Var;
    }

    R_Max = RowMin[0];
    for(i=0; i < order; i++)
    {
        if(RowMin[i] > R_Max) R_Max = RowMin[i];
    }

    C_Min = ColumnMax[0];
    for(i=0; i < order; i++)
    {
        if(ColumnMax[i] < C_Min) C_Min = ColumnMax[i];
    }

    for(i=0; i < order; i++)
    {
       count = 0;
       for(j=0; j < order; j++)
       {
            if(Matrix[j][i] > R_Max) count++;
       }
       Counts[i] = count;
    }

    Var = Counts[0];
    for(i=0; i < order; i++)
    {
        if(Counts[i] < Var) Var = Counts[i];
    }

    return Var;
}
