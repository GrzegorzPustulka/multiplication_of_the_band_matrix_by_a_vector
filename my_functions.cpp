#include <stdio.h>
#include <stdlib.h>
#include "errors.cpp"
#include <string.h>

#pragma warning(disable:4996)

extern void bledy();
extern void bladMacierzKwadratowa();
extern void bladMnozenieMacierzy();
extern void bladMacierzyPasmowej();
double** macierzPasmowa(int *liczba_kolumn_w_macierzy, int *liczba_wierszy_w_macierzy)
{
	FILE* fw = fopen("macierzWstegowa.txt", "r");

	if (fw == NULL)
	{
		bledy();
		exit(1);
	}
	
	char znak;
	int liczba_kolumn = 0;
	int max_liczba_kolumn = 0;
	int liczba_wierszy = 0;
	int pomoc_kolumny = 0;

	while ((znak = getc(fw)) != EOF)
	{
		if (znak == ' ')
		{
			pomoc_kolumny++;
		}
		else if (znak == '\n')
		{
			pomoc_kolumny++;
			if (liczba_kolumn < pomoc_kolumny)
				liczba_kolumn = pomoc_kolumny;
			liczba_wierszy++;
			pomoc_kolumny = 0;
		}
		else
			continue;

	}
	liczba_wierszy++;

	if (liczba_kolumn != liczba_wierszy)
		bladMacierzKwadratowa();
	
	*liczba_kolumn_w_macierzy = liczba_kolumn;
	*liczba_wierszy_w_macierzy = liczba_wierszy;

	double** macierz = (double**)malloc(sizeof(double*) * liczba_wierszy);
	if (!macierz)
	{
		bledy();
		exit(3);
	}
	int i;
	for (i = 0; i < liczba_kolumn; i++)
	{
		macierz[i] = (double*)malloc(sizeof(double) * liczba_kolumn);
		if (!macierz[i])
		{
			bledy();
			exit(4);
		}
	}

	rewind(fw);

	int j;
	for (i = 0; i < liczba_kolumn; i++)
		for (j = 0; j < liczba_wierszy; j++)
			fscanf(fw, "%lf", &macierz[i][j]);

	fclose(fw);

	return macierz;
}
double* wektorOdczyt(int * liczba_wierszy_w_wektorze)
{
	FILE* fp = fopen("wektor.txt", "r");

	if (fp == NULL)
	{
		bledy();
		exit(5);
	}
	int liczba_wierszy = 1;
	char znak;
	while ((znak = getc(fp)) != EOF)
	{
		if (znak == '\n')
			liczba_wierszy++;
	}
	*liczba_wierszy_w_wektorze = liczba_wierszy;

	double* wektor = (double*)malloc(sizeof(double) * liczba_wierszy);
	if (!wektor)
	{
		bledy();
		exit(6);
	}
	int i;

	rewind(fp);

		for (i = 0; i < liczba_wierszy; i++)
			fscanf(fp, "%lf", &wektor[i]);
	
	fclose(fp);

	return wektor;
}
int dlugoscPasma(double** macierz, double* wektor, int liczba_kolumn_w_macierzy, int liczba_wierszy_w_macierzy)
{
	int i, j;
	int a;
	int dlugosc_pasma = 0;
	int max_dlugosc_pasma = 0;
	for(i = 0; i < liczba_wierszy_w_macierzy; i ++)
		for (j = 0; j < liczba_kolumn_w_macierzy; j++)
		{
			if (i == j)
			{
				for(a = j; a < liczba_kolumn_w_macierzy -j;a++)
				{ 
					if (macierz[i][a] != 0)
						dlugosc_pasma++;
					else
					{
						if (dlugosc_pasma > max_dlugosc_pasma)
							max_dlugosc_pasma = dlugosc_pasma;

						dlugosc_pasma = 0;
						break;
					}
				}
			}
		}

	max_dlugosc_pasma = (max_dlugosc_pasma - 1) * 2 + 1;
	
	return max_dlugosc_pasma;
}
void czyToJestMacierzWstegowa(double **macierz, int liczba_wierszy, int liczba_kolumn, int pasmo)
{
	int i;
	int j;
	int x;
	int pol_pasma = (pasmo - 1) / 2 + 1;

	for (i = 0; i < liczba_wierszy; i++)
	{
		for (j = 0; j < liczba_kolumn; j++)
		{
			if (i == j)
			{
				for (x = j + pol_pasma; x < liczba_kolumn; x++)
					if (macierz[i][x] != 0)
						bladMacierzyPasmowej();
			}
		}
	}
}
void czyMoznaPomnozycMacierze(int liczba_kolumn_w_macierzy, int liczba_wierszy_w_wektorze)
{
	if (liczba_kolumn_w_macierzy != liczba_wierszy_w_wektorze)
		bladMnozenieMacierzy();
}
double** redukcjaMacierzyPasmowej(double** macierz_wstegowa, int liczba_wierszy_w_macierzy, int pasmo, int liczba_kolumn_w_macierzy)
{
	double** macierz = (double**)malloc(sizeof(double*) * liczba_wierszy_w_macierzy);
	if (!macierz)
	{
		bledy();
		exit(8);
	}
	int i;
	for (i = 0; i < liczba_wierszy_w_macierzy; i++)
	{
		macierz[i] = (double*)malloc(sizeof(double) * pasmo);
		if (!macierz[i])
		{
			bledy();
			exit(9);
		}
	}
	int j = 0;
	int a;
	int pol_pasma = (pasmo - 1) / 2;
	int b;
	int c;
	int z = 0;
	int x = 0;

	for (i = 0; i < liczba_wierszy_w_macierzy; i++)
		for (j = 0; j < liczba_kolumn_w_macierzy; j++)
		{
			if (i == j)
			{
				b = (liczba_kolumn_w_macierzy - pol_pasma + i);
				c = (liczba_kolumn_w_macierzy - pol_pasma + i) % liczba_kolumn_w_macierzy;
				for (a = 0; a < pasmo; a++)
				{
					if (b < liczba_kolumn_w_macierzy)
					{
						macierz[i][a] = macierz_wstegowa[i][b];
						b++;

						if (b == liczba_kolumn_w_macierzy)
							for (x = 0; x < pasmo - a - 1; x++)
								macierz[i][x + a + 1] = macierz_wstegowa[i][x];

						if (x + a + 1 == pasmo)
						{
							x = 0;
							break;
						}
					}
					else
					{
						macierz[i][a] = macierz_wstegowa[i][c];
						c++;

						if (c == liczba_kolumn_w_macierzy)
							for (x = 0; x < pasmo - a - 1; x++)
								macierz[i][x + a + 1] = macierz_wstegowa[i][x];

						if (x + a + 1 == pasmo)
							break;
					}

				}
			}
		}

	if (macierz_wstegowa)
	{
		for (i = 0; i < liczba_wierszy_w_macierzy; i++)
		{
			if (macierz_wstegowa[i])
			{
				free(macierz_wstegowa[i]);
			}
		}
		free(macierz_wstegowa);
		macierz_wstegowa = NULL;
	}



	return macierz;
}
double* mnozenieMacierzy(double **macierz, double *wektor, int w_macierzy,int k_macierzy, int pasmo)
{
	double* wynik = (double*)malloc(sizeof(double) * w_macierzy);
	if (!wynik)
	{
		bledy();
		exit(10);
	}
	int i, j, c, z = 0,x = 1,s = 1;

	for (i = 0; i < w_macierzy; i++)
		wynik[i] = 0;

	for (i = 0; i < w_macierzy; i++)
	{
		c = (pasmo - 1) / 2 - i;
		if (c >= 0)
		{
			for (j = c; j < pasmo; j++)
			{
				wynik[i] += macierz[i][j] * wektor[z];
				z++;
			}
			z = 0;
		}
		else
		{
			for (j = 0; j < pasmo; j++)
			{
				wynik[i] += macierz[i][j] * wektor[s];
				s++;
			}
			x++;
			s = x;
		}
	}
	return wynik;
}

void wyswietlenieWyniku(double** macierz, double* wektor, double* wynik, int w_macierzy,int pasmo)
{
	int i;
	int j;
	for (i = 0; i < w_macierzy; i++)
	{
		for (j = 0; j < pasmo; j++)
		{
			printf("%.1lf ", macierz[i][j]);
		}
		if (w_macierzy / 2 == i)
		{
			printf("         *        %.1lf", wektor[i]);
			printf("         =        %5.1lf", wynik[i]);
			printf("\n");
		}
		else
		{
			printf("    %17.1lf", wektor[i]);
			printf("    %19.1lf", wynik[i]);
			printf("\n");
		}
	}

	if (macierz)
	{
		for (i = 0; i < w_macierzy; i++)
		{
			if (macierz[i])
			{
				free(macierz[i]);
			}
		}
		free(macierz);
		macierz = NULL;
	}

	if (wynik)
		free(wynik);
	wynik = NULL;

	if (wektor)
		free(wektor);
	wektor = NULL;
}
