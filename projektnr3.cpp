#include <stdio.h>
#include <stdlib.h>
#include "my_functions.cpp"
#include "errors.cpp"
#include <string.h>

#pragma warning(disable:4996)

extern double** macierzPasmowa();
extern double* wektorOdczyt();
extern void czyMoznaPomnozycMacierze();
extern int dlugoscPasma();
extern double** redukcjaMacierzyPasmowej();
extern void mnozenieMacierzy();
extern void czyToJestMacierzWstegowa();
extern void wyswietlenieWyniku();

int main()
{
	int liczba_kolumn_w_macierzy;
	int liczba_wierszy_w_macierzy;
	int liczba_wierszy_w_wektorze;

	double** macierz_wstegowa = macierzPasmowa(&liczba_kolumn_w_macierzy, &liczba_wierszy_w_macierzy);
	double* wektor = wektorOdczyt(&liczba_wierszy_w_wektorze);
	czyMoznaPomnozycMacierze(liczba_kolumn_w_macierzy, liczba_wierszy_w_wektorze);
	int pasmo = dlugoscPasma(macierz_wstegowa, wektor, liczba_kolumn_w_macierzy, liczba_wierszy_w_macierzy);
	czyToJestMacierzWstegowa(macierz_wstegowa, liczba_wierszy_w_macierzy, liczba_kolumn_w_macierzy, pasmo);
	double** zredukowanaMacierzPasmowa = redukcjaMacierzyPasmowej(macierz_wstegowa, liczba_wierszy_w_macierzy, pasmo, liczba_kolumn_w_macierzy);
	double* wynik = mnozenieMacierzy(zredukowanaMacierzPasmowa, wektor, liczba_wierszy_w_macierzy, liczba_kolumn_w_macierzy, pasmo);
	wyswietlenieWyniku(zredukowanaMacierzPasmowa, wektor, wynik, liczba_wierszy_w_macierzy, pasmo);

	return 0;
}