#include "movimentacao.h"

void MoverBob(Rectangle *personagem, Rectangle *frameAtual, float velocidade, Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita) {

    
    if (IsKeyDown(KEY_D)) {
        personagem->x += velocidade; 
        *frameAtual = direita;       
    }
    if (IsKeyDown(KEY_A)) {
        personagem->x -= velocidade;
        *frameAtual = esquerda;
    }
    if (IsKeyDown(KEY_W)) {
        personagem->y -= velocidade;
        *frameAtual = costas;
    }
    if (IsKeyDown(KEY_S)) {
        personagem->y += velocidade;
        *frameAtual = frente;
    }


}