#include <iostream>
#include <time.h>

#include "campo.h"

void inizializzaCampo(Campo campo)
{
    srand(time(NULL));

    for (int i = 0; i < campo.numeroNavi; i++)
    {
        int x = rand() % campo.dimensione;
        int y = rand() % campo.dimensione;
        campo.campo[x][y] = 'N';
    }
}

void stampaCampo(Campo campo)
{
    for (int i = 0; i < campo.dimensione; i++)
    {
        for (int j = 0; j < campo.dimensione; j++)
        {
            std::cout << campo.campo[i][j] << " ";
        }
        std::cout << std::endl;
    }
}