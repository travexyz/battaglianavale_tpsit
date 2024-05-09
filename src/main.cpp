#include <iostream>
#include <string>

#include "campo.h"
#include "utils.h"

int main()
{
    std::string banner1 = " ______         __   __                __ __             _______                     __         ";
    std::string banner2 = "|   __ \\.---.-.|  |_|  |_.---.-.-----.|  |__|.---.-.    |    |  |.---.-.--.--.---.-.|  |.-----.";
    std::string banner3 = "|   __ <|  _  ||   _|   _|  _  |  _  ||  |  ||  _  |    |       ||  _  |  |  |  _  ||  ||  -__| ";
    std::string banner4 = "|______/|___._||____|____|___._|___  ||__|__||___._|    |__|____||___._|\\___/|___._||__||_____|";
    std::string banner5 = "                               |_____|                                                          ";

    scriviConEffetto(banner1, 5);
    scriviConEffetto(banner2, 5);
    scriviConEffetto(banner3, 5);
    scriviConEffetto(banner4, 10);
    scriviConEffetto(banner5, 5);

    scriviConEffetto("Benvenuto, dovrai affondare tutte le navi che veranno generate in modo casuale.", 50);

    // Genero il campo con le navi
    Campo *campoNavi = new Campo;

    unsigned short int dimensione = 10;
    scriviConEffetto("Ora devi inserire la dimensione della zona di guerra (minimo 10): ", 50);
    std::cin >> dimensione;
    campoNavi->dimensione = dimensione;
    campoNavi->campo = new char *[campoNavi->dimensione];

    unsigned short int numeroNavi = 3;
    scriviConEffetto("Infine scegli quante navi renderai disponibili per la battaglia (minimo 3): ", 50);
    std::cin >> numeroNavi;
    campoNavi->numeroNavi = numeroNavi;

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
    return EXIT_SUCCESS;
}