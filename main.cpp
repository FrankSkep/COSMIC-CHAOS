#include "src/game.h"      // Funciones del juego
#include "src/resources.h" // Texturas y sonidos

int main()
{
    /*------------- CONSTANTES -------------*/
    const int playRadius = 45;        // Tamaño del jugador
    const float playerSpeed = 15.0f;  // Velocidad del jugador
    const float spawnInterval = 0.2f; // Intervalo de tiempo entre la aparición de objetos

    /*--------------- VARIABLES ---------------*/
    /* ESTADOS DEL JUEGO */
    bool isPlaying = false;
    bool gameOver = false;

    /* JUEGO */
    float elapsedTime = 0.0f, rotationMeteor = 0.0f;
    short int i, score = 0, lives = 5, level = 0;

    /* CRONOMETRO */
    int totalseconds = 0, minutesT = 0, secondsT = 0;
    float timeseconds = 0;

    /*----------- CONFIGURACION VENTANA -----------*/
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "BETA 0.15");
    SetTargetFPS(75);

    /*----------- Carga de texturas -----------*/
    Texture2D menu, game, gameoverT, cinema[8];
    Texture2D shipTextures[6], coinsTx[6], heartsTx[6], heartsFTx[6], heartsETx[6], misil[6], explosionTx[3];
    Texture2D grayMeteor, brownMeteor;
    loadTextures(&menu, &game, &gameoverT, cinema, shipTextures, &grayMeteor, &brownMeteor, coinsTx, heartsTx, heartsFTx, heartsETx, misil, explosionTx);

    /*----------- Carga de sonidos -----------*/
    InitAudioDevice();
    Music gameMusic, gameover;
    Sound soundcoin, shotSound, burstMisil;
    loadSounds(&gameMusic, &gameover, &soundcoin, &shotSound, &burstMisil);

    /*-------- Ajustes texturas cambiantes --------*/
    short currentFrame = 0; // indice de la textura actual
    short currentFrameExp = 0;
    float frameTimeCounter = 0.0f;
    float frameSpeed = 1.0f / 8.0f; // velocidad de cambio de imagen (cada 1/4 de segundo)

    // Posicion jugador
    Vector2 playerPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};
    // Centro nave
    Vector2 shipCenter;
    // Centro meteoros
    Vector2 grayCenter, brownCenter;

    /*------------------------ BUCLE DEL JUEGO ------------------------*/
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F11))
        {
            ToggleFullscreen();
        }

        if (!isPlaying) // Menu principal
        {
            StopMusicStream(gameover); // Detiene musica gameover
            drawMainMenu(&menu);       // Dibuja menu principal

            menuActions(&secondsT, &isPlaying); // Acciones menu
        }
        else
        { /*-------------------- PARTIDA --------------------*/
            if (!gameOver)
            {
                StopMusicStream(gameover); // Detiene musica de gameover
                UpdateMusicStream(gameMusic);
                PlayMusicStream(gameMusic); // Reproduce musica de la partida

                // Calcula y actualiza la posición del centro de la nave
                shipCenter = {playerPosition.x - shipTextures[currentFrame].width / 2, playerPosition.y - shipTextures[currentFrame].height / 2};

                /***** SPRITES *****/
                frameTimeCounter += GetFrameTime();
                // pasado el tiempo, cambia imagen
                if (frameTimeCounter >= frameSpeed)
                {
                    currentFrame = (currentFrame + 1) % 6; // Cambiar al siguiente marco (0, 1, 2, 0, 1, 2, ...)
                    currentFrameExp = (currentFrameExp + 1) % 3;
                    frameTimeCounter = 0.0f; // Reiniciar el contador de tiempo
                }

                /*------------------ CONTROLES ------------------*/
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) // Mover hacia la derecha
                {
                    if (playerPosition.x + playRadius < SCR_WIDTH)
                    {
                        playerPosition.x += playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) // Mover hacia la izquierda
                {
                    if (playerPosition.x - playRadius > 0)
                    {
                        playerPosition.x -= playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) // Mover hacia arriba
                {
                    if (playerPosition.y - playRadius > 0)
                    {
                        playerPosition.y -= playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) // Ajuste para la parte inferior
                {
                    if (playerPosition.y + playRadius < SCR_HEIGHT)
                    {
                        playerPosition.y += playerSpeed;
                    }
                }

                if (IsKeyPressed(KEY_SPACE)) // Dispara misil
                {
                    for (i = 0; i < MAX_SHOTS; i++)
                    {
                        if (!shots[i].active)
                        {
                            shots[i].active = true;
                            shots[i].position = playerPosition; // Posición inicial del disparo
                            PlaySound(shotSound);
                            break;
                        }
                    }
                }

                /*--------------------- GENERACION OBJETOS ---------------------*/
                elapsedTime += GetFrameTime(); // Actualizar temporizador

                if (elapsedTime >= spawnInterval)
                {
                    for (i = 0; i < MAX_GRAY; i++)
                    {
                        if (!grayMeteors[i].active)
                        {
                            InitObject(&grayMeteors[i], &GRAY_METEOR_RADIUS);
                            break;
                        }
                    }
                    for (i = 0; i < MAX_BROWN_METEORS; i++)
                    {
                        if (!brownMeteors[i].active)
                        {
                            InitObject(&brownMeteors[i], &BROWN_METEOR_RADIUS);
                            break;
                        }
                    }
                    for (i = 0; i < MAX_COINS; i++)
                    {
                        if (!coins[i].active)
                        {
                            InitObject(&coins[i], &COINS_RADIUS);
                            break;
                        }
                    }
                    for (i = 0; i < MAX_HEARTS; i++)
                    {
                        if (!hearts[i].active)
                        {
                            InitObject(&hearts[i], &HEARTS_RADIUS);
                            break;
                        }
                    }
                    elapsedTime = 0.0f; // Reiniciar el temporizador
                }

                /*--------------------- FISICAS Y COLISIONES ---------------------*/

                /*----- Meteoro gris -----*/
                for (i = 0; i < MAX_GRAY; i++)
                {
                    if (grayMeteors[i].active)
                    {
                        grayMeteors[i].position.y += GRAY_METEOR_SPEED;
                        if (grayMeteors[i].position.y > SCR_HEIGHT + GRAY_METEOR_RADIUS * 2)
                        {
                            grayMeteors[i].active = false; // Eliminar meteoro al salir de la pantalla
                        }

                        // Detectar colisión con jugador
                        grayCenter = {grayMeteors[i].position.x - grayMeteor.width / 2, grayMeteors[i].position.y - grayMeteor.height / 2};
                        if (CheckCollision(playerPosition, playRadius, grayCenter, GRAY_METEOR_RADIUS))
                        {
                            grayMeteors[i].active = false; // Eliminar objeto tocado
                            lives--;                       // Pierde una vida
                            if (lives <= 0)
                            {
                                gameOver = true;
                            }
                        }
                    }
                }
                // /*----- Meteoro cafe -----*/
                for (i = 0; i < MAX_BROWN_METEORS; i++)
                {
                    if (brownMeteors[i].active)
                    {
                        brownMeteors[i].position.y += BROWN_METEOR_SPEED;
                        if (brownMeteors[i].position.y > SCR_HEIGHT + BROWN_METEOR_RADIUS * 2)
                        {
                            brownMeteors[i].active = false;
                        }

                        // Detectar colisión con jugador
                        brownCenter = {brownMeteors[i].position.x - brownMeteor.width / 2, brownMeteors[i].position.y - brownMeteor.height / 2};
                        if (CheckCollision(playerPosition, playRadius, brownCenter, BROWN_METEOR_RADIUS))
                        {
                            brownMeteors[i].active = false; // Eliminar objeto tocado
                            lives--;                        // Pierde una vida
                            if (lives <= 0)
                            {
                                gameOver = true;
                            }
                        }
                    }
                }
                /*----- Moneda (Incrementador de puntos) -----*/
                for (i = 0; i < MAX_COINS; i++)
                {
                    if (coins[i].active)
                    {
                        coins[i].position.y += COINS_SPEED;
                        if (coins[i].position.y > SCR_HEIGHT + COINS_RADIUS * 2)
                        {
                            coins[i].active = false;
                        }

                        // Detectar colisión con jugador y aumentar el contador de puntos
                        if (CheckCollision(playerPosition, playRadius, coins[i].position, COINS_RADIUS))
                        {
                            coins[i].active = false; // Eliminar objeto tocado
                            score += 10;             // Aumentar el puntaje
                            PlaySound(soundcoin);
                        }
                    }
                }
                /*----- Corazon (Vida adicional) -----*/
                for (i = 0; i < MAX_HEARTS; i++)
                {
                    if (hearts[i].active)
                    {
                        hearts[i].position.y += HEARTS_SPEED;
                        if (hearts[i].position.y > SCR_HEIGHT + HEARTS_RADIUS * 2)
                        {
                            hearts[i].active = false;
                        }

                        // Detectar colisión con jugador y aumentar vidas
                        if (CheckCollision(playerPosition, playRadius, hearts[i].position, HEARTS_RADIUS))
                        {
                            hearts[i].active = false; // Eliminar objeto tocado
                            lives++;                  // Gana una vida
                        }
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
                                shots[i].collided = false; // Volver bandera falsa
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

                            // Comprobar colisión con los meteoros
                            for (int j = 0; j < MAX_GRAY; j++)
                            {
                                if (grayMeteors[j].active)
                                {
                                    // Calcula punto de collision
                                    grayCenter = {grayMeteors[j].position.x - grayMeteor.width / 2, grayMeteors[j].position.y - grayMeteor.height / 2};
                                    // Colision con meteoro gris
                                    if (CheckCollision(shots[i].position, SHOT_RADIUS, grayCenter, GRAY_METEOR_RADIUS))
                                    {
                                        PlaySound(burstMisil);
                                        StopSound(shotSound);
                                        score += 5;
                                        grayMeteors[j].active = false;
                                        shots[i].collided = true;
                                        shots[i].explosionTimer = 0.4f; // Duración de la animación de explosión (0.5 segundos)
                                    }
                                }
                            }

                            for (int j = 0; j < MAX_BROWN_METEORS; j++)
                            {
                                if (brownMeteors[j].active)
                                {
                                    // Calcula punto de collision
                                    brownCenter = {brownMeteors[j].position.x - brownMeteor.width / 2, brownMeteors[j].position.y - brownMeteor.height / 2};
                                    // Colisión con meteoro café
                                    if (CheckCollision(shots[i].position, SHOT_RADIUS, brownCenter, BROWN_METEOR_RADIUS))
                                    {
                                        PlaySound(burstMisil);
                                        StopSound(shotSound);
                                        score += 5;
                                        brownMeteors[j].active = false;
                                        shots[i].collided = true;
                                        shots[i].explosionTimer = 0.5f; // Duración de la animación de explosión (0.5 segundos)
                                    }
                                }
                            }
                        }
                    }
                }
                /*---------------- DIBUJO PARTIDA EN CURSO ---------------*/
                BeginDrawing();

                // Velocidad de rotacion meteoros
                rotationMeteor += 2.5f;

                // Dibujar interfaz de la partida
                drawGameInterface(&game, &heartsTx[currentFrame], &lives, &score, &level);
                // Dibujar objetos de la partida
                drawGameElements(&shipTextures[currentFrame], &shipCenter, &grayMeteor, &brownMeteor, &coinsTx[currentFrame], &heartsTx[currentFrame], &misil[currentFrame], &explosionTx[currentFrameExp], &rotationMeteor);

                /*--------------- ? ---------------*/
                timeseconds += GetFrameTime(); // Obtener el tiempo transcurrido en segundos
                totalseconds = timeseconds;
                minutesT = totalseconds / 60;
                secondsT = totalseconds % 60;
                // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
                DrawText(TextFormat("%02d:%02d", minutesT, secondsT), 20, 20, 100, WHITE);
                /*--------------- ? ---------------*/

                Levels(cinema, &score, &level, &elapsedTime, &playerPosition, &lives, &totalseconds, &timeseconds);
                /*--------------------------------------------------------*/

                if (gameOver)
                {
                    ClearBackground(BLACK);
                    minutesT = 0, secondsT = 0, totalseconds = 0, timeseconds = 0;
                    rotationMeteor = 0;          // Reiniciar rotacion
                    resetItems(&playerPosition); // Reinicia posicion y desactiva objetos

                    StopMusicStream(gameMusic); // Detener musica partida
                    PlayMusicStream(gameover);  // Reproducir musica gameover
                }
            } /*-------------------- FIN DE PARTIDA --------------------*/
            else
            { /*------------------ GAMEOVER ------------------*/
                // Reproducir musica gameover
                UpdateMusicStream(gameover);

                // Dibuja interfaz
                gameOverInterface(&gameoverT, &score, &level);

                // Vuelve a jugar al presionar enter
                if (IsKeyDown(KEY_ENTER))
                {
                    resetStats(&lives, &score, &level, &timeseconds);
                    gameOver = false;
                }
                // Vuelve al menu al presionar Q
                if (IsKeyDown(KEY_Q))
                {
                    resetStats(&lives, &score, &level, &timeseconds);
                    isPlaying = false;
                    gameOver = false;
                }
                /*---------------------------------------------------*/
            }
            DrawFPS(20, SCR_HEIGHT - 40);
            EndDrawing();
        }
    }

    // Descarga de recursos
    unloadTextures(&menu, &game, &gameoverT, cinema, shipTextures, &grayMeteor, &brownMeteor, coinsTx, heartsTx, heartsFTx, heartsETx, misil, explosionTx);
    unloadSounds(&gameMusic, &gameover, &soundcoin, &shotSound, &burstMisil);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
