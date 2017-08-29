#include<iostream>
using namespace std;

bool IsNice(int **, int);

int main()
{
    int order, i, j;
    bool isNice;

    cout<<"\nOrder of the matrix = ";
    cin>>order;

    int **Matrix = new int *[order]; //Allocating memory for columns
    
    for(i=0; i < order; i++)
    {
    	Matrix[i] = new int [order]; //Allocating memory for rows
    }

    cout<<"\nEnter the matrix:-\n";
    for(i=0; i < order; i++)
    {
        for(j=0; j < order; j++)
        {
            cin>>Matrix[i][j];
        }
    }

    isNice = IsNice(Matrix, order);
    
    if(isNice) cout<<"\nThe matrix is nice already"<<endl;
    
    //Not compulsory to delete
    for(i=0; i < order; i++) delete [] Matrix[i];
    
    delete [] Matrix; 
    
    return 0;
}

bool IsNice(int **Matrix, int order)
{
    int RowMin[order], ColumnMax[order], R_Max, C_Min, Var, i, j;

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

    if(R_Max == C_Min) return true;
    else return false;
}
