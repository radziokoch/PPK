#include <string>
#ifndef pwysocki_wyznacznik_macierzy_datautils
#define pwysocki_wyznacznik_macierzy_datautils

// maksymalny wymiar macierzy przewidziany dla tego programu
const int SIZE = 10;

/*
	Funkcja obslugujaca argumenty wywolania programu; pobierajaca nazwy pozadanych plikow wejsciowego i wyjsciowego,
	ktore uzytkownik wprowadza po odpowiednich przelacznikach (-i,-o), sprawdzajaca poprawnosc rozszerzenia pliku wejsciowego,
	obslugujaca przypadki podania niepoprawnych argumentow, wyswietlajaca pomoc w razie zapytania (przelacznik -h) lub bledu

	parametry funkcji:
	__________________
	argc		-- liczba argumentow wywolania programu
	argv		-- tablica zawierajaca kolejne argumenty jako ciagi znakow
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
	Funkcja obslugujaca pliki wejsciowy i wyjsciowy; obsluguje przypadki, kiedy plik nie mogl zostac otwarty
	lub kiedy plik wejsciowy jest pusty

	parametry funkcji:
	__________________
	&finName	-- referencja do zmiennej przechowujacej nazwe pliku WEJSCIOWEGO
	&foutName	-- referencja do zmiennej przechowujacej nazwe pliku WYJSCIOWEGO
	&fin		-- referencja do WEJSCIOWEGO strumienia plikowego,
	z ktorym zostanie skojarzony pozadany plik
	&fout		-- referencja do WYJSCIOWEGO strumienia plikowego,
	z ktorym zostanie skojarzony pozadany plik

	wartosc zwracana:
	_________________
	false		-- niepowodzenie przy probie powiazania pliku z odpowiednim strumieniem
	lub plik wejsciowy jest pusty
	true		-- udalo sie powiazac pliki ze strumieniami, plik wejsciowy zawiera dane

	uwagi:
	______
	jesli plik wejsciowy bedzie zawieral

	autor: Piotr Wysocki
	2016-11-01
*/
bool handleFiles(const std::string& finName, const std::string& foutName, std::ifstream& fin, std::ofstream& fout);

bool loadData(double M[SIZE][SIZE], int& dim, std::ifstream& fin);

#endif // !pwysocki_wyznacznik_macierzy_datautils