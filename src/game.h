#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* LOGICA */
void InitObject(TGameObject *object, const float *objRadius);
bool CheckCollision(Vector2 *playerPos, float playerRadius, Vector2 *ballPos, float meteorRadius);
void subsCinematicas(const char *text, int tamano, float posY, int frecuencia, int frame1, int frame2);

// Actualiza estados del juego
void updateGameState(GameState *gameState, int keyPressed, GameStats *stats, bool *muteMusic, Vector2 *playPosition);
void updateMusic(GameState gameState, bool muteMusic);

// Niveles
void Levels(GameStats *stats, float *elapsedTime, Vector2 *playPosition, int *totalseconds);

// Fisicas objetos del juego
bool physicAndColision(TGameObject object[], int maxObjects, int objSpeed, float objRadius, Vector2 *playerPosition, int playRadius, Texture2D *texture, bool isMeteor);
void generateObjects(TGameObject *object, int maxObjects, float radius);

// Reinicia juego
void resetItems(Vector2 *playPosition);
void objectfalse(TGameObject *object, int maxObjects);
void resetStats(GameStats *stats);

// Espera un tiempo especifico
void secondspause(float seconds);
void screenMessage(const char *text, float seconds, Color fondo, Color colorText, int fontSize);
void screenpoints(int totalseconds, int score);
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

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
void updateGameState(GameState *gameState, int keyPressed, GameStats *stats, bool *muteMusic, Vector2 *playPosition)
{
    switch (*gameState)
    {
    case MAIN_MENU:
        if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {
            *gameState = IN_GAME;
        }
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

        case KEY_M:
            *muteMusic = !(*muteMusic);
            break;

        case KEY_F11:
            ToggleFullscreen();
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
        if (keyPressed == KEY_ENTER || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {
            resetStats(stats);
            *gameState = IN_GAME;
        }
        else
        {
            if (keyPressed == KEY_Q || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_LEFT))
            {
                resetStats(stats);
                *gameState = MAIN_MENU;
            }
        }
        break;

    case IN_GAME:
        if ((IsKeyDown(KEY_P) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)))
        {
            *gameState = PAUSE;
        }
        break;

    case PAUSE:
        if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {
            *gameState = IN_GAME;
        }
        if (IsKeyPressed(KEY_Q) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_LEFT))
        {
            resetStats(stats);
            resetItems(playPosition);
            *gameState = MAIN_MENU;
        }
        break;
    }
}

void updateMusic(GameState gameState, bool muteMusic)
{
    if (muteMusic)
    {
        StopMusicStream(menuMusic);
        StopMusicStream(gameMusic);
        StopMusicStream(gameover);
        return;
    }

    switch (gameState)
    {
    case MAIN_MENU:
    case HOW_TO_PLAY:
    case ABOUT_GAME:
    case HISTORY_SCORE:
        PlayMusicStream(menuMusic);
        UpdateMusicStream(menuMusic);
        break;
    case IN_GAME:
        StopMusicStream(menuMusic);
        StopMusicStream(gameover);
        PlayMusicStream(gameMusic);
        UpdateMusicStream(gameMusic);
        break;
    case GAME_OVER:
        PlayMusicStream(gameover);
        UpdateMusicStream(gameover);
        break;
    case PAUSE:
        break;
    }
}

// Logica para ingresar nombre de usuario
void ingresarNickName(char inputText[])
{
    int letterCount = 0; // Contador de caracteres
    int key;             // Captura letra ingresada

    // Fondo pantalla inicial
    Texture2D startTx = LoadTexture("resources/images/backgrounds/startbg.png");
    while (!(IsKeyPressed(KEY_ENTER) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) && !WindowShouldClose())
    {
        PlayMusicStream(menuMusic);
        UpdateMusicStream(menuMusic);
        // Terminar cadena cuando presione enter
        if ((IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) && letterCount < MAX_LEN_NAME)
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

// Colision
bool CheckCollision(Vector2 *playerPos, float playerRadius, Vector2 *ballPos, float meteorRadius)
{
    float dx = ballPos->x - playerPos->x;
    float dy = ballPos->y - playerPos->y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSumSquared = (playerRadius + meteorRadius) * (playerRadius + meteorRadius);
    return distanceSquared < radiusSumSquared;
}

// Imprime subtitulos
void subsCinematicas(const char *text, int tamano, float posY, int frecuencia, int frame1, int frame2)
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
        if (cambio)
        {
            DrawTexture(cinema[frame1], 0, 0, WHITE);
        }
        else
        {
            DrawTexture(cinema[frame2], 0, 0, WHITE);
        }

        x = limiteH;
        y = posY;

        for (int j = 0; j <= i; j++)
        {

            if (x + MeasureText(TextFormat("%c", text[j]), tamano) > SCR_WIDTH - limiteH)
            {
                x = limiteH;
                y += tamano + 15;
            }
            DrawText(TextFormat("%c", text[j]), x + 6, y + 6, tamano, BLACK);
            DrawText(TextFormat("%c", text[j]), x, y, tamano, YELLOW);

            x += MeasureText(TextFormat("%c", text[j]), tamano) + 10;
        }
        EndDrawing();

        acumulador++;
    }
}

