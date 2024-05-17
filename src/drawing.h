/*------ PROTOTIPOS DE FUNCIONES ------*/
/* MENUs */
void drawMainMenu();
void drawHowToPlay();
void aboutTheGame();

/* INTERFACES */
void drawGameInterface(Texture2D hearts, Texture2D hearthEmpty, Texture2D shieldTx, GameStats *stats, const char *nickname, short shield, int minutes, int seconds);
void drawQuestion(bool *showQuestion, short *racha, short *shield, short *municion, short *lives, short object);
void gameOverInterface(short score, short level);
void DrawScoresTable(const char *filename, bool muteMusic);

/* OBJETOS */
void drawPlayer(Texture2D ship, Texture2D forceF, Vector2 *playerPosition, float *playerRotation, short shield);
void drawMeteor(TGameObject Meteor[], short MAX_METEOR, Texture2D meteorTexture, float rotation);
void drawObject(Texture2D Textura, TGameObject *objects, int MAX_OBJECTS);
void drawShots(Texture2D shotTx, Texture2D *explosionTx);
void drawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

/* PANTALLAS */
void subsCinematicas(const char *text, int tamano, float positionY, int frecuencia, int frame1, int frame2, Texture2D *cinema);
void textQuestion(const char *text, int tamano, float positionY, int frecuencia, Texture2D *fondo);
void esperarTecla();
void screenpoints(int *totalseconds, short *score);
void pausa(int gamepad, Vector2 *playPosition, GameState *gameState, bool gameover);

/*------ DESARROLLO DE LAS FUNCIONES ------*/

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

    DrawText("(M) Apagar Musica", 20, 840, 45, DARKGRAY);
    DrawText("(M) Apagar Musica", 23, 843, 45, YELLOW);

    drawTextCenter("(ESC) Salir", 2, 802, 60, DARKGRAY);
    drawTextCenter("(ESC) Salir", 2, 800, 60, RED);
    EndDrawing();
}

// Dibuja pantalla de como jugar
void drawHowToPlay()
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

