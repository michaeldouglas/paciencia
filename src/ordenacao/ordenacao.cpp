#include "ordenacao.h"
#include <algorithm>

static inline int key(const Carta &c)
{
    // Ordena por numero e, em empate, por naipe
    return c.numero * 10 + (int)(unsigned char)c.naipe;
}

void bubbleSortCartas(std::vector<Carta> &v)
{
    bool trocou = true;
    for (size_t n = v.size(); trocou && n > 1; --n)
    {
        trocou = false;
        for (size_t i = 0; i + 1 < n; ++i)
        {
            if (key(v[i]) > key(v[i + 1]))
            {
                std::swap(v[i], v[i + 1]);
                trocou = true;
            }
        }
    }
}

static void merge(std::vector<Carta> &v, size_t l, size_t m, size_t r)
{
    size_t n1 = m - l + 1, n2 = r - m;
    std::vector<Carta> L(n1), R(n2);
    for (size_t i = 0; i < n1; ++i)
        L[i] = v[l + i];
    for (size_t j = 0; j < n2; ++j)
        R[j] = v[m + 1 + j];
    size_t i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (key(L[i]) <= key(R[j]))
            v[k++] = L[i++];
        else
            v[k++] = R[j++];
    }
    while (i < n1)
        v[k++] = L[i++];
    while (j < n2)
        v[k++] = R[j++];
}

static void mergeSortRec(std::vector<Carta> &v, size_t l, size_t r)
{
    if (l >= r)
        return;
    size_t m = l + (r - l) / 2;
    mergeSortRec(v, l, m);
    mergeSortRec(v, m + 1, r);
    merge(v, l, m, r);
}

void mergeSortCartas(std::vector<Carta> &v)
{
    if (v.empty())
        return;
    mergeSortRec(v, 0, v.size() - 1);
}

static size_t partition(std::vector<Carta> &v, size_t low, size_t high)
{
    int pivot = key(v[high]);
    size_t i = low;
    for (size_t j = low; j < high; ++j)
    {
        if (key(v[j]) <= pivot)
        {
            std::swap(v[i], v[j]);
            ++i;
        }
    }
    std::swap(v[i], v[high]);
    return i;
}

static void quickSortRec(std::vector<Carta> &v, size_t low, size_t high)
{
    if (low >= high)
        return;
    size_t pi = partition(v, low, high);
    if (pi > 0)
        quickSortRec(v, low, pi - 1);
    quickSortRec(v, pi + 1, high);
}

void quickSortCartas(std::vector<Carta> &v)
{
    if (v.empty())
        return;
    quickSortRec(v, 0, v.size() - 1);
}
