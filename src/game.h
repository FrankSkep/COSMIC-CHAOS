#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>
#include <string.h>

/******** DIMENSIONES PANTALLA *********/
#define SCR_WIDTH 1600 // ALTO  (X)
#define SCR_HEIGHT 900 // ANCHO (Y)

/******** CONSTANTES *********/
// Meteoros
#define MAX_GRAY_METEORS 30     // Maximo de bolas verde
#define GRAY_METEOR_RADIUS 70   // Tamaño
#define GRAY_METEOR_SPEED 7.0f  // Velocidad de caida
#define MAX_BROWN_METEORS 10    // Maximo de bolas cafe
#define BROWN_METEOR_RADIUS 40  // Tamaño
#define BROWN_METEOR_SPEED 9.0f // Velocidad de caida
// Monedas
#define MAX_COINS 2      // Maximo de bolas amarilla
#define COINS_RADIUS 20  // Tamaño
#define COINS_SPEED 8.0f // Velocidad de caida
// Corazones
#define MAX_HEARTS 1      // Maximo bolas rojas
#define HEARTS_RADIUS 20  // Tamaño
#define HEARTS_SPEED 9.0f // Velocidad de caida

/***** STRUCT PARA METEOROS Y OBJETOS DEL JUEGO ******/
typedef struct
{
    Vector2 position;
    bool active;
} Ball;

/*----------- INSTANCIAS NECESARIAS DE STRUCT 'Ball' -----------*/
Ball grayMeteors[MAX_GRAY_METEORS];
Ball brownMeteors[MAX_BROWN_METEORS];
Ball coins[MAX_COINS];
Ball hearts[MAX_HEARTS];

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/

/* MENUS DEL JUEGO */
void drawMainMenu(Texture2D background);
void drawHowToPlay();
void aboutTheGame();
void gameOverInterface(Texture2D *background, int *score, int *level);

/* LOGICA DEL JUEGO */
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, int *lives, int *score, float *rotation);
void logicaMenu(int *seconds, bool *isPlaying);
void vidas(int *lives);
void InitGrayMeteor(Ball *grayMeteor);
void InitBrownMeteor(Ball *brownMeteor);
void InitCoin(Ball *coin);
void InitHearts(Ball *heart);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius);
void Levels(int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *seconds, int *lives);
//void clock(int *totalseconds, int *minutesT, int *econdsT);
void resetItems(Vector2 *playPosition);
void resetStats(int *lives, int *score, int *level, double *timeSeconds);

/* DIBUJO */
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);
void drawGrayMeteor(float *rotation);
void drawBrownMeteor(float *rotation);
void drawCoins(Texture2D *coinsTx);
void drawHearts(Texture2D *heartsTx);

/************** DESARROLLO DE FUNCIONES **************/

void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2 + posX, posY, fontSize, color);
}

// Dibuja menu principal inicial
void drawMainMenu(Texture2D background) // PANTALLA DE MENU
{
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE); // Fondo

    // Titulo
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 150, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 145, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 140, 180, BLUE);

    // Subtitulos
    drawTextCenter("(ENTER) Start", 2, 502, 60, LIME);
    drawTextCenter("(ENTER) Start", 0, 500, 60, GREEN);

    drawTextCenter("(A) How to play", 2, 582, 60, DARKPURPLE);
    drawTextCenter("(A) How to play", 0, 580, 60, PURPLE);

    drawTextCenter("(E) About the game", 2, 662, 60, GRAY);
    drawTextCenter("(E) About the game", 0, 660, 60, YELLOW);

    drawTextCenter("(ESC) Exit", 2, 742, 60, DARKGRAY);
    drawTextCenter("(ESC) Exit", 0, 740, 60, RED);

    EndDrawing();
}

