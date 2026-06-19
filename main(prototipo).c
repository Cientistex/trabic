#include <stdio.h>
#include "raylib.h"
#include "dados.h"
#include "quarto.h"

int main (void){
    Jogador palyer;
    InicializarJogador(&palyer, "Bob");
    CarregarJogo(&palyer);

    InitWindow(800, 450, "Raylib em C Puro!");
    SetTargetFPS(60);

    Texture2D BobTexture = LoadTexture("bob.png");
    Texture2D TileTexture = LoadTexture("tileset.png");
    bool mostrandopuzzle = false;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
      
        DesenharQuarto(&palyer, BobTexture, TileTexture, &mostrandopuzzle);

        EndDrawing();
    }

    UnloadTexture(BobTexture);
    UnloadTexture(TileTexture);
    CloseWindow();

    return 0;
}
