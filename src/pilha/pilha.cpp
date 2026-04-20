#include <iostream>
#include "pilha.h"

using std::cout;

Pilha::Pilha()
{
    topo = -1;
}

bool Pilha::vazia()
{
    return topo == -1;
}

bool Pilha::cheia()
{
    return topo >= CAP - 1;
}

void Pilha::push(Carta c)
{
    if (cheia())
    {
        cout << "Pilha cheia!\n";
        return;
    }
    dados[++topo] = c;
}

Carta Pilha::pop()
{
    if (vazia())
    {
        cout << "Pilha vazia!\n";
        return Carta{0, '?', false};
    }
    return dados[topo--];
}

Carta Pilha::peek()
{
    if (vazia())
    {
        return Carta{0, '?', false};
    }
    return dados[topo];
}
