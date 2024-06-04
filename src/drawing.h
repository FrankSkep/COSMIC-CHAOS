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

/* OBJETOS DEL JUEGO */
void drawPlayer(Texture2D ship, Texture2D forceF, Vector2 *playerPosition, float *playerRotation, short shield);
void drawMeteor(TGameObject Meteor[], short MAX_METEOR, Texture2D meteorTexture, float rotation);
void drawObject(Texture2D Textura, TGameObject *objects, int MAX_OBJECTS);
void drawShots(Texture2D shotTx, Texture2D *explosionTx);

/* PANTALLAS */
void textQuestion(const char *text, int tamano, float positionY, int frecuencia, Texture2D *fondo);
void postAnimationAns(bool *continuar, int *contin, int *colisionTutorial);
void tutorialShow(int *tuto, int colisionTutorial, int *tutorialActive);
void esperarTecla();

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

    char optionStart[20];
    int gamepad = 0;
    IsGamepadAvailable(gamepad) ? strcpy(optionStart, "Start") : strcpy(optionStart, "Enter");

    // Acciones
    drawTextCenter(TextFormat("(%s) Iniciar", optionStart), 2, 482, 60, LIME);
    drawTextCenter(TextFormat("(%s) Iniciar", optionStart), 0, 480, 60, GREEN);

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

    int yOffset = 270; // Ajuste para comenzar después del título
    int lineHeight = 60; // Altura entre líneas

    DrawText("- Muevete con las flechas o Joystick Fisico", 40, yOffset, 45, WHITE);
    DrawText("- Disparar a los meteoros para conseguir puntos", 40, yOffset + lineHeight, 45, GRAY);
    DrawText("- Gana puntos, vidas y sobrevive", 40, yOffset + 2 * lineHeight, 45, YELLOW);
    DrawText("- Sube de nivel conforme consigues puntos", 40, yOffset + 3 * lineHeight, 45, RED);
    DrawText("- Responde preguntas correctamente para obtener powerups", 40, yOffset + 4 * lineHeight, 45, ORANGE);
    DrawText("- Consulta tu historial de partidas", 40, yOffset + 5 * lineHeight, 45, PURPLE);
    DrawText("- Pausa el juego pulsando la tecla P", 40, yOffset + 6 * lineHeight, 45, DARKGREEN);
    DrawText("(Q) Volver al menu", SCR_WIDTH / 2 - MeasureText("(Q) Volver al menu", 45) / 2, yOffset + 7 * lineHeight + 100, 45, GREEN);

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
    // Dibuja fondo correspondiente al nivel
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

    // Meta puntos
    DrawText(TextFormat("Meta : %04d", PTS_LEVEL_UP), SCR_WIDTH - 320, 60, 45, WHITE);

    // Dibuja nivel
    DrawText(TextFormat("Nivel : %d", stats->level), 20, 20, 45, WHITE);

    // Dibujar Nombre jugador
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

