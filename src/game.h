#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* MENUs */
void drawMainMenu();
void drawHowToPlay();
void aboutTheGame();
void menuActions(int *seconds, bool *isPlaying);

/* INTERFACES */
void drawGameInterface(Texture2D hearts, Texture2D hearthEmpty, Texture2D shieldTx, short lives, short score, short level, const char *nickname, short racha, short shield, short municion, int minutes, int seconds);
void ingresarNickName(char inputText[]);
Tdata getDataPlayer();
void gameOverInterface(short score, short level);

/* DIBUJO OBJETOS */
void drawPlayer(Texture2D ship, Texture2D forceF, Vector2 *playerPosition, float *playerRotation, short shield);
void drawMeteors(float rotation);
void drawObject(Texture2D Textura,TGameObject *objects, int MAX_OBJECTS);
void drawShots(Texture2D shotTx, Texture2D *explosionTx);
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

/* LOGICA */
void InitObject(TGameObject *object, const float *objRadius);
bool CheckCollision(Vector2 *playerPos, float playerRadius, Vector2 *ballPos, float meteorRadius);

void Levels(short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives, int *totalseconds, float *timeseconds);
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, int frame1, int frame2);
void pausa();
void screenMessage(const char *text, float seconds, bool background);
void screenpoints(int *totalseconds, short *score);

void resetItems(Vector2 *playPosition);
void resetStats(short *lives, short *score, short *level, short *rachaAciertos, short *municion, float *timeSeconds);
void secondspause(float seconds);

// Datos jugador
void getDate(int *dia, int *mes, int *anio);
void appendScoresToFile(const char *filename, Tdata player);
void DrawScoresTable(const char *filename);

// CUESTIONARIO
void mezclarArray(char array[][20], int size);
void seleccPreguntas();
int busqSecuencial(int vect[], int m, int num);
void drawQuestion(bool *showQuestion, short *racha, short *shield, short *municion, short *lives, short object);

/*-------------------- DESARROLLO DE FUNCIONES --------------------*/
// Dibuja menu principal
void drawMainMenu() // PANTALLA DE MENU
{
    BeginDrawing();

    // Fondo
    DrawTexture(menu, 0, 0, WHITE);

    // Titulo
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC-CHAOS", 180) / 2, 150, 186, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 6 - MeasureText("COSMIC-CHAOS", 180) / 2 + 3, 145, 183, DARKBLUE);
    DrawText("COSMIC-CHAOS", SCR_WIDTH / 2 + 12 - MeasureText("COSMIC-CHAOS", 180) / 2 + 6, 140, 180, BLUE);

    // Acciones
    drawTextCenter("(ENTER) Iniciar", 2, 482, 60, LIME);
    drawTextCenter("(ENTER) Iniciar", 0, 480, 60, GREEN);

    drawTextCenter("(A) Como jugar", 2, 562, 60, DARKPURPLE);
    drawTextCenter("(A) Como jugar", 0, 560, 60, PURPLE);

    drawTextCenter("(E) Acerca del juego", 2, 642, 60, GRAY);
    drawTextCenter("(E) Acerca del juego", 0, 640, 60, YELLOW);

    drawTextCenter("(H) Historial de juego", 2, 722, 60, SKYBLUE);
    drawTextCenter("(H) Historial de juego", 0, 720, 60, BLUE);

    drawTextCenter("(ESC) Salir", 2, 802, 60, DARKGRAY);
    drawTextCenter("(ESC) Salir", 2, 800, 60, RED);

    EndDrawing();
}

// Dibuja pantalla de como jugar
void drawHowToPlay()
{
    while (!IsKeyPressed(KEY_Q))
    {
        UpdateMusicStream(menuMusic);
        BeginDrawing();
        ClearBackground(BLACK);
        drawTextCenter("COMO JUGAR: ", 0, 100, 100, BLUE);
        DrawText("- Muevete con las flechas o WASD", 40, SCR_HEIGHT / 2 + 40, 50, WHITE);
        DrawText("- Disparar (ESPACIO)", 40, SCR_HEIGHT / 2 + 110, 50, GRAY);
        DrawText("- PAUSA (P)", 40, SCR_HEIGHT / 2 + 250, 50, RED);
        DrawText("- Gana puntos, vidas y sobrevive", 40, SCR_HEIGHT / 2 + 180, 50, YELLOW);
        DrawText("(Q) Volver al menu", SCR_WIDTH / 2 - MeasureText("(Q) Back to menu", 50) / 2, SCR_HEIGHT / 2 + 350, 50, GREEN);
        EndDrawing();
    }
}

