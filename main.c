#include "raylib.h"
#include "dados.h" // Inclui a definição dos tipos e protótipos das funções

int main(void) {
    //Cria um jogador e inicializa com o nome "Bob"
    Jogador player; // Declara uma variável do tipo Jogador
    InicializarJogador(&player, "Bob"); 

    CarregarJogo(&player); // Tenta carregar o jogo salvo, se existir
    // Inicializa a janela com largura, altura e o título
    InitWindow(800, 450, "Raylib em C Puro!");
    SetTargetFPS(60); // Controla o jogo a 60 frames por segundo

    int numeroVisor = 0; // Variável para controlar qual "tela" ou "estado" do jogo estamos mostrando
    bool puzzleQuartoResolvido = false; // Variável para controlar se o puzzle do quarto foi resolvido

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // 1. Atualizar variáveis (se necessário)

        // 2. Desenhar na tela
        BeginDrawing();
            ClearBackground(BLACK); // Limpa a tela com a cor preta
            DrawText("Parabéns! Raylib configurada em C.", 190, 200, 20, RAYWHITE);
        EndDrawing();
    }

    // Fecha a janela e o contexto OpenGL
    CloseWindow();

    return 0;
}