// Dibuja pantalla con informacion acerca del juego
void aboutTheGame()
{
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

// Dibuja la interfaz de partida en curso
void drawGameInterface(Texture2D hearts, Texture2D hearthEmpty, Texture2D shieldTx, GameStats *stats, const char *nickname, short shield, int minutes, int seconds)
{
    // Dibuja fondo
    switch (stats->level)
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
    DrawText(TextFormat("Puntos : %04d", stats->score), SCR_WIDTH - 320, 20, 45, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("Nivel : %d", stats->level), 20, 20, 45, WHITE);

    // ******** Dibujar Nombre jugador *********
    float textWidth = MeasureText(TextFormat("Jugador : %s", nickname), 40);
    float posX = (SCR_WIDTH - textWidth) / 2;
    DrawText(TextFormat("Jugador : %s", nickname), posX, 20, 40, YELLOW);

    // Dibuja vidas restantes
    DrawText(TextFormat("Vidas : %d", stats->lives), SCR_WIDTH - 280, SCR_HEIGHT - 130, 50, WHITE);

    DrawText(TextFormat("Racha Aciertos : %d", stats->rachaAciertos), 20, SCR_HEIGHT - 90, 35, WHITE);
    float x;

    for (int i = 0; i < stats->lives; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);
        DrawTexture(hearts, x, SCR_HEIGHT - 65, WHITE);
    }
    for (int i = stats->lives; i < 5; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1);                        // Inicia desde el lado derecho
        DrawTexture(hearthEmpty, x, SCR_HEIGHT - 65, WHITE); // Corazón vacío
    }
    for (int i = 0; i < shield; i++)
    {
        x = SCR_WIDTH - 65 * (i + 1) - 65 * stats->lives;
        DrawTexture(shieldTx, x, SCR_HEIGHT - 70, WHITE);
    }

    // Mostrar estado de los powerups
    DrawText(TextFormat("MUNICION : %02d", stats->totalMunicion), 20, 80, 35, YELLOW);

    // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
    DrawText(TextFormat("%02d:%02d", minutes, seconds), 20, SCR_HEIGHT - 50, 50, WHITE);
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
    char opciones[] = {'Y', 'B', 'A', 'X'};
    Color color[] = {YELLOW, RED, GREEN, BLUE};

    BeginDrawing();
    // subsCinematicas(preguntaActual.pregunta, 45, 200, 7, 0.5, 1, 1, questionTx);
    // DrawTexture(questionTx, 0, 0, WHITE);
    // drawTextCenter(preguntaActual.pregunta, 0, 280, 55, YELLOW);
    textQuestion(preguntaActual.pregunta, 50, 200, 7, &questionTx);
    do
    {

        for (int i = 0; i < 4; i++)
        {
            char opcionLabel = 'A' + i;
            drawTextCenter(TextFormat("      %s  (%c)", opcionesBarajadas[i], opciones[i]), -4, 400 + i * 60, 45, color[i]);
            drawTextCenter(TextFormat("[%c]  %s      ", opcionLabel, opcionesBarajadas[i]), 0, 400 + i * 60, 45, WHITE);
        }

        for (int i = 0; i < 4; i++)
        {
            if (IsKeyPressed(KEY_A + i) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP + i))
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

// Dibuja la interfaz de derrota
void gameOverInterface(short score, short level)
{
    // Fondo
    DrawTexture(gameoverT, 0, 0, WHITE);

    // Dibujar ventana de "Game Over"
    drawTextCenter("FIN DEL JUEGO", 2, 232, 110, WHITE);
    drawTextCenter("FIN DEL JUEGO", 0, 230, 110, RED);

    DrawText(TextFormat("PUNTAJE: %04d", score), SCR_WIDTH / 2 - MeasureText(TextFormat("PUNTAJE: %04i", score), 60) / 2, SCR_HEIGHT / 2 + 10, 60, RAYWHITE);
    DrawText(TextFormat("NIVEL: %1d", level), SCR_WIDTH / 2 - MeasureText(TextFormat("LEVEL: %1i", level), 60) / 2, SCR_HEIGHT / 2 - 50, 60, RAYWHITE);

    drawTextCenter("[ENTER] Jugar de nuevo (START)", 2, 582, 60, LIME);
    drawTextCenter("[ENTER] Jugar de nuevo (START)", 0, 580, 60, GREEN);

    drawTextCenter("[Q] Volver al menu (SELECT)", 2, 662, 60, DARKPURPLE);
    drawTextCenter("[Q] Volver al menu (SELECT)", 0, 660, 60, MAGENTA);

    drawTextCenter("[ESC] Salir", 2, 742, 60, RED);
    drawTextCenter("[ESC] Salir", 0, 740, 60, MAROON);
}

// Dibuja la tabla para mostrar los datos del .dat
void DrawScoresTable(const char *filename, bool muteMusic)
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

    while (!IsKeyPressed(KEY_Q))
    {
        if (!muteMusic)
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
void drawMeteor(TGameObject Meteor[], short MAX_METEOR, Texture2D meteorTexture, float rotation)
{
    Vector2 meteorCenter;

    for (int i = 0; i < MAX_METEOR; i++)
    {
        if (Meteor[i].active)
        {
            // Calculo punto central
            meteorCenter.x = Meteor[i].position.x - meteorTexture.width / 2;
            meteorCenter.y = Meteor[i].position.y - meteorTexture.height / 2;

            // Dibujar textura girando
            DrawTexturePro(meteorTexture, (Rectangle){0, 0, (float)meteorTexture.width, (float)meteorTexture.height},
                           (Rectangle){meteorCenter.x, meteorCenter.y, (float)meteorTexture.width, (float)meteorTexture.height},
                           (Vector2){(float)meteorTexture.width / 2, (float)meteorTexture.height / 2}, rotation, WHITE);
        }
    }
}

// Dibujar monedas y corazones
void drawObject(Texture2D Textura, TGameObject *objects, int MAX_OBJECTS)
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

// Maximo 160 caracteres - tamaño - frecuencia - tiempo - textura - frame1 y frame2
void subsCinematicas(const char *text, int tamano, float positionY, int frecuencia, int frame1, int frame2, Texture2D *cinema)
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

        // Mensaje para saltar cinematica
        DrawText("(S) SKIP", SCR_WIDTH - (250), SCR_HEIGHT - 70, 50, WHITE);
        if (IsKeyPressed(KEY_S))
        {
            return; // Saltar cinematica
        }

        if (cambio)
        {
            DrawTexture(cinema[frame1], 0, 0, WHITE);
        }
        else
        {
            DrawTexture(cinema[frame2], 0, 0, WHITE);
        }

        x = limiteH;
        y = positionY;
        // positionY = (SCR_HEIGHT / 2) * 1.6;

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

}

void textQuestion(const char *text, int tamano, float positionY, int frecuencia, Texture2D *fondo)
{
    int longitud = strlen(text);
    int i, limiteH = 45;
    float x, y;

    for (i = 0; i < longitud; i++)
    {
        BeginDrawing();
        DrawTexture(*fondo, 0, 0, WHITE);

        x = limiteH;
        y = positionY;

        if (IsKeyPressed(KEY_S))
        {
            return;
        }

        for (int j = 0; j <= i; j++)
        {
            if (IsKeyPressed(KEY_S))
            {
                return;
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
    }
}

void esperarTecla()
{
    while (true)
    {
        BeginDrawing();
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))
        {
            break;
        }
        EndDrawing();
    }
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

void pausa(int gamepad, Vector2 *playPosition, GameState *gameState, bool gameover)
{

    if ((IsKeyDown(KEY_P) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) && !gameover)
    {
        do
        {
            drawTextCenter("PAUSA", 0, (SCR_HEIGHT / 2) - 175, 160, YELLOW);
            drawTextCenter("[ENTER] Reanudar partida (START) ", 0, (SCR_HEIGHT / 2), 60, GREEN);
            drawTextCenter("[ESC] Salir al menu (BACK) ", 0, (SCR_HEIGHT / 2) + 100, 60, RED);
            EndDrawing();
            if (IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT) || IsKeyPressed(KEY_ESCAPE))
            {
                resetItems(playPosition);
                *gameState = MAIN_MENU; // salir al menu
                break;
            }
        } while (!IsKeyPressed(KEY_ENTER) && !IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT));
    }
}