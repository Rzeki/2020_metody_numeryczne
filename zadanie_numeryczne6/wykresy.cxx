#include <iostream>
#include "wykresy.hxx"
#include <fstream>
#include <sstream>

double X[8]={0.062500,0.187500,0.312500,0.437500,0.562500,0.687500,0.812500,0.937500};
double Y[8]={0.687959,0.073443,-0.517558,-1.077264,-1.600455,-2.080815,-2.507266,-2.860307};
double a[8]={0,0,0,0,0,0,0,0};
double f[8][8];
//f[k][j]

double l(int j,int x)
{
    double licznik=1;
    for(int i=0;i<8;i++)
    {
        if(i!=j)
        {
            licznik*=(x-X[i])/(X[j]-X[i]);   //obliczanie lj(x)
        }
    }
    return licznik;
}

double W(int x)
{
    double licznik =0;
    for(int i=0;i<8;i++)
    {
        licznik+=(l(i,x)*Y[i]); //obliczanie wielomianu interpolacyjnego
    }
    return licznik;
}

int main()
{
    for(int i=0;i<8;i++)
    {
        f[0][i]=Y[i];      // if k==0  fj^k = fj
    }
    a[0]=W(0);
    for(int i=0;i<7;i++)
    {
        for(int g=0;g<8;g++)
        {
            f[i+1][g]=(f[i][g]-a[i])/X[g];
        }
        for(int v=0;v<8;v++)
        {
            a[i+1]+=l(v,0)*f[i+1][v];
        }
    }
    std::fstream wyniki;
    wyniki.open("wyniki.txt", std::ios::out | std::ios_base::trunc);

    for(int i=0;i<8;i++)
    {
        wyniki<<X[i]<<" "<<Y[i]<<"\n";
    }
    std::stringstream ss;
    ss <<"Funkcja_interpolacyjna(x) = "<<a[7]<<"*x**7 + "<<a[6]<<"*x**6 + "<<a[5]<<"*x**5 + "<<a[4]<<"*x**4 + "<<a[3]<<"*x**3 + "<<a[2]<<"*x**2 + "<<a[1]<<"*x + "<<a[0];
    std::string strin = ss.str();

    
    wyniki.close();
    wykres gnuplot;
    gnuplot("set title \"Punkty które posłużyły do konstrukcji wielomianu\"");
    gnuplot("set xlabel \"X\"");
    gnuplot("set ylabel \"Y\"");
    gnuplot(strin);
    gnuplot("set xrange [-1:1]");
    gnuplot("set yrange [-3:5]");
    gnuplot("plot 'wyniki.txt' w points pointtype 7 title\"Punkty z zadania\",Funkcja_interpolacyjna(x) w lines");

    return 0;
}