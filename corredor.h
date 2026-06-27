#ifndef CORREDOR_H
#define CORREDOR_H

#include "raylib.h"

void AtualizarEDesenharCorredor (Rectangle *personagem, 
    int *TelaAtual,
    Rectangle *frameatual, 
    int velocidade,
    Texture2D BobTexture, 
    Texture2D tileTexture,
    Texture2D PortaTexture,
    Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita,
    Rectangle tileorigem, Rectangle tiledestino,
    Rectangle portaorigem, Rectangle portadestino);







#endif