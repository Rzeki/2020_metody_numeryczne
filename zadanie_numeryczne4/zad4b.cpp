#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#define MAX 128
#define eps 0.000001

using vect = std::vector<double>;
using matrix = std::vector<vect>;

double CalculateNorm(const vect v1)
{
    double norm=0;
    for(int i=0;i<MAX;i++)
    {
        norm+=pow(v1[i],2);
    }
    return sqrt(norm);
}

vect subvectors(const vect v1,const vect v2)
{
    vect temp;
    temp.resize(128);
    for(int i=0;i<MAX;i++)
    {
        temp[i]=v1[i]-v2[i];
    }
    return temp;
}

vect addvectors(const vect v1,const vect v2)
{
    vect temp;
    temp.resize(128);
    for(int i=0;i<MAX;i++)
    {
        temp[i]=v1[i]+v2[i];
    }
    return temp;
}


double multvectors(const vect tab1,const vect tab2)
{
    double sum=0;
    for(int i=0;i<MAX;i++)
    {
        sum+= (tab1[i]*tab2[i]);   //mnozenie wektorow
    }
    return sum;
}

vect matrixtimesvector(const matrix matrix1,const vect v1)
{
    vect temp;
    temp.resize(128);
    for(int r=0;r<MAX;r++)
        {
            temp[r]=0;
        }
    for(int g=0;g<MAX;g++)
    {
        for(int r=0;r<MAX;r++)
        {
            if(matrix1[g][r]!=0)
            {
                temp[g]+=(matrix1[g][r]*v1[r]);
            }
        }
    }
    return temp;
}

vect skaltimesvector(const vect v1,double skal)
{
    vect temp;
    temp.resize(128);
    temp = v1;
    for(int i=0;i<128;i++)
    {
        temp[i]*=skal;
    }
    return temp;
}


int main()
{
    matrix A;
    vect e;
    matrix x;
    matrix r;
    matrix p;
    double alfa;
    double beta;
    e.resize(128);
    p.resize(128);
    x.resize(128);
    r.resize(128);
    A.resize(128);
    for(int i=0;i<128;i++)
    {
        A[i].resize(128);
        r[i].resize(128);
        p[i].resize(128);
        x[i].resize(128);

    }

    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            
            if(i==j)
            {
                A[i][i]=4; //ustawianie przekatnej
            }
            else
            {
                A[i][j]=0;
            }
        }
        x[0][i]=0.01; //zgadywanie wyniku
        e[i]=1; //inicjalizacja e
    }
    for(int k=1;k<=4;k+=3)
    {
        int l=0;
        while(k+l<MAX && l<MAX)  //ustawianie jedynek
        {
            A[l][k+l]=1;
            A[k+l][l]=1;
            l++;
        }
    }

    int k=0;
    r[0] = subvectors(e,matrixtimesvector(A,x[0]));
    p[0]=r[0];
    while(CalculateNorm(r[k])>eps)
    {
        alfa=(multvectors(r[k],r[k]))/multvectors(p[k],matrixtimesvector(A,p[k]));
        r[k+1]=subvectors(r[k],skaltimesvector(matrixtimesvector(A,p[k]),alfa));
        beta = multvectors(r[k+1],r[k+1])/multvectors(r[k],r[k]);
        p[k+1] = addvectors(r[k+1],skaltimesvector(p[k],beta));
        x[k+1] = addvectors(x[k],skaltimesvector(p[k],alfa));
        k++;
    }
    for(int i=0;i<MAX;i++)
    {
        std::cout<<x[k][i]<<"\n";
    }

    return 0;
}