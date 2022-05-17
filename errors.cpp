#pragma once
#pragma warning(disable:4996)
#include <string.h>
#include <locale.h>

void bledy()
{
	setlocale(LC_ALL, "Polish");
	int errnum;
	errnum = errno;
	fprintf(stderr, "numer b³êdu: %d\n", errno);
	fprintf(stderr, "nazwa b³êdu: %s\n", strerror(errnum));
}
void bladMacierzKwadratowa()
{
	fprintf(stderr, "Nie jest to macierz Kwadratowa\n");
	exit(2);
}
void bladMnozenieMacierzy()
{
	fprintf(stderr, "Zeby pomnozyc macierze liczba kolumn pierwszej musi byc rowna wierszy drugiej\n");
	exit(7);
}
void bladMacierzyPasmowej()
{
	fprintf(stderr, "Nie jest to macierz pasmowa");
	exit(11);
}