#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "wykresy.hxx"
#include <sstream>

using vect = std::vector<double>;

vect X;
vect Y;
vect Xtemp;
vect Ytemp;
vect X3;
vect Y3;
double l(int j,int x)
{
    double licznik=1;
    for(int i=0;i<64;i++)
    {
        if(i!=j)
        {
            licznik*=(x-X[i])/(X[j]-X[i]);   //obliczanie lj(x)
        }
    }
    return licznik;
}

double l1(int j,int x)
{
    double licznik=1;
    for(int i=0;i<16;i++)
    {
        if(i!=j)
        {
            licznik*=(x-Xtemp[i])/(Xtemp[j]-Xtemp[i]);   //obliczanie lj(x)
        }
    }
    return licznik;
}

double l2(int j,int x)
{
    double licznik=1;
    for(int i=0;i<8;i++)
    {
        if(i!=j)
        {
            licznik*=(x-X3[i])/(X3[j]-X3[i]);   //obliczanie lj(x)
        }
    }
    return licznik;
}

double W(int x)
{
    double licznik =0;
    for(int i=0;i<64;i++)
    {
        licznik+=(l(i,x)*Y[i]); //obliczanie wielomianu interpolacyjnego
    }
    return licznik;
}

double W1(int x)
{
    double licznik =0;
    for(int i=0;i<16;i++)
    {
        licznik+=(l1(i,x)*Ytemp[i]); //obliczanie wielomianu interpolacyjnego
    }
    return licznik;
}

double W2(int x)
{
    double licznik =0;
    for(int i=0;i<8;i++)
    {
        licznik+=(l2(i,x)*Y3[i]); //obliczanie wielomianu interpolacyjnego
    }
    return licznik;
}

vect Thomas(double D[])
{
    double a[63]; //tablice w ktorych znajduja sie wartosci przekatnych
    double b[63];
    double c[63];
    for(int i=0;i<63;i++)
    {
        a[i]=1.0;
        b[i]=4.0;
        c[i]=1.0;
    }
    a[0]=0;
    c[62]=0;
    double beta[63];
    double gamma[63];  
    vect ksi; 
    ksi.resize(63);
    for(int j=0;j<63;j++)
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
    for(int k=62;k>=0;k--)
    {
        if(k==62)
        {
            ksi[k]=gamma[k];
        }
        else
        {
            ksi[k]=(beta[k]*ksi[k+1]) + gamma[k];
        }
    }
    return ksi;
}

double fx(double x)
{
    return (1/(1+5*x*x));
}


