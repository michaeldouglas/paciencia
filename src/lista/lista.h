#pragma once
#include "estruturas/estruturas.h"

struct No
{
    Carta carta;
    No *prox;
};

class Lista
{
public:
    No *inicio;
    Lista();
    ~Lista();
    void inserir(Carta c);
    bool vazia();
    Carta removerInicio();
};
