#ifndef QUARTO_H
#define QUARTO_H

#include "raylib.h"
#include "dados.h" 

typedef struct {
    bool temChave;
    bool temCarta;
} Inventario;

void AtualizarEDesenharQuarto(Rectangle *personagem, 
    int *TelaAtual,
    Rectangle *frameatual, 
    int velocidade,
    Texture2D BobTexture, 
    Texture2D tileTexture,
    Texture2D PortaTexture,
    Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita,
    Rectangle tileorigem, Rectangle tiledestino,
    Rectangle portaorigem, Rectangle portadestino,
    Inventario *inv); 


#endif
