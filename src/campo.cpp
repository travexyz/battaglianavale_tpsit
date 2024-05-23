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
    srand(time(NULL));

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

// Funzione per verificare se la nave è stata affondata, usata in gestisciColpi
bool esisteNave(Campo *campo, char nave)
{
    for (size_t i = 0; i < campo->dimensione; i++)
    {
        for (size_t j = 0; j < campo->dimensione; j++)
        {
            if (campo->campo[i][j] == nave)
            {
                return true; // La nave non è ancora completamente affondata
            }
        }
    }
    return false; // La nave è completamente affondata
}

void gestisciColpi(Campo *&campoNavi, Campo *&campoTattico)
{
    unsigned short int xColpo = 0, yColpo = 0;

    do
    {
        clearScreen();
        stampaCampo(campoTattico);
        std::cout << "Colpi disponibili: " << campoNavi->colpiDisponibili << std::endl;
        std::cout << "Navi ancora intatte: " << campoNavi->numeroNavi << std::endl;
        std::cout << "Inserisci le coordinate del tuo colpo: (x invia e poi y)" << std::endl;
        std::cin >> yColpo >> xColpo;

        clearScreen();

        // Se il colpo esce dal campo
        if (xColpo > campoTattico->dimensione - 1 || xColpo < 0 || yColpo > campoTattico->dimensione - 1 || yColpo < 0)
        {
            scriviConEffetto("Inserisci delle coordinate valide!", 20);
            sleep(2);
            continue;
        }

        // Se ho gia colpito quella posizione
        if (campoNavi->campo[xColpo][yColpo] == 'C' || campoTattico->campo[xColpo][yColpo] == 'O')
        {
            scriviConEffetto("Hai già colpito questa posizione!", 20);
            sleep(2);
            continue;
        }

        // Se colpisco una nave
        if (std::isdigit(campoNavi->campo[xColpo][yColpo]))
        {
            campoNavi->colpiDisponibili--;
            
            char naveDaCercare = campoNavi->campo[xColpo][yColpo];
            campoNavi->campo[xColpo][yColpo] = 'C';

            // Se ho affondato la nave
            if (!esisteNave(campoNavi, naveDaCercare))
            {
                clearScreen();
                scriviConEffetto("Nave completamente affondata!", 20);
                campoNavi->campo[xColpo][yColpo] = 'X';
                campoTattico->campo[xColpo][yColpo] = 'X';
                campoNavi->numeroNavi--;

                sleep(2);
                continue;
            }
            else
            {
                clearScreen();
                scriviConEffetto("Hai colpito parzialmente una nave!", 20);
                campoTattico->campo[xColpo][yColpo] = 'C';

                sleep(2);
                continue;
            }
        }
        if (campoNavi->campo[xColpo][yColpo] == '~')
        {
            clearScreen();
            scriviConEffetto("Acqua, ridireziona i tuoi colpi!", 20);
            campoTattico->campo[xColpo][yColpo] = 'A';

            sleep(2);
            continue;
        }
    } while (campoNavi->numeroNavi > 0 && campoNavi->colpiDisponibili > 0);
}

void fineGioco(Campo *&campoNavi)
{
    clearScreen();

    std::cout << "Questa era la posizione delle navi: " << std::endl;
    stampaCampo(campoNavi);

    if (campoNavi->numeroNavi <= 0 || campoNavi->colpiDisponibili <= 0)
    {
        std::cout << " _______                            _______                   " << std::endl;
        std::cout << "|     __|.---.-.--------.-----.    |       |.--.--.-----.----." << std::endl;
        std::cout << "|    |  ||  _  |        |  -__|    |   -   ||  |  |  -__|   _|" << std::endl;
        std::cout << "|_______||___._|__|__|__|_____|    |_______| \\___/|_____|__|  " << std::endl;
        std::cout << "Hai perso! Prova a rigiocare magari qualche volta vinci anche!" << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << " ___ ___                   ________              " << std::endl;
        std::cout << "|   |   |.-----.--.--.    |  |  |  |.-----.-----." << std::endl;
        std::cout << " \\     / |  _  |  |  |    |  |  |  ||  _  |     |" << std::endl;
        std::cout << "  |___|  |_____|_____|    |________||_____|__|__|" << std::endl;
        std::cout << "Strano, hai vinto! Hai affondato tutte le navi!" << std::endl
                  << std::endl;
    }
}

bool wantToContinue()
{
    std::cout << "Il gioco è finito. Vuoi rigiocare? (s/n): ";
    char risposta;
    std::cin >> risposta;

    if ((risposta == 's' || risposta == 'S'))
    {
        clearScreen();
        return true;
    }
    else
    {
        std::cout << "Fine del gioco. Arrivederci!" << std::endl;
        return false;
    }
}