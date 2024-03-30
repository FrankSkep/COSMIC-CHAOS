#ifndef GAME_H
#define GAME_H

#include "elements.h"
#include <string.h>

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* MENUs */
void drawMainMenu(Texture2D *background);
void drawHowToPlay();
void aboutTheGame();
void logicaMenu(int *seconds, bool *isPlaying);

/* INTERFACES */
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, short *lives, short *score, short *level, float *rotation);
void gameOverInterface(Texture2D *background, short *score, short *level);

/* DIBUJO OBJETOS */
void drawMeteors(float *rotation);
void drawObjects(Texture2D *coinsTx, Texture2D *heartsTx);
void DrawShots();
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

/* LOGICA */
void InitObject(GameObject *object, float *objRadius);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius);

void Levels(Texture2D *cinema, short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives);
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, Texture2D *texturas, int frame1, int frame2);
void screenlevel(const char *text, int seconds);

void resetItems(Vector2 *playPosition);
void resetStats(short *lives, short *score, short *level, float *timeSeconds);

/************** DESARROLLO DE FUNCIONES **************/

// Dibuja menu principal
void drawMainMenu(Texture2D *background) // PANTALLA DE MENU
{
    BeginDrawing();

    // Fondo
    DrawTexture(*background, 0, 0, WHITE);

    // Titulo
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 150, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 145, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 140, 180, BLUE);

    // Acciones
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

// Dibuja pantalla de como jugar
void drawHowToPlay()
{
    while (!IsKeyPressed(KEY_Q))
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

// Dibuja pantalla con informacion acerca del juego
void aboutTheGame()
{
    while (!IsKeyPressed(KEY_Q)) // Bucle para mostrar la interfaz "about"
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

// Maneja acciones del menu principal
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

// Dibuja la interfaz de partida en curso
void gameInterface(Texture2D *gamebg, Texture2D *ship, Vector2 *shipPosicion, Texture2D *coins, Texture2D *hearts, short *lives, short *score, short *level, float *rotation)
{
    // Dibuja fondo
    DrawTexture(*gamebg, 0, 0, WHITE);

    // Dibuja puntaje
    DrawText(TextFormat("SCORE : %04i", *score), SCR_WIDTH - 363, 20, 50, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("LEVEL : %i", *level), SCR_WIDTH - 1560, 20, 50, WHITE);

    // Dibuja jugador (nave)
    DrawTextureV(*ship, *shipPosicion, WHITE);

    // Dibuja los elementos moviles del juego
    drawMeteors(rotation);
    drawObjects(coins, hearts);
    DrawShots();

    // Dibuja vidas restantes
    DrawText(TextFormat("LIVES : %d", *lives), SCR_WIDTH - 280, SCR_HEIGHT - 130, 50, WHITE);
    for (int i = 0; i < *lives; i++)
    {
        DrawTexture(*hearts, SCR_WIDTH - 330 + (i * 65), SCR_HEIGHT - 65, RED);
    }
    for (int i = *lives; i < 5; i++)
    {
        DrawText(" - ", SCR_WIDTH - 330 + (i * 65), SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }
}

// Dibuja la interfaz de derrota
void gameOverInterface(Texture2D *background, short *score, short *level)
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

// Dibuja meteoros
void drawMeteors(float *rotation)
{
    for (int i = 0; i < MAX_GRAY; i++)
    {
        if (grayMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, GRAY);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(grayMeteors[i].position, 5, GRAY_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
    for (int i = 0; i < MAX_BROWN_METEORS; i++)
    {
        if (brownMeteors[i].active)
        {
            // Dibujar el cuerpo principal del meteoro (polígono relleno)
            DrawPoly(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, BROWN);

            // Dibujar líneas adicionales para dar textura
            DrawPolyLinesEx(brownMeteors[i].position, 5, BROWN_METEOR_RADIUS, *rotation, 8, DARKGRAY);
        }
    }
}

// Dibujar monedas y corazones
void drawObjects(Texture2D *coinsTx, Texture2D *heartsTx)
{
    Vector2 coinCenter;
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coins[i].active)
        {
            // Calcular la posición del centro de la moneda
            coinCenter = {coins[i].position.x - coinsTx->width / 2, coins[i].position.y - coinsTx->height / 2};
            DrawTextureV(*coinsTx, coinCenter, WHITE);
        }
    }
    Vector2 heartCenter;
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        if (hearts[i].active)
        {
            // Calcular la posición del centro de la moneda
            heartCenter = {(float)((int)hearts[i].position.x - heartsTx->width / 2), (float)((int)hearts[i].position.y - heartsTx->height / 2)};
            DrawTextureV(*heartsTx, heartCenter, RED);
        }
    }
}

// Dibujar disparos
void DrawShots()
{
    for (int i = 0; i < MAX_SHOTS; i++)
    {
        if (shots[i].active)
        {
            DrawCircleV(shots[i].position, SHOT_RADIUS, RAYWHITE);
        }
    }
}

// Imprimir texto centrado
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2 + posX, posY, fontSize, color);
}

// Inicializar cualquier objeto
void InitObject(GameObject *object, const float *objRadius)
{
    object->position.x = GetRandomValue(0, SCR_WIDTH);
    object->position.y = -*objRadius * 2;
    object->active = true;
}

// Colisiones
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius)
{
    float dx = ballPos.x - playerPos.x;
    float dy = ballPos.y - playerPos.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSumSquared = (playerRadius + meteorRadius) * (playerRadius + meteorRadius);
    return distanceSquared < radiusSumSquared;
}

