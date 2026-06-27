#include "movimentacao.h"
#include "math.h"

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

void ColisaoObjeto(Rectangle *player, Rectangle obstaculo) {
    if (CheckCollisionRecs(*player, obstaculo)) {
        // Calcula os centros
        float playerCenterX = player->x + player->width / 2.0f;
        float playerCenterY = player->y + player->height / 2.0f;
        float obsCenterX = obstaculo.x + obstaculo.width / 2.0f;
        float obsCenterY = obstaculo.y + obstaculo.height / 2.0f;
        
        // Distância entre os centros
        float dx = playerCenterX - obsCenterX;
        float dy = playerCenterY - obsCenterY;
        
        // Empurra o jogador com base no eixo de maior penetração
        if (fabs(dx) / obstaculo.width > fabs(dy) / obstaculo.height) {
            if (dx > 0) player->x = obstaculo.x + obstaculo.width;
            else player->x = obstaculo.x - player->width;
        } else {
            if (dy > 0) player->y = obstaculo.y + obstaculo.height;
            else player->y = obstaculo.y - player->height;
        }
    }
}