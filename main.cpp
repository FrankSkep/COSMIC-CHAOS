#include "src/game.h"
#include "src/resources.h"

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
    Texture2D shipTextures[6], coinsTx[6], heartsTx[6];
    loadTextures(&menu, &game, &gameoverT, cinema, shipTextures, coinsTx, heartsTx);

    /*----------- Carga de sonidos -----------*/
    InitAudioDevice();
    Music gameMusic, gameover;
    Sound soundcoin, shotSound;
    loadSounds(&gameMusic, &gameover, &soundcoin, &shotSound);

    /*-------- Ajustes texturas cambiantes --------*/
    short currentFrame = 0; // indice de la textura actual
    float frameTimeCounter = 0.0f;
    float frameSpeed = 1.0f / 8.0f; // velocidad de cambio de imagen (cada 1/4 de segundo)

    // Posicion jugador
    Vector2 playerPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};
    // Centro nave
    Vector2 shipCenter;

    /*------------------------ BUCLE DEL JUEGO ------------------------*/
    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        if (!isPlaying) // Menu principal
        {
            StopMusicStream(gameover); // Detiene musica gameover
            drawMainMenu(&menu);       // Dibuja menu principal

            logicaMenu(&secondsT, &isPlaying); // Acciones menu
        }
        else
        {
            /*-------------------- PARTIDA --------------------*/
            if (!gameOver)
            {
                StopMusicStream(gameover); // Detiene musica de gameover
                UpdateMusicStream(gameMusic);
                PlayMusicStream(gameMusic); // Reproduce musica de la partida

                // Calcula y actualiza la posición del centro de la nave
                shipCenter = {playerPosition.x - shipTextures[currentFrame].width / 2, playerPosition.y - shipTextures[currentFrame].height / 2};

                /***** SPRITES *****/
                frameTimeCounter += GetFrameTime();
                // pasado el tiempo, cambia la imagen de la nave
                if (frameTimeCounter >= frameSpeed)
                {
                    currentFrame = (currentFrame + 1) % 6; // Cambiar al siguiente marco (0, 1, 2, 0, 1, 2, ...)
                    frameTimeCounter = 0.0f;               // Reiniciar el contador de tiempo
                }

                /*------------------ CONTROLES ------------------*/
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                {
                    if (playerPosition.x + playRadius < SCR_WIDTH)
                    {
                        playerPosition.x += playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
                {
                    if (playerPosition.x - playRadius > 0)
                    {
                        playerPosition.x -= playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) // Ajuste para la parte superior
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

                if (IsKeyPressed(KEY_SPACE)) // Activa disparo al pulsar espacio
                {
                    for (i = 0; i < MAX_SHOTS; i++)
                    {
                        if (!shots[i].active)
                        {
                            PlaySound(shotSound);
                            shots[i].active = true;
                            shots[i].position = playerPosition; // Posición inicial del disparo
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
                        if (CheckCollision(playerPosition, playRadius, grayMeteors[i].position, GRAY_METEOR_RADIUS))
                        {
                            grayMeteors[i].active = false; // Eliminar objeto tocado
                            lives--;                      // Pierde una vida
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
                        if (CheckCollision(playerPosition, playRadius, brownMeteors[i].position, BROWN_METEOR_RADIUS))
                        {
                            brownMeteors[i].active = false; // Eliminar objeto tocado
                            lives--;                       // Pierde una vida
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
                            score += 10;            // Aumentar el puntaje
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
                            lives++;                 // Gana una vida
                        }
                    }
                }
                /*----- Disparos -----*/
                for (i = 0; i < MAX_SHOTS; i++)
                {
                    if (shots[i].active)
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
                                if (CheckCollision(shots[i].position, SHOT_RADIUS, grayMeteors[j].position, GRAY_METEOR_RADIUS))
                                {
                                    // Colisión con meteoro gris
                                    StopSound(shotSound);
                                    grayMeteors[j].active = false;
                                    shots[i].active = false;
                                }
                            }
                        }

                        for (int j = 0; j < MAX_BROWN_METEORS; j++)
                        {
                            if (brownMeteors[j].active)
                            {
                                // Colisión con meteoro café
                                if (CheckCollision(shots[i].position, SHOT_RADIUS, brownMeteors[j].position, BROWN_METEOR_RADIUS))
                                {
                                    StopSound(shotSound);
                                    brownMeteors[j].active = false;
                                    shots[i].active = false;
                                }
                            }
                        }
                    }
                }

                /*---------------- DIBUJO PARTIDA EN CURSO ---------------*/
                BeginDrawing();
                // Velocidad de rotacion meteoros
                rotationMeteor += 2.5f;
                gameInterface(&game, &shipTextures[currentFrame], &shipCenter, &coinsTx[currentFrame], &heartsTx[currentFrame], &lives, &score, &rotationMeteor);

                /*--------------- ? ---------------*/
                timeseconds = GetTime(); // Obtener el tiempo transcurrido en segundos
                totalseconds = (int)timeseconds;
                minutesT = totalseconds / 60;
                secondsT = totalseconds % 60;
                // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
                DrawText(TextFormat("%02d:%02d", minutesT, secondsT), 20, 20, 100, WHITE);
                /*--------------- ? ---------------*/

                Levels(cinema, &score, &level, &elapsedTime, &playerPosition, &lives);
                /*--------------------------------------------------------*/

                if (gameOver)
                {
                    minutesT = 0, secondsT = 0, totalseconds = 0, timeseconds = 0;
                    rotationMeteor = 0;          // Reiniciar rotacion
                    resetItems(&playerPosition); // Reinicia posicion y desactiva objetos

                    StopMusicStream(gameMusic); // Detener musica partida
                    PlayMusicStream(gameover);  // Reproducir musica gameover
                }
            } /*-------------------- FIN DE PARTIDA --------------------*/
            else
            { /*------------------ GAMEOVER TRUE ------------------*/
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
    unloadTextures(&menu, &game, &gameoverT, cinema, shipTextures, coinsTx, heartsTx);
    unloadSounds(&gameMusic, &gameover, &soundcoin, &shotSound);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
