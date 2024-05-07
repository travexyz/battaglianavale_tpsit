struct Punto
{
    short unsigned int x;
    short unsigned int y;
    short unsigned int tipo; // 0: acqua, 1: nave.
};

struct Campo
{
    short unsigned int dimensione;
    Punto** campo;
};