#include "raylib.h"
#include "game.h"

int main(void)
{
    /******** VARIABLES *********/
    const int playRadius = 25;     // tamaño del jugador
    const float ballSpeed = 15.0f; // velocidad del jugador
    bool gameOver = false;         // controla gameover
    bool istutorial = true;        // INICIAR EN TUTORIAL
    bool isPlaying = false;        // determina si esta en juego
    float elapsedTime = 0.0f;
    const float spawnInterval = 0.3f; // Intervalo de tiempo entre la aparición de esferas verdes
    float rotation = 0.0f;
    int score = 0;  // inicio del puntaje
    int lives = 5; // vidas

    InitWindow(screenWidth, screenHeight, "BETA 0.10");
    SetTargetFPS(75);

    // Imagen y textura del fondo menu principal
    Image menuImg = LoadImage("resources/images/menu.png");
    Texture2D menu = LoadTextureFromImage(menuImg);
    UnloadImage(menuImg);

    // Imagen y textura del fondo del juego
    Image gameImg = LoadImage("resources/images/game.png");
    Texture2D game = LoadTextureFromImage(gameImg);
    UnloadImage(gameImg);

    // Imagen y textura de gameover
    Image gameOvImg = LoadImage("resources/images/gameover.png");
    Texture2D gameoverT = LoadTextureFromImage(gameOvImg);
    UnloadImage(gameOvImg);

    /************** Inicializar audio **************/
    InitAudioDevice();
    Music gameMusic = LoadMusicStream("resources/sounds/music.mp3");
    Music gameover = LoadMusicStream("resources/sounds/gameover.mp3");

    // Vector fondo
    Vector2 stars[NUM_STARS];
    for (int i = 0; i < NUM_STARS; i++)
    {
        stars[i].x = GetRandomValue(0, screenWidth);
        stars[i].y = GetRandomValue(0, screenHeight);
    }

    while (!WindowShouldClose())
    {
        // Actualizar buffers de audio
        UpdateMusicStream(gameMusic);
        UpdateMusicStream(gameover);
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
                drawMainMenu(menu);
                StopMusicStream(gameover);
                // STARS
                for (int i = 0; i < NUM_STARS; i++)
                {
                    DrawCircleV(stars[i], STAR_RADIUS, WHITE);
                }

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

                    // ACTUALIZA CAIDA DE METEORO
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
                    // --------- METEORO CAFE
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

                    // Detener musica
                    if (gameOver)
                    {
                        DrawTexture(gameoverT, 0, 0, WHITE);
                        StopMusicStream(gameMusic);
                        PlayMusicStream(gameover);
                    }

                    // Actualiza caida de esfera amarilla
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
                    // Actualiza caida de esfera Roja
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

                // --------------------------------Background -------------------------------22/03
                DrawTexture(game, 0, 0, WHITE);

                // Dibujar vidas
                vidas(lives);
                DrawText(TextFormat("SCORE: %04i", score), screenWidth - 400, 20, 50, WHITE);

                // Dibujar jugador
                DrawCircleV(playPosition, playRadius, MAROON);

                // DIBUJAR LOS OBJETOS   // 21/03  10:03 pm
                dibujarVerde(rotation);
                dibujarCafe(rotation);
                dibujarAmarillo();
                dibujarRojo();
                //  ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^// 21/03  10:03 pm

                if (gameOver)
                {
                    DrawTexture(gameoverT, 0, 0, WHITE);
                    gameOverInterface(score); // INTERFAZ DE JUEGO TERMINADO

                    // Reiniciar el juego si se presiona Enter
                    if (IsKeyDown(KEY_ENTER))
                    {
                        gameOver = false;
                        lives = 5;
                        score = 0;
                    }
                    if (IsKeyPressed(KEY_Q))
                    {
                        isPlaying = false;
                    }
                }

                DrawFPS(0, 0);
                EndDrawing();
            }
        }
    }
    CloseWindow();
    return 0;
}