// Dibuja pantalla con informacion acerca del juego
void aboutTheGame()
{
    Texture2D aboutBg = LoadTexture("resources/images/backgrounds/cinema9.png");

    while (!IsKeyPressed(KEY_Q)) // Bucle para mostrar la interfaz "about"
    {
        UpdateMusicStream(menuMusic);
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(aboutBg, 400, 280, WHITE);

        drawTextCenter("Acerca del juego", 0, 100, 100, RED);
        drawTextCenter("Desarrolladores:", 0, 270, 50, YELLOW);
        drawTextCenter("- Francisco Cornejo", 0, 340, 50, GREEN);
        drawTextCenter("- Diego Ibarra", 0, 400, 50, GREEN);
        drawTextCenter("(Q) Volver al menu", 0, 800, 50, GOLD);
        EndDrawing();
    }
    UnloadTexture(aboutBg);
}

// Maneja acciones del menu principal
void menuActions(int *seconds, bool *isPlaying)
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
    if (IsKeyPressed(KEY_H))
    {
        DrawScoresTable("record.dat");
    }
}

// Dibuja la interfaz de partida en curso
void drawGameInterface(Texture2D hearts, Texture2D hearthEmpty, Texture2D shieldTx, short lives, short score, short level, const char *nickname, short racha, short shield, short municion, int minutes, int seconds)
{
    // Dibuja fondo
    switch(level)
    {
        case 1:
        DrawTexture(levels[0], 0, 0, WHITE);
        break;

        case 2:
        DrawTexture(levels[1], 0, 0, WHITE);
        break;

        case 3:
        DrawTexture(levels[2], 0, 0, WHITE);
        break;
    }
    
    // Dibuja puntaje
    DrawText(TextFormat("Puntos : %04i", score), SCR_WIDTH - 320, 20, 45, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("Nivel : %i", level), 20, 20, 45, WHITE);

    // ******** Dibujar Nombre jugador *********
    float textWidth = MeasureText(TextFormat("Jugador : %s", nickname), 40);
    float posX = (SCR_WIDTH - textWidth) / 2;
    DrawText(TextFormat("Jugador : %s", nickname), posX, 20, 40, YELLOW);

    // Dibuja vidas restantes
    DrawText(TextFormat("Vidas : %d", lives), SCR_WIDTH - 280, SCR_HEIGHT - 130, 50, WHITE);

    DrawText(TextFormat("Racha Aciertos : %d", racha), 20, SCR_HEIGHT - 90, 35, WHITE);
    float x;

    for (int i = 0; i < lives; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);
        DrawTexture(hearts, x, SCR_HEIGHT - 65, WHITE);
    }
    for (int i = lives; i < 5; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);                        // Inicia desde el lado derecho
        DrawTexture(hearthEmpty, x, SCR_HEIGHT - 65, WHITE); // Corazón vacío
    }
    for (int i = 0; i < shield; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1) - 65 * lives;
        DrawTexture(shieldTx, x, SCR_HEIGHT - 70, WHITE);
    }

    // Mostrar estado de los powerups
    DrawText(TextFormat("MUNICION : %02d", municion), 20, 80, 35, YELLOW);

    // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
    DrawText(TextFormat("%02d:%02d", minutes, seconds), 20, SCR_HEIGHT - 50, 50, WHITE);
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
    char name[MAX_LEN_NAME] = "";
    ingresarNickName(name);
    Tdata data;
    strcpy(data.name, name);                   // Usuario
    data.score = 0;                            // Mejor puntuacion
    data.maxLevel = 0;                         // Maximo Nivel alcanzado
    data.rachaAciertos = 0;                    // Racha de respuestas correctas
    getDate(&data.dia, &data.mes, &data.anio); // Fecha del reporte
    return data;
}

