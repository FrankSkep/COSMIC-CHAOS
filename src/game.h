#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> // Necesario para RAND_MAX y rand()

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* MENUs */
void drawMainMenu();
void drawHowToPlay();
void aboutTheGame();
void menuActions(int *seconds, bool *isPlaying, bool *guardar);

/* INTERFACES */
void drawGameInterface(Texture2D *hearts, short *lives, short *score, short *level, const char *nickname);
void ingresarNickName(char inputText[]);
void drawGameElements(Texture2D *ship, Vector2 *shipPosicion, Texture2D *coinGold, Texture2D *hearts, Texture2D *shotTx, Texture2D *explosionTx, float *rotation, Vector2 *playerPosition, float *playerRotation);
void gameOverInterface(short *score, short *level);

/* DIBUJO OBJETOS */
void drawPlayer(Texture2D *ship, Vector2 *playerPosition, float *playerRotation);
void drawMeteors(float *rotation);
void drawObjects(Texture2D *coinsTx, Texture2D *heartsTx);
void drawShots(Texture2D *shotTx, Texture2D *explosionTx);
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

/* LOGICA */
void InitObject(TGameObject *object, const float *objRadius);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius);

void Levels(short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives, int *totalseconds, float *timeseconds);
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, int frame1, int frame2);
void pausa();
void screenlevel(const char *text, int seconds);
void screenpoints(int *totalseconds, short *score);

void resetItems(Vector2 *playPosition);
void resetStats(short *lives, short *score, short *level, float *timeSeconds);
void secondspause(float seconds);

// Datos jugador
void obtenerFechaAct(int *dia, int *mes, int *anio);
void appendScoresToFile(const char *filename, Tdata player);
void DrawScoresTable(const char *filename);
void mezclarArray(char **array, int size);
void drawQuestion(bool *mostrarPregunta, Pregunta *preguntas, int numPreguntas);

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
    while (!IsKeyPressed(KEY_Q)) // Bucle para mostrar la interfaz "about"
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(cinema[8], 400, 280, WHITE);

        drawTextCenter("Acerca del juego", 0, 100, 100, RED);
        drawTextCenter("Desarrolladores:", 0, 270, 50, YELLOW);
        drawTextCenter("- Francisco Cornejo", 0, 340, 50, GREEN);
        drawTextCenter("- Diego Ibarra", 0, 400, 50, GREEN);
        // drawTextCenter("Sounds:", 0, 580, 50, GOLD);
        // drawTextCenter("Unnamed", 0, 640, 50, LIME);
        drawTextCenter("(Q) Volver al menu", 0, 800, 50, GOLD);

        EndDrawing();
    }
}

// Maneja acciones del menu principal
void menuActions(int *seconds, bool *isPlaying, bool *guardar)
{
    if (IsKeyPressed(KEY_ENTER)) // Iniciar partida
    {
        *seconds = 0;
        *isPlaying = true;
        *guardar = true;
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
void drawGameInterface(Texture2D *hearts, short *lives, short *score, short *level, const char *nickname)
{
    // Dibuja fondo
    DrawTexture(game, 0, 0, WHITE);

    // Dibuja puntaje
    DrawText(TextFormat("PUNTAJE : %04i", *score), SCR_WIDTH - 390, 20, 50, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("NIVEL : %i", *level), SCR_WIDTH - 1560, 20, 50, WHITE);

    // ******** Dibujar Nombre jugador *********
    float textWidth = MeasureText(TextFormat("JUGADOR : %s", nickname), 40);
    float posX = (SCR_WIDTH - textWidth) / 2;
    DrawText(TextFormat("JUGADOR : %s", nickname), posX, 20, 40, YELLOW);

    // Dibuja vidas restantes
    float x;
    DrawText(TextFormat("VIDAS : %d", *lives), SCR_WIDTH - 280, SCR_HEIGHT - 130, 50, WHITE);
    for (int i = 0; i < *lives; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);
        DrawTexture(*hearts, x, SCR_HEIGHT - 65, RED);
    }
    for (int i = *lives; i < 5; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);               // Inicia desde el lado derecho
        DrawText("-", x, SCR_HEIGHT - 60, 50, RED); // Corazón vacío
    }
}