// Manejo de niveles
void Levels(Texture2D *cinema, short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives)
{
    if (*score == 0 && *level == 0)
    {
        // Historia inicial
        subsCinematicas("   INFORME DE ULTIMO MOMENTO                        Hola a todos son las 11:45 am y aqui su servilleta     Javie Alatorre informandolos.", 45, 7, 2, cinema, 4, 5);
        subsCinematicas("Desde la NASA nos llega el informe de que se acaba  de descubrir un asteroide con un color amarillo el    cual tiene a los cientificos conmosionados ", 45, 7, 4, cinema, 0, 1);
        subsCinematicas("Se rumora que podria contener gran cantidad de oro en su interior y en este momento organizaciones de   todo el mundo estan investigando este suceso ", 45, 7, 4, cinema, 0, 1);
        subsCinematicas("  Un momento!  Nos informan que el asteroide acaba   de colisionar contra el cinturon de asteroides", 45, 7, 3, cinema, 2, 3);
        subsCinematicas("y efectivamene, contiene gran cantidad de oro, esto deja a las organzaciones en una carrera para ver    quien sera el que se apropie de el ", 45, 7, 4, cinema, 2, 3);
        subsCinematicas("Olvidenlo, nos informan que españa es el primer      aventado en ir por el, como dicta la historia oro del que lo tenga oro se lo queda ", 45, 7, 4, cinema, 6, 7);
        subsCinematicas("nuestros desarolladores han creado una represent- acion grafica de que es lo que podria estar pasando en este momento aya arriba en el espacio ", 45, 7, 1, cinema, 4, 5);

        /* Estadisticas Nivel 1 */
        *level = 1;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        MAX_GRAY = MAX_METEOR_LV1;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
    }

    if (*score >= 30 && *level == 1)
    {
        // Limpiar objetos
        resetItems(playPosition);

        subsCinematicas("aqui iria la cinematica de descanso", 45, 7, 1, cinema, 0, 1);
        subsCinematicas("continuacion de historia", 45, 7, 2, cinema, 0, 1);

        screenlevel("NIVEL 2", 2);

        /* Estadisticas Nivel 2 */
        *level = 2;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        MAX_GRAY = MAX_METEOR_LV2;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
    }
    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 30 && *level == 2)
    {
        // Limpiar objetos
        resetItems(playPosition);

        screenlevel("NIVEL 3", 2);

        /* Estadisticas Nivel 3 */
        *level = 3;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        MAX_GRAY = MAX_METEOR_LV3;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
    }
}

// Maximo 160 caracteres - tamaño - frecuencia - tiempo - textura - frame1 y frame2
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, Texture2D *texturas, int frame1, int frame2)
{
    int longitud = strlen(text);
    int i, limiteH = 45, acumulador = 0;
    bool cambio = true;
    float x, y;

    for (i = 0; i < longitud; i++)
    {
        if (acumulador >= frecuencia)
        {
            cambio = !cambio;
            acumulador = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Mensaje para saltar cinematica
        DrawText("(S) SKIP", SCR_WIDTH - (250), SCR_HEIGHT - 70, 50, WHITE);
        if (IsKeyPressed(KEY_S))
            return; // Saltar cinematica

        if (cambio)
        {
            DrawTexture(texturas[frame1], 288, 0, WHITE);
        }
        else
        {
            DrawTexture(texturas[frame2], 288, 0, WHITE);
        }

        x = limiteH;
        y = (SCR_HEIGHT / 2) * 1.6;

        for (int j = 0; j <= i; j++)
        {
            if (x + MeasureText(TextFormat("%c", text[j]), tamano) > SCR_WIDTH - limiteH)
            {
                x = limiteH;
                y += tamano + 5;
            }
            DrawText(TextFormat("%c", text[j]), x + 6, y + 6, tamano, BLACK);
            DrawText(TextFormat("%c", text[j]), x, y, tamano, YELLOW);

            x += MeasureText(TextFormat("%c", text[j]), tamano) + 10;
        }
        EndDrawing();

        acumulador++;
    }

    double startTime2 = GetTime(); // Obtener el tiempo de inicio

    while (GetTime() - startTime2 < seconds) // Pausa entre cada texto
        ;
}

// Mostrar pantalla de nivel
void screenlevel(const char *text, int seconds)
{
    int tamano = 200;
    double startTime2 = GetTime(); // Obtener el tiempo de inicio

    while (GetTime() - startTime2 < seconds)
    {
        // Limpiar la pantalla y mostrar "Nivel #" en el centro
        ClearBackground(BLACK);
        DrawText(text, SCR_WIDTH / 2 - MeasureText(text, tamano) / 2, (SCR_HEIGHT / 2) - 100, tamano, WHITE);
        EndDrawing();
    }
}

// Reiniciar posicion de elementos jugador
void resetItems(Vector2 *playPosition)
{
    // Reiniciar posicion nave
    *playPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};
    short i;
    // Limpiar meteoros
    for (i = 0; i < MAX_GRAY; i++)
    {
        grayMeteors[i].active = false;
    }
    for (i = 0; i < MAX_BROWN_METEORS; i++)
    {
        brownMeteors[i].active = false;
    }
    for (i = 0; i < MAX_COINS; i++)
    {
        coins[i].active = false;
    }
    for (i = 0; i < MAX_HEARTS; i++)
    {
        hearts[i].active = false;
    }
    for (i = 0; i < MAX_SHOTS; i++)
    {
        shots[i].active = false;
    }
}

// Reinicia estadisticas
void resetStats(short *lives, short *score, short *level, float *timeSeconds)
{
    *lives = 5;
    *score = 0;
    *level = 1;
    *timeSeconds = 0;
    MAX_GRAY = MAX_METEOR_LV1;
}

#endif