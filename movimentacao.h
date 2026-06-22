#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include "raylib.h"

void MoverBob(Rectangle *personagem, Rectangle *frameAtual, float velocidade, Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita);

#endif