void ingresarNickName(char inputText[])
{
    int letterCount = 0; // Contador de caracteres
    int key;             // Captura letra ingresada

    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose())
    {
        // Terminar cadena cuando presione enter
        if (IsKeyPressed(KEY_ENTER) && letterCount < MAX_INPUT_CHARS)
        {
            inputText[letterCount] = '\0';
        }
        else
        {
            // Capturar tecla presionada
            key = GetKeyPressed();

            // Verificar si la tecla es un carácter imprimible y hay espacio disponible
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
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
        ClearBackground(BLACK);

        DrawText("Bienvenido a Cosmic Chaos", (SCR_WIDTH - MeasureText("Bienvenido a Cosmic Chaos", 70)) / 2, 100, 70, GREEN);
        DrawText("Ingresa tu nombre de usuario:", (SCR_WIDTH - MeasureText("Ingresa tu nombre de usuario:", 40)) / 2, SCR_HEIGHT / 2 - 25, 40, GREEN);

        // Posicion cuadro entrada de texto
        float inputBoxX = (SCR_WIDTH - 450) / 2;

        // Dibujo caja de texto y texto
        DrawRectangleLines(inputBoxX, SCR_HEIGHT / 2 + 50, 450, 60, WHITE);
        DrawText(inputText, inputBoxX + 15, SCR_HEIGHT / 2 + 60, 40, WHITE);

        EndDrawing();
    }
}

// Dibuja elementos de la partida
void drawGameElements(Texture2D *ship, Vector2 *shipPosicion, Texture2D *coinGold, Texture2D *hearts, Texture2D *shotTx, Texture2D *explosionTx, float *rotation, Vector2 *playerPosition, float *playerRotation)
{
    // Dibuja jugador (nave)
    drawPlayer(ship, playerPosition, playerRotation);
    // Dibuja meteoros en rotacion
    drawMeteors(rotation);
    // Dibuja monedas y corazones
    drawObjects(coinGold, hearts);
    // Dibuja disparos (misiles)
    drawShots(shotTx, explosionTx);
}

// Dibuja la interfaz de derrota
void gameOverInterface(short *score, short *level)
{
    // Fondo
    DrawTexture(gameoverT, 0, 0, WHITE);

    // Dibujar ventana de "Game Over"
    drawTextCenter("FIN DEL JUEGO", 2, 232, 110, WHITE);
    drawTextCenter("FIN DEL JUEGO", 0, 230, 110, RED);

    DrawText(TextFormat("PUNTAJE: %04i", *score), SCR_WIDTH / 2 - MeasureText(TextFormat("PUNTAJE: %04i", *score), 60) / 2, SCR_HEIGHT / 2 + 10, 60, RAYWHITE);
    DrawText(TextFormat("NIVEL: %1i", *level), SCR_WIDTH / 2 - MeasureText(TextFormat("LEVEL: %1i", *level), 60) / 2, SCR_HEIGHT / 2 - 50, 60, RAYWHITE);

    drawTextCenter("(ENTER) Jugar de nuevo", 2, 582, 60, LIME);
    drawTextCenter("(ENTER) Jugar de nuevo", 0, 580, 60, GREEN);

    drawTextCenter("(Q) Volver al menu", 2, 662, 60, DARKPURPLE);
    drawTextCenter("(Q) Volver al menu", 0, 660, 60, MAGENTA);

    drawTextCenter("(ESC) Salir", 2, 742, 60, RED);
    drawTextCenter("(ESC) Salir", 0, 740, 60, MAROON);
}

void drawPlayer(Texture2D *ship, Vector2 *playerPosition, float *playerRotation)
{
    // Dibujar textura del jugador con rotación
    DrawTexturePro(*ship, (Rectangle){0, 0, (float)ship->width, (float)ship->height},
                   (Rectangle){playerPosition->x, playerPosition->y, (float)ship->width, (float)ship->height},
                   (Vector2){(float)ship->width / 2, (float)ship->height / 2}, *playerRotation, WHITE);
}

