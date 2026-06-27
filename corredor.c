#include "raylib.h"
#include "corredor.h"
#include "movimentacao.h"


void AtualizarEDesenharCorredor(Rectangle *personagem, 
    int *TelaAtual,
    Rectangle *frameatual, 
    int velocidade,
    Texture2D BobTexture, 
    Texture2D tileTexture,
    Texture2D PortaTexture,
    Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita,
    Rectangle tileorigem, Rectangle tiledestno,
    Rectangle portaorigem, Rectangle portadestino){
   
    Rectangle paredeEsquerda = { 0, 0, 32, 450 }; 
    Rectangle paredeDireita  = { 768, 0, 32, 450 };
    Rectangle paredeCima     = { 0, 0, 800, 150 };
    Rectangle paredeBaixo    = { 0, 300, 800, 150 };


    MoverBob(personagem, frameatual, velocidade, frente, costas, esquerda, direita);

    if (CheckCollisionRecs(*personagem, paredeEsquerda))  personagem->x += velocidade;
    if (CheckCollisionRecs(*personagem, paredeDireita))   personagem->x -= velocidade;
    if (CheckCollisionRecs(*personagem, paredeCima))      personagem->y += velocidade;
    if (CheckCollisionRecs(*personagem, paredeBaixo))     personagem->y -= velocidade;


    for (int y = 0; y <= 600; y += 32) {
        for (int x = 0; x <= 800; x += 32) {
            Rectangle destino = {x, y, 32, 32};
            DrawTexturePro(tileTexture, tileorigem, destino, (Vector2){0,0}, 0.0f, WHITE);
        }
    }

    DrawRectangleRec(paredeEsquerda, GRAY);
    DrawRectangleRec(paredeDireita, GRAY);
    DrawRectangleRec(paredeCima, GRAY);
    DrawRectangleRec(paredeBaixo, GRAY);

    DrawTexturePro(PortaTexture, portaorigem, portadestino,(Vector2){0,0}, 0.0f, WHITE);

    DrawTexturePro(BobTexture, *frameatual, *personagem, (Vector2){0,0}, 0.0f, WHITE);
}