// Dibuja interfaz de como jugar
void drawHowToPlay()
{
    while (!WindowShouldClose() && !IsKeyPressed(KEY_Q))
    {
        BeginDrawing();
        ClearBackground(BLACK);

        drawTextCenter("HOW TO PLAY: ", 0, 100, 100, BLUE);
        DrawText("- MOVE WITH THE ARROUS <-  ->", 40, SCR_HEIGHT / 2 + 40, 50, WHITE);
        DrawText("- AVOID COLLIDING WITH ASTEROIDS", 40, SCR_HEIGHT / 2 + 110, 50, GRAY);
        DrawText("- COLLECT POINTS", 40, SCR_HEIGHT / 2 + 180, 50, YELLOW);
        DrawText("- SURVIVE BY COLLECTING LIVES", 40, SCR_HEIGHT / 2 + 250, 50, RED);
        DrawText("(Q) Back to menu", SCR_WIDTH / 2 - MeasureText("(Q) Back to menu", 50) / 2, SCR_HEIGHT / 2 + 350, 50, GREEN);

        EndDrawing();
    }
}

// Dibuja interfaz con informacion acerca del juego
void aboutTheGame()
{
    while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)) // Bucle para mostrar la interfaz "about"
    {
        BeginDrawing();

        ClearBackground(BLACK);

        drawTextCenter("About the game", 0, 100, 100, RED);
        drawTextCenter("Developers:", 0, 270, 50, YELLOW);
        drawTextCenter("- Francisco Cornejo", 0, 340, 50, GREEN);
        drawTextCenter("- Diego Ibarra", 0, 400, 50, GREEN);
        drawTextCenter("Sounds:", 0, 580, 50, GOLD);
        drawTextCenter("Unnamed", 0, 640, 50, LIME);
        drawTextCenter("(Q) Back to menu", 0, 800, 50, GOLD);

        EndDrawing();
    }
}

// Dibuja la interfaz de juego terminado
void gameOverInterface(Texture2D *background, int *score, int *level)
{
    // Fondo
    DrawTexture(*background, 0, 0, WHITE);

    // Dibujar ventana de "Game Over"
    drawTextCenter("GAME OVER", 2, 232, 130, WHITE);
    drawTextCenter("GAME OVER", 0, 230, 130, RED);

    DrawText(TextFormat("Score: %04i", *score), SCR_WIDTH / 2 - MeasureText(TextFormat("Score: %04i", *score), 70) / 2, SCR_HEIGHT / 2 + 10, 70, RAYWHITE);
    DrawText(TextFormat("Level: %1i", *level), SCR_WIDTH / 2 - MeasureText(TextFormat("LEVEL: %1i", *level), 70) / 2, SCR_HEIGHT / 2 - 50, 70, RAYWHITE);

    drawTextCenter("(ENTER) Play Again", 2, 582, 70, LIME);
    drawTextCenter("(ENTER) Play Again", 0, 580, 70, GREEN);

    drawTextCenter("(Q) Back to menu", 2, 662, 70, DARKPURPLE);
    drawTextCenter("(Q) Back to menu", 0, 660, 70, MAGENTA);

    drawTextCenter("(ESC) Exit", 2, 742, 70, RED);
    drawTextCenter("(ESC) Exit", 0, 740, 70, MAROON);
}

// Dibuja la interfaz de la partida
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, int *lives, int *score, float *rotation)
{
    // Dibujar fondo
    DrawTexture(*gamebg, 0, 0, WHITE);

    // Dibujar vidas
    vidas(lives);

    // Dibujar puntaje
    DrawText(TextFormat("SCORE: %04i", *score), SCR_WIDTH - 400, 20, 50, WHITE);

    // Dibujar jugador (nave)
    DrawTextureV(*ship, *shipPosicion, WHITE);

    // Dibujar los objetos
    drawGrayMeteor(rotation);
    drawBrownMeteor(rotation);
    drawCoins(coins);
    drawHearts(hearts);
}

void logicaMenu(int *seconds, bool *isPlaying)
{
    if (IsKeyPressed(KEY_ENTER)) // Iniciar partida
    {
        *seconds = 0;
        *isPlaying = true;
    }
    if (IsKeyPressed(KEY_A)) // Ir a tutorial como jugar
    {
        drawHowToPlay();
    }
    if (IsKeyPressed(KEY_E)) // Ir a acerca del juego
    {
        aboutTheGame();
    }
}

