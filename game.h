#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>
#include <time.h>

/******** DIMENSIONES PANTALLA *********/
#define SCR_WIDTH 1600 // ALTO  (X)
#define SCR_HEIGHT 900 // ANCHO (Y)

/******** CONSTANTES *********/
#define MAX_GRAY_METEORS 30    // Maximo de bolas verde
#define GRAY_METEOR_RADIUS 70  // Tamaño
#define GRAY_METEOR_SPEED 7.0f // Velocidad de caida

#define MAX_BROWN_METEORS 10    // Maximo de bolas cafe
#define BROWN_METEOR_RADIUS 40  // Tamaño
#define BROWN_METEOR_SPEED 9.0f // Velocidad de caida

#define MAX_COINS 2      // Maximo de bolas amarilla
#define COINS_RADIUS 20  // Tamaño
#define COINS_SPEED 8.0f // Velocidad de caida

#define MAX_HEARTS 1      // Maximo bolas rojas
#define HEARTS_RADIUS 20  // Tamaño
#define HEARTS_SPEED 9.0f // Velocidad de caida

/******** STRUCT *********/
typedef struct
{
    Vector2 position;
    bool active;
} Ball;

/******** INSTANCIAS NECESARIAS DE STRUCT 'Ball' *********/
Ball grayMeteors[MAX_GRAY_METEORS];
Ball brownMeteors[MAX_BROWN_METEORS];
Ball coins[MAX_COINS];
Ball hearts[MAX_HEARTS];

/******** PROTOTIPOS DE FUNCIONES *********/
void Tutorial();
void drawMainMenu(Texture2D background);
void gameInterface(Texture2D gamebg, Texture2D ship, Vector2 shipPosicion, int lives, int score, float rotation, Texture2D coins, Vector2 coinPosition);
void Levels(int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *milliseconds);
void resetGame(Vector2 *playPosition);
void InitGrayMeteor(Ball *ball);
void InitBrownMeteor(Ball *ball);
void InitCoin(Ball *ball);
void InitHearts(Ball *ball);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius);
void drawGrayMeteor(float rotation);
void drawBrownMeteor(float rotation);
void drawCoins(Texture2D coinsTx, Vector2 coinPosition);
void drawHearts();
void vidas(int lives);
void gameOverInterface(Texture2D background, int score);

/******** DESARROLLO DE FUNCIONES *********/
void Tutorial()
{
    BeginDrawing();
    DrawRectangleGradientV(0, 0, SCR_WIDTH, SCR_HEIGHT, PURPLE, DARKPURPLE);
    DrawText("COMO SE JUEGA:", SCR_WIDTH / 2 - MeasureText("COMO SE JUEGA", 100) / 2, 100, 100, BLUE);
    DrawText("- MUEVETE CON LAS FLECHAS   <-  ->", 40, SCR_HEIGHT / 2 + 40, 50, WHITE);
    DrawText("- EVITA COLISIONAR CON LOS ASTEROIDES", 40, SCR_HEIGHT / 2 + 110, 50, GRAY);
    DrawText("- RECOLECTA PUNTOS ", 40, SCR_HEIGHT / 2 + 180, 50, YELLOW);
    DrawText("- SOBREVIVE RECOLECTANTO VIDAS ⏎", 40, SCR_HEIGHT / 2 + 250, 50, RED);
    DrawText("(Q) Exit tutorial", SCR_WIDTH / 2 - MeasureText("(Q) Exit tutorial", 50) / 2, SCR_HEIGHT / 2 + 350, 50, GREEN);
    EndDrawing();
}

void drawMainMenu(Texture2D background) // PANTALLA DE MENU
{
    BeginDrawing();

    DrawTexture(background, 0, 0, WHITE);

    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 200, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 195, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 190, 180, BLUE);

    int sizeStartTxt = MeasureText("(Enter) Start", 60);
    int sizeTuto = MeasureText("(A) Como jugar", 60);
    int sizeExitText = MeasureText("(ESC) Exit", 60);
    DrawText("(Enter) Start", SCR_WIDTH / 2 + 2 - sizeStartTxt / 2 + 2, SCR_HEIGHT / 2 + 82, 60, GREEN);
    DrawText("(Enter) Start", SCR_WIDTH / 2 - sizeStartTxt / 2, SCR_HEIGHT / 2 + 80, 60, LIME);

    DrawText("(A) Como jugar", SCR_WIDTH / 2 + 2 - sizeTuto / 2 + 2, SCR_HEIGHT / 2 + 152, 60, DARKPURPLE);
    DrawText("(A) Como jugar", SCR_WIDTH / 2 - sizeTuto / 2, SCR_HEIGHT / 2 + 150, 60, PURPLE);

    DrawText("(ESC) Exit", SCR_WIDTH / 2 + 2 - sizeExitText / 2 + 2, SCR_HEIGHT / 2 + 224, 60, WHITE);
    DrawText("(ESC) Exit", SCR_WIDTH / 2 - sizeExitText / 2, SCR_HEIGHT / 2 + 222, 60, YELLOW);

    EndDrawing();
}

void gameInterface(Texture2D gamebg, Texture2D ship, Vector2 shipPosicion, int lives, int score, float rotation, Texture2D coins, Vector2 coinPosition)
{
    // Dibujar fondo
    DrawTexture(gamebg, 0, 0, WHITE);

    // Dibujar vidas
    vidas(lives);

    // Dibujar puntaje
    DrawText(TextFormat("SCORE: %04i", score), SCR_WIDTH - 400, 20, 50, WHITE);

    // Dibujar jugador (nave)
    DrawTextureV(ship, shipPosicion, WHITE);

    // Dibujar los objetos
    drawGrayMeteor(rotation);
    drawBrownMeteor(rotation);
    drawCoins(coins, coinPosition);
    drawHearts();
}

