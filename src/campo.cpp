#include <iostream>
#include <time.h>

#include "../include/campo.h"
#include "../include/utils.h"

void inizializzaCampo(Campo *&campo)
{
    // Inizializza il campo con spazi vuoti
    for (size_t i = 0; i < campo->dimensione; i++)
    {
        campo->campo[i] = new char[campo->dimensione];
        for (size_t j = 0; j < campo->dimensione; j++)
        {
            campo->campo[i][j] = '~';
        }
    }
}

void inserisciNavi(Campo *&campo)
{
    // Posiziona le navi
    for (size_t n = 0; n < campo->numeroNavi; n++)
    {
        int lunghezzaNave = rand() % 3 + 2; // Lunghezza casuale tra 2 e 5

        // Se gioco con 9 navi, definisco le lughezze delle navi come nel gioco originale
        if (campo->numeroNavi == 9)
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
        int coordNaveX = rand() % campo->dimensione;
        int coordNaveY = rand() % campo->dimensione;
        int direzione = rand() % 2; // 0 per orizzontale, 1 per verticale

        // Verifica se la nave può essere posizionata nella posizione generata
        bool posizioneValida = true;
        if (direzione == 0) // Orizzontale
        {
            if (coordNaveX + lunghezzaNave > campo->dimensione - 1)
                posizioneValida = false;
            else
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                {
                    // Se la cella non è vuota, quindi è presente
                    // un carattere diverso dal vuoto "~", invalido la posizione
                    if (campo->campo[coordNaveY][coordNaveX + i] != '~')
                    {
                        posizioneValida = false;
                        break;
                    }
                }
            }
        }
        else // Verticale
        {
            if (coordNaveY + lunghezzaNave > campo->dimensione)
                posizioneValida = false;
            else
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                {
                    if (campo->campo[coordNaveY + i][coordNaveX] != '~')
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
                    campo->campo[coordNaveY][coordNaveX + i] = n + '0'; // '0' per convertire il numero in carattere
            }
            else // Verticale
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                    campo->campo[coordNaveY + i][coordNaveX] = n + '0';
            }
        }
        else
            // Torno indietro nel ciclo per generare un'altra nave
            // visto che la precedente non aveva una posizione valida
            n--;
    }
}

void stampaCampo(Campo *campo)
{
    // Scrivo le coordinate orizzontali
    std::cout << "  ";
    for (size_t i = 0; i < campo->dimensione; i++)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    for (size_t i = 0; i < campo->dimensione; i++)
    {
        // Scrivo le coordinate verticali
        std::cout << i << " ";

        for (size_t j = 0; j < campo->dimensione; j++)
        {
            std::cout << campo->campo[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Per la funzione gestisciColpi
bool hasSank(Campo *campo, char nave)
{
    std::cout << "chiamata hasSank, nave: " << nave << std::endl;
    for (size_t i = 0; i < campo->dimensione; i++)
    {
        for (size_t j = 0; j < campo->dimensione; j++)
        {
            // std::cout << campo->campo[i][j] == nave << std::endl;
            if (campo->campo[i][j] == nave)
<<<<<<< trave/fixcolpi
=======

>>>>>>> main
                return false;
        }
    }
    return true;
}

void gestisciColpi(Campo *&campoNavi, Campo *&campoTattico)
{
    unsigned short int xColpo, yColpo;
    while (campoNavi->numeroNavi > 0 && campoNavi->colpiDisponibili > 0)
    {
        clearScreen();
        stampaCampo(campoNavi);
        stampaCampo(campoTattico);
        scriviConEffetto("Tentativ numero " + campoNavi->colpiDisponibili, 10);
        scriviConEffetto("Inserisci le coordinate del tuo colpo: (x poi y)", 10);
        std::cin >> yColpo >> xColpo;

        char puntoCampoNavi = campoNavi->campo[xColpo][yColpo];
        char puntoCampoTattico = campoTattico->campo[xColpo][yColpo];

        campoNavi->colpiDisponibili--;

        // Se il colpo esce dal campo
        if (xColpo > campoTattico->dimensione - 1 || xColpo < 0 || yColpo > campoTattico->dimensione - 1 || yColpo < 0)
        {
            scriviConEffetto("Inserisci delle coordinate valide!", 20);
            sleep(2);
            continue;
        }

        // Se ho gia colpito quella posizione
        if (puntoCampoTattico == 'A' || puntoCampoTattico == 'X' || puntoCampoTattico == 'O')
        {
            scriviConEffetto("Hai già colpito questa posizione!", 20);
            sleep(2);
            continue;
        }

        // Se colpisco una nave
        if (isdigit(puntoCampoNavi))
        {
            // Se ho affondato la nave
            if (hasSank(campoNavi, puntoCampoNavi))
            {
                scriviConEffetto("Hai affondato la nave " + puntoCampoNavi, 20);
                sleep(2);
                puntoCampoTattico = puntoCampoNavi;
                campoNavi->numeroNavi--;
                continue;
            }
            else
            {
                scriviConEffetto("Hai colpito la nave " + puntoCampoNavi, 20);
                sleep(2);
                puntoCampoTattico = puntoCampoNavi;
                puntoCampoNavi = 'C';
                continue;
            }
        }
        if (puntoCampoNavi == '~')
        {
            scriviConEffetto("Hai colpito solo dell'acqua.", 20);
            sleep(2);
            puntoCampoTattico = 'O';
            continue;
        }
    }
}

void finegioco(Campo *&campoNavi, Campo *&campoTattico)
{
    int scelta = 0;
    if (campoNavi->numeroNavi == 0)
    {
        std::cout << "Hai completato il gioco e hai vinto! Complimenti!";
    }
    else
    {
        std::cout << "Sei stato battuto! Mi dispiace! Ritenta sarai più fortunato!" << std::endl;
        std::cout << "Per riniziare il gioco premi 1 per finire primi 0";
        std::cin >> scelta;
        if (scelta == 1)
        {
            inizializzaCampo(campoNavi);
            inserisciNavi(campoNavi);
            // stampaCampo(campoNavi);

            // Genero il campo dove vengono segnati i colpi
            Campo *campoTattico = new Campo;
            campoTattico->dimensione = campoNavi->dimensione;
            campoTattico->campo = new char *[campoTattico->dimensione];
            inizializzaCampo(campoTattico);

            // Inizio il gioco
            gestisciColpi(campoNavi, campoTattico);
            return;
        }
        else
        {
            EXIT_SUCCESS;
        }
    }
}