#include "src/game.h"

int main(void)
{
    /******** VARIABLES *********/
    const int playRadius = 45;     // tamaño del jugador
    const float ballSpeed = 15.0f; // velocidad del jugador
    bool gameOver = false;         // controla gameover
    bool istutorial = false;       // INICIAR EN TUTORIAL
    bool isPlaying = false;        // determina si esta en juego
    float elapsedTime = 0.0f;
    const float spawnInterval = 0.3f; // Intervalo de tiempo entre la aparición de esferas verdes
    float rotation = 0.0f;
    int score = 0; // inicio del puntaje
    int lives = 5; // vidas
    int level = 1; // inicio nivel

    InitWindow(SCR_WIDTH, SCR_HEIGHT, "BETA 0.10"); 
    SetTargetFPS(75);

    /************** Texturas **************/
    // Fondo menu principal;
    Texture2D menu = LoadTexture("resources/images/menu.png");

    // Fondo partida
    Texture2D game = LoadTexture("resources/images/game.png");

    // Fondo gameover
    Texture2D gameoverT = LoadTexture("resources/images/gameover.png");

    // Nave
    Texture2D shipTextures[] =
        {
            LoadTexture("resources/images/nave_01.png"),
            LoadTexture("resources/images/nave_02.png"),
            LoadTexture("resources/images/nave_03.png")};
    int currentFrame = 0; // indice de la textura actual
    float frameTimeCounter = 0.0f;
    float frameSpeed = 1.0f / 4.0f; // velocidad de cambio de imagen (cada 1/4 de segundo)

    /************** Inicializar audio **************/
    InitAudioDevice();
    Music gameMusic = LoadMusicStream("resources/sounds/music.mp3");
    Music gameover = LoadMusicStream("resources/sounds/gameover.mp3");

    /*************** BUCLE DEL JUEGO ***************/
    while (!WindowShouldClose())
    {
        // Calcula y actualiza la posición del centro de la nave
        Vector2 shipCenter = {playPosition.x - shipTextures[currentFrame].width / 2, playPosition.y - shipTextures[currentFrame].height / 2};

        if (istutorial)
        {
            Tutorial();
            if (IsKeyPressed(KEY_Q))
            {
                istutorial = false;
            }
        }
        else
        {
            if (!isPlaying) // Si isPlaying es falso vuelve al menu principal
            {
                drawMainMenu(menu);        // Muestra menu principal
                StopMusicStream(gameover); // Detiene musica

                if (IsKeyPressed(KEY_ENTER))
                {
                    isPlaying = true;
                }
                if (IsKeyPressed(KEY_A))
                {
                    istutorial = true;
                }
            }
            else
            {
                Levels(&score, &level, &elapsedTime, &playPosition);
                UpdateMusicStream(gameMusic);

                /***** SPRITE NAVE *****/
                frameTimeCounter += GetFrameTime();
                // pasado el tiempo, cambia la imagen de la nave
                if (frameTimeCounter >= frameSpeed)
                {
                    currentFrame = (currentFrame + 1) % 3; // Cambiar al siguiente marco (0, 1, 2, 0, 1, 2, ...)
                    frameTimeCounter = 0.0f;               // Reiniciar el contador de tiempo
                }
                // Dibujar la nave con la textura actual
                DrawTexture(shipTextures[currentFrame], playPosition.x, playPosition.y, WHITE);

                // Velocidad de rotacion meteoros
                rotation += 1.5f;

                if (!gameOver)
                {
                    StopMusicStream(gameover);  // Detiene musica de gameover
                    PlayMusicStream(gameMusic); // Reproduce musica de la partida

                    elapsedTime += GetFrameTime(); // Actualizar temporizador

                    // Control del jugador
                    if (IsKeyDown(KEY_RIGHT) && playPosition.x + playRadius < SCR_WIDTH)
                    {
                        playPosition.x += ballSpeed;
                    }
                    if (IsKeyDown(KEY_LEFT) && playPosition.x - playRadius > 0)
                    {
                        playPosition.x -= ballSpeed;
                    }
                    if (IsKeyDown(KEY_UP) && playPosition.y - playRadius > 0) // Ajuste para la parte superior
                    {
                        playPosition.y -= ballSpeed;
                    }
                    if (IsKeyDown(KEY_DOWN) && playPosition.y + playRadius < SCR_HEIGHT) // Ajuste para la parte inferior
                    {
                        playPosition.y += ballSpeed;
                    }

                    // Generar meteoros y objetos
                    if (elapsedTime >= spawnInterval)
                    {
                        for (int i = 0; i < MAX_GRAY_METEORS; i++)
                        {
                            if (!grayMeteors[i].active)
                            {
                                InitGreenBall(&grayMeteors[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_BROWN_METEORS; i++)
                        {
                            if (!brownMeteors[i].active)
                            {
                                InitGreenBall(&brownMeteors[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_COINS; i++)
                        {
                            if (!yellowBalls[i].active)
                            {
                                InitYellowBall(&yellowBalls[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_HEARTS; i++)
                        {
                            if (!RedBalls[i].active)
                            {
                                InitRedBall(&RedBalls[i]);
                                break;
                            }
                        }
                        elapsedTime = 0.0f; // Reiniciar el temporizador
                    }

                    // Fisicas meteoro grande
                    for (int i = 0; i < MAX_GRAY_METEORS; i++)
                    {
                        if (grayMeteors[i].active)
                        {
                            grayMeteors[i].position.y += GRAY_METEOR_SPEED;
                            if (grayMeteors[i].position.y > SCR_HEIGHT + GRAY_METEOR_RADIUS * 2)
                            {
                                grayMeteors[i].active = false;
                            }

                            // Detectar colisión con jugador
                            if (CheckCollision(playPosition, playRadius, grayMeteors[i].position, GRAY_METEOR_RADIUS))
                            {
                                grayMeteors[i].active = false; // Eliminar la esfera tocada
                                lives--;                      // Pierde una vida
                                if (lives <= 0)
                                {
                                    gameOver = true;
                                }
                            }
                        }
                    }
                    // Fisicas meteoro cafe
                    for (int i = 0; i < MAX_BROWN_METEORS; i++)
                    {
                        if (brownMeteors[i].active)
                        {
                            brownMeteors[i].position.y += BROWN_METEOR_SPEED;
                            if (brownMeteors[i].position.y > SCR_HEIGHT + BROWN_METEOR_RADIUS * 2)
                            {
                                brownMeteors[i].active = false;
                            }

                            // Detectar colisión con jugador
                            if (CheckCollision(playPosition, playRadius, brownMeteors[i].position, BROWN_METEOR_RADIUS))
                            {
                                brownMeteors[i].active = false; // Eliminar la esfera tocada
                                lives--;                      // Pierde una vida
                                if (lives <= 0)
                                {
                                    gameOver = true;
                                }
                            }
                        }
                    }

                    // Esfera amarilla (Incrementador de puntos)
                    for (int i = 0; i < MAX_COINS; i++)
                    {
                        if (yellowBalls[i].active)
                        {
                            yellowBalls[i].position.y += COINS_SPEED;
                            if (yellowBalls[i].position.y > SCR_HEIGHT + COINS_RADIUS * 2)
                            {
                                yellowBalls[i].active = false;
                            }

                            // Detectar colisión con jugador y aumentar el contador de puntos
                            if (CheckCollision(playPosition, playRadius, yellowBalls[i].position, COINS_RADIUS))
                            {
                                yellowBalls[i].active = false;
                                score += 10; // Aumentar el puntaje
                            }
                        }
                    }
                    // Esfera Roja (Vida adicional)
                    for (int i = 0; i < MAX_HEARTS; i++)
                    {
                        if (RedBalls[i].active)
                        {
                            RedBalls[i].position.y += HEARTS_SPEED;
                            if (RedBalls[i].position.y > SCR_HEIGHT + HEARTS_RADIUS * 2)
                            {
                                RedBalls[i].active = false;
                            }

                            // Detectar colisión con jugador y aumentar vidas
                            if (CheckCollision(playPosition, playRadius, RedBalls[i].position, HEARTS_RADIUS))
                            {
                                RedBalls[i].active = false; // Eliminar la esfera tocada
                                lives++;                    // Gana una vida
                            }
                        }
                    }
                }

                /************** DIBUJO **************/
                BeginDrawing();

                // Dibuja interfaz y elementos de la partida
                gameInterface(game, shipTextures[currentFrame], shipCenter, lives, score, rotation);

                if (gameOver)
                {
                    StopMusicStream(gameMusic); // Detener musica partida
                    UpdateMusicStream(gameover);
                    PlayMusicStream(gameover); // Reproducir musica gameover

                    gameOverInterface(gameoverT, score); // Dibujar interfaz juego terminado

                    // Reiniciar posicion de la nave y limpiar meteoros
                    resetGame(&playPosition);

                    // Reiniciar el juego al presiona Enter
                    if (IsKeyDown(KEY_ENTER))
                    {
                        gameOver = false;
                        lives = 5;
                        score = 0;
                    }
                    // Vuelve al menu al presionar Q
                    if (IsKeyPressed(KEY_Q))
                    {
                        isPlaying = false;
                    }
                }

                DrawFPS(20, 20);
                EndDrawing();
            }
        }
    }

    // Descargar texturas
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(shipTextures[i]);
    }
    UnloadTexture(game);
    UnloadTexture(gameoverT);
    UnloadTexture(menu);
    UnloadMusicStream(gameMusic);
    UnloadMusicStream(gameover);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
