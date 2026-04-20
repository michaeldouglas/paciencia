#include "baralho.h"
#include <algorithm>
#include <random>
#include <chrono>

void criarBaralhoOrdenado(std::vector<Carta> &baralho)
{
    baralho.clear();
    baralho.reserve(CAP);
    const char naipes[4] = {'c', 'o', 'p', 'e'};
    for (char n : naipes)
    {
        for (int v = 1; v <= 13; ++v)
        {
            baralho.push_back(Carta{v, n, true});
        }
    }
}

void embaralhar(std::vector<Carta> &baralho)
{
    unsigned seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::shuffle(baralho.begin(), baralho.end(), rng);
}

static void embaralharRec(std::vector<Carta> &v, int i, std::mt19937 &rng)
{
    if (i <= 0)
        return;
    std::uniform_int_distribution<int> dist(0, i);
    int j = dist(rng);
    std::swap(v[i], v[j]);
    embaralharRec(v, i - 1, rng);
}

void embaralharRecursivo(std::vector<Carta> &baralho)
{
    if (baralho.empty())
        return;
    unsigned seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    embaralharRec(baralho, (int)baralho.size() - 1, rng);
}
