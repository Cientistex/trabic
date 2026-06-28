#include "raylib.h"
#include "corredor.h"
#include "movimentacao.h"
#include "quarto.h"

void AtualizarEDesenharCorredor(Rectangle *personagem, 
    int *TelaAtual,
    Rectangle *frameatual, 
    int velocidade,
    Texture2D BobTexture, 
    Texture2D tileTexture,
    Texture2D PortaTexture,
    Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita,
    Rectangle tileorigem, Rectangle tiledestino,
    Rectangle portaorigem,
    Inventario *inv,
    bool *luzesApagadas) { 
   
   
    Rectangle paredeEsquerda = { 0, 0, 32, 450 }; 
    Rectangle paredeDireita  = { 768, 0, 32, 450 };
    Rectangle paredeCima     = { 0, 0, 800, 150 };
    Rectangle paredeBaixo    = { 0, 300, 800, 150 };

    
    Rectangle portaQuarto = { 0, 200, 32, 64 };
    Rectangle portaQuartoI = { 32, 200, 32, 64 };
    Rectangle portaEscritorio = { 200, 86, 32, 64 }; 
    Rectangle portaEscritorioI ={ 200, 150, 32, 32 };
    Rectangle caixaForca = { 380, 135, 32, 32 }; 
    Rectangle portaLab = { 520, 86, 32, 64 }; 
    Rectangle portaLabI = { 520, 150, 32, 32 };
    Rectangle portaFinal = { 704, 86, 32, 64 }; 
    Rectangle portaFinalI = { 704, 150, 32, 32 };
    
    MoverBob(personagem, frameatual, velocidade, frente, costas, esquerda, direita);

    ColisaoObjeto(personagem,paredeCima);
    ColisaoObjeto(personagem,paredeBaixo);
    ColisaoObjeto(personagem,paredeEsquerda);
    ColisaoObjeto(personagem,paredeDireita);

  
    if (CheckCollisionRecs(*personagem, portaQuartoI ) && IsKeyPressed(KEY_E)) {
        *TelaAtual = 0;
        personagem->x = 450; 
        personagem->y = 200;
    }

    if (CheckCollisionRecs(*personagem, portaEscritorioI) && IsKeyPressed(KEY_E)) {
        if (inv->temChave) {
            *TelaAtual = 2; 
            personagem->x = 400; 
            personagem->y = 400;
        }
    }

    if (CheckCollisionRecs(*personagem, portaLabI) && IsKeyPressed(KEY_E)) {
        *TelaAtual = 3; 
        personagem->x = 400; 
        personagem->y = 400;
    }

    if (CheckCollisionRecs(*personagem, caixaForca) && IsKeyPressed(KEY_E)) {
        if (inv->temFusivel) {
            *luzesApagadas = false; 
        }
    }


    if (CheckCollisionRecs(*personagem, portaFinalI) && IsKeyPressed(KEY_E)) {
        if (inv->temCorrosivo) {
            *TelaAtual = 4; 
        }
    }


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

    DrawTexturePro(PortaTexture, portaorigem, portaQuarto, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(PortaTexture, portaorigem, portaEscritorio, (Vector2){0,0}, 0.0f, WHITE); 
    DrawTexturePro(PortaTexture, portaorigem, portaLab, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(PortaTexture, portaorigem, portaFinal, (Vector2){0,0}, 0.0f, WHITE);

    DrawRectangleRec(caixaForca, DARKGRAY);
    DrawRectangleLinesEx(caixaForca, 2, !(*luzesApagadas) ? GREEN : RED); 
    DrawText("⚡", caixaForca.x + 12, caixaForca.y + 12, 16, !(*luzesApagadas) ? YELLOW : GRAY);
    DrawTexturePro(BobTexture, *frameatual, *personagem, (Vector2){0,0}, 0.0f, WHITE);


    if (CheckCollisionRecs(*personagem, portaQuartoI)) {
        DrawText("Pressione E para voltar ao Quarto", 32, 280, 16, YELLOW);
    }

    // Feedback: Porta do Escritório
    if (CheckCollisionRecs(*personagem, portaEscritorioI)) {
        if (inv->temChave) {
            DrawText("Pressione E para entrar no Escritorio", 150, 280, 16, YELLOW);
        } else {
            DrawText("Porta Trancada. Voce precisa de uma chave.", 150, 280, 16, RED);
        }
    }

    // Feedback: Porta do Laboratório
    if (CheckCollisionRecs(*personagem, portaLabI)) {
        DrawText("Pressione E para entrar no Lab", 450, 280, 16, YELLOW);
    }

    // Feedback: Caixa de Força
    if (CheckCollisionRecs(*personagem, caixaForca)) {
        if (!(*luzesApagadas)) { // <-- Se NÃO estiver apagada (ou seja, se estiver acesa)
            DrawText("A energia do corredor esta funcionando.", 300, 280, 16, GREEN);
        } else if (inv->temFusivel) {
            DrawText("Pressione E para colocar o Fusivel e acender as luzes!", 220, 280, 16, YELLOW);
        } else {
            DrawText("vc precisa de um fusivel para acender as luzes", 250, 280, 16, RED);
        }
    }

    if (CheckCollisionRecs(*personagem, portaFinalI)) {
        if (inv->temCorrosivo) {
            DrawText("Pressione E para usar o item e ESCAPAR!", 450, 280, 16, GREEN);
        } else {
            DrawText("A porta precisa de um dispositivo do Laboratório para abrir.", 380, 280, 16, RED);
        }
    }
 
}
