#ifndef ESCRITORIO_H
#define ESCRITORIO_H

#include "raylib.h"
#include "dados.h"
#include "movimentacao.h"
#include "quarto.h"

void AtualizarEDesenharEscritorio(Rectangle *personagem, 
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