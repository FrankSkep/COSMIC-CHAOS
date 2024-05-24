#include "raylib.h"
#include "src/elements.h"  // Struct, Enum y Constantes
#include "src/resources.h" // Carga texturas y sonidos
#include "src/game.h"      // Funciones logica del juego
#include "src/drawing.h"   // Funciones de dibujo

int main()
{
    srand(time(NULL));
    selecNpreguntas();

    // Configuración de la ventana
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "BETA 0.9.6.1");
    SetTargetFPS(75);

    // Carga de texturas y sonidos
    loadTextures();
    InitAudioDevice();
    loadSounds();

    // Jugador
    Tdata data = getDataPlayer();          // Entrada de datos
    GameStats stats = {5, 0, 0, 0, 10, 0}; // Inicializacion de estadisticas

    /*------------- Constantes -------------*/
    const int playRadius = 45;                      // Tamaño del jugador
    const float playerSpeed = 15.0f;                // Velocidad del jugador
    const float rotationSpeed = 2.0;                // Velocidad de rotacion
    const float maxRotation = 20.0f;                // Máxima rotación hacia la derecha
    const float minRotation = -20.0f;               // Máxima rotación hacia la izquierda
    const float rotationInterpolationSpeed = 50.0f; // Definir la velocidad de interpolación para volver a la posición original
    const float spawnInterval = 0.2f;               // Intervalo de tiempo entre la aparición de objetos
    const float spawnIntervalPU = 1.2f;             // Intervalo entre aparicion de powerUps

    // Variables del juego
    bool gameOver = false;
    short i, shieldActive = 0, object;
    float elapsedTime1 = 0.0f, elapsedTime2 = 0.0f, rotationMeteor = 0.0f;
    float playerRotation = 0.0f;
    float currentRotation = 0.0f;
    float targetRotation = 0.0f;

    // Variables del cronómetro
    int totalseconds = 0, minutesT = 0, secondsT = 0;
    float timeseconds = 0;
    int tuto = 0, tutorialActive = 1, colisionTutorial = 1; // segundo y tercero = 1

    // Descomentar esto para no mostrar tutorial, para pruebas
    tutorialActive = !tutorialActive;
    colisionTutorial = !colisionTutorial;

    // Variables para sprites
    short currentFrame = 0;         // Índice de textura actual (0, 5)
    short currentFrameExp = 0;      // Índice de textura actual (0, 2)
    float frameTimeCounter = 0.0f;  // Contador de cuadro
    float frameSpeed = 1.0f / 8.0f; // Velocidad de cambio de imagen

    // Posición centrada del jugador
    Vector2 playerPosition = {
        (float)SCR_WIDTH / 2 - shipTx[currentFrame].width / 2,
        (float)SCR_HEIGHT / 1.1f - shipTx[currentFrame].height / 2};

    // Centro de textura de meteoros
    Vector2 grayCenter, brownCenter;

    // Variables de estado
    bool saveProgress = false; // Bandera para guardar estadísticas en archivo
    bool showQuestion = false; // Bandera para mostrar pregunta
    bool continuar = false;    // Bandera para manejar animacion después de pregunta
    int contin = 0;            // Frame de la animacion
    bool muteMusic = false;    // Bandera para desactivar musica
    int showTutorial = 0;      // Bandera para mostrar tutorial inicial

    // Estado inicial del juego
    GameState gameState = MAIN_MENU;
    int keyOption; // Lee tecla opcion del jugador

    // Configuracion para mando fisico - joystick
    float axisX, axisY;
    int gamepad = 0;

    // Movimiento del jugador
    bool rightPressed, leftPressed, upPressed, downPressed;

    /*------------------------ BUCLE DEL JUEGO ------------------------*/
    while (!WindowShouldClose())
    {
        // Actualizar estado del juego
        updateGameState(&gameState, keyOption, &stats, &muteMusic, &playerPosition);
        keyOption = -1; // Reiniciar valor de tecla

        // Actualizar estado de la musica
        updateMusic(gameState, muteMusic);

        // Mostrar tutorial solo la primera vez que abre el juego
        // showTutorial = !saveProgress && (access("resources/record.dat", F_OK) == -1);
        // tutorialActive = colisionTutorial = showTutorial ? 1 : 0;

        // ESTADOS DEL JUEGO
        switch (gameState)
        {
        case MAIN_MENU:
            drawMainMenu();
            keyOption = GetKeyPressed();
            break;

        case HOW_TO_PLAY:
            drawHowToPlay();
            keyOption = GetKeyPressed();
            break;

        case ABOUT_GAME:
            aboutTheGame();
            keyOption = GetKeyPressed();
            break;

        case HISTORY_SCORE:
            DrawScoresTable("resources/record.dat", muteMusic);
            keyOption = GetKeyPressed();
            break;

        case IN_GAME:
            gameOver = false;

            /***** SPRITES *****/
            frameTimeCounter += GetFrameTime();
            // Pasado el tiempo, cambia imagen
            if (frameTimeCounter >= frameSpeed)
            {
                currentFrame = (currentFrame + 1) % 6;       // Cambiar entre 0, 1, 2, 3, 4, 5
                currentFrameExp = (currentFrameExp + 1) % 3; // Cambiar entre 0, 1, 2
                frameTimeCounter = 0.0f;                     // Reiniciar el contador de tiempo
            }

            /*------------------ CONTROLES ------------------*/
            // Obtener el movimiento del joystick izquierdo
            axisX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
            axisY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);

            /*------------------ CONTROLES ------------------*/

            rightPressed = IsKeyDown(KEY_RIGHT) || axisX > 0.1f;
            leftPressed = IsKeyDown(KEY_LEFT) || axisX < -0.1f;
            upPressed = IsKeyDown(KEY_UP) || axisY < -0.1f;
            downPressed = IsKeyDown(KEY_DOWN) || axisY > 0.1f;

            if (rightPressed)
            {
                if (playerPosition.x + playRadius < SCR_WIDTH)
                {
                    playerPosition.x += playerSpeed;
                    currentRotation = fmin(currentRotation + rotationSpeed, maxRotation);
                }
            }
            if (leftPressed)
            {
                if (playerPosition.x - playRadius > 0)
                {
                    playerPosition.x -= playerSpeed;
                    currentRotation = fmax(currentRotation - rotationSpeed, minRotation);
                }
            }

            if (upPressed)
            {
                if (playerPosition.y - playRadius > 0)
                {
                    playerPosition.y -= playerSpeed;
                }
            }

            if (downPressed)
            {
                if (playerPosition.y + playRadius < SCR_HEIGHT)
                {
                    playerPosition.y += playerSpeed;
                }
            }

            // Interpolar la rotación de vuelta a la posición original cuando se suelta la tecla
            if (!rightPressed && !leftPressed)
            {
                if (fabs(axisX) < 0.1f)
                {
                    // Si la rotación actual no es igual a la rotación objetivo, interpola hacia la rotación objetivo
                    if (currentRotation != targetRotation)
                    {
                        float deltaRotation = rotationInterpolationSpeed * GetFrameTime();

                        if (currentRotation < targetRotation)
                        {
                            currentRotation += deltaRotation;
                            if (currentRotation > targetRotation)
                            {
                                currentRotation = targetRotation;
                            }
                        }
                        else
                        {
                            currentRotation -= deltaRotation;
                            if (currentRotation < targetRotation)
                            {
                                currentRotation = targetRotation;
                            }
                        }
                    }
                }
            }

            // Actualizar la rotación del jugador
            playerRotation = currentRotation;

            // Disparo de misil
            if (IsKeyPressed(KEY_SPACE) || IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
            {
                for (int i = 0; i < MAX_SHOTS; i++)
                {
                    if (!shots[i].active)
                    {
                        if (stats.totalMunicion > 0)
                        {
                            shots[i].active = true;
                            shots[i].position = playerPosition; // Posición inicial del disparo
                            PlaySound(shotSound);
                            stats.totalMunicion--;
                            break;
                        }
                    }
                }
            }

            /*--------------------- GENERACION OBJETOS ---------------------*/
            elapsedTime1 += GetFrameTime();
            elapsedTime2 += GetFrameTime();
            if (elapsedTime1 >= spawnInterval)
            {
                generateObjects(grayMeteors, MAX_GRAY, GRAY_METEOR_RADIUS);

                generateObjects(brownMeteors, MAX_BROWN, BROWN_METEOR_RADIUS);

                generateObjects(coinGold, MAX_COINS, COINS_RADIUS);

                generateObjects(hearts, MAX_HEART, HEARTS_RADIUS);

                elapsedTime1 = 0.0f; // Reiniciar el temporizador
            }
            if (elapsedTime2 >= spawnIntervalPU)
            {
                generateObjects(shieldB, MAX_OBJECT, COINS_RADIUS);

                generateObjects(municiones, MAX_OBJECT, COINS_RADIUS);
                elapsedTime2 = 0.0f; // Reiniciar el temporizador
            }

            /*--------------------- FISICAS Y COLISIONES ---------------------*/
            if (objectColision(grayMeteors, MAX_GRAY, GRAY_METEOR_SPEED, GRAY_METEOR_RADIUS, &playerPosition, playRadius, &grayMeteor, true))
            {
                if (shieldActive <= 0)
                {
                    stats.lives--; // Pierde una vida
                    if (stats.lives <= 0)
                    {
                        gameOver = true;
                    }
                }
                else
                {
                    shieldActive--;
                }
            }
            if (objectColision(brownMeteors, MAX_BROWN, BROWN_METEOR_SPEED, BROWN_METEOR_RADIUS, &playerPosition, playRadius, &brownMeteor, true))
            {
                if (shieldActive <= 0)
                {
                    stats.lives--; // Pierde una vida
                    if (stats.lives <= 0)
                    {
                        gameOver = true;
                    }
                }
                else
                {
                    shieldActive--;
                }
            }
            /*----- Moneda (Incrementador de puntos) -----*/
            if (objectColision(coinGold, MAX_COINS, COINS_SPEED, COINS_RADIUS, &playerPosition, playRadius, &coinsTx[currentFrame], false))
            {
                stats.score += 10; // Aumentar el puntaje
                PlaySound(soundcoin);
            }
            // Caja de municion
            if (objectColision(shieldB, MAX_OBJECT, SHIELD_SPEED, COINS_RADIUS, &playerPosition, playRadius, &shield, false))
            {
                object = 1;
                showQuestion = true;
                PlaySound(soundcoin);
            }
            if (objectColision(municiones, MAX_OBJECT, AMMO_SPEED, COINS_RADIUS, &playerPosition, playRadius, &ammoTx, false))
            {
                object = 2;
                showQuestion = true;
                PlaySound(soundcoin);
            }
            /*----- Corazon (Vida adicional) -----*/
            if (objectColision(hearts, MAX_HEART, HEARTS_SPEED, HEARTS_RADIUS, &playerPosition, playRadius, &heartsTx[currentFrameExp], false))
            {
                if (stats.lives < 5)
                {
                    stats.lives++; // Gana una vida
                }
            }

            /*----- Disparos -----*/
            for (i = 0; i < MAX_SHOTS; i++)
            {
                if (shots[i].active)
                {
                    if (shots[i].collided)
                    {
                        // Disminuir el temporizador de la explosión
                        shots[i].explosionTimer -= GetFrameTime();

                        if (shots[i].explosionTimer <= 0)
                        {
                            // Desactivar el disparo después de la animación de explosión
                            shots[i].active = false;
                            shots[i].collided = false;
                        }
                    }
                    else
                    {
                        // Mover el disparo hacia arriba
                        shots[i].position.y -= SHOT_SPEED * GetFrameTime();

                        // Comprobar si el disparo está fuera de la pantalla y desactivarlo
                        if (shots[i].position.y < 0)
                        {
                            shots[i].active = false;
                        }

                        for (int j = 0; j < MAX_GRAY; j++)
                        {
                            if (grayMeteors[j].active)
                            {
                                // Calcula punto de collision
                                grayCenter.x = grayMeteors[j].position.x - grayMeteor.width / 2;
                                grayCenter.y = grayMeteors[j].position.y - grayMeteor.height / 2;
                                //  Colision con meteoro gris
                                if (CheckCollision(&shots[i].position, SHOT_RADIUS, &grayCenter, GRAY_METEOR_RADIUS))
                                {
                                    PlaySound(burstShotSound);
                                    StopSound(shotSound);
                                    stats.score += 5;
                                    grayMeteors[j].active = false;
                                    shots[i].collided = true;
                                    shots[i].explosionTimer = 0.4f; // Duracion animacion de explosión (0.4 segundos)
                                }
                            }
                        }
                        for (int j = 0; j < MAX_BROWN; j++)
                        {
                            if (brownMeteors[j].active)
                            {
                                // Calcula punto de collision
                                brownCenter.x = brownMeteors[j].position.x - brownMeteor.width / 2;
                                brownCenter.y = brownMeteors[j].position.y - brownMeteor.height / 2;
                                //  Colisión con meteoro café
                                if (CheckCollision(&shots[i].position, SHOT_RADIUS, &brownCenter, BROWN_METEOR_RADIUS))
                                {
                                    PlaySound(burstShotSound);
                                    StopSound(shotSound);
                                    stats.score += 5;
                                    brownMeteors[j].active = false;
                                    shots[i].collided = true;
                                    shots[i].explosionTimer = 0.4f; // Duracion animacion de explosión (0.4 segundos)
                                }
                            }
                        }
                    }
                }
            }
            rotationMeteor += 2.5f; // Velocidad de rotacion meteoros

            /*---------------- DIBUJO PARTIDA EN CURSO ---------------*/
            BeginDrawing();

            // Dibujar interfaz de la partida
            drawGameInterface(hearthF[currentFrameExp], hearthE[currentFrame], shield, &stats, data.name, shieldActive, minutesT, secondsT); // Dibujar objetos de la partida

            // Dibuja jugador (nave)
            drawPlayer(shipTx[currentFrameExp], forceF[currentFrame], &playerPosition, &playerRotation, shieldActive);

            // Dibuja meteoros
            drawMeteor(grayMeteors, MAX_GRAY, grayMeteor, rotationMeteor);
            drawMeteor(brownMeteors, MAX_GRAY, brownMeteor, rotationMeteor);

            // Dibuja monedas, corazones y powerUps
            drawObject(coinsTx[currentFrame], coinGold, MAX_COINS);
            drawObject(heartsTx[currentFrameExp], hearts, MAX_HEART);
            drawObject(ballE[currentFrameExp], shieldB, MAX_OBJECT);
            drawObject(ammoTx, municiones, MAX_OBJECT);

            // Dibuja misiles
            drawShots(misil, &explosionTx[currentFrameExp]);

            // Animacion despues de responder pregunta
            if (continuar)
            {
                if (contin == 5)
                {
                    PlaySound(soundcoin);
                    PlaySound(soundcoin);
                    screenMessage("¡GO!", 0.5, BLANK, WHITE, 180);
                    contin = 0;
                    continuar = false;
                }
                if (contin == 4)
                {
                    PlaySound(soundcoin);
                    screenMessage("1", 0.7, BLANK, WHITE, 180);
                    contin = 5;
                }
                if (contin == 3)
                {
                    PlaySound(soundcoin);
                    screenMessage("2", 0.7, BLANK, WHITE, 180);
                    contin = 4;
                }
                if (contin == 2)
                {
                    if (colisionTutorial)
                    {
                        textQuestion("", 100, 0, 0, &tutotx);
                        subsCinematicas("ACABAS DE CHOCAR CON UNO DE LOS POWER UPS                                           ", 40, SCR_HEIGHT - 300, 12, 10, 11);
                        subsCinematicas("SI RESPONDES BIEN A LA PREGUNTA LO OBTENDRAS                                        ", 40, SCR_HEIGHT - 250, 12, 10, 11);
                        secondspause(1);
                        colisionTutorial = 0;
                    }
                    PlaySound(soundcoin);
                    screenMessage("3", 0.7, BLANK, WHITE, 180);
                    contin = 3;
                }
                if (contin == 1)
                {
                    contin = 2;
                }
            }

            if (showQuestion) // Si tomo moneda de pregunta
            {
                drawQuestion(&showQuestion, &stats.rachaAciertos, &shieldActive, &stats.totalMunicion, &stats.lives, object);
                continuar = true;
                contin = 1;
            }

            if (tutorialActive) // ESTO IRA EN FUNCIO TRANQUI CORNEJO
            {
                tutorialShow(&tuto, colisionTutorial, &tutorialActive);
            }

            /*-------- TIEMPO TRANSCURRIDO --------*/
            timeseconds += GetFrameTime(); // Obtener el tiempo transcurrido en segundos
            totalseconds = timeseconds;
            minutesT = totalseconds / 60;
            secondsT = totalseconds % 60;
            Levels(&stats, &elapsedTime1, &playerPosition, &totalseconds);

            if (gameOver)
            {
                DrawTexture(tutotx, 0, 0, BLACK);
                DrawTexture(tutotx, 0, 0, BLACK);
                screenMessage("TE QUEDASTE SIN VIDAS", 1, BLANK, RED, 100);
                ClearBackground(BLACK);
                screenpoints(totalseconds, stats.score);

                minutesT = 0, secondsT = 0, totalseconds = 0;
                rotationMeteor = 0;          // Reiniciar rotacion
                resetItems(&playerPosition); // Reinicia posicion y desactiva objetos

                saveProgress = true; // Al terminar almenos un juego, ya puede guardar progreso

                // Actualizar mejor puntaje
                if (stats.score > data.score)
                {
                    data.score = stats.score;
                }
                // Actualizar maximo nivel alcanzado
                if (stats.level > data.maxLevel)
                {
                    data.maxLevel = stats.level;
                }
                // Actualizar maxima racha de respuestas correctas
                if (stats.rachaAciertos > data.rachaAciertos)
                {
                    data.rachaAciertos = stats.rachaAciertos;
                }

                if (!muteMusic)
                {
                    StopMusicStream(gameMusic); // Detener musica partida
                    PlayMusicStream(gameover);  // Reproducir musica gameover
                }
                gameState = GAME_OVER;
            }
            EndDrawing();
            break;

        case PAUSE:
            BeginDrawing();
            drawTextCenter("PAUSA", 0, (SCR_HEIGHT / 2) - 175, 160, YELLOW);
            drawTextCenter("[ENTER] Reanudar partida (START) ", 0, (SCR_HEIGHT / 2), 60, GREEN);
            drawTextCenter("[Q] Salir al menu (BACK) ", 0, (SCR_HEIGHT / 2) + 100, 60, RED);
            EndDrawing();
            keyOption = GetKeyPressed();
            break;

        case GAME_OVER:
            // Dibuja interfaz
            BeginDrawing();
            gameOverInterface(stats.score, stats.level);
            EndDrawing();

            keyOption = GetKeyPressed();
            break;
        }
    }

    // Guardar estadisticas en archivo record.dat
    if (saveProgress)
    {
        appendScoresToFile("resources/record.dat", data);
    }
    // Descarga de recursos
    unloadTextures();
    unloadSounds();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