// Dibuja las vidas restantes
void vidas(int *lives)
{
    DrawText(TextFormat("Vidas: %d", *lives), SCR_WIDTH - 250, SCR_HEIGHT - 140, 50, WHITE);
    for (int i = 0; i < *lives; i++)
    {

        DrawText("<3 ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón lleno
    }
    for (int i = *lives; i < 5; i++)
    {
        DrawText(" - ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }                                                                          //  Horizontal, Espaciado,         Altura, Tamaño
}

// Inicializa los meteoros gris
void InitGrayMeteor(Ball *grayMeteor)
{
    grayMeteor->position.x = GetRandomValue(0, GetScreenWidth());
    grayMeteor->position.y = -GRAY_METEOR_RADIUS * 2;
    grayMeteor->active = true;
}

// Inicializa los meteoros cafe
void InitBrownMeteor(Ball *brownMeteor)
{
    brownMeteor->position.x = GetRandomValue(0, GetScreenWidth());
    brownMeteor->position.y = -BROWN_METEOR_RADIUS * 2;
    brownMeteor->active = true;
}

// Inicializa las monedas de puntos
void InitCoin(Ball *coin)
{
    coin->position.x = GetRandomValue(0, GetScreenWidth());
    coin->position.y = -COINS_RADIUS * 2;
    coin->active = true;
}

// Inicializa los corazones de vida adicional
void InitHearts(Ball *heart)
{
    heart->position.x = GetRandomValue(0, GetScreenWidth());
    heart->position.y = -HEARTS_RADIUS * 2;
    heart->active = true;
}

// Colisiones
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius)
{
    float distance = sqrt(pow(ballPos.x - playerPos.x, 2) + pow(ballPos.y - playerPos.y, 2));
    return (distance < (playerRadius + playRadius));
}

// Manejo de niveles
void Levels(int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *seconds, int *lives)
{
    if (*score >= 30 && *level == 1)
    {
        // Limpiar todas las esferas en la pantalla
        resetItems(playPosition);
        *level = 2;
        char str[] = "no te puedo regalar unas florees amarillas pero si te puedo dedicar un codigo ---- ya esto es aparte  mas texto aqui para ver sus limites mas y mas texto mas y mas ya fin  NOTA: CAMBIAR ESTO MEJOR A LA IZQUIERDA ";
        int tamano = 60;
        int longitud = strlen(str);
        int i;

        for (i = 0; i < longitud; i++)
        {
            double cinematica1 = GetTime(); // Obtener el tiempo de inicio

            while (GetTime() - cinematica1 < 0.05)
            {
                BeginDrawing();
                ClearBackground(BLACK);

                // Calcular el ancho total de todas las letras mostradas hasta ahora
                float totalWidth = 0.0f;
                int j;
                for (j = 0; j <= i; j++)
                {
                    totalWidth += MeasureText(TextFormat("%c", str[j]), tamano);
                }

                // Calcular la posición horizontal del texto para centrarlo
                float x = (SCR_WIDTH - totalWidth) / 2;
                float y = SCR_HEIGHT / 2 + 10; // Iniciar en la mitad vertical de la pantalla

                // Verificar si el texto se sale de la pantalla por la izquierda
                if (x < 50)
                {
                    // Si se sale, ajustar la posición horizontal para que sea 50
                    x = 50;
                }

                // Mostrar todas las letras hasta el índice actual
                for (j = 0; j <= i; j++)
                {
                    // Verificar si la posición horizontal excede el límite máximo de línea
                    if (x + MeasureText(TextFormat("%c", str[j]), tamano) > SCR_WIDTH)
                    {
                        // Si excede, mover a la siguiente línea
                        x = 50;  // Iniciar desde el borde izquierdo
                        y += 70; // Asumiendo una altura de línea de 40 píxeles
                    }

                    // Dibujar cada letra en la posición calculada
                    DrawText(TextFormat("%c", str[j]), x, y, tamano, RAYWHITE);
                    // Incrementar la posición horizontal para la próxima letra
                    x += MeasureText(TextFormat("%c", str[j]), tamano) + 10; // Agregar un margen de 10 píxeles entre letras
                }

                EndDrawing();
            }
        }

        // Esperar hasta que se presione la tecla Skip
        while (!IsKeyPressed(KEY_S))
        {
            // Limpiar la pantalla y mostrar "Presiona ESPACIO" en el centro
            DrawText("(S) SKIP", SCR_WIDTH - (100) - MeasureText("(S) SKIP", 50) - (100), SCR_HEIGHT - 50, 50, WHITE);
            // Actualizar la pantalla
            EndDrawing();
        }

        double startTime2 = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime2 < *seconds)
        {
            // Limpiar la pantalla y mostrar "Nivel 2" en el centro
            ClearBackground(BLACK);
            DrawText("NIVEL 2", SCR_WIDTH / 2 - MeasureText("NIVEL 2", 200) / 2, SCR_HEIGHT / 2 - 200, 200, WHITE);
            // Actualizar la pantalla

            EndDrawing();
        }
        ClearBackground(BLACK);
        *elapsedTime = 0.0f;
        *score = 0;
        *lives = 5;
    }

    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 20 && *level == 2)
    {
        *level = 3;
        double startTime = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime < *seconds)
        {
            // Limpiar la pantalla y mostrar "Nivel 2" en el centro
            ClearBackground(BLACK);
            DrawText("Nivel 3", SCR_WIDTH / 2 - MeasureText("Nivel 3", 200) / 2, SCR_HEIGHT / 2, 200, WHITE);
            // Actualizar la pantalla
            EndDrawing();
        }

        *elapsedTime = 0.0f;
        *score = 0;
        *lives = 5;
        // Limpiar todas las esferas en la pantalla
        resetItems(playPosition);
    }
}

