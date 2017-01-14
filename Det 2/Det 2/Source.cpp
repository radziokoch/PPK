#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const int MAX_DIM = 10;

double det_rek(const pwysocki::Matrix& m) {
	if (m.getDim() == 1) return m.get(0, 0);
	double sum = 0.0;
	double sgn = 1.0;
	for (int i = 0; i < m.getDim(); ++i) {
		sum += det_rek(m.minor(0, i)) * sgn * m.get(0, i);
		-sgn;
	}
	return sum;
}

bool loadData(std::ifstream& fin, int& size, double** &tab) {
	double		buffer[MAX_DIM*MAX_DIM + 1];		// bufor liczbowy z jednym miejscem zapasu (na wypadek przekroczenia zakresu)
	int			cnt = 0;				// ile liczb poprawnie wczytano z pliku
	const int	BAD_RATIO = 0;			// stala informujaca o niepoprawnych wymiarach macierzy


	size = BAD_RATIO;

	// wczytywanie kolejnych liczb do bufora
	while (fin >> buffer[cnt]) {
		cnt++;

		// sprawdzenie czy macierz z pliku nie jest zbyt duza
		if (cnt > MAX_DIM*MAX_DIM) {
			std::cout << "Przekroczono maksymalny dopuszczalny rozmiar macierzy";
			return false;
		}
	}

	// okreslenie wymiaru, jesli macierz jest kwadratowa
	for (int i = 1; i <= MAX_DIM; i++)
		if (i*i == cnt) size = i;

	// wczytana macierz nie jest kwadratowa lub jest 0x0
	if (size == BAD_RATIO) {
		std::cout << "Niepoprawne wymiary macierzy" << std::endl;
		return false;
	}

	// wczytana macierz jest kwadratowa
	else {
		tab = new double*[size];
		for (int i = 0; i < size; i++) tab[i] = new double[size];
		// wypelnienie przekazanej tablicy zawartoscia bufora  
		for (int r = 0; r < size; r++)
			for (int c = 0; c < size; c++)
				tab[r][c] = buffer[r*size + c];
		return true;
	}
}

int main(int argc, char** argv) {
	
	std::ifstream fin("test.txt");
	int size;
	double** vv = nullptr;
	
	size = 2;

	vv = new double*[size];
	vv[0] = new double[size];
	vv[1] = new double[size];
	vv[0][0] = 1.0;
	vv[0][1] = 2.0;
	vv[1][0] = 3.0;
	vv[1][1] = 5.0;

	double** vi;
	int size2 = 0;
	loadData(fin, size2, vi);
	pwysocki::Matrix M2(vi, size2);

	pwysocki::Matrix M(vv,size);
	M.print();
	std::cout << "\n\n";
	M.getMinor(0, 0).print();

	std::cout << det_rek(M2);
	int d;
	std::cin >> d;
}

