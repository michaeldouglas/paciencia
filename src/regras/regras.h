#pragma once
#include "fila/fila.h"
#include "pilha/pilha.h"
#include "lista/lista.h"

// Regras simples: alternância de cor e valor descendente
bool podeEmpilharEmLista(const Lista &lista, const Carta &c);

// Regra para empilhar em Pilha (fundação):
// - Pilha vazia aceita somente Ás (numero == 1)
// - Caso contrário, mesmo naipe e valor ascendente (c.numero == topo.numero + 1)
bool podeEmpilharEmPilha(const Pilha &pilha, const Carta &c);

// M1: Fila -> Lista
bool M1_verifica(const Lista &lista, const Fila &fila);
void M1_aplica(Lista &lista, Fila &fila);

// M2: Pilha -> Lista
bool M2_verifica(const Lista &lista, const Pilha &pilha);
void M2_aplica(Lista &lista, Pilha &pilha);

// M3: Lista(posição) -> Lista
bool M3_verifica(const Lista &destino, const Lista &origem, int pos);
void M3_aplica(Lista &destino, Lista &origem, int pos);
