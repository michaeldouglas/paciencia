#pragma once
#include "estruturas/estruturas.h"

class Pilha
{
public:
    Carta dados[CAP];
    int topo;
    Pilha();
    bool vazia();
    bool cheia();
    void push(Carta c);
    Carta pop();
    Carta peek();
};
