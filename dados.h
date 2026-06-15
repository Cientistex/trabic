#ifndef DADOS_H
#define DADOS_H

// Definição do Tipo Item
#include <stdbool.h>
typedef struct{
    char nome[30];
    char conteudo[150];
    bool possui; // Indica se o jogador coletou ou não a pista  
}Item;

// Definição do Tipo Jogador
typedef struct{
    char nome[50];
    Item inventario[5]; //Slot 0: Bilhete, Slot 1: Chave Lab, etc.
}Jogador;

//Declaração das funções que MIGUEL irá programar (o grupo terá acesso a elas)
void InicializarJogador(Jogador *j, const char *nome_inicial);
bool SalvarJogo(Jogador *j);
bool CarregarJogo(Jogador *j);

#endif
