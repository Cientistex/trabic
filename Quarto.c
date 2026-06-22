#if 0
#include "quarto.h"
#include "movimentacao.h"



// --- VARIÁVEIS GLOBAIS (Apenas constantes puras) ---
Rectangle personagem = {400, 225, 32, 32}; 
Rectangle frente = {32, 0, 16, 32};
Rectangle costas = {16, 0, 15, 32};
Rectangle esquerda = {32, 0, 16, 32};
Rectangle direita = {0, 0, 16, 32};

// CORREÇÃO: Inicializado com números diretos para ser uma constante válida
Rectangle frameatual = {32, 0, 16, 32}; 

float velocidade = 4.0f; 

Rectangle paredeesquerda = {0, 0, 32, 600}; 
Rectangle paredecima = {0, 0, 800, 32}; 
Rectangle parededireita = {768, 0, 32, 600}; 
Rectangle paredebaixo = {0, 568, 800, 32}; 

void DesenharQuarto(Jogador *player, Texture2D bobTex, Texture2D tileTex, bool *mostrandoPuzzle) {

    Rectangle terminalComputador = {600, 400, 100, 100}; 

    // 1. MOVIMENTAÇÃO (Apenas se o puzzle não estiver aberto)
    if (!(*mostrandoPuzzle)) {
        MoverBob(&personagem, &frameatual, velocidade, frente, costas, esquerda, direita);
    }
    
    // 2. SISTEMA DE COLISÕES (Independentes do Puzzle)
    if (CheckCollisionRecs(personagem, paredeesquerda)) {
        personagem.x += velocidade;
    }
    if (CheckCollisionRecs(personagem, paredecima)) {
        personagem.y += velocidade;
    }
    if (CheckCollisionRecs(personagem, parededireita)) {
        personagem.x -= velocidade;
    }
    if (CheckCollisionRecs(personagem, paredebaixo)) {
        personagem.y -= velocidade;
    }

    // 3. LÓGICA DO INTERATIVO / PUZZLE
    // Se o puzzle ainda não foi resolvido, permite interagir
    if (!player->estado.puzzleQuartoResolvido) {
        
        // Se apertar E perto do PC, abre a tela do puzzle
        if (IsKeyPressed(KEY_E) && CheckCollisionRecs(personagem, terminalComputador)) {
            *mostrandoPuzzle = true; 
        }

        // Se a tela do puzzle estiver aberta, processa os inputs dele
        if (*mostrandoPuzzle) {
            if (IsKeyPressed(KEY_UP)) {
                player->estado.numeroVisorAtual++;  
            }
            if (IsKeyPressed(KEY_DOWN) && player->estado.numeroVisorAtual > 0) {
                player->estado.numeroVisorAtual--;
            }
            
            // Condição de vitória do puzzle
            if (player->estado.numeroVisorAtual == 21) {
                player->estado.puzzleQuartoResolvido = true;
                player->inventario[1].possui = true;
                SalvarJogo(player);
                *mostrandoPuzzle = false; // Fecha o puzzle automaticamente ao acertar
            }
        }
    }

    // 4. CAMADA DE DESENHO (Tudo trazido para dentro da função!)
    
    // Desenha o chão completo do quarto
    for (int y = 0; y <= 600; y += 32) {
        for (int x = 0; x <= 800; x += 32) {
            DrawTexturePro(tileTex, (Rectangle){0,0,32,32}, (Rectangle){x,y,32,32}, (Vector2){0,0}, 0.0f, WHITE);
        }
    }

    // Desenha as Paredes invisíveis (mude para WHITE ou tire o comentário se quiser vê-las)
    DrawRectangleRec(paredeesquerda, BLANK);
    DrawRectangleRec(paredecima, BLANK);
    DrawRectangleRec(parededireita, BLANK);
    DrawRectangleRec(paredebaixo, BLANK);
    
    // Desenha o Terminal (Apenas um retângulo indicador por enquanto)
    DrawRectangleRec(terminalComputador, BLUE);

    // Desenha o Bob (CORREÇÃO: Usando o parâmetro 'bobTex' que veio do main)
    DrawTexturePro(bobTex, frameatual, personagem, (Vector2){0,0}, 0.0f, WHITE);

    // Se o puzzle estiver ativo, desenha a interface por cima de tudo
    if (*mostrandoPuzzle) {
        DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.85f)); 
        DrawText("===== TERMINAL DE ACESSO - QUARTO 505 =====", 50, 50, 20, WHITE);
        DrawText("Sequência: 1, 1, 2, 3, 5, 8, 13, ...", 50, 100, 20, WHITE);
        DrawText("Use as setas para CIMA e para BAIXO para decifrar o código.", 50, 150, 20, WHITE);
        DrawText(TextFormat("Número atual no visor: %d", player->estado.numeroVisorAtual), 50, 200, 20, YELLOW);
    }

} 
    #endif