// Manejo de niveles
void Levels(GameStats *stats, float *elapsedTime, Vector2 *playPosition, int *totalseconds)
{
    if (stats->score == 0 && stats->level == 0)
    {
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

    if (stats->score >= PTS_LEVEL_UP && stats->level == 1)
    {
        DrawTexture(tutotx, 0, 0, BLACK);
        DrawTexture(tutotx, 0, 0, BLACK);
        screenMessage("HAS SUPERADO LA META", 1, BLANK, GREEN, 100);
        screenpoints(*totalseconds, stats->score);
        // Limpiar objetos
        resetItems(playPosition);
        DrawTexture(levels[1], 0, 0, WHITE);
        screenMessage("NIVEL 2", 2, BLANK, WHITE, 180);

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
    if (stats->score >= PTS_LEVEL_UP && stats->level == 2)
    {
        DrawTexture(tutotx, 0, 0, BLACK);
        DrawTexture(tutotx, 0, 0, BLACK);

        screenMessage("HAS SUPERADO LA META", 1, BLANK, GREEN, 100);
        screenpoints(*totalseconds, stats->score);
        // Limpiar objetos
        resetItems(playPosition);
        DrawTexture(levels[2], 0, 0, WHITE);
        screenMessage("NIVEL 3", 2, BLACK, WHITE, 180);

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

// Maneja fisicas y colision de los objetos
bool physicAndColision(TGameObject object[], int maxObjects, int objSpeed, float objRadius, Vector2 *playerPosition, int playRadius, Texture2D *texture, bool isMeteor)
{
    short i;
    Vector2 objectPos;

    for (i = 0; i < maxObjects; i++)
    {
        if (object[i].active)
        {
            object[i].position.y += objSpeed;
            if (object[i].position.y > SCR_HEIGHT + objRadius * 2)
            {
                object[i].active = false; // Eliminar al salir de la pantalla
            }
            // Posicion correspondiente
            if (isMeteor)
            {
                objectPos.x = object[i].position.x - (texture->width / 2);
                objectPos.y = object[i].position.y - (texture->height / 2);
            }
            else
            {
                objectPos.x = object[i].position.x;
                objectPos.y = object[i].position.y;
            }
            // Deteccion colision
            if (CheckCollision(playerPosition, playRadius, &objectPos, objRadius))
            {
                object[i].active = false; // Eliminar objeto tocado
                return true;
            }
        }
    }
    return false;
}

// Genera / inicializa objetos del juego
void generateObjects(TGameObject *object, int maxObjects, float radius)
{
    for (int i = 0; i < maxObjects; i++)
    {
        if (!object[i].active)
        {
            InitObject(&object[i], &radius);
            break;
        }
    }
}

// Reiniciar posicion y desactiva los elementos del juego
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

// Desactiva cualquier objeto del juego
void objectfalse(TGameObject *object, int maxObjects)
{
    short i;
    for (i = 0; i < maxObjects; i++)
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

// Selecciona N preguntas aleatorias a utilizar del archivo
void selecNpreguntas()
{
    FILE *pregsArch = fopen("resources/preguntas.dat", "rb");
    int posiciones[PREG_SELEC];

    // Genera posiciones sin repetir, para selec. preguntas
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

// Busqueda secuencial
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

// Mezcla arreglo
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

// Pausa determinados segundos
void secondspause(float seconds)
{
    double startTime2 = GetTime();
    while (GetTime() - startTime2 < seconds)
        ;
}

// Mostrar mensaje en pantalla
void screenMessage(const char *text, float seconds, Color fondo, Color colorText, int fontSize)
{
    ClearBackground(fondo);

    drawTextCenter(text, 0, (SCR_HEIGHT / 2 - 100), fontSize, colorText);
    EndDrawing();
    secondspause(seconds);
}

// Pantalla de logros obtenidos en cada nivel
void screenpoints(int totalseconds, int score)
{
    // Variables para el puntaje real y el tiempo transcurrido
    float realScore = 0.0, tempscore = (score / (float)(totalseconds)) * 1.5;

    do
    {
        secondspause(0.001); // Esperar
        if (score > 0)
        {
            score -= 2; // Simular una disminución del puntaje
            if (score <= 0)
            {
                score = 0;
            }
        }
        if (totalseconds > 0)
        {
            totalseconds -= 0.001; // Simular una disminución del tiempo transcurrido
            if (totalseconds <= 0)
            {
                totalseconds = 0;
            }
        }
        if (realScore <= tempscore)
        {
            realScore += 0.03; // simular aumento de puntaje
            if (realScore >= tempscore)
            {
                realScore = tempscore;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(scoreLevel, 0, 0, WHITE);
        DrawText(TextFormat("Tiempo: %02d:%02d", totalseconds / 60, totalseconds % 60), 30, 100, 100, WHITE);
        DrawText(TextFormat("Oro recolectado: %d", score), 30, 220, 100, WHITE);
        DrawText(TextFormat("Oro total ganado: %3.2f", realScore), 30, 340, 100, WHITE);
        EndDrawing();
    } while (realScore != tempscore); // Termina al llegar a el puntaje real
    secondspause(1);
}

// Imprimir texto centrado
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2 + posX, posY, fontSize, color);
}