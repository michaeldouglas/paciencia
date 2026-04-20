#include <iostream>
#include "fila.h"

using std::cout;

Fila::Fila()
{
    ini = 0;
    fim = 0;
    qtd = 0;
}

bool Fila::vazia()
{
    return qtd == 0;
}

bool Fila::cheia()
{
    return qtd == CAP;
}

void Fila::enqueue(Carta c)
{
    if (cheia())
    {
        cout << "Fila cheia!\n";
        return;
    }
    dados[fim] = c;
    fim = (fim + 1) % CAP;
    qtd++;
}

Carta Fila::dequeue()
{
    if (vazia())
    {
        cout << "Fila vazia!\n";
        return Carta{0, '?', false};
    }
    Carta c = dados[ini];
    ini = (ini + 1) % CAP;
    qtd--;
    return c;
}
