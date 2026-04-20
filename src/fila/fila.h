#pragma once
#include "estruturas/estruturas.h"

class Fila
{
public:
    Carta dados[CAP];
    int ini, fim, qtd;
    Fila();
    bool vazia();
    bool cheia();
    void enqueue(Carta c);
    Carta dequeue();
};
