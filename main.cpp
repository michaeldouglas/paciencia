
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
        cout << "Fila 1:\n";
        mostrarFila(fila1);
        cout << "Fila 2:\n";
        mostrarFila(fila2);
        mostrarPilhas(pilhas, 4);
        mostrarListas(listas, 7);
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
        {
            if (fila1.vazia())
            {
                cout << "Fila vazia!\n";
                break;
            }
            cout << "Destino (Pilha 1-4): ";
            int pi = 1;
            if (!(cin >> pi))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (pi < 1 || pi > 4)
            {
                cout << "Índice inválido!\n";
                break;
            }
            Carta frente = fila1.dados[fila1.ini];
            if (podeEmpilharEmPilha(pilhas[pi - 1], frente))
            {
                pilhas[pi - 1].push(fila1.dequeue());
                cout << "OK: Fila1 -> Pilha " << pi << "\n";
            }
            else
            {
                cout << "Movimento inválido por regra (Pilha)\n";
            }
            break;
        }
        case 3:
        {
            if (fila1.vazia())
            {
                cout << "Fila vazia!\n";
                break;
            }
            cout << "Destino (Lista 1-7): ";
            int li = 1;
            if (!(cin >> li))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (li < 1 || li > 7)
            {
                cout << "Índice inválido!\n";
                break;
            }
            if (M1_verifica(listas[li - 1], fila1))
            {
                M1_aplica(listas[li - 1], fila1);
                cout << "OK: Fila1 -> Lista " << li << " (M1)\n";
            }
            else
            {
                cout << "Movimento inválido por regra (M1)\n";
            }
            break;
        }
        case 4:
        {
            cout << "Origem (Pilha 1-4): ";
            int ps = 1;
            if (!(cin >> ps))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ps < 1 || ps > 4)
            {
                cout << "Índice inválido!\n";
                break;
            }
            if (pilhas[ps - 1].vazia())
            {
                cout << "Pilha vazia!\n";
                break;
            }
            cout << "Destino (Lista 1-7): ";
            int ld = 1;
            if (!(cin >> ld))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ld < 1 || ld > 7)
            {
                cout << "Índice inválido!\n";
                break;
            }
            if (M2_verifica(listas[ld - 1], pilhas[ps - 1]))
            {
                M2_aplica(listas[ld - 1], pilhas[ps - 1]);
                cout << "OK: Pilha " << ps << " -> Lista " << ld << " (M2)\n";
            }
            else
            {
                cout << "Movimento inválido por regra (M2)\n";
            }
            break;
        }
        case 5:
        {
            cout << "Origem (Lista 1-7): ";
            int ls = 1;
            if (!(cin >> ls))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ls < 1 || ls > 7)
            {
                cout << "Índice inválido!\n";
                break;
            }
            if (listas[ls - 1].vazia())
            {
                cout << "Lista vazia!\n";
                break;
            }
            cout << "Destino (Pilha 1-4): ";
            int pd = 1;
            if (!(cin >> pd))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (pd < 1 || pd > 4)
            {
                cout << "Índice inválido!\n";
                break;
            }
            Carta cabeca = listas[ls - 1].inicio->carta;
            if (podeEmpilharEmPilha(pilhas[pd - 1], cabeca))
            {
                pilhas[pd - 1].push(listas[ls - 1].removerInicio());
                cout << "OK: Lista " << ls << " -> Pilha " << pd << "\n";
            }
            else
            {
                cout << "Movimento inválido por regra (Pilha)\n";
            }
            break;
        }
        case 6:
        {
            cout << "Origem (Lista 1-7): ";
            int ls = 1;
            if (!(cin >> ls))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Destino (Lista 1-7): ";
            int ld = 1;
            if (!(cin >> ld))
            {
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ls < 1 || ls > 7 || ld < 1 || ld > 7)
            {
                cout << "Índice inválido!\n";
                break;
            }
            cout << "Posição na origem (0 = início): ";
            int pos = 0;
            if (!(cin >> pos))
            {
                cin.clear();
                pos = 0;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (M3_verifica(listas[ld - 1], listas[ls - 1], pos))
            {
                M3_aplica(listas[ld - 1], listas[ls - 1], pos);
                cout << "OK: Lista " << ls << " -> Lista " << ld << " (M3)\n";
            }
            else
            {
                cout << "Movimento inválido por regra/posição (M3)\n";
            }
            break;
        }
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
        case 16:
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
            embaralharMilTrocas(baralho);
            while (!fila1.vazia())
                (void)fila1.dequeue();
            for (const auto &c : baralho)
                fila1.enqueue(c);
            cout << "OK: Baralho embaralhado (1000 trocas) e recarregado\n";
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
        case 17:
        {
            // Testes simples automáticos
            cout << "\n[TESTES]\n";
            // 1) Recursão: criar ordenado, copiar, embaralhar recursivo e checar difere
            std::vector<Carta> t1, t2;
            criarBaralhoOrdenado(t1);
            t2 = t1;
            embaralharRecursivo(t2);
            bool diferente = false;
            for (size_t i = 0; i < t1.size(); ++i)
                if (t1[i].numero != t2[i].numero || t1[i].naipe != t2[i].naipe)
                {
                    diferente = true;
                    break;
                }
            cout << "Recursão (embaralharRecursivo): " << (diferente ? "OK" : "FALHOU") << "\n";
            // 2) Ordenações: baralho aleatório deve ordenar igual ao ordenado base
            auto randDeck = t1;
            embaralharMilTrocas(randDeck);
            auto b = randDeck, m = randDeck, q = randDeck;
            bubbleSortCartas(b);
            mergeSortCartas(m);
            quickSortCartas(q);
            bool okB = (b == t1), okM = (m == t1), okQ = (q == t1);
            cout << "BubbleSort: " << (okB ? "OK" : "FALHOU") << ", MergeSort: " << (okM ? "OK" : "FALHOU") << ", QuickSort: " << (okQ ? "OK" : "FALHOU") << "\n";
            // 3) Pilha (verifica): vazia aceita Ás; rejeita 2; sobre Ás de copas, aceita 2 de copas
            Pilha tp;
            bool tP1 = podeEmpilharEmPilha(tp, Carta{1, 'c', true});
            bool tP2 = !podeEmpilharEmPilha(tp, Carta{2, 'c', true});
            if (tP1)
                tp.push(Carta{1, 'c', true});
            bool tP3 = podeEmpilharEmPilha(tp, Carta{2, 'c', true});
            cout << "Pilha (verifica): " << ((tP1 && tP2 && tP3) ? "OK" : "FALHOU") << "\n";
            // 4) Listas (M1/M2/M3) smoke test
            Fila tf;
            tf.enqueue(Carta{5, 'c', true}); // aceitar em lista vazia
            Lista tl1, tl2;
            Pilha tpilha;
            bool v1 = M1_verifica(tl1, tf);
            if (v1)
                M1_aplica(tl1, tf);
            tpilha.push(Carta{6, 'o', true});
            bool v2 = M2_verifica(tl1, tpilha) == false; // cores iguais (ambas vermelhas) devem falhar na regra de lista alternada
            bool v3 = M3_verifica(tl2, tl1, 0);          // mover 5c para lista2 deve ser permitido em lista vazia
            if (v3)
                M3_aplica(tl2, tl1, 0);
            cout << "Listas (M1/M2/M3): " << ((v1 && v2 && v3) ? "OK" : "FALHOU") << "\n";
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