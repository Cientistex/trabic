#include "raylib.h"
#include "dados.h" // Inclui a definição dos tipos e protótipos das funções


int main(void) {
<<<<<<< HEAD
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
=======
    int largurax = 800, alturay = 600;
    InitWindow(largurax, alturay, "Quando eu fui pro C.A.P.S.");

    SetTargetFPS(60); 
    Texture2D BobTexture = LoadTexture ("assets/texture/Modern tiles_Free/Characters_free/Bob_16x16.png");
    Rectangle frente = {48, 0, 16, 32};
    Rectangle costas = {16, 0, 16, 32};
    Rectangle esquerda = {32, 0, 16, 32};
    Rectangle direita = {0, 0, 16, 32};
    Rectangle frameatual = frente;
    Rectangle personagem = {400, 300, 32, 64}; //retângulos do bob


    Rectangle paredeesquerda = {0, 0, 50, 600};
    Rectangle paredecima = {0, 0, 800, 50};
    Rectangle parededireita = {750, 0, 50, 800};
    Rectangle paredebaixo = {0, 550, 800, 50};

    float velocidade = 4.0f;

    
    Texture2D TileTexture = LoadTexture ("assets/texture/Tiles/tile_0117.png");
    Rectangle tileorigem = {0, 0, 16, 16};


>>>>>>> 62595ff06424d30956b9859dd129509c7c6d4d12
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