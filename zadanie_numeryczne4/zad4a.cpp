#include <iostream>
#include <cmath>
#include <cstring>
#define MAX 128


int main()
{
    double A[MAX][MAX];
    double e[MAX];
    double x[MAX];
    double x2[MAX];
    double e2[MAX];

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
        x[i]=0.01; //zgadywanie wyniku
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

    int iterations = 0;;
    bool koniec = true;
    double eps = 0.000001;


    do
    {
        for(int i=0;i<MAX;i++)
        {
            x2[i]=x[i];
        }
        for(int i=0;i<MAX;i++)
        {
            e2[i] = e[i];
            for(int j=0;j<i;j++)
            {
                if(A[i][j]!=0)
                {
                    e2[i]-=(A[i][j]*x[j]);
                }
            }
            for(int j=i+1;j<MAX;j++)
            {
                if(A[i][j]!=0)
                {
                    e2[i]-=(A[i][j]*x2[j]);
                }
            }
            x[i] = e2[i]/A[i][i];
        }
        for(int i=0;i<MAX;i++)
        {
            if(fabs(x[i]-x2[i])>=eps)
            {
                koniec = true;
                break;
            }
            else
            {
                koniec = false;
            }
        }
        iterations++;
    } while (koniec && iterations < MAX);

    for(int g=0;g<MAX;g++)
    {
        std::cout<<std::fixed<<x[g]<<"\n";
    }
    
    std::cout<<iterations<<std::endl;

    


    return 0;
}