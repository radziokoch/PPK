#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <bitset>

using std::cout;
using std::cin;
using std::endl;
using std::cout;
using std::cerr;

// maksymalny wymiar macierzy przewidziany dla tego programu
const int DIM = 10;

/*
	Funkcja tworzaca minor z zadanej macierzy poprzez wykreslenie pierwszego wiersza i jednej z kolumn,
	a nastepnie "spajajaca" go do postaci kwadratu i "dosuwajaca" do gornego lewego rogu zawierajacej go tablicy, 
	tak aby mozliwe bylo dalsze rozwijanie wyznacznika

	parametry funkcji:
	__________________
	M		-- tablica dwuwymiarowa zawierajaca zadana macierz
	rM		-- tablica dwuwymiarowa w ktorej zostanie zawarty minor
	dim		-- liczba okreslajaca wymiar macierzy z ktorej brany jest minor
			   (operacje odbywaja sie wtedy na podtablicy z rM o wymiarach dim x dim, 
			   ktorej pierwszy wyraz znajduje sie w gornym lewym rogu)
	piv		-- liczba okreslajaca kolumne (os) wykreslana wraz z pierwszym wierszem 
			   celem utworzenia minora

	wartosc zwracana:
	_________________
	brak

	autor: Piotr Wysocki
	2016-10-18
*/
void rearrange(double M[DIM][DIM], double rM[DIM][DIM], int dim, int piv);

/*
	Funkcja obliczajaca wyznacznik z zadanej macierzy (max 10x10) przy pomocy rozwiniecia LaPlace'a (korzysta z rekurencji)

	parametry funkcji:
	__________________
	M		-- tablica dwuwymiarowa zawierajaca zadana macierz
	dim		-- liczba okreslajaca wymiar danej macierzy

	wartosc zwracana:
	_________________
	wyznacznik danej macierzy (double)

	uwagi:
	______
	korzysta z funkcji rearrange(double (*)[10], double(*)[10],int,int)

	autor: Piotr Wysocki
	2016-10-18
*/
double determinant(double M[DIM][DIM], int dim);

/*
	Funkcja obslugujaca argumenty wywolania programu; pobierajaca nazwy pozadych plikow wejsciowego i wyjsciowego,
	ktore uzytkownik wprowadza po odpowiednich przelacznikach (-i,-o), sprawdzajaca poprawnosc rozszerzenia pliku wejsciowego,
	obslugujaca przypadki podania niepoprawnych argumentow, wyswietlajaca pomoc w razie zadania (przelacznik -h) lub bledu 

	parametry funkcji:
	__________________
	argc		-- liczba argumentow wywolania programu
	argv		-- tablica zawierajaca argumenty jako ciagi znakow
	&finName	-- referencja do zmiennej przechowujacej nazwe pliku wejsciowego
	&foutName	-- referencja do zmiennej przechowujacej nazwe pliku wyjsciowego

	wartosc zwracana:
	_________________
	false	-- argumenty wywolania programu zawieraja bledy (jest ich za malo, niepoprawne rozszerzenie etc.) 
			   lub uzytkownik chce uzyskac pomoc			   
	true	-- argumenty poprawne

	uwagi:
	______
	przypadek, gdy uzytkownik rownoczesnie poda nazwy plikow oraz zazada pomocy (-h) jest potraktowany jak
	niepoprawne argumenty - zostaje wyswietlona wowczas pomoc, a funkcja zwraca false

	autor: Piotr Wysocki
	2016-10-31
*/
bool handleArgs(int argc, std::string* argv, std::string& finName, std::string& foutName);

/*
	Funkcja 
*/
bool handleFiles(const std::string& finName, const std::string& foutName, std::ifstream& fin, std::ofstream& fout);

bool loadData(double M[DIM][DIM], int& dim, std::ifstream& fin);

void printHelp();


int main(int argc, char** argv) {
	
	std::ofstream	fout;		
	std::string		foutName;	
	std::ifstream	fin;		
	std::string		finName;	
	std::string*	argvS =		
		new std::string[argc];	
	int				dim;
	double			M[DIM][DIM];

	for (int i = 0; i < argc; i++) argvS[i] = argv[i];

	if (handleArgs(argc, argvS, finName, foutName)) {
		if (handleFiles(finName, foutName, fin, fout)) {
			if (loadData(M, dim, fin)) {
				double det = determinant(M, dim);
				fout << determinant(M, dim);
				cout << "det M = " << det;
			}
			fin.close();
			fout.close();
		}
	}

	delete[] argvS;
	return 0;
}

