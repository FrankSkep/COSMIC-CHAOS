#include "raylib.h"
#include "game.h"

int main(void)
{
    /******** VARIABLES *********/
    const int playRadius = 45;     // tamaño del jugador
    const float ballSpeed = 15.0f; // velocidad del jugador
    bool gameOver = false;         // controla gameover
    bool istutorial = true;        // INICIAR EN TUTORIAL
    bool isPlaying = false;        // determina si esta en juego
    float elapsedTime = 0.0f;
    const float spawnInterval = 0.3f; // Intervalo de tiempo entre la aparición de esferas verdes
    float rotation = 0.0f;
    int score = 0; // inicio del puntaje
    int lives = 5; // vidas

    InitWindow(screenWidth, screenHeight, "BETA 0.10");
    SetTargetFPS(75);

    /************** Imagenes y texturas **************/
    // Fondo menu principal
    Image menuImg = LoadImage("resources/images/menu.png");
    Texture2D menu = LoadTextureFromImage(menuImg);
    UnloadImage(menuImg);

    // Fondo partida
    Image gameImg = LoadImage("resources/images/game.png");
    Texture2D game = LoadTextureFromImage(gameImg);
    UnloadImage(gameImg);

    // Fondo gameover
    Image gameOvImg = LoadImage("resources/images/gameover.png");
    Texture2D gameoverT = LoadTextureFromImage(gameOvImg);
    UnloadImage(gameOvImg);

    // Nave
    Image shipImg = LoadImage("resources/images/nave_01.png");
    Texture2D ship = LoadTextureFromImage(shipImg);
    UnloadImage(shipImg);

    /************** Inicializar audio **************/
    InitAudioDevice();
    Music gameMusic = LoadMusicStream("resources/sounds/music.mp3");
    Music gameover = LoadMusicStream("resources/sounds/gameover.mp3");

    while (!WindowShouldClose())
    {
        // Actualizar buffers de audio
        UpdateMusicStream(gameMusic);
        UpdateMusicStream(gameover);

        // Calcula y actualiza la posición del centro de la nave
        Vector2 shipCenter = {playPosition.x - ship.width / 2, playPosition.y - ship.height / 2};

        if (istutorial)
        {
            StopMusicStream(gameover);
            Tutorial();
            if (IsKeyPressed(KEY_ENTER))
            {
                istutorial = false;
            }
        }
        else
        {

            if (!isPlaying) // Si isPlaying es falso vuelve al menu principal
            {
                drawMainMenu(menu); // Muestra menu principal
                StopMusicStream(gameover); // Detiene musica

                if (IsKeyPressed(KEY_ENTER))
                {
                    isPlaying = true;
                }
            }
            else
            {
                // Velocidad de rotacion meteoros
                rotation += 1.5f;

                if (!gameOver)
                {
                    StopMusicStream(gameover);
                    PlayMusicStream(gameMusic);
                    // Actualizar temporizador
                    elapsedTime += GetFrameTime();

                    // Control del jugador
                    if (IsKeyDown(KEY_RIGHT) && playPosition.x + playRadius < screenWidth)
                    {
                        playPosition.x += ballSpeed;
                    }
                    if (IsKeyDown(KEY_LEFT) && playPosition.x - playRadius > 0)
                    {
                        playPosition.x -= ballSpeed;
                    }
                    if (IsKeyDown(KEY_UP))
                    {
                        playPosition.y -= ballSpeed;
                    }
                    if (IsKeyDown(KEY_DOWN))
                    {
                        playPosition.y += ballSpeed;
                    }

                    // Generar meteoros y objetos
                    if (elapsedTime >= spawnInterval)
                    {
                        for (int i = 0; i < MAX_GREEN_BALLS; i++)
                        {
                            if (!greenBalls[i].active)
                            {
                                InitGreenBall(&greenBalls[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_BROWN_BALLS; i++)
                        {
                            if (!brownBalls[i].active)
                            {
                                InitGreenBall(&brownBalls[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_YELLOW_BALLS; i++)
                        {
                            if (!yellowBalls[i].active)
                            {
                                InitYellowBall(&yellowBalls[i]);
                                break;
                            }
                        }
                        for (int i = 0; i < MAX_RED_BALLS; i++)
                        {
                            if (!RedBalls[i].active)
                            {
                                InitRedBall(&RedBalls[i]);
                                break;
                            }
                        }

                        elapsedTime = 0.0f; // Reiniciar el temporizador
                    }

                    // Meteoro amarillo
                    for (int i = 0; i < MAX_GREEN_BALLS; i++)
                    {
                        if (greenBalls[i].active)
                        {
                            greenBalls[i].position.y += GREEN_BALL_SPEED;
                            if (greenBalls[i].position.y > screenHeight + GREEN_BALL_RADIUS * 2)
                            {
                                greenBalls[i].active = false;
                            }

                            // Detectar colisión con jugador
                            if (CheckCollision(playPosition, playRadius, greenBalls[i].position, GREEN_BALL_RADIUS))
                            {
                                greenBalls[i].active = false; // Eliminar la esfera tocada
                                lives--;                      // Pierde una vida
                                if (lives <= 0)
                                {
                                    gameOver = true;
                                }
                            }
                        }
                    }
                    // Meteoro cafe
                    for (int i = 0; i < MAX_BROWN_BALLS; i++)
                    {
                        if (brownBalls[i].active)
                        {
                            brownBalls[i].position.y += BROWN_BALL_SPEED;
                            if (brownBalls[i].position.y > screenHeight + BROWN_BALL_RADIUS * 2)
                            {
                                brownBalls[i].active = false;
                            }

                            // Detectar colisión con jugador
                            if (CheckCollision(playPosition, playRadius, brownBalls[i].position, BROWN_BALL_RADIUS))
                            {
                                brownBalls[i].active = false; // Eliminar la esfera tocada
                                lives--;                      // Pierde una vida
                                if (lives <= 0)
                                {
                                    gameOver = true;
                                }
                            }
                        }
                    }

                    // Esfera amarilla
                    for (int i = 0; i < MAX_YELLOW_BALLS; i++)
                    {
                        if (yellowBalls[i].active)
                        {
                            yellowBalls[i].position.y += YELLOW_BALL_SPEED;
                            if (yellowBalls[i].position.y > screenHeight + YELLOW_BALL_RADIUS * 2)
                            {
                                yellowBalls[i].active = false;
                            }

                            // Detectar colisión con jugador y aumentar el contador de puntos
                            if (CheckCollision(playPosition, playRadius, yellowBalls[i].position, YELLOW_BALL_RADIUS))
                            {
                                yellowBalls[i].active = false;
                                score += 10; // Aumentar el puntaje
                            }
                        }
                    }
                    // Esfera Roja
                    for (int i = 0; i < MAX_RED_BALLS; i++)
                    {
                        if (RedBalls[i].active)
                        {
                            RedBalls[i].position.y += RED_BALL_SPEED;
                            if (RedBalls[i].position.y > screenHeight + RED_BALL_RADIUS * 2)
                            {
                                RedBalls[i].active = false;
                            }

                            // Detectar colisión con jugador
                            if (CheckCollision(playPosition, playRadius, RedBalls[i].position, RED_BALL_RADIUS))
                            {
                                RedBalls[i].active = false; // Eliminar la esfera tocada
                                lives++;                    // Gana una vida
                            }
                        }
                    }
                }
                
                BeginDrawing();

                // Dibuja interfaz y elementos de la partida
                gameInterface(game, ship, shipCenter, lives, score, rotation);

                if (gameOver)
                {
                    // Detener musica partida
                    StopMusicStream(gameMusic);
                    // Reproducir musica gameover
                    PlayMusicStream(gameover);

                    gameOverInterface(gameoverT, score); // INTERFAZ DE JUEGO TERMINADO

                    // Reiniciar posicion de la nave
                    playPosition = {(float)screenWidth / 2, (float)screenHeight / 1.1f};

                    // Reiniciar el juego si se presiona Enter
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
    CloseWindow();
    return 0;
}