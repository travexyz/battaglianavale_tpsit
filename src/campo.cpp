#include <iostream>
#include <time.h>

#include "../include/campo.h"

void inizializzaCampo(Campo &campo)
{
    srand(time(NULL));

    // Inizializza il campo con spazi vuoti
    for (size_t i = 0; i < campo.dimensione; i++)
    {
        campo.campo[i] = new char[campo.dimensione];
        for (size_t j = 0; j < campo.dimensione; j++)
        {
            campo.campo[i][j] = '-';
        }
    }
}

void inserisciNavi(Campo &campo)
{
    // Posiziona le navi
    for (size_t n = 0; n < campo.numeroNavi; n++)
    {
        int lunghezzaNave = rand() % 3 + 2; // Lunghezza casuale tra 2 e 5

        // Se gioco con 9 navi, definisco le lughezze delle navi come nel gioco originale
        if (campo.numeroNavi == 9)
        {
            switch (n)
            {
            case 0:
                lunghezzaNave = 6;
                break;
            case 1:
                lunghezzaNave = 4;
                break;
            case 2:
                lunghezzaNave = 4;
                break;
            case 3:
                lunghezzaNave = 3;
                break;
            case 4:
                lunghezzaNave = 3;
                break;
            case 5:
                lunghezzaNave = 3;
                break;
            case 6:
                lunghezzaNave = 2;
                break;
            case 7:
                lunghezzaNave = 2;
                break;
            case 8:
                lunghezzaNave = 2;
                break;

            default:
                break;
            }
        }
        int altezzaNave = 1; // Le navi hanno sempre uno spessore di 1
        int coordNaveX = rand() % campo.dimensione;
        int coordNaveY = rand() % campo.dimensione;
        int direzione = rand() % 2; // 0 per orizzontale, 1 per verticale

        // Verifica se la nave può essere posizionata nella posizione generata
        bool posizioneValida = true;
        if (direzione == 0) // Orizzontale
        {
            if (coordNaveX + lunghezzaNave > campo.dimensione - 1)
                posizioneValida = false;
            else
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                {
                    // Se la cella non è vuota, quindi è presente
                    // un carattere diverso dal vuoto '-', invalido la posizione
                    if (campo.campo[coordNaveY][coordNaveX + i] != '-')
                    {
                        posizioneValida = false;
                        break;
                    }
                }
            }
        }
        else // Verticale
        {
            if (coordNaveY + lunghezzaNave > campo.dimensione)
                posizioneValida = false;
            else
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                {
                    if (campo.campo[coordNaveY + i][coordNaveX] != '-')
                    {
                        posizioneValida = false;
                        break;
                    }
                }
            }
        }

        // Se la posizione è valida, posiziona la nave
        if (posizioneValida)
        {
            if (direzione == 0) // Orizzontale
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                    campo.campo[coordNaveY][coordNaveX + i] = n + '0'; // '0' per convertire il numero in carattere
            }
            else // Verticale
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                    campo.campo[coordNaveY + i][coordNaveX] = n + '0';
            }
        }
        else
            // Torno indietro nel ciclo per generare un'altra nave
            // visto che la precedente non aveva una posizione valida
            n--;
    }
}

void stampaCampo(Campo campo)
{
    // Scrivo le coordinate orizzontali
    std::cout << "  ";
    for (size_t i = 0; i < campo.dimensione; i++)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    for (size_t i = 0; i < campo.dimensione; i++)
    {
        // Scrivo le coordinate verticali
        std::cout << i << " ";

        for (size_t j = 0; j < campo.dimensione; j++)
        {
            std::cout << campo.campo[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{

    Campo campo;
    campo.dimensione = 10;
    campo.campo = new char *[campo.dimensione];
    campo.numeroNavi = 9;
    inizializzaCampo(campo);
    inserisciNavi(campo);
    stampaCampo(campo);

    return EXIT_SUCCESS;
}
