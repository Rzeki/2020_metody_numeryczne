#include <iostream>

int main() //numerki
{
    //Ax=b
    double matrix[7][7] = {{4,1,0,0,0,0,0},{1,4,1,0,0,0,0},{0,1,4,1,0,0,0},{0,0,1,4,1,0,0},{0,0,0,1,4,1,0},{0,0,0,0,1,4,1},{0,0,0,0,0,1,4}}; //macierz A
    double D[7] = {1,2,3,4,5,6,7}; //macierz b
    double x[7]; //macierz w ktorej jest wynik (x)
    double a[7]; //tablice w ktorych znajduja sie wartosci przekatnych
    double b[7];
    double c[7];
    double beta[7];
    double gamma[7];
    for(int i=0;i<7;i++)
    {
        b[i]=matrix[i][i];
        if(i==0)
        {
            a[i]=0;
            c[i]=matrix[i][i+1];
        }
        else if(i==6)
        {
            a[i]=matrix[i][i-1];
            c[i]=0;
        }
        else
        {
            a[i]=matrix[i][i-1];
            c[i]=matrix[i][i+1];
        }
    }
    for(int j=0;j<7;j++)
    {
        if(j==0)
        {
            beta[j]=-(c[j]/b[j]);
            gamma[j]=(D[j]/b[j]);
        }
        else
        {
            beta[j]=-(c[j]/((a[j]*beta[j-1])+b[j]));
            gamma[j]=((D[j]-a[j]*gamma[j-1])/((a[j]*beta[j-1])+b[j]));
        }
    }
    for(int k=6;k>=0;k--)
    {
        if(k==6)
        {
            x[k]=gamma[k];
        }
        else
        {
            x[k]=(beta[k]*x[k+1]) + gamma[k];
        }
    }

    for(int z=0;z<7;z++)
    {
        std::cout<<"x"<<z+1<<": "<<x[z]<<std::endl;
    }

    //Kacper Druzdzel
    return 0;
}