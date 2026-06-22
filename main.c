#include "raylib.h"
#include "dados.h" // Inclui a definição dos tipos e protótipos das funções
#include "movimentacao.h"
#include "corredor.h"
#include <stdbool.h>

typedef enum {
    TELA_CORREDOR
    
}EstadoJogo;

int main(void) {
  
    Jogador player; 



    Rectangle personagem = {400, 225, 32, 64}; //retângulos do bob
    Rectangle frente = {48, 0, 16, 32};
    Rectangle costas = {16, 0, 16, 32};
    Rectangle esquerda = {32, 0, 16, 32};
    Rectangle direita = {0, 0, 16, 32};
    Rectangle frameatual = frente;

    Rectangle tileorigem = {0, 0, 16, 16};
    Rectangle tiledestino = {0, 0, 32, 32};

    int velocidade = 4;

    Rectangle paredeesquerda = {0, 0, 32, 450};
    Rectangle paredecima = {0, 0, 800, 32};
    Rectangle parededireita = {768, 0, 32, 450};
    Rectangle paredebaixo = {0, 418, 800, 32};

    int telax = 800;
    int telay = 450;

    // Inicializa a janela com largura, altura e o título
    InitWindow(telax, telay, "Raylib em C Puro!");
    SetTargetFPS(60); // Controla o jogo a 60 frames por segundo

    EstadoJogo TelaAtual = TELA_CORREDOR;

    bool luzesApagadas = true;
     
    Texture2D TileTexture = LoadTexture("assets/texture/Tiles/tile_0117.png");

    Texture2D BobTexture = LoadTexture("assets/texture/Modern tiles_Free/Characters_free/Bob_idle_16x16.png");

    Texture2D PortaTexture = LoadTexture ("assets/texture/Tiles/tile_0310.png");
    
   
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            luzesApagadas = !luzesApagadas;
        }
        
        BeginDrawing();
            ClearBackground(BLACK); 


            switch (TelaAtual)
            {
                case TELA_CORREDOR:
                    AtualizarEDesenharCorredor(&personagem, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita);
                    break;
                
                default:
                    break;
            }
            if (luzesApagadas) {
                BeginBlendMode(BLEND_MULTIPLIED);
                    
                    // Um azul bem escuro/cinza funciona melhor que preto puro no Multiply.
                    // Quanto menores os números RGB, mais escuro fica o jogo.
                    Color escuro = { 0, 0, 51, 200 }; 
                    
                    DrawRectangle(0, 0, telax, telay, escuro);
                    
                EndBlendMode();
            }

        EndDrawing();
    }

    UnloadTexture(BobTexture); 
    UnloadTexture(TileTexture);
    CloseWindow();

    return 0;
}