void Levels(int *score, int *level, float *elapsedTime, Vector2 *playPosition, int *milliseconds, int *lives)
{
    if (*score >= 30 && *level == 1)
    {
        *level = 2;
        double startTime = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime < *milliseconds / 1000.0)
        {
            // Limpiar la pantalla y mostrar "Nivel 2" en el centro
            ClearBackground(BLACK);
            DrawText("Nivel 2", SCR_WIDTH / 2 - MeasureText("Nivel 2", 200) / 2, SCR_HEIGHT / 2 - 200, 200, WHITE);
            // Actualizar la pantalla
            ClearBackground(BLACK);

            EndDrawing();
        }

        *elapsedTime = 0.0f;
        *score = 0;
        *lives = 5;
        // Limpiar todas las esferas en la pantalla
        resetGame(playPosition);
    }

    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 20 && *level == 2)
    {
        *level = 3;
        double startTime = GetTime(); // Obtener el tiempo de inicio

        while (GetTime() - startTime < *milliseconds / 1000.0)
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
        resetGame(playPosition);
    }
}

// Función para limpiar todas las esferas en la pantalla
void resetGame(Vector2 *playPosition)
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

void InitGrayMeteor(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -GRAY_METEOR_RADIUS * 2;
    ball->active = true;
}
void InitBrownMeteor(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -BROWN_METEOR_RADIUS * 2;
    ball->active = true;
}

void InitCoin(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -COINS_RADIUS * 2;
    ball->active = true;
}

void InitHearts(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -HEARTS_RADIUS * 2;
    ball->active = true;
}

bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius)
{
    float distance = sqrt(pow(ballPos.x - playerPos.x, 2) + pow(ballPos.y - playerPos.y, 2));
    return (distance < (playerRadius + playRadius));
}

void drawGrayMeteor(float rotation)
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_GRAY_METEORS; i++)
    {
        if (grayMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, rotation, GRAY);

            // Dibujar líneas para resaltar bordes del meteoro
            DrawPolyLines(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, rotation, BLACK);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, rotation, 8, DARKGRAY);

            // Dibujar puntos aleatorios dentro del meteoro para textura
            for (int j = 0; j < 15; j++)
            {
                Vector2 point = {
                    grayMeteors[i].position.x + GetRandomValue(-GRAY_METEOR_RADIUS / 2, GRAY_METEOR_RADIUS / 2),
                    grayMeteors[i].position.y + GetRandomValue(-GRAY_METEOR_RADIUS / 2, GRAY_METEOR_RADIUS / 2)};
                DrawCircleV(point, 3, BLACK);
            }
        }
    }
}

void drawBrownMeteor(float rotation)
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_BROWN_METEORS / 2; i++)
    {
        if (brownMeteors[i].active)
        {
            DrawPoly(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, rotation, BROWN);
            DrawPolyLines(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, rotation, DARKBROWN);
            DrawPolyLinesEx(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, rotation, 8, DARKGRAY);
        }
    }
}



void drawCoins(Texture2D coinsTx, Vector2 coinPosition)
{
    // Dibujar esferas amarillas
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].active)
        {
            DrawTextureV(coinsTx, coinPosition, WHITE);
        }
    }
}
void drawHearts()
{
    // Dibujar esferas Rojas
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        if (hearts[i].active)
        {
            DrawCircleV(hearts[i].position, HEARTS_RADIUS, RED);
        }
    }
} //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  21/03  10:03 pm

void vidas(int lives)
{
    DrawText(TextFormat("Vidas: %d", lives), SCR_WIDTH - 250, SCR_HEIGHT - 140, 50, WHITE);
    for (int i = 0; i < lives; i++)
    {
        DrawText("<3 ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón lleno
    }
    for (int i = lives; i < 5; i++)
    {
        DrawText(" - ", SCR_WIDTH - 350 + (i * 60), SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }                                                                          //  Horizontal, Espaciado,         Altura, Tamaño
}
void gameOverInterface(Texture2D background, int score)
{
    // Fondo gameover
    DrawTexture(background, 0, 0, WHITE);

    int width = SCR_WIDTH;
    int height = SCR_HEIGHT;
    // Dibujar ventana de "Game Over"
    DrawText("GAME OVER", width / 2 + 2 - MeasureText("GAME OVER", 130) / 2 + 2, height / 2 - 218, 130, WHITE);
    DrawText("GAME OVER", width / 2 - MeasureText("GAME OVER", 130) / 2, height / 2 - 220, 130, RED);
    DrawText(TextFormat("Score: %04i", score), width / 2 - MeasureText(TextFormat("Score: %04i", score), 70) / 2, height / 2 - 50, 70, RAYWHITE);
    DrawText("(ENTER) Play Again", width / 2 + 2 - MeasureText("(ENTER) Play Again", 70) / 2 + 2, height / 2 + 130 + 2, 70, LIME);
    DrawText("(ENTER) Play Again", width / 2 - MeasureText("(ENTER) Play Again", 70) / 2, height / 2 + 130, 70, GREEN);
    DrawText("(Q) Back to menu", width / 2 + 2 - MeasureText("(Q) Back to menu", 70) / 2 + 2, height / 2 + 200 + 2, 70, WHITE);
    DrawText("(Q) Back to menu", width / 2 - MeasureText("(Q) Back to menu", 70) / 2, height / 2 + 200, 70, MAGENTA);
    DrawText("(Esc) Exit.", width / 2 + 2 - MeasureText("(Q) Exit", 90) / 2 + 2, height / 2 + 270 + 2, 70, WHITE);
    DrawText("(Esc) Exit.", width / 2 - MeasureText("(Q) Exit", 90) / 2, height / 2 + 270, 70, RED);
}

#endif