#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* LOGICA */
void InitObject(TGameObject *object, const float *objRadius);
bool CheckCollision(Vector2 *playerPos, float playerRadius, Vector2 *ballPos, float meteorRadius);

// Actualiza estados del juego
void updateGameState(GameState *gameState, int keyPressed, GameStats *stats);

// Niveles
void Levels(GameStats *stats, float *elapsedTime, Vector2 *playPosition, int *totalseconds);

// Reinicia juego
void resetItems(Vector2 *playPosition);
void objectfalse(TGameObject *object, int Max_object);
void resetStats(GameStats *stats);

// Espera un tiempo especifico
void secondspause(float seconds);
void screenMessage(const char *text, float seconds, Color colorbg);

// Recoge Datos jugador
void ingresarNickName(char inputText[]);
Tdata getDataPlayer();
void getDate(int *dia, int *mes, int *anio);

// Agrega al archivo los datos y estadisticas del jugador.
void appendScoresToFile(const char *filename, Tdata player);

// Logica de las preguntas presentadas
void mezclarArray(char array[][20], int size);
void selecNpreguntas();
int busqSecuencial(int vect[], int m, int num);

/*-------------------- DESARROLLO DE FUNCIONES --------------------*/
void updateGameState(GameState *gameState, int keyPressed, GameStats *stats)
{
    switch (*gameState)
    {
    case MAIN_MENU:
        switch (keyPressed)
        {
        case KEY_ENTER:
            *gameState = IN_GAME;
            break;

        case KEY_A:
            *gameState = HOW_TO_PLAY;
            break;

        case KEY_E:
            aboutBg = LoadTexture("resources/images/backgrounds/cinema9.png");
            *gameState = ABOUT_GAME;
            break;

        case KEY_H:
            scoreboardTx = LoadTexture("resources/images/backgrounds/scorebg.png");
            *gameState = HISTORY_SCORE;
            break;
        }
        break;

    case HOW_TO_PLAY:
    case ABOUT_GAME:
    case HISTORY_SCORE:
        if (keyPressed == KEY_Q)
        {
            UnloadTexture(scoreboardTx);
            UnloadTexture(aboutBg);
            *gameState = MAIN_MENU;
        }
        break;

    case GAME_OVER:
        if (keyPressed == KEY_ENTER)
        {
            resetStats(stats);
            *gameState = IN_GAME;
        }
        else if (keyPressed == KEY_Q)
        {
            resetStats(stats);
            *gameState = MAIN_MENU;
        }
        break;

    case IN_GAME:
        break;
    }
}

void ingresarNickName(char inputText[])
{
    int letterCount = 0; // Contador de caracteres
    int key;             // Captura letra ingresada

    // Fondo pantalla inicial
    Texture2D startTx = LoadTexture("resources/images/backgrounds/startbg.png");
    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose())
    {
        PlayMusicStream(menuMusic);
        UpdateMusicStream(menuMusic);
        // Terminar cadena cuando presione enter
        if (IsKeyPressed(KEY_ENTER) && letterCount < MAX_LEN_NAME)
        {
            inputText[letterCount] = '\0';
        }
        else
        {
            // Capturar tecla presionada
            key = GetKeyPressed();

            // Verificar si la tecla es un carácter imprimible y hay espacio disponible
            if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122))
            {
                inputText[letterCount] = (char)key;
                letterCount++;
            }
            else
            { // Borrar caracter - tecla retroceso
                if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
                {
                    letterCount--;
                    inputText[letterCount] = '\0';
                }
            }
        }
        // DIBUJO
        BeginDrawing();
        DrawTexture(startTx, 0, 0, WHITE);

        DrawText("Bienvenid@ a Cosmic Chaos!", (SCR_WIDTH - MeasureText("Bienvenid@ a Cosmic Chaos!", 80)) / 2, 100, 80, RAYWHITE);
        DrawText("Ingresa tu nombre de usuario y presiona enter:", (SCR_WIDTH - MeasureText("Ingresa tu nombre de usuario y presiona enter:", 40)) / 2, SCR_HEIGHT / 2 - 25, 40, WHITE);

        // Posicion cuadro entrada de texto
        float inputBoxX = (SCR_WIDTH - 450) / 2;

        // Dibujo caja de texto y texto
        DrawRectangleLines(inputBoxX, SCR_HEIGHT / 2 + 50, 450, 60, WHITE);
        DrawText(inputText, inputBoxX + 15, SCR_HEIGHT / 2 + 60, 40, WHITE);

        EndDrawing();
    }
    UnloadTexture(startTx);
}

