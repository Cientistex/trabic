#ifndef QUARTO_H
#define QUARTO_H

#include "raylib.h"
#include "dados.h" 

typedef struct {
    bool temChave;
    bool temCarta;
    bool temFusivel;    
    bool temItemFinal;  // <-- Nova: Item que dropa do puzzle do Lab
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
    Rectangle portaorigem,
    Inventario *inv); 


#endif
