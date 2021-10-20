#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#define MAX 64
#define eps 0.000001

using vect = std::vector<double>;
using matrix = std::vector<vect>;

matrix subtract(matrix &A, matrix &B)
{
    for(int i=0; i<MAX; i++)
    {
        for(int j=0;j<MAX;j++)                //odejmowanie macierzy
        {
            A[i][j] -= B[i][j];
        }
    }
    return A;
}

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
    temp.resize(MAX);
    for(int i=0;i<MAX;i++)
    {
        temp[i]=v1[i]-v2[i];
    }
    return temp;
}

vect addvectors(const vect v1,const vect v2)
{
    vect temp;
    temp.resize(MAX);
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
    temp.resize(MAX);
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
    temp.resize(MAX);
    temp = v1;
    for(int i=0;i<MAX;i++)
    {
        temp[i]*=skal;
    }
    return temp;
}
vect Conjugate_Gradient(matrix &A,matrix &x,vect &e)
{
    int k=0;
    double alfa;
    double beta;
    matrix r;
    matrix p;
    r.resize(MAX);
    p.resize(MAX);
    for(int g=0;g<MAX;g++)
    {
        r[g].resize(MAX);
        p[g].resize(MAX);
    }
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
    return x[k];
}
int main()
{
    matrix A;
    matrix uvT;
    matrix q;
    vect u;
    vect w1;
    vect w2;
    vect v;
    vect e;
    matrix x;
    matrix r;
    matrix p;
    double alfa;
    double beta;
    e.resize(MAX);
    w1.resize(MAX);
    w2.resize(MAX);
    p.resize(MAX);
    q.resize(MAX);
    x.resize(MAX);
    r.resize(MAX);
    A.resize(MAX);
    uvT.resize(MAX);
    u.resize(MAX);
    v.resize(MAX);
    for(int i=0;i<MAX;i++)
    {
        uvT[i].resize(MAX);
        A[i].resize(MAX);
        r[i].resize(MAX);
        p[i].resize(MAX);
        x[i].resize(MAX);
        q[i].resize(MAX);

    }

    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            uvT[i][j]=1;
            if(i==j)
            {
                A[i][i]=5; //ustawianie przekatnej
            }
            else
            {
                A[i][j]=1;
            }
        }
        x[0][i]=0.01; //zgadywanie wyniku
        q[0][i]=0.01; //zgadywanie wyniku
        e[i]=1; //inicjalizacja e
        v[i]=1;
        u[i]=1;
    }
    for(int k=1;k<=4;k+=3)
    {
        int l=0;
        while(k+l<MAX && l<MAX)  //ustawianie jedynek
        {
            A[l][k+l]=2;
            A[k+l][l]=2;
            l++;
        }
    }

    //-------------------------------------------------------------------------------------------------------------------------------------
    //rozwiazujemy uklad A = A1 - uvT
    A = subtract(A,uvT);
    // nastepnie rozwiazujemy dwa rownania macierzowe metodą gradientów sprzężonych
    //1. Ax = e
    w1 = Conjugate_Gradient(A,x,e);
    //2. Aq = v
    w2 = Conjugate_Gradient(A,q,v);
    double skal = (multvectors(v,w1)/(1+multvectors(v,w2)));
    w2 = skaltimesvector(w2,skal);
    vect last;
    last.resize(MAX);
    last = subvectors(w1,w2);
    for(double i:last)
    {
       std::cout<<i<<"\n";
    }
    

    return 0;
}