// TIEMPO TRASCURRIDO
// void clock(int *totalseconds, int *minutesT, int *secondsT)
// {
//     double timeseconds = GetTime(); // Obtener el tiempo transcurrido en segundos
//     *totalseconds = (int)timeseconds;
//     *minutesT = *totalseconds / 60;
//     *secondsT = *totalseconds % 60;

//     // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
//     DrawText(TextFormat("%02d:%02d", *minutesT, *secondsT), 100, 100, 100, WHITE);
// }

// Limpiar elementos y posicion jugador
void resetItems(Vector2 *playPosition)
{
    // Reiniciar posicion nave
    *playPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};

    // Limpiar meteoros
    for (int i = 0; i < MAX_GRAY_METEORS; i++)
    {
        grayMeteors[i].active = false;
    }
    for (int i = 0; i < MAX_BROWN_METEORS; i++)
    {
        brownMeteors[i].active = false;
    }
    for (int i = 0; i < MAX_COINS; i++)
    {
        coins[i].active = false;
    }
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        hearts[i].active = false;
    }
}

void resetStats(int *lives, int *score, int *level, double *timeSeconds)
{
    // Reinicia vidas y puntaje
    *lives = 5;
    *score = 0;
    *level = 1;
    *timeSeconds = 0;
}

// Dibujar meteoros grises
void drawGrayMeteor(float *rotation)
{
    for (int i = 0; i < MAX_GRAY_METEORS; i++)
    {
        if (grayMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, GRAY);

            // Dibujar líneas para resaltar bordes del meteoro
            DrawPolyLines(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, BLACK);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
}

// Dibujar meteoros cafe
void drawBrownMeteor(float *rotation)
{
    for (int i = 0; i < MAX_BROWN_METEORS / 2; i++)
    {
        if (brownMeteors[i].active)
        {
            DrawPoly(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, BROWN);
            DrawPolyLines(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, DARKBROWN);
            DrawPolyLinesEx(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
}

// Dibujar esferas amarillas
void drawCoins(Texture2D *coinsTx)
{
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].active)
        {
            // Calcular la posición del centro de la moneda
            Vector2 coinCenter = {coins[i].position.x - coinsTx->width / 2, coins[i].position.y - coinsTx->height / 2};
            DrawTextureV(*coinsTx, coinCenter, WHITE);
        }
    }
}

// Dibujar esferas Rojas
void drawHearts(Texture2D *heartsTx)
{
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        if (hearts[i].active)
        {
            Vector2 heartCenter = {(float)((int)hearts[i].position.x - heartsTx->width / 2), (float)((int)hearts[i].position.y - heartsTx->height / 2)};
            DrawTextureV(*heartsTx, heartCenter, RED);
        }
    }
}

#endif