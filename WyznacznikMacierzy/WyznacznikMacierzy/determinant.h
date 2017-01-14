#include <string>

#ifndef pwysocki_wyznacznik_macierzy_determinant
#define pwysocki_wyznacznik_macierzy_determinant

// maksymalny wymiar macierzy przewidziany dla tego programu
const int SIZE = 10;

/*
	Funkcja tworzaca minor z zadanej macierzy poprzez wykreslenie pierwszego wiersza i jednej z kolumn,
	a nastepnie "dosuwajaca" do gornego lewego rogu zawierajacej go tablicy,
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
void rearrange(double M[SIZE][SIZE], double rM[SIZE][SIZE], int dim, int piv);

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
double determinant(double M[SIZE][SIZE], int dim);



#endif // !pwysocki_wyznacznik_macierzy_determinant
