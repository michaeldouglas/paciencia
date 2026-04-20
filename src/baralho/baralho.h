#pragma once
#include <vector>
#include "estruturas/estruturas.h"

void criarBaralhoOrdenado(std::vector<Carta> &baralho);
void embaralhar(std::vector<Carta> &baralho);
void embaralharRecursivo(std::vector<Carta> &baralho);
// Embaralhamento por 1000 trocas aleatórias (iterativo),
// alinhado ao enunciado da prática inicial
void embaralharMilTrocas(std::vector<Carta> &baralho);
