# Manuale Tecnico per il Codice di Gioco delle Navi
Questo documento fornisce una guida tecnica dettagliata per comprendere e lavorare con il codice del gioco delle navi, scritto in C++. Esploreremo le funzioni principali, la struttura del codice e alcuni suggerimenti per l'estensione e la modifica.
## Indice
   - [Struttura del Progetto](#struttura-del-progetto)
   - [Descrizione delle Funzioni](#descrizione-delle-funzioni)
   - [inizializzaCampo](#inizializzacampo)
   - [inserisciNavi](#inseriscinavi)
   - [stampaCampo](#stampacampo)
   - [esisteNave](#esistenave)
   - [gestisciColpi](#gestiscicolpi)
   - [fineGioco](#finegioco)
   - [wantToContinue](#wanttocontinue)
   - [Suggerimenti per l'Estensione](#suggerimenti-per-lestensione)
## Struttura del Progetto
Il progetto è suddiviso in vari file, con le seguenti inclusioni principali:
- `#include <iostream>`
- `#include <time.h>`
- `#include "../include/campo.h"`
- `#include "../include/utils.h"`
Le funzioni principali sono definite nel file sorgente principale e utilizzano strutture e funzioni dichiarate negli header inclusi.
## Descrizione delle Funzioni
### inizializzaCampo
```cpp
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
```
Questa funzione inizializza il campo di gioco, riempiendolo con caratteri vuoti (`~`). Si itera attraverso le dimensioni del campo, allocando la memoria per ogni riga e impostando ogni cella con il carattere vuoto.
### inserisciNavi
```cpp
void inserisciNavi(Campo *&campo)
{
    srand(time(NULL));
    // Posiziona le navi
    for (size_t n = 0; n < campo->numeroNavi; n++)
    {
        int lunghezzaNave = rand() % 3 + 2; // Lunghezza casuale tra 2 e 5
        // Se gioco con 9 navi, definisco le lunghezze delle navi come nel gioco originale
        if (campo->numeroNavi == 9)
        {
            // Logica per le lunghezze delle navi specifica
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
                    campo->campo[coordNaveY][coordNaveX + i] = n + '0';
            }
            else // Verticale
            {
                for (size_t i = 0; i < lunghezzaNave; i++)
                    campo->campo[coordNaveY + i][coordNaveX] = n + '0';
            }
        }
        else
            n--;
    }
}
```
Questa funzione posiziona le navi nel campo in posizioni casuali. La lunghezza e la direzione delle navi sono determinate casualmente. La funzione verifica anche se la posizione generata è valida e, in caso contrario, ripete il processo fino a trovare una posizione valida.
### stampaCampo
```cpp
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
```
Questa funzione stampa il campo di gioco sullo schermo, mostrando sia le coordinate orizzontali che verticali, seguite dai valori delle celle del campo.
### esisteNave
```cpp
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
```
Questa funzione verifica se una nave specifica (identificata dal carattere `nave`) è ancora presente nel campo di gioco. Se una cella contiene ancora il carattere della nave, essa non è stata completamente affondata.
### gestisciColpi
```cpp
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
        if (xColpo > campoTattico->dimensione - 1 || xColpo < 0 || yColpo > campoTattico->dimensione - 1 || yColpo < 0)
        {
            scriviConEffetto("Inserisci delle coordinate valide!", 20);
            sleep(2);
            continue;
        }
        if (campoNavi->campo[xColpo][yColpo] == 'C' || campoTattico->campo[xColpo][yColpo] == 'O')
        {
            scriviConEffetto("Hai già colpito questa posizione!", 20);
            sleep(2);
            continue;
        }
        if (std::isdigit(campoNavi->campo[xColpo][yColpo]))
        {
            campoNavi->colpiDisponibili--;
            
            char naveDaCercare = campoNavi->campo[xColpo][yColpo];
            campoNavi->campo[xColpo][yColpo] = 'C';
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
            }
        }    
    }
}
```
questa funzione gestisce tutto ciò che ha a che fare con i colpi, gli spari, gli annunci, stampare il campo.
### fineGioco(Campo *&campoNavi)
```cpp
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
```
questa funzione scrive in output quando il gioco è finito se il giocatore ha vinto o perso: (you won)(game over).
### wantToContinue()
```cpp
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
```
questa funzione verifica se il giocatore desidera continuare a giocare o meno. 
