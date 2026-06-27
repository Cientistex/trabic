/*

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct{
	char nome[30];
	char conteudo[150];
	bool possui; // Indica se o jogador coletou ou não a pista
}Item;
	
typedef struct{
	char nome[50];
	Item inventario[5];
}Jogador;

int main(){
	
	Jogador player;
	player.inventario[0]=false;
	player.inventario[1]=false;
	player.inventario[2]=false;
	player.inventario[3]=false;
	player.inventario[4]=false;
	
	bool BilheteColetado = false;
	

	
	printf("UM BILHETE COM UMA ESTRANHA MENSAGEM ESTÁ PRESO NA MOLDURA DO ESPELHO\n");
	
	//Jogador passa o mouse/clica em cima desse espelho
	
	//Mensagem do bilhete
	printf("ACORDO SEMPRE ÀS 03H. CONTO 54 CARNEIROS. OUÇO 7 BATIDAS NA PORTA. ESPERO 8 SEGUNDOS. ENTÃO MAIS 2.\n");
	
	//Usuário pega o bilhete e atualiza o estado lógico
	player.inventario[0].possui = true;
	BilheteColetado = true;
	
	//SEGUNDO PUZZLE
	
	
	//O jogador observa um pequeno terminal de acesso no quarto
	printf("=====TERMINAL DE ACESSO -QUARTO 505=====\n");
	printf("O terminal emite BIPs e exibe uma sequência numérica na tela\n");
	
		 "!" representa negação de um estado lógico
		Se for false -> !(variável) = true
		Se for true - > !(variável) = false
	
	int RespostaDoJogador = 0;
	int Tentativas = 0;
	bool PuzzleQuartoResolvido = false;
	
		while(!PuzzleQuartoResolvido){
			printf("Sequência: 1, 1, 2, 3, 5, 8, 13, ...\n");
			printf("Qual é o próximo número da sequência?\n");
			scanf("%d",&RespostaDoJogador);
			Tentativas++;
			
			if(RespostaDoJogador == 21){
				PuzzleQuartoResolvido = true;
				
				printf("Os BIPs foram encerrados\n");
				printf("Uma gaveta abaixo do terminal se abre\n");
				
				//Usuário desliza o mouse/clica sobre a gaveta e pega a chave
				printf("Chave do laboratório obtida!\n");
				player.inventario[1].possui=true;
				
			}else{
				printf("[BIP DE ERRO]--> Código incorreto\n");
				
				if(Tentativas>=3){
					printf("DICA: Cada número é a soma dos dois anteriores\n");
				}
				printf("Tente novamente\n");
			}
		}	
*/