void rearrange(double M[DIM][DIM], double rM[DIM][DIM], int dim, int piv) {
	for (int r = 0; r < dim; r++)
		for (int c = 0; c < dim; c++)
			rM[r][c] = M[r][c];
	for (int left = piv + 1; left < dim; left++)
		for (int r = 0; r < dim; r++)
			rM[r][left - 1] = rM[r][left];
	for (int c = 0; c < dim; c++)
		for (int r = 1; r < dim; r++)
			rM[r - 1][c] = rM[r][c];
	return;
}

double determinant(double M[DIM][DIM], int dim) {
	if (dim == 1)
		return M[0][0];
	double rM[DIM][DIM];
	double sum = 0.0;
	double sgn = 1.0;
	for (int piv = 0; piv < dim; piv++) {
		rearrange(M, rM, dim, piv);
		sum += determinant(rM, dim - 1) * sgn * M[0][piv];
		sgn = -sgn;
	}
	return sum;
}

void printHelp() {
	cout << "Wyznacznik Macierzy (autor: Piotr Wysocki) \n\t-i [plik wejsciowy *.mac] -o [plik wyjsciowy]" << endl;
}

bool handleArgs(int argc, std::string* argv, std::string& finName, std::string& foutName) {
	const std::string				SWITCH_IN("-i");
	const std::string				SWITCH_OUT("-o");
	const std::string				INPUT_FILE_EXTENSION(".mac");
	const int						SIZE_BITSET = 2;
	const std::bitset<SIZE_BITSET>	FLAG_IN(1);
	const std::bitset<SIZE_BITSET>	FLAG_OUT(FLAG_IN << 1);
	const std::bitset<SIZE_BITSET>	FLAG_OK(FLAG_IN | FLAG_OUT);
	std::bitset<SIZE_BITSET>		STATE(0);

	if (argc == 1 || ((argc == 2) && (argv[1] == "-h"))) {}

	else if (argc == 5) {
		for (int i = 1; i < argc - 1; i++) {
			if (argv[i] == SWITCH_IN) {
				finName = argv[i + 1];
				if (finName.length() > 4
					&& finName.substr(finName.length() - 4, 4) == INPUT_FILE_EXTENSION)
					STATE |= FLAG_IN;
				else cerr << "Blad! Niepoprawna nazwa lub rozszerzenie pliku wejsciowego" << endl;
			}
			else if (argv[i] == SWITCH_OUT) {
				foutName = argv[i + 1];
				STATE |= FLAG_OUT;
			}
			//else 
			//	cerr << "Blad! Nie odnaleziono wymaganych argumentow" << endl;
		}
	}

	else
		cerr << "Blad! Niepoprawne argumenty" << endl;

	if (STATE == FLAG_OK) return true;
	else {
		printHelp();
		return false;
	}
}

bool handleFiles(const std::string& finName, const std::string& foutName, std::ifstream& fin, std::ofstream& fout) {
	bool isSuccessful = true;

	fin.open(finName);
	if (!fin.is_open()) {
		cerr << "Blad pliku wejsciowego!" << endl;
		isSuccessful = false;
	}
	fout.open(foutName);
	if (!fout.is_open()) {
		cerr << "Blad pliku wyjsciowego!" << endl;
		isSuccessful = false;
	}

	fin.seekg(0, std::ios_base::end);
	if (fin.tellg() == (std::streampos)0) {
		cerr << "Blad! Plik wejsciowy pusty" << endl;
		isSuccessful = false;
	}
	fin.seekg(std::ios_base::beg);

	return isSuccessful;
}

bool loadData(double M[DIM][DIM], int& dim, std::ifstream& fin) {
	double		buffer[DIM*DIM];
	int			cnt = 0;
	const int	NOT_SQUARE_DIM = 0;

	dim = NOT_SQUARE_DIM;
	while (fin >> buffer[cnt]) cnt++;
	for (int i = 1; i <= DIM; i++)
		if (i*i == cnt) dim = i;

	if (dim == NOT_SQUARE_DIM) {
		cerr << "Blad! Niepoprawne wymiary macierzy" << endl;
		return false;
	}

	else {
		for (int r = 0; r < dim; r++)
			for (int c = 0; c < dim; c++)
				M[r][c] = buffer[r*dim + c];
		return true;
	}
}