// Dibuja meteoros
void drawMeteors(float *rotation)
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
                           (Vector2){(float)grayMeteor.width / 2, (float)grayMeteor.height / 2}, *rotation, WHITE);
        }
    }
    for (int i = 0; i < MAX_BROWN_METEORS; i++)
    {
        if (brownMeteors[i].active)
        {
            // Calcular el punto central
            brownCenter.x = brownMeteors[i].position.x - brownMeteor.width / 2;
            brownCenter.y = brownMeteors[i].position.y - brownMeteor.height / 2;

            // Dibujar textura meteoro girando
            DrawTexturePro(brownMeteor, (Rectangle){0, 0, (float)brownMeteor.width, (float)brownMeteor.height},
                           (Rectangle){brownCenter.x, brownCenter.y, (float)brownMeteor.width, (float)brownMeteor.height},
                           (Vector2){(float)brownMeteor.width / 2, (float)brownMeteor.height / 2}, *rotation, WHITE);
        }
    }
}

// Dibujar monedas y corazones
void drawObjects(Texture2D *coinsTx, Texture2D *heartsTx)
{
    Vector2 coinCenter, heartCenter;

    // Dibujar monedas
    for (int i = 0; i < MAX_COINS; i++)
    {
        if (coinGold[i].active)
        {
            // Calcular la posición del centro de la moneda
            coinCenter.x = coinGold[i].position.x - coinsTx->width / 2;
            coinCenter.y = coinGold[i].position.y - coinsTx->height / 2;
            DrawTextureV(*coinsTx, coinCenter, WHITE);
        }
        if (coinRed[i].active)
        {
            DrawCircle(coinRed[i].position.x, coinRed[i].position.y, COINS_RADIUS, RED);
        }
    }
    // Dibujar corazones
    for (int i = 0; i < MAX_HEARTS; i++)
    {
        if (hearts[i].active)
        {
            // Calcular la posición del centro del corazon
            heartCenter.x = (float)((int)hearts[i].position.x - heartsTx->width / 2);
            heartCenter.y = (float)((int)hearts[i].position.y - heartsTx->height / 2);
            DrawTextureV(*heartsTx, heartCenter, RED);
        }
    }
}