// Dibuja la interfaz de derrota
void gameOverInterface(short score, short level)
{
    // Fondo
    DrawTexture(gameoverT, 0, 0, WHITE);

    // Dibujar ventana de "Game Over"
    drawTextCenter("FIN DEL JUEGO", 2, 232, 110, WHITE);
    drawTextCenter("FIN DEL JUEGO", 0, 230, 110, RED);

    DrawText(TextFormat("PUNTAJE: %04i", score), SCR_WIDTH / 2 - MeasureText(TextFormat("PUNTAJE: %04i", score), 60) / 2, SCR_HEIGHT / 2 + 10, 60, RAYWHITE);
    DrawText(TextFormat("NIVEL: %1i", level), SCR_WIDTH / 2 - MeasureText(TextFormat("LEVEL: %1i", level), 60) / 2, SCR_HEIGHT / 2 - 50, 60, RAYWHITE);

    drawTextCenter("(ENTER) Jugar de nuevo", 2, 582, 60, LIME);
    drawTextCenter("(ENTER) Jugar de nuevo", 0, 580, 60, GREEN);

    drawTextCenter("(Q) Volver al menu", 2, 662, 60, DARKPURPLE);
    drawTextCenter("(Q) Volver al menu", 0, 660, 60, MAGENTA);

    drawTextCenter("(ESC) Salir", 2, 742, 60, RED);
    drawTextCenter("(ESC) Salir", 0, 740, 60, MAROON);
}

void drawPlayer(Texture2D ship, Texture2D forceF, Vector2 *playerPosition, float *playerRotation, short shield)
{
    // Dibujar textura del jugador con rotación
    DrawTexturePro(ship, (Rectangle){0, 0, (float)ship.width, (float)ship.height},
                   (Rectangle){playerPosition->x, playerPosition->y, (float)ship.width, (float)ship.height},
                   (Vector2){(float)ship.width / 2, (float)ship.height / 2}, *playerRotation, WHITE);

    if (shield > 0)
    {
        DrawTexturePro(forceF, (Rectangle){0, 0, (float)forceF.width, (float)forceF.height},
                       (Rectangle){playerPosition->x, playerPosition->y, (float)forceF.width, (float)forceF.height},
                       (Vector2){(float)forceF.width / 2, (float)forceF.height / 2}, *playerRotation, WHITE);
    }
}

// Dibuja meteoros
void drawMeteors(float rotation)
{
    Vector2 grayCenter, brownCenter;

    for (int i = 0; i < MAX_GRAY; i++)
    {
        if (grayMeteors[i].active)
        {
            // Calcular el punto central
            grayCenter.x = grayMeteors[i].position.x - grayMeteor.width / 2;
            grayCenter.y = grayMeteors[i].position.y - grayMeteor.height / 2;

            // Dibujar textura meteoro girando
            DrawTexturePro(grayMeteor, (Rectangle){0, 0, (float)grayMeteor.width, (float)grayMeteor.height},
                           (Rectangle){grayCenter.x, grayCenter.y, (float)grayMeteor.width, (float)grayMeteor.height},
                           (Vector2){(float)grayMeteor.width / 2, (float)grayMeteor.height / 2}, rotation, WHITE);
        }
    }
    for (int i = 0; i < MAX_BROWN; i++)
    {
        if (brownMeteors[i].active)
        {
            // Calcular el punto central
            brownCenter.x = brownMeteors[i].position.x - brownMeteor.width / 2;
            brownCenter.y = brownMeteors[i].position.y - brownMeteor.height / 2;

            // Dibujar textura meteoro girando
            DrawTexturePro(brownMeteor, (Rectangle){0, 0, (float)brownMeteor.width, (float)brownMeteor.height},
                           (Rectangle){brownCenter.x, brownCenter.y, (float)brownMeteor.width, (float)brownMeteor.height},
                           (Vector2){(float)brownMeteor.width / 2, (float)brownMeteor.height / 2}, rotation, WHITE);
        }
    }
}

// Dibujar monedas y corazones
void drawObject(Texture2D Textura,TGameObject *objects, int MAX_OBJECTS)
{
    Vector2 objectCenter;

    // Dibujar monedas
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (objects[i].active)
        {
            // Calcular la posición del centro de la moneda
            objectCenter.x = objects[i].position.x - Textura.width / 2;
            objectCenter.y = objects[i].position.y - Textura.height / 2;
            DrawTextureV(Textura, objectCenter, WHITE);
        }
    }
}

// Dibujar disparos
void drawShots(Texture2D shotTx, Texture2D *explosionTx)
{
    // Calcular la posición y centro de la bala
    Vector2 shotPos;

    for (int i = 0; i < MAX_SHOTS; i++)
    {
        if (shots[i].active)
        {
            if (!shots[i].collided) // Si no ha habido colisión, dibuja el misil
            {
                shotPos.x = shots[i].position.x - shotTx.width / 2;
                shotPos.y = shots[i].position.y - shotTx.height / 2;
                DrawTextureV(shotTx, shotPos, WHITE);
            }
            else // Si ha habido una colisión, dibuja la explosión
            {
                shotPos.x = shots[i].position.x - explosionTx->width / 2;
                shotPos.y = shots[i].position.y - explosionTx->height / 2;
                DrawTextureV(*explosionTx, shotPos, WHITE);
            }
        }
    }
}

