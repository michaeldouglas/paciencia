#include "regras.h"
#include <vector>

static bool isRed(char n) { return (n == 'c' || n == 'o'); }

static Carta ultimoDaLista(const Lista &l)
{
    No *a = l.inicio;
    if (!a)
        return Carta{0, '?', false};
    while (a->prox)
        a = a->prox;
    return a->carta;
}

bool podeEmpilharEmLista(const Lista &lista, const Carta &c)
{
    if (!c.status || c.numero <= 0)
        return false;
    if (!lista.inicio)
        return true; // lista vazia aceita qualquer carta
    Carta ult = ultimoDaLista(lista);
    if (!ult.status || ult.numero <= 0)
        return true;
    // alternância de cor e valor descendente
    bool altCor = (isRed(ult.naipe) != isRed(c.naipe));
    bool desc = (c.numero == ult.numero - 1);
    return altCor && desc;
}

bool M1_verifica(const Lista &lista, const Fila &fila)
{
    if (fila.qtd == 0)
        return false;
    int idx = fila.fim == 0 ? (CAP - 1) : (fila.fim - 1); // último enfileirado
    Carta c = fila.dados[idx];
    return podeEmpilharEmLista(lista, c);
}

void M1_aplica(Lista &lista, Fila &fila)
{
    if (!fila.vazia() && M1_verifica(lista, fila))
    {
        lista.inserir(fila.dequeue());
    }
}

bool M2_verifica(const Lista &lista, const Pilha &pilha)
{
    if (pilha.topo < 0)
        return false;
    Carta c = pilha.dados[pilha.topo];
    return podeEmpilharEmLista(lista, c);
}

void M2_aplica(Lista &lista, Pilha &pilha)
{
    if (!pilha.vazia() && M2_verifica(lista, pilha))
    {
        lista.inserir(pilha.pop());
    }
}

bool M3_verifica(const Lista &destino, const Lista &origem, int pos)
{
    if (pos < 0)
        return false;
    No *a = origem.inicio;
    int i = 0;
    while (a && i < pos)
    {
        a = a->prox;
        ++i;
    }
    if (!a)
        return false; // pos fora
    return podeEmpilharEmLista(destino, a->carta);
}

void M3_aplica(Lista &destino, Lista &origem, int pos)
{
    if (!M3_verifica(destino, origem, pos))
        return;
    // destacar sublista a partir de pos e anexar a destino
    if (pos == 0)
    {
        // anexar lista inteira de origem ao fim de destino
        No *tail = destino.inicio;
        if (!tail)
        {
            destino.inicio = origem.inicio;
            origem.inicio = nullptr;
            return;
        }
        while (tail->prox)
            tail = tail->prox;
        tail->prox = origem.inicio;
        origem.inicio = nullptr;
        return;
    }
    // encontrar nó anterior a pos
    No *prev = origem.inicio;
    for (int i = 0; i < pos - 1 && prev; ++i)
        prev = prev->prox;
    if (!prev || !prev->prox)
        return;
    No *start = prev->prox;
    prev->prox = nullptr; // corta origem
    // anexa start ao fim de destino
    if (!destino.inicio)
    {
        destino.inicio = start;
        return;
    }
    No *tail = destino.inicio;
    while (tail->prox)
        tail = tail->prox;
    tail->prox = start;
}
