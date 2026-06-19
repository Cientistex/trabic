#include "dados.h" //Inclui a definição dos tipos e protótipos das funções
#include <stdio.h>
#include <string.h>

//Função que limpa e prepara os dados do jogador no início do jogo
void InicializarJogador(Jogador *j, const char *nome_inicial){
    strcpy(j->nome, nome_inicial);

    //Configura o item do bilhete(Quarto)
    strcpy(j->inventario[0].nome, "Bilhete");
    strcpy(j->inventario[0].conteudo, "ACORDO SEMPRE AS 03H. CONTO 54 CARNEIROS. OUÇO 7 BATIDAS NA PORTA. ESPERO 8 SEGUNDOS. ENTÃO MAIS 2.");

    //Configura o item do terminal(Quarto
    strcpy(j->inventario[1].nome, "Chave do Laboratório");
    strcpy(j->inventario[1].conteudo, "Uma chave eletrônica obtida no terminal do quarto 505.");
    j->inventario[1].possui = false;

    //Zera os outros slots de itens por segurança
    int i;
    for(i=2; i<5; i++){
        j->inventario[i].possui = false;
    }
}

//Grava a struct inteira do jogador no disco
bool SalvarJogo(Jogador *j){
    FILE *arquivo = fopen("savegame.dat", "wb");
    if(arquivo == NULL){
        return false; //Erro ao abrir o arquivo
    }
    fwrite(j, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    return true;
}

//Lê o arquivo do disco e reconstrói o jogador
bool CarregarJogo(Jogador *j){
    FILE *arquivo = fopen("savegame.dat", "rb");
    if(arquivo == NULL){
        return false; //Erro ao abrir o arquivo
    }
    fread(j, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    return true;
}