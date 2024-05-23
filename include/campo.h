struct Campo
{
    char **campo;
    unsigned short int dimensione;
    unsigned short int numeroNavi;
    unsigned short int colpiDisponibili;
};

/// @brief funzione che inizializza il campo con tutti i simboli "~"
/// @param campo
void inizializzaCampo(Campo *&campo);

/// @brief inserisce le navi nel campo
/// @param campo
void inserisciNavi(Campo *&campo);

/// @brief stampa il campo in output
/// @param campo
void stampaCampo(Campo *campo);

/// @brief gestisce tutto ciò che ha a che fare coi colpi
/// @param campoNavi
/// @param campoTattico
void gestisciColpi(Campo *&campoNavi, Campo *&campoTattico);

<<<<<<< Updated upstream
/// @brief
/// @param campoNavi
void fineGioco(Campo *&campoNavi);

/// @brief 
/// @return 
bool wantToContinue();
=======
/// @brief per continuare a giocare o finire il gioco
/// @param ricominciare
/// @return se si continua o meno
bool fineGioco(bool ricominciare);
>>>>>>> Stashed changes
