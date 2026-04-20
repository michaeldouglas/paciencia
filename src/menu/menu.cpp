#include <iostream>
#include <string>
#include <limits>

using std::cin;
using std::cout;
using std::getline;
using std::numeric_limits;
using std::streamsize;
using std::string;

int menu()
{
    cout << "\n==============================\n";
    cout << "1 - Fila -> Fila\n";
    cout << "2 - Fila -> Pilha\n";
    cout << "3 - Fila -> Lista\n";
    cout << "4 - Pilha -> Lista\n";
    cout << "5 - Lista -> Pilha\n";
    cout << "6 - Lista -> Lista\n";
    cout << "7 - Criar baralho ordenado (carregar Fila1)\n";
    cout << "8 - Embaralhar recursivo (recarregar Fila1)\n";
    cout << "9 - Abrir visual 2D (raylib)\n";
    cout << "10 - Ordenar (BubbleSort) e recarregar Fila1\n";
    cout << "11 - Ordenar (MergeSort) e recarregar Fila1\n";
    cout << "12 - Ordenar (QuickSort) e recarregar Fila1\n";
    cout << "13 - Validado: Fila -> Lista (M1)\n";
    cout << "14 - Validado: Pilha -> Lista (M2)\n";
    cout << "15 - Validado: Lista1 -> Lista2 (M3)\n";
    cout << "0 - Sair\n";
    cout << "Escolha: ";
    string line;
    if (!getline(cin, line))
    {
        return 0;
    }
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return -1;
    size_t end = line.find_last_not_of(" \t\r\n");
    string trimmed = line.substr(start, end - start + 1);
    try
    {
        return std::stoi(trimmed);
    }
    catch (...)
    {
        return -1;
    }
}
