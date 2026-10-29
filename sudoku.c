#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 9
int provera(int tabla[N][N], int red, int kol, int br)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        if (tabla[red][i] == br)
            return 0;
    }
    for (i = 0; i < N; i++)
    {
        if (tabla[i][kol] == br)
            return 0;
    }
    int red_kvadrata = red - red % 3;
    int kolona_kvadrata = kol - kol % 3;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (tabla[red_kvadrata + i][kolona_kvadrata + j] == br)
                return 0;
        }
    }
    return 1;
}
int nadjiprazan(int tabla[N][N], int* red, int* kol)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (tabla[i][j] == 0)
            {
                *red = i;
                *kol = j;
                return 1;
            }
        }
    }
    return 0;
}
int resiSudoku(int tabla[N][N])
{
    int red, kol;
    if (!nadjiprazan(tabla, &red, &kol))
        return 1;
    for (int br = 1; br <= 9; br++)
    {
        if (provera(tabla, red, kol, br))
        {
            tabla[red][kol] = br;

            if (resiSudoku(tabla))
                return 1;
            tabla[red][kol] = 0;
        }
    }
    return 0;
}
void ispisi_sudoku(int tabla[N][N])
{
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            printf("___________________\n");
        }
        for (int j = 0; j < N; j++)
        {
            if (j == 0)
                printf("|");
            if (j % 3 != 2)
                printf("%d ", tabla[i][j]);
            else if (j % 3 == 2)
            {
                printf("%d", tabla[i][j]);
                printf("|");
            }
        }
        if (i % 3 == 2)
            printf("\n-------------------");
        printf("\n");
    }
}
int pravilno_popunjen(int tabla[N][N], int red, int kol)
{
    if(tabla[red][kol] == 0)
		return 1;
	int br = tabla[red][kol];
    tabla[red][kol] = 0;
    if(!provera(tabla, red, kol, br))
            return 0;
	tabla[red][kol] = br;
    return 1;
}
int popuni_sudoku(int tabla[N][N])
{
    printf("Unesite Sudoku (9x9, koristiti 0 za prazna polja):\n");
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            printf("__________________\n");
        }
        if (i % 3 == 0 && i != 0)
            printf("------------------\n");
        for (int j = 0; j < N; j++)
        {
            if (j == 0)
                printf("|");
            scanf("%d", &tabla[i][j]);
            if (tabla[i][j] > 9 || tabla[i][j] < 0 || !pravilno_popunjen(tabla,i,j))
            {
                printf("\nGreska pri unosu Sudokua\n");
                return 0;
            }
        }
    }
    return 1;
}
void vrati_tablu_na_pocetak(int tabla[N][N])
{
    for(int i=0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tabla[i][j] = 0;
        }
	}
}
int main()
{
    int tabla[N][N] = {0};
    int k = 1;
    while (k != 0)
    {
        printf("1. Unesite tablu Sudokua koju zelite da resite\n");
        printf("0. Kraj\n");
        scanf("%d", &k);
        if (k != 1 && k != 0)
            printf("Pogresan unos.\n");
        if (k == 1)
        {
            if (!popuni_sudoku(tabla))
                goto a;
            if (resiSudoku(tabla))
            {
                printf("\nResenje Sudokua:\n");
                ispisi_sudoku(tabla);
            }
            else
            {
                printf("\nNe postoji resenje.\n");
            }
        }
        a:;
        vrati_tablu_na_pocetak(tabla);
    }
    return 0;
}