// Imprimir texto centrado
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2 + posX, posY, fontSize, color);
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
void Levels(short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives, int *totalseconds, float *timeseconds)
{
    if (*score == 0 && *level == 0)
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
        *level = 1;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV1;
        MAX_BROWN = MAX_METEOR_LV1;
        MAX_HEART = MAX_HEART_LV1;
    }

    if (*score >= 50 && *level == 1)
    {
        // Limpiar objetos
        resetItems(playPosition);
        // screenpoints(totalseconds, score);

        // subsCinematicas("aqui iria la cinematica de descanso", 45, 7, 1, 0, 1);
        // subsCinematicas("continuacion de historia", 45, 7, 2, 0, 1);

        screenMessage("NIVEL 2", 2, true);

        /* Estadisticas Nivel 2 */
        *level = 2;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV2;
        MAX_BROWN = MAX_METEOR_LV2;
        MAX_HEART = MAX_HEART_LV2;
    }
    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 50 && *level == 2)
    {
        // Limpiar objetos
        resetItems(playPosition);

        screenMessage("NIVEL 3", 2, true);

        /* Estadisticas Nivel 3 */
        *level = 3;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV3;
        MAX_BROWN = MAX_METEOR_LV3;
        MAX_HEART = MAX_HEART_LV3;
    }
}