// Dibuja la pregunta y respuestas, y maneja logica de respuesta
void drawQuestion(bool *showQuestion, short *racha, short *shield, short *municion, short *lives, short object)
{
    Tpregunta preguntaActual = preguntas[rand() % PREG_SELEC];

    // Hacer una copia de las opciones de respuesta
    char opcionesBarajadas[4][20];
    memcpy(opcionesBarajadas, preguntaActual.opciones, sizeof(preguntaActual.opciones));
    mezclarArray(opcionesBarajadas, 4);

    char opciones[] = {'Y', 'B', 'A', 'X'};

    Color color[] = {YELLOW, RED, GREEN, BLUE};

    BeginDrawing();
    const int gamepad = 0; // Usamos el primer controlador (índice 0)

    textQuestion(preguntaActual.pregunta, 50, 200, 7, &questionTx);
    do
    {
        for (int i = 0; i < 4; i++)
        {
            char opcionLabel = 'A' + i;
            if (IsGamepadAvailable(gamepad))
            {
                // Cambiar el tamaño de la fuente si la opción está seleccionada
                if (IsKeyPressed(KEY_A + i) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP + i))
                {
                    drawTextCenter(TextFormat("      %s  (%c)", opcionesBarajadas[i], opciones[i]), -4, 400 + i * 60, 45, Fade(BLANK, 0.7f));
                    drawTextCenter(TextFormat("      %s  (%c)", opcionesBarajadas[i], opciones[i]), 0, 400 + i * 60, 55, color[i]);
                }
                else
                {
                    drawTextCenter(TextFormat("      %s  (%c)", opcionesBarajadas[i], opciones[i]), -4, 400 + i * 60, 45, color[i]);
                }
            }
            else
            {
                // Cambiar el tamaño de la fuente si la opción está seleccionada
                if (IsKeyPressed(KEY_A + i))
                {
                    drawTextCenter(TextFormat("[%c]  %s      ", opcionLabel, opcionesBarajadas[i]), 0, 400 + i * 60, 45, Fade(BLANK, 0.7f));
                    drawTextCenter(TextFormat("[%c]  %s      ", opcionLabel, opcionesBarajadas[i]), 7, 400 + i * 60, 55, GREEN);
                }
                else
                {
                    drawTextCenter(TextFormat("[%c]  %s      ", opcionLabel, opcionesBarajadas[i]), 0, 400 + i * 60, 45, WHITE);
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (IsKeyPressed(KEY_A + i) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP + i))
            {
                if (strcmp(opcionesBarajadas[i], preguntaActual.opciones[preguntaActual.respuestaCorrecta]) == 0)
                {
                    drawTextCenter("¡Correcto!", 0, 680, 45, GREEN);
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
                        (*lives) += 2;
                    }
                }
                else
                {
                    *racha = 0;
                    drawTextCenter("¡Incorrecto!", 0, 680, 45, RED);
                    drawTextCenter(TextFormat("La respuesta correcta era: %s", preguntaActual.opciones[preguntaActual.respuestaCorrecta]), 0, 770, 45, WHITE);
                }
                *showQuestion = false;
                break;
            }
        }
        EndDrawing();
    } while (*showQuestion);
    secondspause(1.5);
    ClearBackground(BLACK);
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

    int gamepad = 0;
    char optionPlayAgain[20];
    IsGamepadAvailable(gamepad) ? strcpy(optionPlayAgain, "Start") : strcpy(optionPlayAgain, "Enter");
    drawTextCenter(TextFormat("[%s] Jugar de nuevo", optionPlayAgain), 2, 582, 60, LIME);
    drawTextCenter(TextFormat("[%s] Jugar de nuevo", optionPlayAgain), 0, 580, 60, GREEN);

    char optionBackmenu[20];
    IsGamepadAvailable(gamepad) ? strcpy(optionBackmenu, "Select") : strcpy(optionBackmenu, "Q");
    drawTextCenter(TextFormat("[%s] Volver al menu", optionBackmenu), 2, 662, 60, DARKPURPLE);
    drawTextCenter(TextFormat("[%s] Volver al menu", optionBackmenu), 0, 660, 60, MAGENTA);

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

// Dibuja al jugador
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

// Dibuja los objetos del juego (monedas, corazones, powerups)
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

// Dibuja disparos
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

// Muestra pregunta con texto animado
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

