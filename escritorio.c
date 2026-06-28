#include "raylib.h"
#include "dados.h"
#include "movimentacao.h"
#include "quarto.h"


typedef enum {
    MODO_EXPLORACAO = 0,
    MODO_PUZZLE_ESTANTE = 1,
    MODO_PUZZLE_CADEADO = 2
} EstadoEscritorio;

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
    Inventario *inv) {

    static int estadointerno = MODO_EXPLORACAO;
    static bool estanteresolvida = false; 
    static bool cadeadoresolvido = false;

    static int rotorCadeado[7] = {0, 0, 0, 0, 0, 0, 0};
    int senhaCadeado[7] = {0, 3, 5, 4, 7, 8, 2};

    
    
    static Texture2D cofre;
    static Texture2D estantetexture;
    static bool texturasCarregadas = false;

    if (!texturasCarregadas) {
        estantetexture = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/lab_wooden_cabinet_full.png");
        cofre = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/room_cabinet.png");
        texturasCarregadas = true;
    }
    static int estante[2][2] = {
        {1, 0},
        {0, 1}
    };
    int gabaritoEstante[2][2] = {
        {0, 1},
        {1, 0}
    };

    Rectangle paredeEsquerda = {0, 0, 32, 600}; 
    Rectangle paredeCima = {0, 0, 800, 32}; 
    Rectangle paredeDireita = {768, 0, 32, 600}; 
    Rectangle paredeBaixo = {0, 418, 800, 32};
  
    Rectangle cadeadoorigem = {0, 0, 16,32};
    Rectangle cadeadodestino = { 500, 32, 60, 40 };
    Rectangle cadeadodestinoI = { 500, 32, 60, 80 };

    Rectangle estanteorigem = {0, 0, 32, 32};
    Rectangle estantedestino = { 200, 32, 100, 40 };
    Rectangle estantedetinoI = { 200, 32, 100, 80 };

    Rectangle portasaida = {368, 418, 32, 32};
    Rectangle portasaidaI = {368, 390, 32, 32};

    Vector2 mouse = GetMousePosition();

    if (estadointerno == MODO_EXPLORACAO) {
        

        MoverBob(personagem, frameatual, velocidade, frente, costas, esquerda, direita);

        ColisaoObjeto(personagem, paredeCima);
        ColisaoObjeto(personagem, paredeBaixo);
        ColisaoObjeto(personagem, paredeEsquerda);
        ColisaoObjeto(personagem, paredeDireita);
        

        ColisaoObjeto(personagem, estantedestino);
        ColisaoObjeto(personagem, cadeadodestino); 
        if (CheckCollisionRecs(*personagem, portasaidaI)&& IsKeyPressed(KEY_E)){
            *TelaAtual = 1;

            personagem->x = 200;
            personagem->y = 150;
        }

        if (CheckCollisionRecs(*personagem, estantedetinoI) && IsKeyPressed(KEY_E) && !estanteresolvida) {
            estadointerno = MODO_PUZZLE_ESTANTE;
        }


        if (CheckCollisionRecs(*personagem, cadeadodestinoI) && IsKeyPressed(KEY_E) && !cadeadoresolvido) {
            estadointerno = MODO_PUZZLE_CADEADO;
        }
    }else if (estadointerno == MODO_PUZZLE_ESTANTE) {
        if (IsKeyPressed(KEY_Q)) {
            estadointerno = MODO_EXPLORACAO;
        }

        int startX = 336; 
        int startY = 160;
        int tamSlot = 48;
        int espacamento = 16;


        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                Rectangle slotLivro = { 
                    startX + j * (tamSlot + espacamento), 
                    startY + i * (tamSlot + espacamento), 
                    tamSlot, 
                    tamSlot 
                };


                if (CheckCollisionPointRec(mouse, slotLivro) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    estante[i][j] = (estante[i][j] == 0) ? 1 : 0; 
                }
            }
        }


        bool acertouTudo = true;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (estante[i][j] != gabaritoEstante[i][j]) {
                    acertouTudo = false;
                }
            }
        }

        if (acertouTudo) {
            estanteresolvida = true;
            estadointerno = MODO_EXPLORACAO; 
        }
    }else if (estadointerno == MODO_PUZZLE_CADEADO) {
        if (IsKeyPressed(KEY_Q)) {
            estadointerno = MODO_EXPLORACAO;
        }

        int startX = 195;
        int startY = 200;
        int tamW = 50;
        int tamH = 60;
        int espacamento = 10;

        for (int i = 0; i < 7; i++) {
            Rectangle slotRotor = { startX + i * (tamW + espacamento), startY, tamW, tamH };


            if (CheckCollisionPointRec(mouse, slotRotor) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                rotorCadeado[i] = (rotorCadeado[i] + 1) % 10;
            }
        }


        bool senhaCorreta = true;
        for (int i = 0; i < 7; i++) {
            if (rotorCadeado[i] != senhaCadeado[i]) {
                senhaCorreta = false;
            }
        }

        if (senhaCorreta) {
            cadeadoresolvido = true;
            inv->temFusivel = true;
            estadointerno = MODO_EXPLORACAO; 
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

    DrawTexturePro(PortaTexture, portaorigem, portasaida,(Vector2){0,0}, 0.0f, RAYWHITE),

    DrawTexturePro(estantetexture, estanteorigem, estantedetinoI,(Vector2){0,0}, 0.0f, RAYWHITE);
    
    DrawTexturePro(cofre, cadeadoorigem, cadeadodestino, (Vector2){0,0}, 0.0f, RAYWHITE);

    if (estadointerno == MODO_EXPLORACAO && CheckCollisionRecs(*personagem, cadeadodestinoI) && !cadeadoresolvido) {
        DrawText("Pressione E para mexer no Cadeado", 250, 350, 18, YELLOW);
    }
    if (estadointerno == MODO_EXPLORACAO && CheckCollisionRecs(*personagem, portasaidaI) ) {
        DrawText("Pressione E para voltar ao corredor", 250, 350, 18, YELLOW);
    }

    if (estadointerno == MODO_EXPLORACAO) {
        DrawTexturePro(BobTexture, *frameatual, *personagem, (Vector2){0,0}, 0.0f, WHITE);

        if (CheckCollisionRecs(*personagem, estantedetinoI) && !estanteresolvida) {
            DrawText("Pressione E para examinar a Estante", 250, 350, 18, YELLOW);
        }

        if (CheckCollisionRecs(*personagem, cadeadodestinoI) && !cadeadoresolvido) {
            DrawText("Pressione E para mexer no Cadeado", 250, 350, 18, YELLOW);
        }
    }
    if (estadointerno == MODO_PUZZLE_ESTANTE) {

        DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.85f));
        
        DrawText("Resolve o Puzzle da Estante", 260, 80, 20, RAYWHITE);
        DrawText("Q para voltar", 20, 20, 16, RED);

        int startX = 336; 
        int startY = 160;
        int tamSlot = 48;
        int espacamento = 16;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                Rectangle slotLivro = { startX + j * (tamSlot + espacamento), startY + i * (tamSlot + espacamento), tamSlot, tamSlot };
                

                Color corLivro = (estante[i][j] == 1) ? BLUE : DARKGRAY;
                
                DrawRectangleRec(slotLivro, corLivro);
                DrawRectangleLinesEx(slotLivro, 2, WHITE); 
            }
        }
    }
    
    if (estadointerno == MODO_PUZZLE_CADEADO) {
        DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.85f));
        DrawText("Insira a Senha do Cadeado (Clique para girar)", 180, 80, 20, RAYWHITE);
        DrawText("Q voltar", 20, 20, 16, RED);

        int startX = 195;
        int startY = 200;
        int tamW = 50;
        int tamH = 60;
        int espacamento = 10;

        for (int i = 0; i < 7; i++) {
            Rectangle slotRotor = { startX + i * (tamW + espacamento), startY, tamW, tamH };
            
            DrawRectangleRec(slotRotor, LIGHTGRAY);
            DrawRectangleLinesEx(slotRotor, 3, WHITE);
            
            DrawText(TextFormat("%d", rotorCadeado[i]), slotRotor.x + 16, slotRotor.y + 15, 32, BLACK);
        }
    }

}