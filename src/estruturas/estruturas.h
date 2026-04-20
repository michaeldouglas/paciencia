#pragma once

static const int CAP = 52;

struct Carta
{
    int numero;
    char naipe;
    bool status;
};

// Igualdade de cartas: considera número e naipe (status é estado interno)
inline bool operator==(const Carta &a, const Carta &b)
{
    return a.numero == b.numero && a.naipe == b.naipe;
}

inline bool operator!=(const Carta &a, const Carta &b)
{
    return !(a == b);
}
