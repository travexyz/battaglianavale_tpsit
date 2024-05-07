struct Punto
{
    short unsigned int x;
    short unsigned int y;
};

struct Nave
{
    short unsigned int height;
    short unsigned int width;
    Punto posizione;
};

struct Campo
{
    short unsigned int dimensione;
    Nave *navi;
};