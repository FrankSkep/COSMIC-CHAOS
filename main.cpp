#include "game.h"

int main(void)
{
    /************ VARIABLES *************/
    const int playRadius = 45;     // Tamaño del jugador
    const float ballSpeed = 15.0f; // Velocidad del jugador
    bool gameOver = false;         // Controla gameover
    bool istutorial = false;       // Controla cuando entra al tutorial
    bool isPlaying = false;        // Determina si esta en juego
    float elapsedTime = 0.0f;
    const float spawnInterval = 0.3f; // Intervalo de tiempo entre la aparición de esferas verdes
    float rotation = 0.0f;            // Rotacion de meteoros
    int score = 0;                    // Inicio del puntaje
    int lives = 5;                    // Vidas Iniciales
    int level = 1;                    // Nivel inicial
    int milliseconds = 2000;

    InitWindow(SCR_WIDTH, SCR_HEIGHT, "BETA 0.12");
    SetTargetFPS(75);

    /************** Texturas **************/
    // Fondo menu principal;
    Texture2D menu = LoadTexture("images/backgrounds/menu.png");
    // Fondo partida
    Texture2D game = LoadTexture("images/backgrounds/game.png");
    // Fondo gameovership/
    Texture2D gameoverT = LoadTexture("images/backgrounds/gameover.png");
    // Nave
    Texture2D shipTextures[] =
        {
            LoadTexture("images/ship/ship01.png"),
            LoadTexture("images/ship/ship02.png"),
            LoadTexture("images/ship/ship03.png"),
            LoadTexture("images/ship/ship02.png"),
            LoadTexture("images/ship/ship01.png"),
            LoadTexture("images/ship/ship02.png"),
            LoadTexture("images/ship/ship03.png")};

    Texture2D coinsTx[] =
        {
            LoadTexture("images/coins/coin_01.png"),
            LoadTexture("images/coins/coin_02.png"),
            LoadTexture("images/coins/coin_03.png"),
            LoadTexture("images/coins/coin_04.png"),
            LoadTexture("images/coins/coin_05.png"),
            LoadTexture("images/coins/coin_06.png"),
            LoadTexture("images/coins/coin_07.png")};

    /***** Ajustes textura nave *****/
    int currentFrame = 0; // indice de la textura actual
    float frameTimeCounter = 0.0f;
    float frameSpeed = 1.0f / 4.0f; // velocidad de cambio de imagen (cada 1/4 de segundo)

    /************** Inicializacion audio **************/
    InitAudioDevice();
    Music gameMusic = LoadMusicStream("sounds/music.mp3");
    Music gameover = LoadMusicStream("sounds/gameover.mp3");
    Sound soundcoin = LoadSound("sounds/coin.wav");

    // Posicion jugador
    Vector2 playPosition = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 1.1f};

    /*************** BUCLE DEL JUEGO ***************/
    while (!WindowShouldClose())
    {
        // Calcula y actualiza la posición del centro de la nave
        Vector2 shipCenter = {playPosition.x - shipTextures[currentFrame].width / 2, playPosition.y - shipTextures[currentFrame].height / 2};

        // Calcula y actualiza la posición del centro de la moneda
        Vector2 coinCenter = {coins->position.x - coinsTx[currentFrame].width / 2, coins->position.y - coinsTx[currentFrame].height / 2};

        if (istutorial)
        {
            Tutorial();
            if (IsKeyPressed(KEY_Q))
            {
                istutorial = false; // Sale del tutorial
            }
        }
        else
        {
            if (!isPlaying) // Si isPlaying es falso, manda a menu principal
            {
                drawMainMenu(menu);        // Dibuja menu principal
                StopMusicStream(gameover); // Detiene musica gameover

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
                UpdateMusicStream(gameMusic);

                /***** SPRITE NAVE *****/
                frameTimeCounter += GetFrameTime();
                // pasado el tiempo, cambia la imagen de la nave
                if (frameTimeCounter >= frameSpeed)
                {
                    currentFrame = (currentFrame + 1) % 7; // Cambiar al siguiente marco (0, 1, 2, 0, 1, 2, ...)
                    frameTimeCounter = 0.0f;               // Reiniciar el contador de tiempo
                }

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
                                InitGrayMeteor(&grayMeteors[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_BROWN_METEORS; i++)
                        {
                            if (!brownMeteors[i].active)
                            {
                                InitBrownMeteor(&brownMeteors[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_COINS; i++)
                        {
                            if (!coins[i].active)
                            {
                                InitCoin(&coins[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_HEARTS; i++)
                        {
                            if (!hearts[i].active)
                            {
                                InitHearts(&hearts[i]);
                                break;
                            }
                        }
                        elapsedTime = 0.0f; // Reiniciar el temporizador
                    }

                    // Fisicas meteoro gris
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
                                lives--;                       // Pierde una vida
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
                                lives--;                        // Pierde una vida
                                if (lives <= 0)
                                {
                                    gameOver = true;
                                }
                            }
                        }
                    }

                    // Fisicas moneda (Incrementador de puntos)
                    for (int i = 0; i < MAX_COINS; i++)
                    {
                        if (coins[i].active)
                        {
                            coins[i].position.y += COINS_SPEED;
                            if (coins[i].position.y > SCR_HEIGHT + COINS_RADIUS * 2)
                            {
                                coins[i].active = false;
                            }

                            // Detectar colisión con jugador y aumentar el contador de puntos
                            if (CheckCollision(playPosition, playRadius, coins[i].position, COINS_RADIUS))
                            {
                                coins[i].active = false;
                                score += 10; // Aumentar el puntaje
                                PlaySound(soundcoin);
                            }
                        }
                    }
                    // Fisicas corazon (Vida adicional)
                    for (int i = 0; i < MAX_HEARTS; i++)
                    {
                        if (hearts[i].active)
                        {
                            hearts[i].position.y += HEARTS_SPEED;
                            if (hearts[i].position.y > SCR_HEIGHT + HEARTS_RADIUS * 2)
                            {
                                hearts[i].active = false;
                            }

                            // Detectar colisión con jugador y aumentar vidas
                            if (CheckCollision(playPosition, playRadius, hearts[i].position, HEARTS_RADIUS))
                            {
                                hearts[i].active = false; // Eliminar la esfera tocada
                                lives++;                  // Gana una vida
                            }
                        }
                    }
                }

                /********************* DIBUJO *********************/
                BeginDrawing();

                // Dibuja interfaz y elementos de la partida
                gameInterface(game, shipTextures[currentFrame], shipCenter, lives, score, rotation, coinsTx[currentFrame], coinCenter);

                if (gameOver)
                {
                    StopMusicStream(gameMusic); // Detener musica partida
                    UpdateMusicStream(gameover);
                    PlayMusicStream(gameover); // Reproducir musica gameover

                    gameOverInterface(gameoverT, score); // Dibujar interfaz juego terminado

                    // Reiniciar posicion de la nave, limpiar meteoros
                    resetGame(&playPosition);

                    level = 1;

                    // Reiniciar el juego al presiona Enter
                    if (IsKeyDown(KEY_ENTER))
                    {
                        // Reinicia vidas y puntaje
                        lives = 5;
                        score = 0;
                        gameOver = false;
                    }
                    // Vuelve al menu al presionar Q
                    if (IsKeyPressed(KEY_Q))
                    {
                        isPlaying = false;
                    }
                }
                Levels(&score, &level, &elapsedTime, &playPosition, &milliseconds);

                DrawFPS(20, 20);
                EndDrawing();
            }
        }
    }

    // Descargar texturas
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(shipTextures[i]);
        UnloadTexture(coinsTx[i]);
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
