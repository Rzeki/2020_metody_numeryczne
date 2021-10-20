#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

constexpr double epsilon = 0.00000001;

typedef std::mt19937 RNG;
typedef std::random_device DEVICE;
typedef std::uniform_real_distribution<> RANGE;

double fx(double x)
{
    return ((std::pow(x,2)-1)*std::pow(sinh(x),3));
}

class Point
{
    public:
    double x;
    double y;

    Point() = default;

    Point(double x,double y)
    {
        this->x=x;
        this->y=y;
    }

    bool operator < (const Point& str) const
    {
        return (y<str.y);
    }
};

std::vector<Point> sort(std::vector<Point>& tablica)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(tablica[i].y>tablica[j].y)
            {
                std::swap(tablica[i].y,tablica[i].y);
                std::swap(tablica[i].x,tablica[j].x);
            }
        }
    }
    return tablica;
}

double Secant_method(Point p1, Point p2)
{
    Point p3;
    while (std::fabs(p1.x - p2.x)>epsilon)
    {   
        if(std::fabs(p1.y - p2.y) < epsilon)
        {
            break;
        }
        p3.x = (p1.y*p2.x - p2.y*p1.x)/(p1.y-p2.y);

        p3.y=fx(p3.x);

        if(std::fabs(p3.y)<epsilon){return p3.x;}
        p2=p1;
        p1=p3;
    }
    return p3.x;
}

double Inverse_interp(std::vector<Point>& punkty)
{
    double temp;
    double temp1;
    punkty = sort(punkty);
    for(int i=0;i<3;i++)
    {
        temp1 = punkty[i].x;
        punkty[i].x = punkty[i].y;
        punkty[i].y = temp1;
    }

    do
    {
        temp=0;
        for(int i=0;i<3;i++)
        {
            double inter=1;
            for(int j=0;j<3;j++)
            {
                if(i!=j)
                {
                    inter*=(0.0-punkty[j].x)/(punkty[i].x-punkty[j].x);   //obliczanie lj(x)
                }
            }
            temp+=(inter*punkty[i].y); //obliczanie wielomianu interpolacyjnego
        }
        Point t1 = punkty[1];
        Point t2 = punkty[2];
        punkty.clear();
        punkty.push_back(t1);
        punkty.push_back(t2);
        punkty.push_back(Point(fx(temp),temp));
    } while (std::fabs(fx(punkty[2].y))>epsilon);
    return temp;
    
}

int main()
{
    DEVICE new_device;
    RNG new_rng(new_device());
    RANGE dist(0,1);
    double x,y;
    std::vector<Point> punkty;
    for (int k=0;k<10;k++)
    {
        for(int i=0;i<3;i++)
        {
            x=dist(new_rng);
            y=fx(x);
            punkty.push_back(Point(x,y));
        }
        for(int i=0;i<3;i++)
        {
            std::cout<<"P"<<i+1<<": "<<"("<<punkty[i].x<<","<<punkty[i].y<<")\n";
        }
        std::cout<<"Metoda siecznych: "<<Secant_method(punkty[0],punkty[2])<<"\n";
        std::cout<<"Interpolacja odwrotna: "<<Inverse_interp(punkty)<<"\n\n";
        punkty.clear();
    }
    return 0;
}