// Dibujar disparos
void drawShots(Texture2D *shotTx, Texture2D *explosionTx)
{
    // Calcular la posición y centro de la bala
    Vector2 shotPos;

    for (int i = 0; i < MAX_SHOTS; i++)
    {
        if (shots[i].active)
        {
            if (!shots[i].collided) // Si no ha habido colisión, dibuja el misil
            {
                shotPos.x = shots[i].position.x - shotTx->width / 2;
                shotPos.y = shots[i].position.y - shotTx->height / 2;
                DrawTextureV(*shotTx, shotPos, WHITE);
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
void Levels(short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives, int *totalseconds, float *timeseconds)
{
    if (*score == 0 && *level == 0)
    {
        // Historia inicial
        subsCinematicas("   INFORME DE ULTIMO MOMENTO                        Hola a todos son las 11:45 am y aqui su servilleta     Javie Alatorre informandolos.", 45, 7, 2, 4, 5);
        subsCinematicas("Desde la NASA nos llega el informe de que se acaba  de descubrir un asteroide con un color amarillo el    cual tiene a los cientificos conmosionados ", 45, 7, 4, 0, 1);
        subsCinematicas("Se rumora que podria contener gran cantidad de oro en su interior y en este momento organizaciones de   todo el mundo estan investigando este suceso ", 45, 7, 4, 0, 1);
        subsCinematicas("  Un momento!  Nos informan que el asteroide acaba   de colisionar contra el cinturon de asteroides", 45, 7, 3, 2, 3);
        subsCinematicas("y efectivamene, contiene gran cantidad de oro, esto deja a las organzaciones en una carrera para ver    quien sera el que se apropie de el ", 45, 7, 4, 2, 3);
        subsCinematicas("Olvidenlo, nos informan que españa es el primer      aventado en ir por el, como dicta la historia oro del que lo tenga oro se lo queda ", 45, 7, 4, 6, 7);
        subsCinematicas("nuestros desarolladores han creado una represent- acion grafica de que es lo que podria estar pasando en este momento aya arriba en el espacio ", 45, 7, 1, 4, 5);

        /* Estadisticas Nivel 1 */
        *level = 1;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV1;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
    }

    if (*score >= 50 && *level == 1)
    {
        // Limpiar objetos
        resetItems(playPosition);
        screenpoints(totalseconds, score);

        subsCinematicas("aqui iria la cinematica de descanso", 45, 7, 1, 0, 1);
        subsCinematicas("continuacion de historia", 45, 7, 2, 0, 1);

        screenlevel("NIVEL 2", 2);

        /* Estadisticas Nivel 2 */
        *level = 2;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV2;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
    }
    // Verificar si el jugador ha alcanzado el nivel 3
    if (*score >= 50 && *level == 2)
    {
        // Limpiar objetos
        resetItems(playPosition);

        screenlevel("NIVEL 3", 2);

        /* Estadisticas Nivel 3 */
        *level = 3;
        *score = 0;
        *lives = 5;
        *elapsedTime = 0.0f;
        *timeseconds = 0;

        MAX_GRAY = MAX_METEOR_LV3;
        // MAX_BROWN =
        // MAX_COIN =
        // MAX_HEART =
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
void screenlevel(const char *text, int seconds)
{
    int tamano = 180;
    double startTime2 = GetTime(); // Obtener el tiempo de inicio

    while (GetTime() - startTime2 < seconds)
    {
        // Limpiar la pantalla y mostrar "Nivel #" en el centro
        ClearBackground(BLACK);
        DrawText(text, SCR_WIDTH / 2 - MeasureText(text, tamano) / 2, (SCR_HEIGHT / 2) - 100, tamano, WHITE);
        EndDrawing();
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
    for (i = 0; i < MAX_GRAY; i++)
    {
        grayMeteors[i].active = false;
    }
    for (i = 0; i < MAX_BROWN_METEORS; i++)
    {
        brownMeteors[i].active = false;
    }
    for (i = 0; i < MAX_COINS; i++) // GOLD COIN
    {
        coinGold[i].active = false;
    }
    for (i = 0; i < MAX_COINS; i++) // RED COIN
    {
        coinRed[i].active = false;
    }
    for (i = 0; i < MAX_HEARTS; i++)
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
void resetStats(short *lives, short *score, short *level, float *timeSeconds)
{
    *lives = 5;
    *score = 0;
    *level = 1;
    *timeSeconds = 0;
    MAX_GRAY = MAX_METEOR_LV1;
}

// Obtiene fecha actual
void obtenerFechaAct(int *dia, int *mes, int *anio)
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
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    Tdata players[MAX_PLAYERS];
    int numPlayers = 0;

    while (fread(&players[numPlayers], sizeof(Tdata), 1, file) == 1)
    {
        numPlayers++;
    }

    fclose(file);

    // Calcular posición y dimensiones de la tabla
    int tableWidth = SCR_WIDTH * 0.6f;   // Porcentaje del ancho de la pantalla
    int tableHeight = SCR_HEIGHT * 0.6f; // Porcentaje del alto de la pantalla
    int tablePosX = (SCR_WIDTH - tableWidth) / 2;
    int tablePosY = (SCR_HEIGHT - tableHeight) / 2;

    int cellWidth = tableWidth / 4;
    int cellHeight = 50;
    int scrollOffset = 0;
    int maxVisibleRows = (tableHeight - 50) / cellHeight; // Calcula el número máximo de filas visibles

    while (!IsKeyPressed(KEY_Q))
    {
        BeginDrawing();
        ClearBackground(BLACK);
        drawTextCenter("HISTORIAL DE JUEGOS", 0, 50, 50, WHITE);
        drawTextCenter("(Q) Volver al menu", 0, 750, 40, RED);

        // Dibujar encabezados de la tabla
        DrawRectangleLines(tablePosX, tablePosY, tableWidth, cellHeight, WHITE);
        DrawText("Name", tablePosX + cellWidth * 0.5f - MeasureText("Name", 20) / 2, tablePosY + 10, 20, YELLOW);
        DrawText("Max Level", tablePosX + cellWidth * 1.5f - MeasureText("Max Level", 20) / 2, tablePosY + 10, 20, YELLOW);
        DrawText("Score", tablePosX + cellWidth * 2.5f - MeasureText("Score", 20) / 2, tablePosY + 10, 20, YELLOW);
        DrawText("Date", tablePosX + cellWidth * 3.5f - MeasureText("Date", 20) / 2, tablePosY + 10, 20, YELLOW);

        // Dibujar cada jugador en la tabla
        for (int i = 0; i < maxVisibleRows; i++)
        {
            int playerIndex = i + scrollOffset;
            if (playerIndex >= 0 && playerIndex < numPlayers)
            {
                // Ajusta las coordenadas de dibujo para dejar un espacio entre el borde superior de la celda y el texto
                float textPosY = tablePosY + cellHeight + cellHeight * i + 10; // Ajusta el valor 10 según sea necesario

                DrawText(players[playerIndex].name, tablePosX + cellWidth * 0.5f - MeasureText(players[playerIndex].name, 20) / 2, textPosY, 20, GREEN);
                DrawText(TextFormat("%d", players[playerIndex].maxLevel), tablePosX + cellWidth * 1.5f - MeasureText(TextFormat("%d", players[playerIndex].maxLevel), 20) / 2, textPosY, 20, GREEN);
                DrawText(TextFormat("%d", players[playerIndex].score), tablePosX + cellWidth * 2.5f - MeasureText(TextFormat("%d", players[playerIndex].score), 20) / 2, textPosY, 20, GREEN);
                DrawText(TextFormat("%d/%d/%d", players[playerIndex].dia, players[playerIndex].mes, players[playerIndex].anio), tablePosX + cellWidth * 3.5f - MeasureText(TextFormat("%d/%d/%d", players[playerIndex].dia, players[playerIndex].mes, players[playerIndex].anio), 20) / 2, textPosY, 20, GREEN);
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
}

void mezclarArray(char **array, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        if (i != j)
        {
            char *temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}
void drawQuestion(bool *mostrarPregunta, Pregunta *preguntas, int numPreguntas)
{
    int indicePregunta = rand() % numPreguntas;
    Pregunta preguntaActual = preguntas[indicePregunta];

    // Hacer una copia de las opciones de respuesta
    char *opcionesBarajadas[4];
    memcpy(opcionesBarajadas, preguntaActual.opciones, sizeof(preguntaActual.opciones));

    mezclarArray(opcionesBarajadas, 4);

    do
    {
        drawTextCenter(preguntaActual.pregunta, 0, 280, 60, YELLOW);
        for (int i = 0; i < 4; i++)
        {
            char opcionLabel = 'A' + i;
            drawTextCenter(TextFormat("%c) %s", opcionLabel, opcionesBarajadas[i]), 0, 400 + i * 60, 45, GREEN);
        }

        for (int i = 0; i < 4; i++)
        {
            if (IsKeyPressed(KEY_A + i))
            {
                if (strcmp(opcionesBarajadas[i], preguntaActual.opciones[preguntaActual.respuestaCorrecta]) == 0)
                {
                    drawTextCenter("¡Correcto!", 0, 650, 45, GREEN);
                }
                else
                {
                    drawTextCenter("¡Incorrecto!", 0, 650, 45, RED);
                }
                *mostrarPregunta = false;
                break; 
            }
        }
        EndDrawing();
    } while (*mostrarPregunta);

    // Espera entre cada pregunta
    secondspause(1.5);
}
void secondspause(float seconds)
{
    double startTime2 = GetTime(); 
    while (GetTime() - startTime2 < seconds)
        ;
}