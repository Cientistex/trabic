#include "raylib.h"
#include "dados.h" // Inclui a definição dos tipos e protótipos das funções
#include "movimentacao.h"
#include "corredor.h"
#include "quarto.h"
#include "escritorio.h"
#include "lab.h"
#include <stdbool.h>

typedef enum {
    TELA_QUARTO = 0,
    TELA_CORREDOR = 1,
    TELA_ESCRITORIO = 2,
    TELA_LAB = 3
    
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

 
    InitWindow(telax, telay, "Quando eu fui pro CAPS!");
    SetTargetFPS(60); 

    int TelaAtual = TELA_QUARTO;

    bool luzesApagadas = true;
    bool lendoCarta = false;
     
    Texture2D TileTexture = LoadTexture("assets/texture/Tiles/tile_0117.png");

    Texture2D BobTexture = LoadTexture("assets/texture/Modern tiles_Free/Characters_free/Bob_idle_16x16.png");

    Texture2D PortaTexture = LoadTexture ("assets/texture/Tiles/tile_0283.png");
    
   
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            luzesApagadas = !luzesApagadas;
        }
        if (playerInv.temCarta && IsKeyPressed(KEY_C)) {
        lendoCarta = !lendoCarta; 
        }
        
        BeginDrawing();
            ClearBackground(BLACK); 


            switch (TelaAtual)
            {
                case TELA_QUARTO:
                    AtualizarEDesenharQuarto(&personagem, &TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, &playerInv);
                break;
                case TELA_CORREDOR:
                    AtualizarEDesenharCorredor(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, &playerInv, &luzesApagadas);
                    break;
                    
              case TELA_ESCRITORIO:
                    AtualizarEDesenharEscritorio(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, &playerInv);
                break;

                case TELA_LAB:
                    AtualizarEDesenharLab(&personagem,&TelaAtual, &frameatual, velocidade, BobTexture, TileTexture,PortaTexture, frente, costas, esquerda, direita, tileorigem, tiledestino, portaorigem, &playerInv);
                break;
                
                default:
                    break;
            }
            if (luzesApagadas) {
                BeginBlendMode(BLEND_MULTIPLIED);
                    
                    Color escuro = { 0, 0, 51, 200 }; 
                    
                    DrawRectangle(0, 0, telax, telay, escuro);
                    
                EndBlendMode();
            }
        if (playerInv.temChave) {
            DrawRectangle(730, 20, 50, 50, Fade(GOLD, 0.6f));
            DrawRectangleLines(730, 20, 50, 50, YELLOW);
            DrawText("CHAVE", 736, 38, 12, WHITE);
        } else {
            DrawRectangleLines(730, 20, 50, 50, GRAY);
        }
        if (playerInv.temCarta) {
            DrawRectangle(670, 20, 50, 50, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(670, 20, 50, 50, BLUE);
            DrawText("CARTA", 680, 38, 12, WHITE);
        } else {
            DrawRectangleLines(670, 20, 50, 50, GRAY);
        }
        if (playerInv.temFusivel) {
            DrawRectangle(610, 20, 50, 50, Fade(ORANGE, 0.5f));
            DrawRectangleLines(610, 20, 50, 50, ORANGE);
            DrawText("FUSIVEL", 614, 38, 10, WHITE);
        } else {
            DrawRectangleLines(610, 20, 50, 50, GRAY);
        }
        if (playerInv.temCorrosivo) {
            DrawRectangle(550, 20, 50, 50, Fade(LIME, 0.5f));
            DrawRectangleLines(550, 20, 50, 50, LIME);
            DrawText("ACIDO", 558, 38, 12, WHITE);
        } else {
            DrawRectangleLines(550, 20, 50, 50, GRAY);
        }

        if (lendoCarta) {

        if (IsKeyPressed(KEY_Q)) {
            lendoCarta = false;
        }

        DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.6f));
        DrawRectangle(150, 50, 500, 350, BEIGE);
        DrawRectangleLines(150, 50, 500, 350, BROWN);

        DrawText("ACORDO SEMPRE ÀS 03H.", 180, 100, 18, DARKGRAY);
        DrawText("CONTO 54 CARNEIROS.", 180, 130, 18, DARKGRAY);
        DrawText("OUÇO 7 BATIDAS NA PORTA.", 180, 160, 18, DARKGRAY);
        DrawText("ESPERO 8 SEGUNDOS.", 180, 190, 18, DARKGRAY);
        DrawText("ENTÃO MAIS 2.", 180, 220, 18, DARKGRAY);
        
        DrawText("Pressione C ou Q para fechar", 280, 360, 16, RED);
    }

        EndDrawing();
    }

    UnloadTexture(BobTexture); 
    UnloadTexture(TileTexture);
    CloseWindow();

    return 0;
}