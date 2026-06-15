#ifndef DADOS_H
#define DADOS_H

#include <stdbool.h>
typedef struct{
    char nome[30];
    char conteudo[150];
    bool possui; // Indica se o jogador coletou ou não a pista  
}Item;

typedef struct{
    char nome[50];
    Item inventario[5];    
}Jogador;

void InicializarJogador(Jogador *j, const char *nome_inicial);
bool SalvarJogo(Jogador *j);
boolCarregarJogo(Jogador *j);

#endif
