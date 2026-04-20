#include <iostream>
#include <vector>
#include <string>
#include "render_console.h"

using std::cout;
using std::string;
using std::vector;

static inline const char *suitSymbol(char naipe)
{
    switch (naipe)
    {
    case 'c':
        return "\u2665";
    case 'o':
        return "\u2666";
    case 'p':
        return "\u2663";
    case 'e':
        return "\u2660";
    default:
        return "?";
    }
}

static inline bool isRedSuit(char naipe)
{
    return (naipe == 'c' || naipe == 'o');
}

static string colorize(const string &text, bool red)
{
    if (red)
        return string("\x1b[31m") + text + "\x1b[0m";
    return text;
}

static string faceValue(int n)
{
    if (n == 1)
        return "A";
    if (n == 11)
        return "J";
    if (n == 12)
        return "Q";
    if (n == 13)
        return "K";
    return std::to_string(n);
}

static void renderCardsBoxes(const vector<Carta> &cards)
{
    if (cards.empty())
    {
        cout << "(vazia)\n";
        return;
    }
    string top, mid, bot;
    for (const auto &c : cards)
    {
        top += "+---";
        top += "+ ";
        string v = faceValue(c.numero);
        string s = suitSymbol(c.naipe);
        int glyphs = (c.status && c.numero > 0) ? (int)v.size() + 1 : 0;
        string inside = (c.status && c.numero > 0) ? (v + s) : string("   ");
        while (glyphs < 3)
        {
            inside = " " + inside;
            glyphs++;
        }
        bool red = isRedSuit(c.naipe) && c.status && c.numero > 0;
        mid += "|" + colorize(inside, red) + "| ";
        bot += "+---";
        bot += "+ ";
    }
    cout << top << "\n";
    cout << mid << "\n";
    cout << bot << "\n";
}

void mostrarFila(const Fila &f)
{
    cout << "Fila:  \n";
    if (f.qtd == 0)
    {
        cout << "(vazia)\n";
        return;
    }
    vector<Carta> v;
    v.reserve(f.qtd);
    int idx = f.ini;
    for (int i = 0; i < f.qtd; i++)
    {
        v.push_back(f.dados[idx]);
        idx = (idx + 1) % CAP;
    }
    renderCardsBoxes(v);
}

void mostrarPilha(const Pilha &p)
{
    cout << "Pilha: \n";
    if (p.topo < 0)
    {
        cout << "(vazia)\n";
        return;
    }
    vector<Carta> v;
    v.reserve(p.topo + 1);
    for (int i = 0; i <= p.topo; i++)
    {
        v.push_back(p.dados[i]);
    }
    renderCardsBoxes(v);
}

void mostrarLista(const Lista &l)
{
    cout << "Lista: \n";
    if (l.inicio == nullptr)
    {
        cout << "(vazia)\n";
        return;
    }
    vector<Carta> v;
    No *aux = l.inicio;
    while (aux != nullptr)
    {
        v.push_back(aux->carta);
        aux = aux->prox;
    }
    renderCardsBoxes(v);
}
