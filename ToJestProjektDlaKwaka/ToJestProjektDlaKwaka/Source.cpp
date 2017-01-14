#include <iostream>
#include <cmath>
#include <complex>
#include <vector>

struct ComplexMatrixSq {
	std::vector<std::vector<std::complex<double>>> pM;
	int size;

	ComplexMatrixSq() {
		pM.resize(1);
		for (auto x : pM) x.resize(1);
	}

	ComplexMatrixSq(double** tab,int n) {
		size = n;
		pM.resize(n);
		for (auto x : pM) x.resize(n);

		for (int w = 0; w < n; w++)
			for (int k = 0; k < n; k++)
				pM[w][k] = tab[w][k];
	}

	void print() {
		for (int w = 0; w < size; w++) {
			for (int k = 0; k < size; k++) {
				std::cout.width(8);
				std::cout << pM[w][k];
			}
			std::cout << std::endl << std::endl;
		}
				
	}
};

int main() {
	double xd[3][3] = {
		{23,12,11},
		{1,2,3},
		{2,6,7}
	};
	ComplexMatrixSq a(xd,3);
	a.print();

	int d;

	std::cin >> d;\
}