#include <stdbool.h>
#include <string.h>

/*--------------------- PROTOTIPOS FUNCIONES ---------------------*/
/* MENUs */
void loadingScreen();
void drawMainMenu();
void drawHowToPlay();
void aboutTheGame();
void menuActions(int *seconds, bool *isPlaying);

/* INTERFACES */
void drawGameInterface(Texture2D *hearts, short *lives, short *score, short *level, const char *nickname);
void ingresarTexto(char *inputText);
void drawGameElements(Texture2D *ship, Vector2 *shipPosicion, Texture2D *coinGold, Texture2D *hearts, Texture2D *shotTx, Texture2D *explosionTx, float *rotation, Vector2 *playerPosition, float *playerRotation);
void gameOverInterface(short *score, short *level);

/* DIBUJO OBJETOS */
void drawPlayer(Texture2D *ship, Vector2 *playerPosition, float *playerRotation);
void drawMeteors(float *rotation);
void drawObjects(Texture2D *coinsTx, Texture2D *heartsTx);
void drawShots(Texture2D *shotTx, Texture2D *explosionTx);
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

/* LOGICA */
void InitObject(GameObject *object, const float *objRadius);
bool CheckCollision(Vector2 playerPos, float playerRadius, Vector2 ballPos, float meteorRadius);

void Levels(short *score, short *level, float *elapsedTime, Vector2 *playPosition, short *lives, int *totalseconds, float *timeseconds);
void subsCinematicas(const char *text, int tamano, int frecuencia, float seconds, int frame1, int frame2);
void pausa();
void screenlevel(const char *text, int seconds);
void screenpoints(int *totalseconds, short *score);

void resetItems(Vector2 *playPosition);
void resetStats(short *lives, short *score, short *level, float *timeSeconds);

/*-------------------- DESARROLLO DE FUNCIONES --------------------*/

void loadingScreen()
{
    BeginDrawing();
    const char texto[] = "Cargando...";
    const int tam = 80;
    ClearBackground(BLACK);
    DrawText(texto, SCR_WIDTH / 2 - MeasureText(texto, tam) / 2, (SCR_HEIGHT / 2) - 100, tam, WHITE);
    EndDrawing();
}

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
        DrawTexture(cinema[8], 400, 280, WHITE);

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
}

// Dibuja la interfaz de partida en curso
void drawGameInterface(Texture2D *hearts, short *lives, short *score, short *level, const char *nickname)
{
    // Dibuja fondo
    DrawTexture(game, 0, 0, WHITE);

    // Dibuja puntaje
    DrawText(TextFormat("SCORE : %04i", *score), SCR_WIDTH - 363, 20, 50, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("LEVEL : %i", *level), SCR_WIDTH - 1560, 20, 50, WHITE);

    // ******** Dibujar Nombre jugador *********
    // Obtener el ancho del texto
    float textWidth = MeasureText(TextFormat("PLAYER : %s", nickname), 40);
    // Calcular la posición horizontal centrada
    float posX = (SCR_WIDTH - textWidth) / 2;
    // Dibujar el texto centrado
    DrawText(TextFormat("PLAYER : %s", nickname), posX, 20, 40, YELLOW);

    // Dibuja vidas restantes
    float x;
    DrawText(TextFormat("LIVES : %d", *lives), SCR_WIDTH - 280, SCR_HEIGHT - 130, 50, WHITE);
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

void ingresarTexto(char *inputText)
{
    // Dibujar
    BeginDrawing();

    ClearBackground(BLACK);

    // Dibujar el texto de bienvenida centrado
    DrawText("Bienvenido a Cosmic Chaos", (SCR_WIDTH - MeasureText("Bienvenido a Cosmic Chaos", 70)) / 2, 100, 70, GREEN);

    // Dibujar el mensaje para solicitar al usuario que ingrese texto
    DrawText("Ingrese su nombre de usuario:", (SCR_WIDTH - MeasureText("Ingresa tu nombre de usuario:", 40)) / 2 - 50, SCR_HEIGHT / 2, 40, GREEN);

    // Centrar el cuadro de entrada de texto horizontalmente
    float inputBoxX = (SCR_WIDTH - 400) / 2;

    // Dibujar el cuadro de entrada de texto
    DrawRectangleLines(inputBoxX, SCR_HEIGHT / 2 + 50, 400, 60, WHITE);
    DrawText(inputText, inputBoxX + 10, SCR_HEIGHT / 2 + 60, 40, WHITE);

    EndDrawing();
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
        // screenpoints(totalseconds, score);

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
        double startTime = GetTime();
        while (GetTime() - startTime < 0.001) // Tiempo de espera entre iteracion
        {
        } // Esperar
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
    double startTime2 = GetTime();
    while (GetTime() - startTime2 < 2)
        ;
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
    for (i = 0; i < MAX_COINS; i++)
    {
        coinGold[i].active = false;
    }
    for (i = 0; i < MAX_COINS; i++)
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