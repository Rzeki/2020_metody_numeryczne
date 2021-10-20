#include <iostream>

void subtract(double tab1[7][7], double tab2[7][7])
{
    for(int i=0; i<7; i++)
    {
        for(int j=0;j<7;j++)                //odejmowanie macierzy
        {
            tab1[i][j]= tab1[i][j] - tab2[i][j];
        }
    }
}

double multvectors(double tab1[], double tab2[])
{
    double sum=0;
    for(int i=0;i<7;i++)
    {
        sum+= (tab1[i]*tab2[i]);   //mnozenie wektorow
    }
    return sum;
}

void subtractvectors(double tab1[], double tab2[], double tab3[])
{
    double sum=0;
    for(int i=0;i<7;i++)  //odejmowanie wektorow
    {
        tab3[i]= tab1[i]-tab2[i];
    }
}

void multiplyscal(double skal, double tab1[])
{
    for(int i=0;i<7;i++)
    {
        tab1[i]*=skal;  //mnozenie wektora przez skalar
    }
}


void Thomas(double matrix[][7], double D[], double x[])
{
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
            c[i]=matrix[i][i+1];                 //algorytm Thomasa dla rozwiazywania ukladow Ax=b (jako funkcja)
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
}

//Ax=b
    
    

int main()
{
    double matrix[7][7] = {{4,1,0,0,0,0,1},{1,4,1,0,0,0,0},{0,1,4,1,0,0,0},{0,0,1,4,1,0,0},{0,0,0,1,4,1,0},{0,0,0,0,1,4,1},{1,0,0,0,0,1,4}}; //macierz A
    double uvT[7][7] = {{1,0,0,0,0,0,1},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{1,0,0,0,0,0,1}}; //macierz ktora musimy odjac od A aby otrzymac macierz trójprzekatniowa
    double u[7] = {1,0,0,0,0,0,1}; //wektor u
    double v[7] = {1,0,0,0,0,0,1}; //wektor v
    double D[7] = {1,2,3,4,5,6,7}; //macierz b
    double x[7];
    double z[7];
    double q[7];
    double w[7]={0,0,0,0,0,0,0}; //wektor zawierajacy wynik
    double skal;
    // A = A1 - uv^T
    subtract(matrix,uvT);
    // nastepnie rozwiazujemy dwa rownania macierzowe algorytmem Thomasa
    //1. Az = D
    Thomas(matrix,D,z);
    //2. Aa = u
    Thomas(matrix,u,q);
    skal = (multvectors(v,z))/(1+multvectors(v,q));
    //nastepnie mnozymy przez otrzymany skalar wektor q
    multiplyscal(skal,q);
    // na koniec po odjeciu od wektora z otrzymujemy wynik
    subtractvectors(z,q,w);

    for(int z=0;z<7;z++)
    {
       std::cout<<"w"<<z+1<<": "<<w[z]<<std::endl;
    }

    //Kacper Druzdzel
    return 0;
}