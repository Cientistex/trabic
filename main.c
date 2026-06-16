#include "raylib.h"


int main(void) {
    
    InitWindow(800, 600, "Quando eu fui pro C.A.P.S.");

    SetTargetFPS(60); 
    Rectangle frente = {48, 0, 16, 32};
    Rectangle costas = {16, 0, 16, 32};
    Rectangle esquerda = {32, 0, 16, 32};
    Rectangle direita = {0, 0, 16, 32};
    Rectangle frameatual = frente;
    Rectangle personagem = {400, 300, 32, 64};

    float velocidade = 4.0f;

    Texture2D BobTexture = LoadTexture ("assets/texture/Modern tiles_Free/Characters_free/Bob_16x16.png");

    while (!WindowShouldClose()) {
        
    if (IsKeyDown(KEY_D)){
        personagem.x += velocidade;
        frameatual = direita;
    }
    if (IsKeyDown(KEY_A)){
        personagem.x -= velocidade;
        frameatual = esquerda;
    }
    if (IsKeyDown(KEY_W)){
        personagem.y -= velocidade;
        frameatual = costas;
    }
    if (IsKeyDown(KEY_S)){
        personagem.y += velocidade;
        frameatual = frente;
    }

        BeginDrawing();
            ClearBackground((Color){ 10, 25, 20, 255 }); 
            DrawTexturePro(BobTexture, frameatual, personagem, (Vector2){0,0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(BobTexture); 
    CloseWindow();

    return 0;
}