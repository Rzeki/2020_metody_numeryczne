#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>

double function(double x) {
	return sin(M_PI*(1+std::sqrt(x))/(1+std::pow(x,2)))*std::pow(M_E, -x);
}

void print_row(size_t n, double arr[]) {
	std::cout << "R" << n << ": ";
	for (size_t i = 0; i <= n; ++i) {
		std::cout << ' ' << arr[i] << ' ';
	}
	std::cout << '\n';
}

void swap(double a[],double b[])
{
	double temp;
	for(int i=0;i<20;i++)
	{
		temp = a[i];
		a[i]=b[i];
		b[i]=temp;
	}
}

double Romberg(double (*f)(double), double a, double b, double acc) {
	double rc[20];
	double rp[20];

	double h = b-a;

	rp[0] = ((h*(f(a) + f(b)))/2);
	rc[0] = 0;
	
 	print_row(0, rp);
	size_t i = 1;

	do {
		h /= 2.;
		double I = 0.0;
		size_t N = 1 << (i-1);
		
		for(size_t j = 0; j<=N;j++) {
			I += f(a+(2*j-1)*h);
		}
		rc[0] = h*I + rp[0]/2;
		
		for (size_t j = 1; j < i; ++j) {
			rc[j] = (std::pow(4, j)*rc[j-1] - rp[j-1])/(std::pow(4, j)-1);
		}
		rc[i] = ((std::pow(4, i)*rc[i-1] - rp[i-1])/(std::pow(4, i)-1));
		rp[i] = 0;
	 	print_row(i, rc);
		swap(rc,rp);
		i++;
 	} while (std::fabs(rp[i-1]-rc[i-2]) >= acc);

	return rp[i-1];
}

int main() {
	std::cout << std::setprecision(6);
	constexpr double acc = 1e-7;
	constexpr double A = 17.0;

	std::cout<<"Pierwszy przedzial: \n";
	double r1 = Romberg(function, 0.0, 1.0, acc);
	std::cout<<"\nDrugi przedzial: \n";
	double r2 = Romberg(function, 1.0, A, acc);

	std::cout << "\nWynik: " << r1+r2 << '\n';
}