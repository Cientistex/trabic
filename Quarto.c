#include "quarto.h"

Rectangle personagem = {100, 100, 32, 32}; // Define a posição e tamanho do personagem
float velocidade = 4.0f; // Define a velocidade de movimento do personagem

Rectangle paredeesquerda = {0, 0, 32, 600}; // Define a posição e tamanho da parede esquerda
Rectangle paredecima = {0, 0, 800, 32}; // Define a posição e tamanho da parede cima
Rectangle parededireita = {768, 0, 32, 600}; //
Rectangle paredebaixo = {0, 568, 800, 32}; // Define a posição e tamanho da parede baixo

void DesenharQuarto(Jogador *player, Texture2D bobTex, Texture2D tileTex, bool *mostrandoPuzzle){

    // Define a posição e tamanho do terminal de acesso
    Rectangle terminalComputador = {600, 400, 100, 100}; // Exemplo de posição e tamanho do terminal

    if(!(*mostrandoPuzzle)){
        if(IsKeyDown(KEY_D)){
            personagem.x += velocidade;
        }
        if(IsKeyDown(KEY_A)){
            personagem.x -= velocidade;
        }
        if(IsKeyDown(KEY_W)){
            personagem.y -= velocidade;
        }
        if(IsKeyDown(KEY_S)){
            personagem.y += velocidade;
        }
        else{
            
            //Lógica do puzzle do terminal de acesso
            if(!player->estado.puzzleQuartoResolvido){
                // Verifica se o jogador está colidindo com o terminal de acesso e pressionou a tecla E para interagir
                if(IsKeyPressed(KEY_E) && CheckCollisionRecs(personagem, terminalComputador)){
                    *mostrandoPuzzle = true; // Ativa a exibição do puzzle do terminal
                    // Aqui você pode adicionar código para exibir o puzzle do terminal, como desenhar uma interface gráfica ou mostrar uma mensagem na tela
                    if(IsKeyPressed(KEY_UP)){
                        player->estado.numeroVisorAtual++;  
                    }
                    if(IsKeyPressed(KEY_DOWN) && player->estado.numeroVisorAtual > 0){// Evita que o número do visor fique negativo
                        player->estado.numeroVisorAtual--;
                    }
                    //Se o jogador acertar a resposta do puzzle, atualiza o estado lógico e salva o progresso
                    if(player->estado.numeroVisorAtual == 21){
                        player->estado.puzzleQuartoResolvido = true;
                        player->inventario[1].possui = true;
                        SalvarJogo(player);
                    }
                }
                
            }
        }
    }
}

// Desenha o quarto, incluindo o personagem, as paredes e o terminal de acesso
for (int y =0; y <= 600; y += 32){
    for(int x = 0; x <= 800; x += 32){
        DrawTexturePro (tileTex, (Rectangle){0,0,32,32}, (Rectangle){x,y,32,32}, (Vector2){0,0}, 0.0f, WHITE);
    }
}

//Desenha o Bob e as paredes
DrawTexturePro(bobTex, (Rectangle){0,0,32,32}, personagem, (Vector2){0,0}, 0.0f, WHITE);

//Se o puzzle do terminal de acesso estiver sendo mostrado, desenha a interface do puzzle
if(*mostrandoPuzzle){
    DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.85f)); // Fundo escuro para destacar o puzzle
    DrawText("=====TERMINAL DE ACESSO - QUARTO 505=====", 50, 50, 20, WHITE);
    DrawText("Sequência: 1, 1, 2, 3, 5, 8, 13, ...", 50, 100, 20, WHITE);
    DrawText("Use as setas para cima e para baixo para escolher o número", 50, 150, 20, WHITE);
    DrawText(TextFormat("Número atual: %d", player->estado.numeroVisorAtual), 50, 200, 20, WHITE);
}
