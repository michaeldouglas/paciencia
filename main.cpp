
#include <iostream>
#include <string>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;

#include "estruturas/estruturas.h"
#include "pilha/pilha.h"
#include "fila/fila.h"
#include "lista/lista.h"
#include "render/render_console.h"
#include "menu/menu.h"
#include "graphics/graphics.h"
#include <vector>
#include "baralho/baralho.h"
#include "ordenacao/ordenacao.h"
#include "regras/regras.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    Fila fila1, fila2;
    Pilha pilhas[4];
    Lista listas[7];
    auto &pilha = pilhas[0];
    auto &lista1 = listas[0];
    auto &lista2 = listas[1];
    // baralho em memória para operações de criação/embaralhe/ordenação
    std::vector<Carta> baralho;
    // Estado inicial: cinco cartas exemplo
    fila1.enqueue({1, 'c', true});
    fila1.enqueue({2, 'o', true});
    fila1.enqueue({3, 'p', true});
    fila1.enqueue({4, 'e', true});
    fila1.enqueue({5, 'c', true});
    int op;
    do
    {
        cout << "\n=== ESTADO DO JOGO ===\n";
        mostrarFila(fila1);
        mostrarPilha(pilha);
        mostrarLista(lista1);
        op = menu();
        switch (op)
        {
        case 1:
            if (!fila1.vazia())
            {
                fila2.enqueue(fila1.dequeue());
                cout << "OK: Fila1 -> Fila2\n";
            }
            else
            {
                cout << "Fila vazia!\n";
            }
            break;
        case 2:
            if (!fila1.vazia())
            {
                pilha.push(fila1.dequeue());
                cout << "OK: Fila -> Pilha\n";
            }
            else
            {
                cout << "Fila vazia!\n";
            }
            break;
        case 3:
            if (!fila1.vazia())
            {
                lista1.inserir(fila1.dequeue());
                cout << "OK: Fila -> Lista\n";
            }
            else
            {
                cout << "Fila vazia!\n";
            }
            break;
        case 4:
            if (!pilha.vazia())
            {
                lista1.inserir(pilha.pop());
                cout << "OK: Pilha -> Lista\n";
            }
            else
            {
                cout << "Pilha vazia!\n";
            }
            break;
        case 5:
            if (!lista1.vazia())
            {
                pilha.push(lista1.removerInicio());
                cout << "OK: Lista -> Pilha\n";
            }
            else
            {
                cout << "Lista vazia!\n";
            }
            break;
        case 6:
            if (!lista1.vazia())
            {
                lista2.inserir(lista1.removerInicio());
                cout << "OK: Lista1 -> Lista2\n";
            }
            else
            {
                cout << "Lista vazia!\n";
            }
            break;
        case 7:
        {
            criarBaralhoOrdenado(baralho);
            // recarrega Fila1
            while (!fila1.vazia())
                (void)fila1.dequeue();
            for (const auto &c : baralho)
                fila1.enqueue(c);
            cout << "OK: Baralho ordenado carregado na Fila1\n";
            break;
        }
        case 8:
        {
            if (baralho.empty())
            {
                // captura estado atual da Fila1 como baralho
                int idx = fila1.ini;
                baralho.clear();
                for (int i = 0; i < fila1.qtd; i++)
                {
                    baralho.push_back(fila1.dados[idx]);
                    idx = (idx + 1) % CAP;
                }
            }
            embaralharRecursivo(baralho);
            while (!fila1.vazia())
                (void)fila1.dequeue();
            for (const auto &c : baralho)
                fila1.enqueue(c);
            cout << "OK: Baralho embaralhado recursivamente e recarregado\n";
            break;
        }
        case 10:
        case 11:
        case 12:
        {
            if (baralho.empty())
            {
                int idx = fila1.ini;
                baralho.clear();
                for (int i = 0; i < fila1.qtd; i++)
                {
                    baralho.push_back(fila1.dados[idx]);
                    idx = (idx + 1) % CAP;
                }
            }
            if (op == 10)
                bubbleSortCartas(baralho);
            if (op == 11)
                mergeSortCartas(baralho);
            if (op == 12)
                quickSortCartas(baralho);
            while (!fila1.vazia())
                (void)fila1.dequeue();
            for (const auto &c : baralho)
                fila1.enqueue(c);
            cout << "OK: Baralho ordenado e Fila1 recarregada\n";
            break;
        }
        case 13: // Validado: Fila -> Lista (M1)
            if (M1_verifica(lista1, fila1))
            {
                M1_aplica(lista1, fila1);
                cout << "OK: (M1) Fila -> Lista\n";
            }
            else
            {
                cout << "Movimento inválido por regra (M1) ou origem vazia\n";
            }
            break;
        case 14: // Validado: Pilha -> Lista (M2)
            if (M2_verifica(lista1, pilha))
            {
                M2_aplica(lista1, pilha);
                cout << "OK: (M2) Pilha -> Lista\n";
            }
            else
            {
                cout << "Movimento inválido por regra (M2) ou origem vazia\n";
            }
            break;
        case 15: // Validado: Lista1 -> Lista2 (M3)
        {
            cout << "Posição (0 = início): ";
            int pos = 0;
            if (!(cin >> pos))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pos = 0;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (M3_verifica(lista2, lista1, pos))
            {
                M3_aplica(lista2, lista1, pos);
                cout << "OK: (M3) Lista1 -> Lista2\n";
            }
            else
            {
                cout << "Movimento inválido por regra/posição (M3)\n";
            }
            break;
        }
        case 9:
            runGraphics(fila1, fila2, pilha, lista1, lista2);
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    } while (op != 0);
    return 0;
}