# Paciência jogo

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

Opcional (VS Code): use as tasks "Build (console)" ou "Build (raylib)" já configuradas.

## Como executar

```powershell
./build/paciencia.exe
```

### Estado inicial e baralho completo

- Ao iniciar, a Fila1 contém 5 cartas de exemplo apenas para visualização rápida.
- Para trabalhar com o baralho completo (52 cartas), use a opção 7 do menu ("Criar baralho ordenado") e, se desejar, a 16 ("Embaralhar iterativo") antes de ordenar (10/11/12).
- As opções de ordenação e embaralhamento atuam sobre o baralho em memória; se ele estiver vazio, o programa captura o conteúdo atual da Fila1 e então aplica a operação.

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
- 16: Embaralhar iterativo (1000 trocas) e recarregar Fila1
- 17: Rodar testes automáticos (recursão/ordenação/pilha/listas)
- 0: Sair

Obs.: No Windows o programa ajusta UTF-8 automaticamente (símbolos dos naipes).

### Testes automáticos

Para validar recursão, ordenações, regras de pilha e listas:

```powershell
./build/paciencia.exe
# no menu, digite: 17
```

O programa imprimirá o resultado esperado como "OK" para cada categoria de teste.

### Uso no modo Raylib (janela)

- 1..6: mesmos movimentos básicos do console
- 7: Criar baralho ordenado e carregar Fila1
- 8: Embaralhar recursivo e recarregar Fila1
- B/M/Q: Ordenar (Bubble/Merge/Quick) e recarregar Fila1
- F1: (M1) Fila → Lista | F2: (M2) Pilha → Lista | F3: (M3) Lista1 → Lista2
- - / = : Ajusta a posição usada pelo (M3)
- ESC: sair da janela

Se o ambiente bloquear a execução do binário, rode a partir de um diretório permitido.
