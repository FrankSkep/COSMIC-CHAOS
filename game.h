#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <math.h>

/******** DIMENSIONES PANTALLA *********/
#define screenWidth 1600 // ALTO  (X)
#define screenHeight 900 // ANCHO (Y)

/******** CONSTANTES *********/
#define MAX_GREEN_BALLS 30    // Maximo de bolas verde
#define GREEN_BALL_RADIUS 70  // Tamaño
#define GREEN_BALL_SPEED 7.0f // Velocidad de caida

#define MAX_BROWN_BALLS 10    // Maximo de bolas cafe
#define BROWN_BALL_RADIUS 40  // Tamaño
#define BROWN_BALL_SPEED 9.0f // Velocidad de caida

#define MAX_YELLOW_BALLS 2     // Maximo de bolas amarilla
#define YELLOW_BALL_RADIUS 20  // Tamaño
#define YELLOW_BALL_SPEED 8.0f // Velocidad de caida

#define MAX_RED_BALLS 1     // Maximo bolas rojas
#define RED_BALL_RADIUS 20  // Tamaño
#define RED_BALL_SPEED 9.0f // Velocidad de caida

/******** STRUCT *********/
typedef struct
{
    Vector2 position;
    bool active;
} Ball;

/******** INSTANCIAS NECESARIAS DE STRUCT 'Ball' *********/
Ball greenBalls[MAX_GREEN_BALLS];
Ball brownBalls[MAX_BROWN_BALLS];
Ball yellowBalls[MAX_YELLOW_BALLS];
Ball RedBalls[MAX_RED_BALLS];

Vector2 playPosition = {(float)screenWidth / 2, (float)screenHeight / 1.1f};

/******** PROTOTIPOS DE FUNCIONES *********/
void Tutorial();
void drawMainMenu(Texture2D background);
void InitGreenBall(Ball *ball);
void InitBrownBall(Ball *ball);
void InitYellowBall(Ball *ball);
void InitRedBall(Ball *ball);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius);
void dibujarVerde(float rotation);
void dibujarCafe(float rotation);
void dibujarAmarillo();
void dibujarRojo();
void vidas(int lives);
void gameOverInterface(Texture2D background, int score);

/******** DESARROLLO DE FUNCIONES *********/
void Tutorial()
{
    BeginDrawing();
    DrawText("COMO SE JUEGA:", screenWidth / 2 - MeasureText("COMO SE JUEGA", 100) / 2, 100, 100, DARKBLUE);
    DrawText("- MUEVETE CON LAS FLECHAS   <-  ->", 40, screenHeight / 2 + 40, 50, WHITE);
    DrawText("- EVITA COLISIONAR CON LOS ASTEROIDES", 40, screenHeight / 2 + 110, 50, GRAY);
    DrawText("- RECOLECTA PUNTOS ", 40, screenHeight / 2 + 180, 50, YELLOW);
    DrawText("- SOBREVIVE RECOLECTANTO VIDAS ⏎", 40, screenHeight / 2 + 250, 50, RED);
    EndDrawing();
}

void drawMainMenu(Texture2D background) // PANTALLA DE MENU
{
    BeginDrawing();

    DrawTexture(background, 0, 0, WHITE);

    DrawText("COSMIC-CHAOS", screenWidth / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 200, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", screenWidth / 2+6 - MeasureText("COSMIC-CHAOS", 180) / 2+3, 195, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", screenWidth / 2+12 - MeasureText("COSMIC-CHAOS", 180) / 2+6, 190, 180, BLUE);


    int sizeStartTxt = MeasureText("(Enter) Start", 60);
    int sizeExitText = MeasureText("(ESC) Exit", 60);
    DrawText("(Enter) Start", screenWidth / 2 +2 - sizeStartTxt / 2+2, screenHeight / 2 + 82, 60, GREEN);
    DrawText("(Enter) Start", screenWidth / 2 - sizeStartTxt / 2, screenHeight / 2 + 80, 60, LIME);
    DrawText("(ESC) Exit", screenWidth / 2 +2- sizeExitText / 2+2, screenHeight / 2 + 152, 60, WHITE);
    DrawText("(ESC) Exit", screenWidth / 2 - sizeExitText / 2, screenHeight / 2 + 150, 60, YELLOW);
    EndDrawing();
}

void InitGreenBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -GREEN_BALL_RADIUS * 2;
    ball->active = true;
}
void InitBrownBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -BROWN_BALL_RADIUS * 2;
    ball->active = true;
}

void InitYellowBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -YELLOW_BALL_RADIUS * 2;
    ball->active = true;
}

void InitRedBall(Ball *ball)
{
    ball->position.x = GetRandomValue(0, GetScreenWidth());
    ball->position.y = -RED_BALL_RADIUS * 2;
    ball->active = true;
}

bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float playRadius)
{
    float distance = sqrt(pow(ballPos.x - playerPos.x, 2) + pow(ballPos.y - playerPos.y, 2));
    return (distance < (playerRadius + playRadius));
}

void dibujarVerde(float rotation) // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv// 21/03  10:03 pm
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_GREEN_BALLS; i++)
    {
        if (greenBalls[i].active)
        {
            DrawPoly(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, GRAY);
            DrawPolyLines(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, DARKGRAY);
            DrawPolyLinesEx(greenBalls[i].position, 5, GREEN_BALL_RADIUS, rotation, 5, DARKGRAY);
        }
    }
}

void dibujarCafe(float rotation)
{
    // Velocidad de rotacion
    rotation += 2.5f;
    // Dibujar esferas verdes
    for (int i = 0; i < MAX_BROWN_BALLS / 2; i++)
    {
        if (brownBalls[i].active)
        {
            DrawPoly(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, BROWN);
            DrawPolyLines(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, DARKBROWN);
            DrawPolyLinesEx(brownBalls[i].position, 5, BROWN_BALL_RADIUS, rotation, 5, DARKGRAY);
        }
    }
}
void dibujarAmarillo()
{
    // Dibujar esferas amarillas
    for (int i = 0; i < MAX_YELLOW_BALLS; i++)
    {
        if (yellowBalls[i].active)
        {
            DrawCircleV(yellowBalls[i].position, YELLOW_BALL_RADIUS, YELLOW);
        }
    }
}
void dibujarRojo()
{
    // Dibujar esferas Rojas
    for (int i = 0; i < MAX_RED_BALLS; i++)
    {
        if (RedBalls[i].active)
        {
            DrawCircleV(RedBalls[i].position, RED_BALL_RADIUS, RED);
        }
    }
} //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  21/03  10:03 pm

void vidas(int lives)
{
    DrawText(TextFormat("Vidas: %d", lives), screenWidth - 250, screenHeight - 140, 50, WHITE);
    for (int i = 0; i < lives; i++)
    {
        DrawText("<3 ", screenWidth - 350 + (i * 60), screenHeight - 60, 50, RED); // Corazón lleno
    }
    for (int i = lives; i < 5; i++)
    {
        DrawText(" - ", screenWidth - 350 + (i * 60), screenHeight - 60, 50, RED); // Corazón vacío
    }                         //  Horizontal, Espaciado,         Altura, Tamaño
}
void gameOverInterface(Texture2D background, int score)
{
    // Fondo gameover
    DrawTexture(background, 0, 0, WHITE);

    int width = screenWidth;
    int height = screenHeight;
    // Dibujar ventana de "Game Over"
    DrawText("GAME OVER", width / 2 +2 - MeasureText("GAME OVER", 130) / 2+2, height / 2 - 218, 130, WHITE);
    DrawText("GAME OVER", width / 2 - MeasureText("GAME OVER", 130) / 2, height / 2 - 220, 130, RED);
    DrawText(TextFormat("Score: %04i", score), width / 2 - MeasureText(TextFormat("Score: %04i", score), 70) / 2, height / 2 - 50, 70, RAYWHITE);
    DrawText("(ENTER) Play Again", width / 2+2 - MeasureText("(ENTER) Play Again", 70) / 2+2, height / 2 + 130+2, 70, LIME);
    DrawText("(ENTER) Play Again", width / 2 - MeasureText("(ENTER) Play Again", 70) / 2, height / 2 + 130, 70, GREEN);
    DrawText("(Q) Back to menu", width / 2+2 - MeasureText("(Q) Back to menu", 70) / 2+2, height / 2 + 200+2, 70, WHITE);
    DrawText("(Q) Back to menu", width / 2 - MeasureText("(Q) Back to menu", 70) / 2, height / 2 + 200, 70, MAGENTA);
    DrawText("(Esc) Exit.", width / 2+2 - MeasureText("(Q) Exit", 90) / 2+2, height / 2 + 270+2, 70, WHITE);
    DrawText("(Esc) Exit.", width / 2 - MeasureText("(Q) Exit", 90) / 2, height / 2 + 270, 70, RED);
}

#endif