#include "raylib.h"
#include "dados.h"
#include "movimentacao.h"
#include "quarto.h"

typedef enum {
    MODO_EXPLORACAO = 0,
    MODO_PUZZLE_COMPUTADOR = 1,
    MODO_PUZZLE_BANCADA = 2
} EstadoLaboratorio;

void AtualizarEDesenharLab(Rectangle *personagem, 
    int *TelaAtual,
    Rectangle *frameatual, 
    int velocidade,
    Texture2D BobTexture, 
    Texture2D tileTexture,
    Texture2D PortaTexture,
    Rectangle frente, Rectangle costas, Rectangle esquerda, Rectangle direita,
    Rectangle tileorigem, Rectangle tiledestino,
    Rectangle portaorigem,
    Inventario *inv) {

static int estadointerno = MODO_EXPLORACAO;
    static int telaPC = 0; 
    static int telaBancada = 0; 

    static bool tuboAcido = false;
    static bool tuboAgua = false;
    static bool tuboCatalisador = false;
    static bool erroMistura = false;

    static Texture2D computadorTexture;
    static Texture2D bancadaTexture;
    static bool texturasCarregadas = false;

    if (!texturasCarregadas) {
        computadorTexture = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/lab_computer.png");
        bancadaTexture = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/lab_large_table.png");
        texturasCarregadas = true;
    }

    Rectangle paredeEsquerda = { 0, 0, 32, 450 }; 
    Rectangle paredeDireita  = { 768, 0, 32, 450 };
    Rectangle paredeCima     = { 0, 0, 800, 32 }; 
    Rectangle paredeBaixo    = { 0, 418, 800, 32 };
    Rectangle portaSaidaI    = { 368, 390, 64, 32 }; 

    Rectangle pcorigem      = {0, 0, 16, 32}; 
    Rectangle pcdestino     = {200, 100, 48, 96}; 
    Rectangle pcdestinoI    = {200, 100, 96, 80}; 

    Rectangle bancadaOrigem    = {0, 0, 64, 32};
    Rectangle bancadaDestino   = {500, 100, 96, 48};
    Rectangle bancadaInteracao = {500, 132, 96, 80};

    Rectangle iconePasta   = { 100, 100, 64, 64 };
    Rectangle iconeLixo    = { 100, 200, 64, 64 };
    Rectangle botaoFechar  = { 700, 50, 40, 40 };
    Rectangle arquivoTexto = { 200, 150, 200, 40 }; 

    Rectangle recTubo1 = { 200, 180, 70, 110 };       // Ácido
    Rectangle recTubo2 = { 365, 180, 70, 110 };       // Água
    Rectangle recTubo3 = { 530, 180, 70, 110 };       // Catalisador
    Rectangle botaoMisturar = { 320, 340, 160, 40 };
    Rectangle fecharBancada = { 700, 50, 40, 40 };

    Vector2 mousePos = GetMousePosition();

    if (estadointerno == MODO_EXPLORACAO) {
        MoverBob(personagem, frameatual, velocidade, frente, costas, esquerda, direita);

        ColisaoObjeto(personagem, paredeCima);
        ColisaoObjeto(personagem, paredeBaixo);
        ColisaoObjeto(personagem, paredeEsquerda);
        ColisaoObjeto(personagem, paredeDireita);
        ColisaoObjeto(personagem, pcdestino);
        ColisaoObjeto(personagem, bancadaDestino);

        if (CheckCollisionRecs(*personagem, portaSaidaI) && IsKeyPressed(KEY_E)) {
            *TelaAtual = 1;
            personagem->x = 520;
            personagem->y = 160;
        }

        if (CheckCollisionRecs(*personagem, pcdestinoI) && IsKeyPressed(KEY_E)) {
            estadointerno = MODO_PUZZLE_COMPUTADOR;
        }
        if (CheckCollisionRecs(*personagem, bancadaInteracao) && IsKeyPressed(KEY_E) && inv->temFormula) {
            estadointerno = MODO_PUZZLE_BANCADA;
        }
        if (CheckCollisionRecs(*personagem, bancadaInteracao)) {
            if (inv->temFormula) {
                DrawText("Pressione E para examinar a Bancada", 230, 250, 16, YELLOW);
            } else {
                DrawText("Bloqueado: Voce precisa de uma formula quimica.", 190, 250, 16, RED);
            }
        }
    } 

    else if (estadointerno == MODO_PUZZLE_COMPUTADOR) {

        if (IsKeyPressed(KEY_Q)) {
            estadointerno = MODO_EXPLORACAO;
            telaPC = 0; 
        }


        if (telaPC == 0) { 
            if (CheckCollisionPointRec(mousePos, iconePasta) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                telaPC = 1; 
            }
        } 
        else if (telaPC == 1) { 
            if (CheckCollisionPointRec(mousePos, arquivoTexto) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                telaPC = 2; 
                inv->temFormula = true; 
            }
            if (CheckCollisionPointRec(mousePos, botaoFechar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                telaPC = 0;
            }
        } 
        else if (telaPC == 2) { 
            if (CheckCollisionPointRec(mousePos, botaoFechar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                telaPC = 1;
            }
        }
    }else if (estadointerno == MODO_PUZZLE_BANCADA) {

        if (IsKeyPressed(KEY_Q) || (CheckCollisionPointRec(mousePos, fecharBancada) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            estadointerno = MODO_EXPLORACAO;
            if (!inv->temCorrosivo) { 
                telaBancada = 0;
                tuboAcido = tuboAgua = tuboCatalisador = false;
                erroMistura = false;
            }
        }

        if (telaBancada == 0) {

            if (CheckCollisionPointRec(mousePos, recTubo1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                tuboAcido = !tuboAcido;
                erroMistura = false;
            }
            if (CheckCollisionPointRec(mousePos, recTubo2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                tuboAgua = !tuboAgua;
                erroMistura = false;
            }
            if (CheckCollisionPointRec(mousePos, recTubo3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                tuboCatalisador = !tuboCatalisador;
                erroMistura = false;
            }

            if (CheckCollisionPointRec(mousePos, botaoMisturar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                if (tuboAcido && !tuboAgua && tuboCatalisador) {
                    telaBancada = 1;
                    inv->temCorrosivo = true; 
                } else {
                    erroMistura = true;
                }
            }
        }
    }


    for (int y = 0; y <= 450; y += 32) {
        for (int x = 0; x <= 800; x += 32) {
            DrawTexturePro(tileTexture, tileorigem, (Rectangle){x, y, 32, 32}, (Vector2){0,0}, 0.0f, WHITE);
        }
    }

    DrawRectangleRec(paredeEsquerda, GRAY);
    DrawRectangleRec(paredeDireita, GRAY);
    DrawRectangleRec(paredeCima, GRAY);
    DrawRectangleRec(paredeBaixo, GRAY);

    DrawTexturePro(PortaTexture, portaorigem, (Rectangle){ 368, 418, 64, 32 }, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(computadorTexture, pcorigem, pcdestino, (Vector2){0,0}, 0.0f, WHITE);
    DrawTexturePro(bancadaTexture, bancadaOrigem, bancadaDestino, (Vector2){0,0}, 0.0f, WHITE);


    if (estadointerno == MODO_EXPLORACAO) {
        DrawTexturePro(BobTexture, *frameatual, *personagem, (Vector2){0,0}, 0.0f, WHITE);

        if (CheckCollisionRecs(*personagem, pcdestinoI)) {
            DrawText("Pressione E para acessar o Computador", 220, 250, 16, YELLOW);
        }
        if (CheckCollisionRecs(*personagem, bancadaInteracao)) {
            DrawText("Pressione E para examinar a Bancada", 230, 250, 16, YELLOW);
        }
        if (CheckCollisionRecs(*personagem, portaSaidaI)) {
            DrawText("Pressione E para voltar ao Corredor", 260, 350, 18, YELLOW);
        }
    }

    if (estadointerno == MODO_PUZZLE_COMPUTADOR) {
        DrawRectangle(50, 30, 700, 390, DARKGRAY); 
        DrawRectangle(60, 40, 680, 370, BLUE); 
        
        DrawRectangle(60, 385, 680, 25, LIGHTGRAY);
        DrawText("Iniciar", 70, 390, 12, BLACK);
        DrawText("Pressione Q para desligar o PC", 500, 390, 12, BLACK);

        if (telaPC == 0) {
            DrawRectangleRec(iconePasta, YELLOW);
            DrawText("Projetos", iconePasta.x, iconePasta.y + 70, 12, WHITE);

            DrawRectangleRec(iconeLixo, GRAY);
            DrawText("Lixeira", iconeLixo.x, iconeLixo.y + 70, 12, WHITE);
            
            DrawText("Clique na pasta para investigar.", 250, 200, 20, WHITE);
        } 
        else if (telaPC == 1) {
            DrawRectangle(150, 50, 600, 300, WHITE);
            DrawRectangle(150, 50, 600, 30, LIGHTGRAY); 
            DrawText("Diretorio: C:/Projetos/Lab_Secret", 160, 58, 14, BLACK);
            
            DrawRectangleRec(botaoFechar, RED);
            DrawText("X", botaoFechar.x + 15, botaoFechar.y + 10, 16, WHITE);

            if (CheckCollisionPointRec(mousePos, arquivoTexto)) {
                DrawRectangleRec(arquivoTexto, LIGHTGRAY); 
            }
            DrawText("formula_composta.txt", arquivoTexto.x + 10, arquivoTexto.y + 10, 16, BLACK);
        } 
        else if (telaPC == 2) {
            DrawRectangle(150, 50, 600, 300, RAYWHITE);
            DrawRectangle(150, 50, 600, 30, GRAY);
            DrawText("Notepad - formula_composta.txt", 160, 58, 14, WHITE);

            DrawRectangleRec(botaoFechar, RED);
            DrawText("X", botaoFechar.x + 15, botaoFechar.y + 10, 16, WHITE);

            DrawText("DERRETE METAL - REQUISITOS:", 180, 100, 16, BLACK);
            DrawText("- Misturar o Composto Corrosivo na Bancada.", 180, 130, 14, DARKGRAY);
            DrawText("- Manter a temperatura estavel.", 180, 150, 14, DARKGRAY);
            
            DrawText("[ FORMULA ANOTADA ]", 250, 250, 16, GREEN);
        }
    }

    if (estadointerno == MODO_PUZZLE_BANCADA) {
        DrawRectangle(50, 30, 700, 390, DARKGRAY);
        DrawRectangle(60, 40, 680, 370, BLACK); 
        
        DrawRectangleRec(fecharBancada, RED);
        DrawText("X", fecharBancada.x + 15, fecharBancada.y + 10, 16, WHITE);

        if (telaBancada == 0) {
            DrawText("EQUIPAMENTO DE REAÇÃO QUÍMICA", 230, 60, 20, GREEN);
            DrawText("Selecione os elementos corretos para a mistura:", 180, 100, 15, LIGHTGRAY);

            DrawRectangleRec(recTubo1, tuboAcido ? RED : MAROON);
            DrawText("Reativo A\n (Acido)", recTubo1.x + 5, recTubo1.y + 40, 12, WHITE);
            if (tuboAcido) DrawRectangleLinesEx(recTubo1, 3, GREEN);

            DrawRectangleRec(recTubo2, tuboAgua ? BLUE : DARKBLUE);
            DrawText("Reativo B\n  (Agua)", recTubo2.x + 5, recTubo2.y + 40, 12, WHITE);
            if (tuboAgua) DrawRectangleLinesEx(recTubo2, 3, GREEN);


            DrawRectangleRec(recTubo3, tuboCatalisador ? PURPLE : DARKPURPLE);
            DrawText("Reativo C\n(Catalis.)", recTubo3.x + 5, recTubo3.y + 40, 12, WHITE);
            if (tuboCatalisador) DrawRectangleLinesEx(recTubo3, 3, GREEN);

            DrawRectangleRec(botaoMisturar, GREEN);
            DrawText("MISTURAR", botaoMisturar.x + 40, botaoMisturar.y + 12, 16, BLACK);

            if (erroMistura) {
                DrawText("REACAO ABORTADA: Proporcoes incorretas ou instaveis!", 180, 310, 14, RED);
            }
        } 
        else if (telaBancada == 1) {
            DrawText("SINTESE CONCLUIDA!", 280, 120, 24, GREEN);
            DrawText("Os reativos se estabilizaram e fundiram com sucesso.", 190, 180, 16, WHITE);
            
            DrawText("[ OBTIDO: COMPOSTO CORROSIVO ]", 240, 240, 18, YELLOW);
            DrawText("Pressione Q ou clique no X para retornar", 240, 340, 14, GRAY);
        }
    }
}