// Obtiene datos a guardar del jugador
Tdata getDataPlayer()
{
    Tdata data = {"", 0, 0, 0, 0, 0, 0};
    ingresarNickName(data.name);
    getDate(&data.dia, &data.mes, &data.anio); // Fecha del reporte
    return data;
}

// Inicializar cualquier objeto
void InitObject(TGameObject *object, const float *objRadius)
{
    object->position.x = GetRandomValue(0, SCR_WIDTH);
    object->position.y = -(*objRadius) * 2;
    object->active = true;
}

// Colisiones
bool CheckCollision(Vector2 *playerPos, float playerRadius, Vector2 *ballPos, float meteorRadius)
{
    float dx = ballPos->x - playerPos->x;
    float dy = ballPos->y - playerPos->y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSumSquared = (playerRadius + meteorRadius) * (playerRadius + meteorRadius);
    return distanceSquared < radiusSumSquared;
}

// Manejo de niveles
void Levels(GameStats *stats, float *elapsedTime, Vector2 *playPosition, int *totalseconds)
{
    if (stats->score == 0 && stats->level == 0)
    {
        // Historia inicial
        // subsCinematicas("   INFORME DE ULTIMO MOMENTO                        Hola a todos son las 11:45 am y aqui su servilleta     Javie Alatorre informandolos.", 45, 7, 2, 4, 5);
        // subsCinematicas("Desde la NASA nos llega el informe de que se acaba  de descubrir un asteroide con un color amarillo el    cual tiene a los cientificos conmosionados ", 45, 7, 4, 0, 1);
        // subsCinematicas("Se rumora que podria contener gran cantidad de oro en su interior y en este momento organizaciones de   todo el mundo estan investigando este suceso ", 45, 7, 4, 0, 1);
        // subsCinematicas("  Un momento!  Nos informan que el asteroide acaba   de colisionar contra el cinturon de asteroides", 45, 7, 3, 2, 3);
        // subsCinematicas("y efectivamene, contiene gran cantidad de oro, esto deja a las organzaciones en una carrera para ver    quien sera el que se apropie de el ", 45, 7, 4, 2, 3);
        // subsCinematicas("Olvidenlo, nos informan que españa es el primer      aventado en ir por el, como dicta la historia oro del que lo tenga oro se lo queda ", 45, 7, 4, 6, 7);
        // subsCinematicas("nuestros desarolladores han creado una represent- acion grafica de que es lo que podria estar pasando en este momento aya arriba en el espacio ", 45, 7, 1, 4, 5);

        /* Estadisticas Nivel 1 */
        stats->level = 1;
        stats->score = 0;
        stats->lives = 5;
        *elapsedTime = 0.0f;
        stats->timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV1;
        MAX_BROWN = MAX_METEOR_LV1;
        MAX_HEART = MAX_HEART_LV1;
    }

    if (stats->score >= 50 && stats->level == 1)
    {
        // Limpiar objetos
        resetItems(playPosition);
        // screenpoints(totalseconds, score);

        // subsCinematicas("aqui iria la cinematica de descanso", 45, 7, 1, 0, 1);
        // subsCinematicas("continuacion de historia", 45, 7, 2, 0, 1);

        screenMessage("NIVEL 2", 2, BLACK);

        /* Estadisticas Nivel 2 */
        stats->level = 2;
        stats->score = 0;
        stats->lives = 5;
        *elapsedTime = 0.0f;
        stats->timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV2;
        MAX_BROWN = MAX_METEOR_LV2;
        MAX_HEART = MAX_HEART_LV2;
    }
    // Verificar si el jugador ha alcanzado el nivel 3
    if (stats->score >= 50 && stats->level == 2)
    {
        // Limpiar objetos
        resetItems(playPosition);

        screenMessage("NIVEL 3", 2, BLACK);

        /* Estadisticas Nivel 3 */
        stats->level = 3;
        stats->score = 0;
        stats->lives = 5;
        *elapsedTime = 0.0f;
        stats->timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV3;
        MAX_BROWN = MAX_METEOR_LV3;
        MAX_HEART = MAX_HEART_LV3;
    }
}

