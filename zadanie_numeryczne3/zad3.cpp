#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#define MAX 5

void LUDECOMPOSITION(double matrix[][MAX], double lower[][MAX], double higher[][MAX])
{
    for(int i = 0; i<5; i++)
    {
        for(int k=i; k<5; k++)
        {
            double sum=0;
            for(int j=0;j<i;j++)
            {
                sum+=(lower[i][j]*higher[j][k]);
            }
            higher[i][k] = matrix[i][k] - sum;
        }                                                          //Rozklad LU (Doolittle algorithm)
        for(int k=i; k<5; k++)
        {
            if(i==k)
            {
                lower[i][i]=1;
            }
            else
            {
                double sum=0;
                for(int j=0;j<i; j++)
                {
                    sum+= (lower[k][j] * higher[j][i]);
                }
                lower[k][i] = (matrix[k][i] - sum)/higher[i][i];
            }
            
        }
    }
}  

void solvelinearequasion(double L[][MAX] , double U[][MAX] , double res[] , double b[])
{
    double suma;
    double temp[5];
    memset(temp,0,sizeof(temp));
    for(int i=0;i<5;i++)
    {
        suma=0;
        for(int j=0;j<i;j++)
        {
            suma+=L[i][j]*temp[j];  //forward substitution
            
        }
        temp[i]=(b[i]-suma)/L[i][i];
    }

    for(int i=4;i>=0;i--)
    {
        suma=0;
        for(int j=4;j>i;j--)
        {
            suma+=U[i][j]*res[j]; //backwards substitution
            
        }
        res[i]=(temp[i]-suma)/U[i][i];
    }
}

double CalculateNorm(double v1[], double v2[])
{
    double v3[5];
    for(int i=0;i<5;i++)
    {
        v3[i]=v1[i]-v2[i];
    }
    double norm=0;
    for(int i=0;i<5;i++)
    {
        norm+=pow(v3[i],2);
    }
    return sqrt(norm);
}

int main()
{
    double A[5][5]={{-116.66654 , 583.33346 , -333.33308 , 100.00012 , 100.00012}, 
                    {583.33346 , -116.66654 , -333.33308 , 100.00012 , 100.00012}, 
                    {-333.33308, -333.33308, 133.33383, 200.00025, 200.00025}, 
                    {100.00012, 100.00012, 200.00025, 50.000125, -649.99988}, 
                    {100.00012, 100.00012, 200.00025, -649.99988, 50.000125}};

    double b1[5]={-0.33388066, 1.08033290, -0.98559856, 1.31947922, -0.09473435};
    double b2[5]={-0.33388066, 1.0803329, -0.98559855, 1.32655028, -0.10180541};
    double b3[5]={0.72677951, 0.72677951, -0.27849178, 0.96592583, 0.96592583};
    double b4[5]={0.73031505, 0.73031505, -0.27142071, 0.96946136, 0.96946136};

    double z1[5]={0,0,0,0,0};
    double z2[5]={0,0,0,0,0};
    double z3[5]={0,0,0,0,0};
    double z4[5]={0,0,0,0,0};

    double lower[5][5];
    double higher[5][5];
    memset(lower,0,sizeof(lower));
    memset(higher,0,sizeof(higher));


    LUDECOMPOSITION(A,lower,higher);
    solvelinearequasion(lower,higher,z1,b1);
    solvelinearequasion(lower,higher,z2,b2);
    solvelinearequasion(lower,higher,z3,b3);
    solvelinearequasion(lower,higher,z4,b4);

    std::cout<<"Z1:"<<"\n";
    for(int i=0;i<5;i++)
    {
        std::cout<<std::setprecision(11)<<std::fixed<<z1[i]<<"\n";
    }
    std::cout<<"\n";
    std::cout<<"Z2:"<<"\n";
    for(int i=0;i<5;i++)
    {
        std::cout<<z2[i]<<"\n";
    }
    std::cout<<"\n";
    std::cout<<"Z3:"<<"\n";
    for(int i=0;i<5;i++)
    {
        std::cout<<z3[i]<<"\n";
    }
    std::cout<<"\n";
    std::cout<<"Z4:"<<"\n";
    for(int i=0;i<5;i++)
    {
        std::cout<<z4[i]<<"\n";
    }
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"||b1-b2|| = "<<CalculateNorm(b1,b2)<<"\n";
    std::cout<<"||b3-b4|| = "<<CalculateNorm(b3,b4)<<"\n";
    std::cout<<"||z1-z2|| / ||b1-b2|| = "<<CalculateNorm(z1,z2)/CalculateNorm(b1,b2)<<"\n";
    std::cout<<"||z3-z4|| / ||b3-b4|| = "<<CalculateNorm(z3,z4)/CalculateNorm(b3,b4)<<"\n";
   

    return 0;
}