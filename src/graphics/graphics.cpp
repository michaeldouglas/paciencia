#include <string>
#ifdef USE_RAYLIB
#include "raylib.h"
#endif
#include <vector>
#include "graphics.h"
#ifdef USE_RAYLIB
#include "baralho/baralho.h"
#include "ordenacao/ordenacao.h"
#include "regras/regras.h"
#endif

#ifdef USE_RAYLIB
static std::string faceValue(int n)
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

static bool isRedSuit(char naipe)
{
    return (naipe == 'c' || naipe == 'o');
}

static void drawCardBoxRaylib(float x, float y, const Carta &c)
{
    const float w = 60.0f, h = 84.0f;
    Color border = BLACK;
    Color fill = RAYWHITE;
    Rectangle outer{x, y, w, h};
    DrawRectangleRoundedLines(outer, 0.1f, 6, border);
    Rectangle inner{x + 2, y + 2, w - 4, h - 4};
    DrawRectangleRounded(inner, 0.1f, 6, fill);
    if (!c.status || c.numero <= 0)
        return;
    std::string v = faceValue(c.numero);
    bool red = isRedSuit(c.naipe);
    Color txt = red ? RED : BLACK;
    char suitC = 'S';
    if (c.naipe == 'c')
        suitC = 'H';
    else if (c.naipe == 'o')
        suitC = 'D';
    else if (c.naipe == 'p')
        suitC = 'C';
    else if (c.naipe == 'e')
        suitC = 'S';
    std::string s(1, suitC);
    DrawText(v.c_str(), (int)(x + 6), (int)(y + 6), 18, txt);
    DrawText(s.c_str(), (int)(x + 6), (int)(y + 26), 18, txt);
}

static void drawRowRaylib(float startX, float y, const std::vector<Carta> &cards)
{
    float x = startX;
    for (const auto &c : cards)
    {
        drawCardBoxRaylib(x, y, c);
        x += 70.0f;
    }
}

static void drawStackRaylib(float x, float startY, const std::vector<Carta> &cards, float dy)
{
    float y = startY;
    for (const auto &c : cards)
    {
        drawCardBoxRaylib(x, y, c);
        y += dy;
    }
}

static std::vector<Carta> toVector(const Fila &f)
{
    std::vector<Carta> v;
    int idx = f.ini;
    for (int i = 0; i < f.qtd; i++)
    {
        v.push_back(f.dados[idx]);
        idx = (idx + 1) % CAP;
    }
    return v;
}

static std::vector<Carta> toVector(const Pilha &p)
{
    std::vector<Carta> v;
    for (int i = 0; i <= p.topo; i++)
        v.push_back(p.dados[i]);
    return v;
}

static std::vector<Carta> toVector(const Lista &l)
{
    std::vector<Carta> v;
    No *aux = l.inicio;
    while (aux)
    {
        v.push_back(aux->carta);
        aux = aux->prox;
    }
    return v;
}

