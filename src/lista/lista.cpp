#include "lista.h"

Lista::Lista()
{
    inicio = nullptr;
}

Lista::~Lista()
{
    No *aux = inicio;
    while (aux != nullptr)
    {
        No *prox = aux->prox;
        delete aux;
        aux = prox;
    }
    inicio = nullptr;
}

void Lista::inserir(Carta c)
{
    No *n = new No;
    n->carta = c;
    n->prox = nullptr;
    if (inicio == nullptr)
    {
        inicio = n;
    }
    else
    {
        No *aux = inicio;
        while (aux->prox != nullptr)
        {
            aux = aux->prox;
        }
        aux->prox = n;
    }
}

bool Lista::vazia()
{
    return inicio == nullptr;
}

Carta Lista::removerInicio()
{
    No *aux = inicio;
    Carta c = aux->carta;
    inicio = inicio->prox;
    delete aux;
    return c;
}
