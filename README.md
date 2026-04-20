# paciencia

Jogo Paciência para estudo de Estruturas de Dados (pilha, fila e lista ligada), com modo console (ASCII) e opção 2D via Raylib.

## Como compilar

- Pré-requisito (apenas para Raylib): headers/libs presentes no MSYS2 `ucrt64` (padrão do script). Caso não tenha Raylib instalado, use o modo somente console (`-NoRaylib`).

- Compilar (Raylib ativado por padrão):

```powershell
pwsh -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

- Compilar sem Raylib (apenas console):

```powershell
pwsh -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -NoRaylib
```

O binário é gerado em `build/paciencia.exe`.

## Como executar

```powershell
./build/paciencia.exe
```

### Uso no console (menu)

- 1: Fila → Fila
- 2: Fila → Pilha
- 3: Fila → Lista
- 4: Pilha → Lista
- 5: Lista → Pilha
- 6: Lista → Lista
- 7: Criar baralho ordenado (carrega Fila1)
- 8: Embaralhar recursivo (recarrega Fila1)
- 9: Abrir visual 2D (Raylib)
- 10/11/12: Ordenar (Bubble/Merge/Quick) e recarregar Fila1
- 13: (M1) Validado Fila → Lista
- 14: (M2) Validado Pilha → Lista
- 15: (M3) Validado Lista1 → Lista2 (solicita posição)

Obs.: No Windows o programa ajusta UTF-8 automaticamente (símbolos dos naipes).

### Uso no modo Raylib (janela)

- 1..6: mesmos movimentos básicos do console
- 7: Criar baralho ordenado e carregar Fila1
- 8: Embaralhar recursivo e recarregar Fila1
- B/M/Q: Ordenar (Bubble/Merge/Quick) e recarregar Fila1
- F1: (M1) Fila → Lista | F2: (M2) Pilha → Lista | F3: (M3) Lista1 → Lista2
- - / = : Ajusta a posição usada pelo (M3)
- ESC: sair da janela

Se o ambiente bloquear a execução do binário, rode a partir de um diretório permitido.