void runGraphics(Fila &fila1, Fila &fila2, Pilha &pilha, Lista &lista1, Lista &lista2)
{
    InitWindow(1000, 600, "Paciência - Visual 2D");
    SetTargetFPS(60);
    static std::vector<Carta> gDeck;
    static int m3Pos = 0;
    auto loadFila = [](Fila &f, const std::vector<Carta> &cards)
    {
        while (!f.vazia())
            (void)f.dequeue();
        for (const auto &c : cards)
            f.enqueue(c);
    };
    auto listLen = [](const Lista &l)
    {
        int n = 0;
        for (No *a = l.inicio; a; a = a->prox)
            ++n;
        return n;
    };
    while (!WindowShouldClose())
    {
        // Inputs equivalentes às opções do modo console
        if (IsKeyPressed(KEY_ONE))
        {
            if (!fila1.vazia())
                fila2.enqueue(fila1.dequeue());
        }
        if (IsKeyPressed(KEY_TWO))
        {
            if (!fila1.vazia())
                pilha.push(fila1.dequeue());
        }
        if (IsKeyPressed(KEY_THREE))
        {
            if (!fila1.vazia())
                lista1.inserir(fila1.dequeue());
        }
        if (IsKeyPressed(KEY_FOUR))
        {
            if (!pilha.vazia())
                lista1.inserir(pilha.pop());
        }
        if (IsKeyPressed(KEY_FIVE))
        {
            if (!lista1.vazia())
                pilha.push(lista1.removerInicio());
        }
        if (IsKeyPressed(KEY_SIX))
        {
            if (!lista1.vazia())
                lista2.inserir(lista1.removerInicio());
        }
        // 7: criar baralho ordenado e carregar Fila1
        if (IsKeyPressed(KEY_SEVEN))
        {
            criarBaralhoOrdenado(gDeck);
            loadFila(fila1, gDeck);
        }
        // 8: embaralhar recursivo e recarregar Fila1
        if (IsKeyPressed(KEY_EIGHT))
        {
            if (gDeck.empty())
                gDeck = toVector(fila1);
            embaralharRecursivo(gDeck);
            loadFila(fila1, gDeck);
        }
        // B/M/Q: ordenar e recarregar Fila1
        if (IsKeyPressed(KEY_B))
        {
            if (gDeck.empty())
                gDeck = toVector(fila1);
            bubbleSortCartas(gDeck);
            loadFila(fila1, gDeck);
        }
        if (IsKeyPressed(KEY_M))
        {
            if (gDeck.empty())
                gDeck = toVector(fila1);
            mergeSortCartas(gDeck);
            loadFila(fila1, gDeck);
        }
        if (IsKeyPressed(KEY_Q))
        {
            if (gDeck.empty())
                gDeck = toVector(fila1);
            quickSortCartas(gDeck);
            loadFila(fila1, gDeck);
        }
        // F1/F2/F3: movimentos validados M1/M2/M3; '-' e '=' ajustam pos
        if (IsKeyPressed(KEY_MINUS))
        {
            if (m3Pos > 0)
                --m3Pos;
        }
        if (IsKeyPressed(KEY_EQUAL))
        {
            int n = listLen(lista1);
            if (m3Pos + 1 < n)
                ++m3Pos;
        }
        if (IsKeyPressed(KEY_F1))
        {
            if (M1_verifica(lista1, fila1))
                M1_aplica(lista1, fila1);
        }
        if (IsKeyPressed(KEY_F2))
        {
            if (M2_verifica(lista1, pilha))
                M2_aplica(lista1, pilha);
        }
        if (IsKeyPressed(KEY_F3))
        {
            if (M3_verifica(lista2, lista1, m3Pos))
                M3_aplica(lista2, lista1, m3Pos);
        }
        BeginDrawing();
        ClearBackground(Color{240, 240, 240, 255});
        DrawText("Fila1", 40, 30, 24, DARKGRAY);
        DrawText("Fila2", 40, 130, 24, DARKGRAY);
        DrawText("Pilha", 40, 230, 24, DARKGRAY);
        DrawText("Lista1", 40, 330, 24, DARKGRAY);
        DrawText("Lista2", 300, 330, 24, DARKGRAY);
        auto vf1 = toVector(fila1);
        auto vf2 = toVector(fila2);
        auto vp = toVector(pilha);
        auto vl1 = toVector(lista1);
        auto vl2 = toVector(lista2);
        drawRowRaylib(40.0f, 70.0f, vf1);
        drawRowRaylib(40.0f, 170.0f, vf2);
        drawStackRaylib(40.0f, 270.0f, vp, 18.0f);
        drawStackRaylib(40.0f, 370.0f, vl1, 18.0f);
        drawStackRaylib(300.0f, 370.0f, vl2, 18.0f);
        DrawText("1..6: movimentos basicos | 7: baralho | 8: embaralhar rec | B/M/Q: ordenar", 40, 510, 18, GRAY);
        DrawText("F1:(M1) Fila->Lista  F2:(M2) Pilha->Lista  F3:(M3) Lista1->Lista2  pos[-/=]: ", 40, 535, 18, GRAY);
        DrawText(TextFormat("%d", m3Pos), 780, 535, 18, GRAY);
        EndDrawing();
    }
    CloseWindow();
}
#else
void runGraphics(Fila &, Fila &, Pilha &, Lista &, Lista &)
{
}
#endif