// Maximo 160 caracteres - tamaño - frecuencia - tiempo - textura - frame1 y frame2
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, int frame1, int frame2)
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
        {
            return; // Saltar cinematica
        }

        if (cambio)
        {
            DrawTexture(cinema[frame1], 288, 0, WHITE);
        }
        else
        {
            DrawTexture(cinema[frame2], 288, 0, WHITE);
        }

        x = limiteH;
        y = (SCR_HEIGHT / 2) * 1.6;

        for (int j = 0; j <= i; j++)
        {
            if (IsKeyPressed(KEY_S))
            {
                return; // Saltar cinematica
            }

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
// Mostrar pantalla de puntos
void screenpoints(int *totalseconds, short *score)
{
    // Variables para el puntaje real y el tiempo transcurrido
    float realScore = 0.0, tempscore = (*score / (float)(*totalseconds)) * 1.5;

    do
    {
        secondspause(0.001); // Esperar
        if (*score > 0)
        {
            *score -= 2; // Simular una disminución del puntaje
            if (*score <= 0)
            {
                *score = 0;
            }
        }
        if (*totalseconds > 0)
        {
            *totalseconds -= 0.001; // Simular una disminución del tiempo transcurrido
            if (*totalseconds <= 0)
            {
                *totalseconds = 0;
            }
        }
        if (realScore <= tempscore)
        {
            realScore += 0.01; // simular aumento de puntaje
            if (realScore >= tempscore)
            {
                realScore = tempscore;
            }
        }
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText(TextFormat("Tiempo: %02d:%02d", *totalseconds / 60, *totalseconds % 60), 30, 100, 100, WHITE);
        DrawText(TextFormat("Oro recolectado: %d", *score), 30, 220, 100, WHITE);
        DrawText(TextFormat("Oto total ganado: %3.2f", realScore), 30, 340, 100, WHITE);
        EndDrawing();
    } while (realScore != tempscore); // Termina al llegar a el puntaje real
    secondspause(2);
}

void pausa()
{
    int tamano = 160;
    const char text[] = "Pausa";
    const char text2[] = "(Enter) Reanudar partida";

    if (IsKeyDown(KEY_P))
    {
        do
        {
            DrawText(text, SCR_WIDTH / 2 - MeasureText(text, tamano) / 2, (SCR_HEIGHT / 2) - 165, tamano, WHITE);
            DrawText(text2, SCR_WIDTH / 2 - MeasureText(text2, 80) / 2, (SCR_HEIGHT / 2) + 150, 80, WHITE);
            EndDrawing();
        } while (!IsKeyPressed(KEY_ENTER));
    }
}

// Mostrar pantalla de nivel
void screenMessage(const char *text, float seconds, bool background)
{
    int tamano = 180;

    if (background)
    {
        ClearBackground(BLACK);
    }
    DrawText(text, SCR_WIDTH / 2 - MeasureText(text, tamano) / 2, (SCR_HEIGHT / 2) - 100, tamano, WHITE);
    EndDrawing();
    secondspause(seconds);
}

// Reiniciar posicion de elementos y jugador
void resetItems(Vector2 *playPosition)
{
    // Reiniciar posicion nave
    (*playPosition).x = (float)SCR_WIDTH / 2;
    (*playPosition).y = (float)SCR_HEIGHT / 1.1f;
    short i;

    // Limpiar meteoros
    for (i = 0; i < MAX_GRAY; i++)
    {
        grayMeteors[i].active = false;
    }
    for (i = 0; i < MAX_BROWN; i++)
    {
        brownMeteors[i].active = false;
    }
    // Limpiar monedas
    for (i = 0; i < MAX_COINS; i++) // GOLD COIN
    {
        coinGold[i].active = false;
    }
    for (i = 0; i < MAX_OBJECT; i++) // RED COIN
    {
        shieldB[i].active = false;
    }
    for (i = 0; i < MAX_OBJECT; i++) // MUNICIONES
    {
        municiones[i].active = false;
    }
    // Limpiar corazones
    for (i = 0; i < MAX_HEART; i++)
    {
        hearts[i].active = false;
    }
    // Limpiar disparos
    for (i = 0; i < MAX_SHOTS; i++)
    {
        shots[i].active = false;
    }
}

// Reinicia estadisticas
void resetStats(short *lives, short *score, short *level, short *rachaAciertos, short *municion, float *timeSeconds)
{
    *lives = 5;
    *score = 0;
    *level = 1;
    *rachaAciertos = 0;
    *timeSeconds = 0;
    *municion = 10;
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

    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    fwrite(&player, sizeof(Tdata), 1, file);

    fclose(file);
}

// Dibuja la tabla para mostrar los datos del .dat
void DrawScoresTable(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    Tdata players[MAX_PLAYERS];
    int numPlayers = 0;

    while (fread(&players[numPlayers], sizeof(Tdata), 1, file) == 1)
    {
        numPlayers++;
    }
    if (numPlayers <= 0)
    {
        drawTextCenter("No hay registros", 0, (SCR_HEIGHT / 2) + 200, 50, WHITE);
    }
    fclose(file);

    // Calcular posición y dimensiones de la tabla
    int tableWidth = SCR_WIDTH * 0.6f;   // Porcentaje del ancho de la pantalla
    int tableHeight = SCR_HEIGHT * 0.6f; // Porcentaje del alto de la pantalla
    int tablePosX = (SCR_WIDTH - tableWidth) / 2;
    int tablePosY = (SCR_HEIGHT - tableHeight) / 2;

    int cellWidth = tableWidth / 5; // Ajustar para la nueva columna
    int cellHeight = 50;
    int scrollOffset = 0;
    int maxVisibleRows = (tableHeight - 50) / cellHeight; // Calcula el número máximo de filas visibles

    // Fondo tabla de estadisticas
    Texture2D scoreboardTx = LoadTexture("resources/images/backgrounds/scorebg.png");

    while (!IsKeyPressed(KEY_Q))
    {
        UpdateMusicStream(menuMusic);
        BeginDrawing();
        DrawTexture(scoreboardTx, 0, 0, WHITE);
        drawTextCenter("HISTORIAL DE JUEGOS", 0, 50, 50, WHITE);
        drawTextCenter("(UP , DOWN) Navegar en la tabla", 0, 750, 40, PURPLE);
        drawTextCenter("(Q) Volver al menu", 0, 820, 40, RED);

        // Dibujar encabezados de la tabla
        DrawRectangleLines(tablePosX, tablePosY, tableWidth, cellHeight, WHITE);
        DrawText("Nombre", tablePosX + cellWidth * 0.5f - MeasureText("Nombre", 20) / 2, tablePosY + 10, 20, WHITE);
        DrawText("Nivel alcanzado", tablePosX + cellWidth * 1.5f - MeasureText("Nivel alcanzado", 20) / 2, tablePosY + 10, 20, WHITE);
        DrawText("Puntaje", tablePosX + cellWidth * 2.5f - MeasureText("Puntaje", 20) / 2, tablePosY + 10, 20, WHITE);
        DrawText("Aciertos Maximos", tablePosX + cellWidth * 3.5f - MeasureText("Aciertos Maximos", 20) / 2, tablePosY + 10, 20, WHITE); // Nuevo encabezado
        DrawText("Fecha", tablePosX + cellWidth * 4.5f - MeasureText("Date", 20) / 2, tablePosY + 10, 20, WHITE);

        // Dibujar cada jugador en la tabla
        for (int i = 0; i < maxVisibleRows; i++)
        {
            int playerIndex = i + scrollOffset;
            if (playerIndex >= 0 && playerIndex < numPlayers)
            {
                // Espacio entre el borde superior de la celda y el texto
                float textPosY = tablePosY + cellHeight + cellHeight * i + 10;

                DrawText(players[playerIndex].name, tablePosX + cellWidth * 0.5f - MeasureText(players[playerIndex].name, 20) / 2, textPosY, 20, YELLOW);
                DrawText(TextFormat("%d", players[playerIndex].maxLevel), tablePosX + cellWidth * 1.5f - MeasureText(TextFormat("%d", players[playerIndex].maxLevel), 20) / 2, textPosY, 20, YELLOW);
                DrawText(TextFormat("%d", players[playerIndex].score), tablePosX + cellWidth * 2.5f - MeasureText(TextFormat("%d", players[playerIndex].score), 20) / 2, textPosY, 20, YELLOW);
                DrawText(TextFormat("%d", players[playerIndex].rachaAciertos), tablePosX + cellWidth * 3.5f - MeasureText(TextFormat("%d", players[playerIndex].rachaAciertos), 20) / 2, textPosY, 20, YELLOW); // Nuevo campo
                DrawText(TextFormat("%02d/%02d/%d", players[playerIndex].dia, players[playerIndex].mes, players[playerIndex].anio), tablePosX + cellWidth * 4.5f - MeasureText(TextFormat("%02d/%02d/%02d", players[playerIndex].dia, players[playerIndex].mes, players[playerIndex].anio), 20) / 2, textPosY, 20, YELLOW);
            }
        }

        // Control de desplazamiento
        if (IsKeyDown(KEY_UP) && scrollOffset > 0)
        {
            scrollOffset -= 1;
        }
        if (IsKeyDown(KEY_DOWN) && scrollOffset < numPlayers - maxVisibleRows)
        {
            scrollOffset += 1;
        }

        EndDrawing();
    }
    UnloadTexture(scoreboardTx);
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

void seleccPreguntas()
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

void drawQuestion(bool *showQuestion, short *racha, short *shield, short *municion, short *lives, short object)
{
    int indicePregunta = rand() % PREG_SELEC;
    Tpregunta preguntaActual = preguntas[indicePregunta];

    // Hacer una copia de las opciones de respuesta
    char opcionesBarajadas[4][20];
    memcpy(opcionesBarajadas, preguntaActual.opciones, sizeof(preguntaActual.opciones));
    mezclarArray(opcionesBarajadas, 4);

    // Fondo pregunta
    Texture2D questionTx = LoadTexture("resources/images/backgrounds/questionbg.png");

    do
    {
        BeginDrawing();
        DrawTexture(questionTx, 0, 0, WHITE);
        drawTextCenter(preguntaActual.pregunta, 0, 280, 55, YELLOW);
        for (int i = 0; i < 4; i++)
        {
            char opcionLabel = 'A' + i;
            drawTextCenter(TextFormat("%c) %s", opcionLabel, opcionesBarajadas[i]), 0, 400 + i * 60, 45, WHITE);
        }

        for (int i = 0; i < 4; i++)
        {
            if (IsKeyPressed(KEY_A + i))
            {
                if (strcmp(opcionesBarajadas[i], preguntaActual.opciones[preguntaActual.respuestaCorrecta]) == 0)
                {
                    drawTextCenter("¡Correcto!", 0, 650, 45, GREEN);
                    if (object == 1)
                    {
                        (*shield) = 2;
                    }
                    if (object == 2)
                    {
                        (*municion) += 3;
                    }

                    (*racha)++;
                    if ((*racha) % 3 == 0) // 1 Vida adicional por cada racha de 3 aciertos
                    {
                        (*lives)++;
                    }
                }
                else
                {
                    *racha = 0;
                    drawTextCenter("¡Incorrecto!", 0, 650, 45, RED);
                }
                *showQuestion = false;
                break;
            }
        }
        EndDrawing();
    } while (*showQuestion);
    UnloadTexture(questionTx);
    // Espera entre cada pregunta
    secondspause(1.5);
}
void secondspause(float seconds)
{
    double startTime2 = GetTime();
    while (GetTime() - startTime2 < seconds)
        ;
}