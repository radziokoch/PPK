#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


bool ruch(int** szachownica, const int &N, int wariant, int x, int y, int &nx, int &ny)
{
	switch (wariant)
	{
	case 0:
		nx = x + 1;
		ny = y - 2;
		break;
	case 1:
		nx = x + 2;
		ny = y - 1;
		break;
	case 2:
		nx = x + 2;
		ny = y + 1;
		break;
	case 3:
		nx = x + 1;
		ny = y + 2;
		break;
	case 4:
		nx = x - 1;
		ny = y + 2;
		break;
	case 5:
		nx = x - 2;
		ny = y + 1;
		break;
	case 6:
		nx = x - 2;
		ny = y - 1;
		break;
	case 7:
		nx = x - 1;
		ny = y - 2;
		break;
	}
	if (nx >= 0 && nx<N && ny >= 0 && ny<N && szachownica[nx][ny] == 0)
		return true;
	return false;
}


bool skoczek(int** szachownica, const int &n, int x, int y, int ktory, ofstream& plik_wyjsciowy)
{
	int nx, ny, w;

	szachownica[x][y] = ktory;

	if (ktory == n*n)
	{
		for (int i = 0; i<n; i++)
		{
			plik_wyjsciowy << endl;
			for (int j = 0; j<n; j++)
				plik_wyjsciowy << szachownica[j][i] << " ";

		}

		return 1;
	}
	else
	{
		for (w = 0; w<8; w++)
			if (ruch(szachownica, n, w, x, y, nx, ny) == true)
				if (skoczek(szachownica, n, nx, ny, ktory + 1, plik_wyjsciowy) == true)
					return true;
		szachownica[x][y] = 0;
	}

	return false;
}

void clearfield(int** szachownica, const int &n)
{
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			szachownica[i][j] = 0;
}

bool check(int argc, string* argv, string& nazwaPliku, int& max)
{
	nazwaPliku = "";
	
	const string opi("-o");
	const string opn("-n");

	for (int i = 1; i < argc - 1; i++) {

		// Napotkano "-i"
		if (argv[i] == opi) nazwaPliku = argv[i + 1];

		// Napotkano "-n"
		else if (argv[i] == opn) max = atoi(argv[i + 1].c_str());

	}

	if (nazwaPliku == "") return false;
	else return true;
}
int main(int argc, char** argv)
{
	string* argv_str = new string[argc];
	for (int i = 0; i < argc; i++) argv_str[i] = argv[i];
	int max;
	string nazwaPliku;
	ofstream plik_wyjsciowy;
	if (check(argc, argv_str, nazwaPliku,max) == true)
	{
		plik_wyjsciowy.open(nazwaPliku);
		int** szachownica = new int*[max];
		for (int i = 0; i < max; i++)
			szachownica[i] = new int[max];

		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
			{
				clearfield(szachownica, max);
				plik_wyjsciowy << "\n(i,j)= " << i << ", " << j << endl;
				if (skoczek(szachownica, max, i, j, 1, plik_wyjsciowy) == true)
					skoczek(szachownica, max, i, j, 1, plik_wyjsciowy);

				else
					plik_wyjsciowy << "brak rozwiazan dla tego punktu" << endl;

			}

		for (int i = 0; i < max; i++)
		delete[] szachownica[i];

		plik_wyjsciowy.close();

		delete[] argv_str;
		return 0;
	}

}