int main()
{  
    double a1[64];
    double a2[16];
    double a3[8];
    for(int i=0;i<64;i++)
    {
        a1[i]=0;
    }
    for(int i=0;i<16;i++)
    {
        a2[i]=0;
    }
    for(int i=0;i<8;i++)
    {
        a3[i]=0;
    }
    X.resize(65);
    Y.resize(65);
    Xtemp.resize(17);
    Ytemp.resize(17);
    X3.resize(9);
    Y3.resize(9);
    for(int i=0;i<=64;i++)
    {
        double a = -1 + (double)i/32.0;
        X[i]=a;
        Y[i]=fx(a);
    }
    for(int i=0;i<=16;i++)
    {
        double u = -1 + (double)i/8.0;
        Xtemp[i]=u;
        Ytemp[i]=fx(u); 
    }
    for(int i=0;i<=8;i++)
    {
        double v = -1 + (double)i/4.0;
        X3[i]=v;
        Y3[i]=fx(v); 
    }
    double Dvect[63];
    for(int i=2;i<65;i++)
    {
        double exp = Y[i-2] - 2*Y[i-1] + Y[i];
        Dvect[i-2]= (6.0/((1.0/32.0)*(1.0/32.0))) * exp;  //h=1/32
    }
    vect ksi;
    ksi = Thomas(Dvect);
    double A,B,C,D,x,y;
    std::fstream wynikisplajn;
    wynikisplajn.open("wynikisplajn.txt", std::ios::out | std::ios_base::trunc);
    std::fstream wyniki;
    wyniki.open("wyniki.txt", std::ios::out | std::ios_base::trunc);
    for(int j=0;j<65;j++)
    {
        wyniki<<X[j]<<" "<<Y[j]<<"\n";
    }
    for(int i=0;i<63;i++)
    {
        x=(X[i]+X[i+1])/2;
        A=(X[i+1]-x)/(X[i+1]-X[i]);
        B=(x-X[i])/(X[i+1]-X[i]);
        C=(1.0/6.0)*(pow(A,3)-A)*(pow(X[i+1]-X[i],2));
        D=(1.0/6.0)*(pow(B,3)-B)*(pow(X[i+1]-X[i],2));
        y= A*Y[i] + B*Y[i+1] + C*ksi[i] + D*ksi[i+1];
        wynikisplajn<<x<<" "<<y<<"\n";
    }
    wyniki.close();
    wynikisplajn.close();


    for(int i=0;i<65;i++)
    {
        if(X[i]==0)
        {
            X.erase(X.begin()+i);
            Y.erase(Y.begin()+i);
        }
    }
    for(int i=0;i<=16;i++)
    {
        if(Xtemp[i]==0)
        {
            Xtemp.erase(Xtemp.begin()+i);
            Ytemp.erase(Ytemp.begin()+i);
        }
    }
    for(int i=0;i<=8;i++)
    {
        if(X3[i]==0)
        {
            X3.erase(X3.begin()+i);
            Y3.erase(Y3.begin()+i);
        }
    }
    double f[64][64];
    double f2[16][16];
    double f3[8][8];

    for(int i=0;i<64;i++)
    {
        f[0][i]=Y[i];      // if k==0  fj^k = fj
    }

    for(int i=0;i<16;i++)
    {
        f2[0][i]=Ytemp[i];      // if k==0  fj^k = fj
    }

    for(int i=0;i<8;i++)
    {
        f3[0][i]=Y3[i];      // if k==0  fj^k = fj
    }

    a1[0]=W(0);
    a2[0]=W1(0);
    a3[0]=W2(0);
    
    for(int i=0;i<63;i++)
    {
        for(int g=0;g<64;g++)
        {
            f[i+1][g]=(f[i][g]-a1[i])/X[g];
        }
        for(int v=0;v<64;v++)
        {
            a1[i+1]+=l(v,0)*f[i+1][v];
        }
    }

    for(int i=0;i<15;i++)
    {
        for(int g=0;g<16;g++)
        {
            f2[i+1][g]=(f2[i][g]-a2[i])/Xtemp[g];
        }
        for(int v=0;v<16;v++)
        {
            a2[i+1]+=l1(v,0)*f2[i+1][v];
        }
    }

    for(int i=0;i<7;i++)
    {
        for(int g=0;g<8;g++)
        {
            f3[i+1][g]=(f3[i][g]-a3[i])/X3[g];
        }
        for(int v=0;v<8;v++)
        {
            a3[i+1]+=l2(v,0)*f3[i+1][v];
        }
    }
    
    

    std::stringstream ss,ss1,ss2;
    ss<<"Funkinter_64_points(x) = ";
    ss1<<"Funkinter_16_points(x) = ";
    ss2<<"Funkinter_8_points(x) = ";
    for(int i=63;i>=0;i--)
    {
        if(i==1)
        {
            ss<<a1[i]<<"*x"<<" + ";
        }
        else if(i==0)
        {
            ss<<a1[i];
        }
        else
        {
            ss<<a1[i]<<"*x**"<<i<<" + ";
        }
    }

    for(int i=15;i>=0;i--)
    {
        if(i==1)
        {
            ss1<<a2[i]<<"*x"<<" + ";
        }
        else if(i==0)
        {
            ss1<<a2[i];
        }
        else
        {
            ss1<<a2[i]<<"*x**"<<i<<" + ";
        }
    }

    for(int i=7;i>=0;i--)
    {
        if(i==1)
        {
            ss2<<a3[i]<<"*x"<<" + ";
        }
        else if(i==0)
        {
            ss2<<a3[i];
        }
        else
        {
            ss2<<a3[i]<<"*x**"<<i<<" + ";
        }
    }
    std::string strin = ss.str();
    std::string strin1 = ss1.str();
    std::string strin2 = ss2.str();
    wykres gnuplot;
    gnuplot("set title \"Punkty które posłużyły do konstrukcji wielomianu\"");
    gnuplot("set xlabel \"X\"");
    gnuplot("set ylabel \"Y\"");
    gnuplot("set yrange [0:2]");
    gnuplot("set xrange [-1:1]");
    gnuplot(strin);
    gnuplot(strin1);
    gnuplot(strin2);
    gnuplot("plot 'wyniki.txt' w lines lc \"blue\",'wynikisplajn.txt' w points pointtype 7 title\"Punkty splajnu\",Funkinter_64_points(x) w lines linecolor \"red\",Funkinter_16_points(x) w lines linecolor \"green\" lw 2,Funkinter_8_points(x) w lines linecolor \"purple\" lw 3");
    
    

    return 0;
}