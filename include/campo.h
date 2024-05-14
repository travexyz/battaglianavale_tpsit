struct Campo
{
    char **campo;
    unsigned short int dimensione;
    unsigned short int numeroNavi;
    unsigned short int colpiDisponibili;
};

/// @brief
/// @param campo
void inizializzaCampo(Campo *&campo);

/// @brief
/// @param campo
void inserisciNavi(Campo *&campo);

/// @brief
/// @param campo
void stampaCampo(Campo *campo);

/// @brief
/// @param campoNavi
/// @param campoTattico
void gestisciColpi(Campo *&campoNavi, Campo *&campoTattico);

/// @brief 
/// @param campoNavi 
/// @param campoTattico 
void finegioco(Campo *&campoNavi, Campo *&campoTattico);