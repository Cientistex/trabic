#include "quarto.h"
#include "movimentacao.h"
#include <math.h> 

typedef enum {
    QUARTO_EXPLORANDO,
    QUARTO_PUZZLE_PC
} SubEstadoQuarto;

static SubEstadoQuarto estadointerno = QUARTO_EXPLORANDO;

static bool erroAtivo = false;
static bool puzzleResolvido = false; 
static bool lendoCarta = false;      

float velocidade = 4.0f; 

Rectangle paredeEsquerda = {0, 0, 32, 600}; 
Rectangle paredeCima = {0, 0, 800, 32}; 
Rectangle paredeDireita = {768, 0, 32, 600}; 
Rectangle paredeBaixo = {0, 418, 800, 32}; 


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
    Inventario *inv){

    static Texture2D carta;
    static Texture2D mesa;
    static Texture2D pc;
    static Texture2D maca;
    static bool texturasCarregadas = false;

    if (!texturasCarregadas) {
        mesa = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/lab_medium_table.png");
        pc = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/lab_computer.png");
        maca = LoadTexture("assets/texture/topdown_hospital_Assets/Pngs/room_bed_v.png");
        carta = LoadTexture("assets/texture/HospitalHorrorPack1/Paper/Paper_Plain.png");
        texturasCarregadas = true;
    }

   
    Rectangle pcdestino = {69, 40, 48, 48}; 
    Rectangle pcorigem = {0, 4, 16, 16};
    Rectangle terminalComputador = {pcdestino.x - 10, pcdestino.y - 10, pcdestino.width + 20, pcdestino.height + 30}; 
   
    Rectangle mesadestino = {400, 180, 96, 48}; 
    Rectangle mesadestino2 = {45, 50, 96, 48};
    Rectangle mesaorigem = {0, 0, 32, 16}; 

    Rectangle macadestino = {710, 45, 48, 96}; 
    Rectangle macaorigem = {0, 0, 16, 32}; 

    Rectangle pegarcarta = {mesadestino.x, mesadestino.y, 96, 60};
    Rectangle cartaorigem = {0, 0, 32, 32};
    Rectangle cartadestino = {mesadestino.x + 20, mesadestino.y + 15, 16, 16};

    Rectangle portadestino = {768, 200, 32, 64};
    Rectangle portaSaida = {736, 200, 32, 64}; 
    
    static char textoDigitado[10] = ""; 
    static int contagemLetras = 0;      

    switch (estadointerno) {
        
        case QUARTO_EXPLORANDO:
            

            if (!lendoCarta) {
                MoverBob(personagem, frameatual, velocidade, frente, costas, esquerda, direita);

                // 1. Colisões com as Paredes do Quarto
                if (CheckCollisionRecs(*personagem, paredeEsquerda))  personagem->x += velocidade;
                if (CheckCollisionRecs(*personagem, paredeDireita))   personagem->x -= velocidade;
                if (CheckCollisionRecs(*personagem, paredeCima))      personagem->y += velocidade;
                if (CheckCollisionRecs(*personagem, paredeBaixo))     personagem->y -= velocidade;

                ColisaoObjeto(personagem, mesadestino);
                ColisaoObjeto(personagem, mesadestino2);
                ColisaoObjeto(personagem, pcdestino);
                ColisaoObjeto(personagem, macadestino); 

                if (!puzzleResolvido && CheckCollisionRecs(*personagem, terminalComputador) && IsKeyPressed(KEY_E)) {
                     estadointerno = QUARTO_PUZZLE_PC;
                }

                if (CheckCollisionRecs(*personagem, portaSaida) && IsKeyPressed(KEY_E)) {
                    *TelaAtual = 1; 
                    personagem->x = 100; 
                }

                if (!inv->temCarta && CheckCollisionRecs(*personagem, pegarcarta) && IsKeyPressed(KEY_E)) {
                    inv->temCarta = true; 
                }

                if (inv->temCarta && IsKeyPressed(KEY_C)) {
                    lendoCarta = true;
                }
            } 
            else {
                if (IsKeyPressed(KEY_C)) {
                    lendoCarta = false;
                }
            }

            for (int y = 0; y <= 600; y += 32) {
                for (int x = 0; x <= 800; x += 32) {
                    Rectangle destino = {x, y, 32, 32};
                    DrawTexturePro(tileTexture, tileorigem, destino, (Vector2){0,0}, 0.0f, WHITE);
                }
            }


            DrawRectangleRec(paredeEsquerda, GRAY);
            DrawRectangleRec(paredeDireita, GRAY);
            DrawRectangleRec(paredeCima, GRAY);
            DrawRectangleRec(paredeBaixo, GRAY);
            DrawTexturePro(PortaTexture, portaorigem, portadestino, (Vector2){0,0}, 0.0f, WHITE);

            DrawTexturePro(mesa, mesaorigem, mesadestino, (Vector2){0,0}, 0.0f, WHITE);

            DrawTexturePro(mesa, mesaorigem, mesadestino2, (Vector2){0,0}, 0.0f, WHITE);


            if (!inv->temCarta) {
                DrawTexturePro(carta, cartaorigem, cartadestino, (Vector2){0,0}, 0.0f, RAYWHITE);
                
            }
            DrawTexturePro(pc,pcorigem,pcdestino,(Vector2){0,0}, 0.0f, RAYWHITE);

            DrawTexturePro(maca, macaorigem, macadestino, (Vector2){0,0}, 0.0f, RAYWHITE);


            DrawTexturePro(BobTexture, *frameatual, *personagem, (Vector2){0,0}, 0.0f, WHITE);

            if (!lendoCarta) {
                if (!puzzleResolvido && CheckCollisionRecs(*personagem, terminalComputador)) {
                    DrawText("Pressione E para interagir com o PC", pcdestino.x - 40, pcdestino.y - 30, 16, YELLOW);
                }
                
                if (!inv->temCarta && CheckCollisionRecs(*personagem, pegarcarta)) {
                    DrawText("Pressione E para pegar a carta", mesadestino.x - 30, mesadestino.y - 30, 16, YELLOW);
                }
            }
            break;

        case QUARTO_PUZZLE_PC:

            int caractere = GetCharPressed();
            while (caractere > 0) {
                if ((caractere >= '0' && caractere <= '9') && (contagemLetras < 5)) {
                    textoDigitado[contagemLetras] = (char)caractere;
                    contagemLetras++;
                    textoDigitado[contagemLetras] = '\0'; 
                    erroAtivo = false;
                }
                caractere = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                contagemLetras--;
                if (contagemLetras < 0) contagemLetras = 0;
                textoDigitado[contagemLetras] = '\0'; 
                erroAtivo = false;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (TextIsEqual(textoDigitado, "21")) {
                    puzzleResolvido = true; 
                    estadointerno = QUARTO_EXPLORANDO;
                    textoDigitado[0] = '\0';
                    contagemLetras = 0;
                    erroAtivo = false;
                    inv->temChave = true;
                } else {
                    erroAtivo = true;
                }
            }

            DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.8f));
            DrawRectangleLinesEx((Rectangle){0,0,800,450}, 50, GOLD); 

            DrawText("CAPS System", 120, 100, 40, GREEN);
            DrawText("INSIRA O PROXIMO NUMERO DA SEQUENCIA:", 120, 150, 18, GREEN);
            DrawText("0, 1, 1, 2, 3, 5, 8, 13, ...", 120, 180, 18, GREEN);

            DrawText("RESPOSTA: ", 120, 250, 20, GREEN);
            DrawText(textoDigitado, 240, 250, 20, GREEN);

            if ((int)(GetTime() * 2) % 2 == 0) {
                DrawText("_", 240 + (contagemLetras * 12), 250, 20, GREEN);
            }

            if (erroAtivo) {
                DrawText(">>> ERRO: SEQUENCIA INCORRETA. ACESSO NEGADO. <<<", 120, 310, 16, RED);
            }

            DrawText("[Pressione ENTER para enviar | Q para sair]", 120, 380, 14, DARKGREEN);
            break;
    }
}