// Reiniciar posicion de elementos y jugador
void resetItems(Vector2 *playPosition)
{
    // Reiniciar posicion nave
    (*playPosition).x = (float)SCR_WIDTH / 2;
    (*playPosition).y = (float)SCR_HEIGHT / 1.1f;
    short i;

    // Limpiar meteoros
    objectfalse(grayMeteors, MAX_GRAY);
    objectfalse(brownMeteors, MAX_BROWN);
    // Limpiar Objetos
    objectfalse(coinGold, MAX_COINS);
    objectfalse(shieldB, MAX_OBJECT);
    objectfalse(municiones, MAX_OBJECT);
    objectfalse(hearts, MAX_HEART);
    // Limpiar disparos
    for (i = 0; i < MAX_SHOTS; i++)
    {
        shots[i].active = false;
    }
}
void objectfalse(TGameObject *object, int Max_object)
{
    short i;
    for (i = 0; i < Max_object; i++)
    {
        object[i].active = false;
    }
}
// Reinicia estadisticas
void resetStats(GameStats *stats)
{
    stats->lives = 5;
    stats->score = 0;
    stats->level = 1;
    stats->rachaAciertos = 0;
    stats->timeseconds = 0;
    stats->totalMunicion = 10;
    MAX_GRAY = MAX_METEOR_LV1;
    MAX_BROWN = MAX_METEOR_LV1;
    MAX_HEART = MAX_HEART_LV1;
}

// Obtiene fecha actual
void getDate(int *dia, int *mes, int *anio)
{
    time_t tiempoActual = time(NULL);
    struct tm *fecha = localtime(&tiempoActual); // DD/MM/AAAA
    *dia = fecha->tm_mday;
    *mes = fecha->tm_mon + 1;
    *anio = fecha->tm_year + 1900;
}

// Agrega estadisticas del jugador al archivo .dat
void appendScoresToFile(const char *filename, Tdata player)
{
    FILE *file = fopen(filename, "ab");
    fwrite(&player, sizeof(Tdata), 1, file);
    fclose(file);
}

void selecNpreguntas()
{
    FILE *pregsArch = fopen("resources/preguntas.dat", "rb");
    int posiciones[PREG_SELEC];

    // Gen. posiciones sin repetir, para selec. preguntas
    int pos;
    for (int i = 0; i < PREG_SELEC; i++)
    {
        do
        {
            pos = rand() % TOTAL_PREG;
        } while (busqSecuencial(posiciones, i, pos) != -1);
        posiciones[i] = pos;
    }

    // Seleccionar N preguntas del .dat
    for (int i = 0; i < PREG_SELEC; i++)
    {
        fseek(pregsArch, posiciones[i] * sizeof(Tpregunta), SEEK_SET);
        fread(&preguntas[i], sizeof(Tpregunta), 1, pregsArch);
    }
    fclose(pregsArch);
}

int busqSecuencial(int vect[], int m, int num)
{
    for (int i = 0; i < m; i++)
    {
        if (vect[i] == num)
        {
            return i;
        }
    }
    return -1;
}

void mezclarArray(char array[][20], int size)
{
    char temp[20];
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        if (i != j)
        {
            strcpy(temp, array[i]);
            strcpy(array[i], array[j]);
            strcpy(array[j], temp);
        }
    }
}

void secondspause(float seconds)
{
    double startTime2 = GetTime();
    while (GetTime() - startTime2 < seconds)
        ;
}

// Mostrar mensaje en pantalla
void screenMessage(const char *text, float seconds, Color colorbg)
{
    int tamano = 180;

    ClearBackground(colorbg);

    DrawText(text, SCR_WIDTH / 2 - MeasureText(text, tamano) / 2, (SCR_HEIGHT / 2) - 100, tamano, WHITE);
    EndDrawing();
    secondspause(seconds);
}