// Animacion despues de responder una pregunta
void postAnimationAns(bool *continuar, int *contin, int *colisionTutorial)
{
    // Animacion despues de responder pregunta
    if (*continuar)
    {
        if (*contin == 5)
        {
            PlaySound(soundcoin);
            PlaySound(soundcoin);
            screenMessage("¡GO!", 0.5, BLANK, WHITE, 180);
            *contin = 0;
            *continuar = false;
        }
        if (*contin == 4)
        {
            PlaySound(soundcoin);
            screenMessage("1", 0.7, BLANK, WHITE, 180);
            *contin = 5;
        }
        if (*contin == 3)
        {
            PlaySound(soundcoin);
            screenMessage("2", 0.7, BLANK, WHITE, 180);
            *contin = 4;
        }
        if (*contin == 2)
        {
            if (*colisionTutorial)
            {
                textQuestion("", 100, 0, 0, &tutotx);
                subsCinematicas("ACABAS DE CHOCAR CON UNO DE LOS POWER UPS                                           ", 40, SCR_HEIGHT - 300, 12, 10, 11);
                subsCinematicas("SI RESPONDES BIEN A LA PREGUNTA LO OBTENDRAS                                        ", 40, SCR_HEIGHT - 250, 12, 10, 11);
                secondspause(1);
                *colisionTutorial = 0;
            }
            PlaySound(soundcoin);
            screenMessage("3", 0.7, BLANK, WHITE, 180);
            *contin = 3;
        }
        if (*contin == 1)
        {
            *contin = 2;
        }
    }
}

// Esperar pulsacion
void esperarTecla()
{
    float axisX,axisY;
    while (true)
    {
        BeginDrawing();

        axisX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        axisY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        // Expresiones logicas de pulsacion de teclas
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)||axisX > 0.1f||axisX < -0.1f||axisY < -0.1f|| axisY > 0.1f)
        {
            break;
        }
        EndDrawing();
    }
}

// Mostrar tutorial interactivo
void tutorialShow(int *tuto, int colisionTutorial, int *tutorialActive)
{
    (*tuto)++;
    switch (*tuto)
    {
    case 5:
        DrawTexture(tutotx, 0, 0, WHITE);
        textQuestion("hola gran viajero bienvenido a \"COSMIC-CAOS\" ", 40, SCR_HEIGHT - 300, 3, &tutotx1);
        secondspause(4);
        break;
    case 8:
        subsCinematicas("Utiliza las FLECHAS de tu teclado o el JOYSTICK          izquierdo ", 40, SCR_HEIGHT - 300, 12, 0, 1);
        secondspause(0.1);
        subsCinematicas("             para moverte en la direccion que deses Y      ATRAPAR ESAS MONEDAS                                                          ", 40, SCR_HEIGHT - 250, 12, 0, 1);
        esperarTecla();
        break;
    case 70:
        textQuestion("PERO NO TAN RAPIDO ", 40, SCR_HEIGHT - 300, 3, &tutotx1);
        secondspause(1);
        subsCinematicas("TIENES QUE SABER QUE ESOS METEORITOS PODRIAN    CHOCAR CONTIGO                                                                              ", 40, SCR_HEIGHT - 250, 12, 2, 3);
        secondspause(1);
        break;
    case 73:
        subsCinematicas("AL COLISIONAR CON ELLOS BAJARA TUS CORAZONES                                                        ", 40, SCR_HEIGHT - 300, 12, 6, 7);
        subsCinematicas("PUEDES TOMAR UNAS DE LAS VIDAS QUE CAEN PARA     PODER SOBREVIVIR MAS TIEMPO                   ", 40, SCR_HEIGHT - 250, 12, 6, 7);
        secondspause(4);
        break;
    case 260:
        if (colisionTutorial)
        {
            textQuestion("VAS BIEN YA TE ESTAS ADAPTANDO ", 40, SCR_HEIGHT - 300, 3, &tutotx1);
            secondspause(2);
            textQuestion("VEAMOS QUE PASA SI CAPTURAS UNO DE ESOS OBJETOS AZULES ", 40, SCR_HEIGHT - 250, 3, &tutotx1);
            secondspause(2);
        }
        break;
    case 500:
        subsCinematicas(" PRESIONA [ESPACIO] PARA PROTEGERTE DE LOS          METEOROS CON LOS MISILES QUE TIENES             ", 40, SCR_HEIGHT - 300, 12, 8, 9);
        secondspause(2);

        break;
    case 1501:
        for (int i = 0; i < totalcinema; i++)
        {
            UnloadTexture(cinema[i]);
        }
        tutorialActive = 0;
        break;
    default:
        break;
    }
}