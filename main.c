#include "raylib.h"
#include "dados.h" // Inclui a definição dos tipos e protótipos das funções
#include "movimentacao.h"
#include "corredor.h"
#include "quarto.h"
#include <stdbool.h>

typedef enum {
    TELA_QUARTO = 0,
    TELA_CORREDOR = 1,
   // TELA_ESCRITORIO = 2,
    //TELA_LAB = 3
    
}EstadoJogo;

Inventario playerInv = {.temChave = false, .temCarta = false};

int main(void) {
  
    Rectangle personagem = {400, 225, 32, 48}; //retângulos do bob
    Rectangle frente = {48, 8, 16, 24};
    Rectangle costas = {16, 8, 16, 24};
    Rectangle esquerda = {32, 8, 16, 24};
    Rectangle direita = {0, 8, 16, 24};
    Rectangle frameatual = frente;

    Rectangle tileorigem = {0, 0, 16, 16};
    Rectangle tiledestino = {0, 0, 32, 32};

    
    Rectangle portaorigem = {0, 0, 16, 16};
    Rectangle portadestino = {0, 193, 32, 64};

    int velocidade = 4;

    int telax = 800;
    int telay = 450;

    // Inicializa a janela com largura, altura e o título
    InitWindow(telax, telay, "Raylib em C Puro!");
    SetTargetFPS(60); // Controla o jogo a 60 frames por segundo

    int TelaAtual = TELA_QUARTO;

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
                case TELA_QUARTO:
                    AtualizarEDesenharQuarto(&personagem, &TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, portadestino, &playerInv);
                break;
                case TELA_CORREDOR:
                    AtualizarEDesenharCorredor(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, portadestino);
                    break;
              /*  case TELA_ESCRITORIO:
                    AtualizarEDesenharEscritorio(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, portadestino);
                break;
                case TELA_LAB:
                    AtualizarEDesenharLab(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, portadestino);
                break;
                */
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
            if (playerInv.temChave) {
            // Desenha o slot ativo (Dourado) se o jogador tiver a chave
            DrawRectangle(730, 20, 50, 50, Fade(GOLD, 0.6f));
            DrawRectangleLines(730, 20, 50, 50, YELLOW);
            DrawText("CHAVE", 736, 38, 12, WHITE);
        } else {
            // Desenha o slot vazio (Cinza)
            DrawRectangleLines(730, 20, 50, 50, GRAY);
        }
        if (playerInv.temCarta) {
            // Desenha o slot ativo (Azul acinzentado/Papel)
            DrawRectangle(670, 20, 50, 50, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(670, 20, 50, 50, BLUE);
            DrawText("CARTA", 680, 38, 12, WHITE);
        } else {
            // Desenha o slot vazio (Cinza)
            DrawRectangleLines(670, 20, 50, 50, GRAY);
        }

        EndDrawing();
    }

    UnloadTexture(BobTexture); 
    UnloadTexture(TileTexture);
    CloseWindow();

    return 0;
}