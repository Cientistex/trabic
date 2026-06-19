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

    
    // Loop principal do jogo
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

    if(CheckCollisionRecs(personagem, paredeesquerda)){
        personagem.x += velocidade;
    }
    if(CheckCollisionRecs(personagem, paredecima)){
        personagem.y += velocidade;
    }
    if(CheckCollisionRecs(personagem, parededireita)){
        personagem.x -= velocidade;
    }
    if(CheckCollisionRecs(personagem, paredebaixo)){
        personagem.y -= velocidade;
    }
    

        BeginDrawing();

            

            ClearBackground((Color){ 10, 25, 20, 255 }); 
            for (int y = 0; y <= 600 ; y += 32){
                for (int x = 0; x <= 800; x+= 32){
                    Rectangle tiledestino = {x, y, 32, 32};
                    DrawTexturePro (TileTexture, tileorigem, tiledestino, (Vector2){0,0}, 0.0f, WHITE);
                }
            }
            DrawTexturePro(BobTexture, frameatual, personagem, (Vector2){0,0}, 0.0f, WHITE);
            DrawRectangleRec (paredeesquerda, GRAY);
            DrawRectangleRec (paredecima, GRAY);
            DrawRectangleRec (parededireita, GRAY);
            DrawRectangleRec (paredebaixo, GRAY);



        EndDrawing();
    }

    UnloadTexture(BobTexture); 
    UnloadTexture(TileTexture);
    CloseWindow();

    return 0;
}