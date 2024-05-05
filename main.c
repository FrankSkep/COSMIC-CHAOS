#include "raylib.h"
#include "src/elements.h"
#include "src/resources.h" // Texturas y sonidos
#include "src/game.h"      // Funciones del juego

int main()
{
    /*------------- CONSTANTES -------------*/
    const int playRadius = 45;       // Tamaño del jugador
    const float playerSpeed = 15.0f; // Velocidad del jugador
    float playerRotation = 0.0;
    float rotationSpeed = 2.0;
    const float maxRotation = 20.0f;                // Máxima rotación hacia la derecha
    const float minRotation = -20.0f;               // Máxima rotación hacia la izquierda
    const float rotationInterpolationSpeed = 50.0f; // Definir la velocidad de interpolación para volver a la posición original
    float currentRotation = 0.0f;                   // Variables para la rotación actual y la interpolación de la rotación
    float targetRotation = 0.0f;
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
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "BETA 1.0");
    SetTargetFPS(75);

    /*----------- Carga de texturas y sonidos -----------*/
    loadTextures();
    InitAudioDevice();
    loadSounds();

    /*-------- Ajustes texturas cambiantes --------*/
    short currentFrame = 0; // indice de la textura actual
    short currentFrameExp = 0;
    float frameTimeCounter = 0.0f;
    float frameSpeed = 1.0f / 8.0f; // velocidad de cambio de imagen (cada 1/8 de segundo)

    // Posicion y centro de jugador/nave
    Vector2 playerPosition = {(float)SCR_WIDTH / 2 - shipTx[currentFrame].width / 2, (float)SCR_HEIGHT / 1.1f - shipTx[currentFrame].height / 2};
    // Centro meteoros
    Vector2 grayCenter, brownCenter;

    // ------- DATOS JUGADOR -------
    Tdata data;
    char name[MAX_INPUT_CHARS + 1] = "";
    ingresarNickName(name);
    strcpy(data.name, name);
    data.score = 0;
    data.maxLevel = 0;
    getDate(&data.dia, &data.mes, &data.anio);

    bool saveProgress = false; // Guardar estadisticas de jugador
    bool showQuestion = false; // Mostrar pregunta
    bool continuar = false;    // Mostrar pregunta
    int contin = 0;            // Mostrar pregunta

    /*------------------------ BUCLE DEL JUEGO ------------------------*/
    while (!WindowShouldClose())
    {
        if (!isPlaying) // Menu principal
        {
            StopMusicStream(gameover);          // Detiene musica gameover
            drawMainMenu();                     // Dibuja menu principal
            menuActions(&secondsT, &isPlaying); // Acciones menu
        }
        else
        { /*-------------------- PARTIDA --------------------*/
            if (!gameOver)
            {
                StopMusicStream(gameover); // Detiene musica de gameover
                UpdateMusicStream(gameMusic);
                PlayMusicStream(gameMusic); // Reproduce musica de la partida

                /***** SPRITES *****/
                frameTimeCounter += GetFrameTime();
                // Pasado el tiempo, cambia imagen
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
                        // Limitar la rotación hacia la derecha
                        if (currentRotation < maxRotation)
                        {
                            currentRotation += rotationSpeed;
                        }
                    }
                }
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) // Mover hacia la izquierda
                {
                    if (playerPosition.x - playRadius > 0)
                    {
                        playerPosition.x -= playerSpeed;

                        // Limitar la rotación hacia la izquierda
                        if (currentRotation > minRotation)
                        {
                            currentRotation -= rotationSpeed;
                        }
                    }
                }
                // Interpolar la rotación de vuelta a la posición original cuando se suelta la tecla
                if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_A))
                {
                    // Si la rotación actual no es igual a la rotación objetivo, interpola hacia la rotación objetivo
                    if (currentRotation != targetRotation)
                    {
                        if (currentRotation < targetRotation)
                        {
                            currentRotation += rotationInterpolationSpeed * GetFrameTime();
                            if (currentRotation > targetRotation)
                            {
                                currentRotation = targetRotation;
                            }
                        }
                        else
                        {
                            if (currentRotation > targetRotation)
                            {
                                currentRotation -= rotationInterpolationSpeed * GetFrameTime();
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
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) // Mover hacia arriba
                {
                    if (playerPosition.y - playRadius > 0)
                    {
                        playerPosition.y -= playerSpeed;
                    }
                }
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) // Mover hacia abajo
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
                        if (!coinGold[i].active)
                        {
                            InitObject(&coinGold[i], &COINS_RADIUS);
                            InitObject(&coinRed[i], &COINS_RADIUS);
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
                        grayCenter.x = grayMeteors[i].position.x - grayMeteor.width / 2;
                        grayCenter.y = grayMeteors[i].position.y - grayMeteor.height / 2;
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
                        brownCenter.x = brownMeteors[i].position.x - brownMeteor.width / 2;
                        brownCenter.y = brownMeteors[i].position.y - brownMeteor.height / 2;
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
                    if (coinGold[i].active)
                    {
                        coinGold[i].position.y += COINS_SPEED;
                        if (coinGold[i].position.y > SCR_HEIGHT + COINS_RADIUS * 2)
                        {
                            coinGold[i].active = false;
                        }

                        // Detectar colisión con jugador y aumentar el contador de puntos
                        if (CheckCollision(playerPosition, playRadius, coinGold[i].position, COINS_RADIUS))
                        {
                            coinGold[i].active = false; // Eliminar objeto tocado
                            score += 10;                // Aumentar el puntaje
                            PlaySound(soundcoin);
                        }
                    }

                    // Moneda tipo 2 (Operacion matematica)
                    if (coinRed[i].active)
                    {
                        coinRed[i].position.y += COINS_SPEED;
                        if (coinRed[i].position.y > SCR_HEIGHT + COINS_RADIUS * 2)
                        {
                            coinRed[i].active = false;
                        }

                        // Detectar colisión con jugador y aumentar el contador de puntos
                        if (CheckCollision(playerPosition, playRadius, coinRed[i].position, COINS_RADIUS))
                        {
                            coinRed[i].active = false; // Eliminar objeto tocado
                            showQuestion = true;
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
                                    grayCenter.x = grayMeteors[j].position.x - grayMeteor.width / 2;
                                    grayCenter.y = grayMeteors[j].position.y - grayMeteor.height / 2;
                                    //  Colision con meteoro gris
                                    if (CheckCollision(shots[i].position, SHOT_RADIUS, grayCenter, GRAY_METEOR_RADIUS))
                                    {
                                        PlaySound(burstMisil);
                                        StopSound(shotSound);
                                        score += 5;
                                        grayMeteors[j].active = false;
                                        shots[i].collided = true;
                                        shots[i].explosionTimer = 0.4f; // Duración de la animación de explosión (0.4 segundos)
                                    }
                                }
                            }

                            for (int j = 0; j < MAX_BROWN_METEORS; j++)
                            {
                                if (brownMeteors[j].active)
                                {
                                    // Calcula punto de collision
                                    brownCenter.x = brownMeteors[j].position.x - brownMeteor.width / 2;
                                    brownCenter.y = brownMeteors[j].position.y - brownMeteor.height / 2;
                                    //  Colisión con meteoro café
                                    if (CheckCollision(shots[i].position, SHOT_RADIUS, brownCenter, BROWN_METEOR_RADIUS))
                                    {
                                        PlaySound(burstMisil);
                                        StopSound(shotSound);
                                        score += 5;
                                        brownMeteors[j].active = false;
                                        shots[i].collided = true;
                                        shots[i].explosionTimer = 0.4f; // Duración de la animación de explosión (0.4 segundos)
                                    }
                                }
                            }
                        }
                    }
                }
                pausa();
                /*---------------- DIBUJO PARTIDA EN CURSO ---------------*/
                BeginDrawing();
                // Velocidad de rotacion meteoros
                rotationMeteor += 2.5f;

                // Dibujar interfaz de la partida
                drawGameInterface(&heartsTx[currentFrame], &lives, &score, &level, data.name);
                // Dibujar objetos de la partida
                drawGameElements(&shipTx[currentFrame], &playerPosition, &coinsTx[currentFrame], &heartsTx[currentFrame], &misil[currentFrame], &explosionTx[currentFrameExp], &rotationMeteor, &playerPosition, &playerRotation);

                if (continuar)
                {
                    if (contin == 4)
                    {
                        PlaySound(soundcoin);
                        PlaySound(soundcoin);
                        screenMessage("¡GOO!", 0.5, false);
                        contin = 0;
                        continuar = false;
                    }
                    if (contin == 3)
                    {
                        PlaySound(soundcoin);
                        screenMessage("1", 0.7, false);
                        contin = 4;
                    }
                    if (contin == 2)
                    {
                        PlaySound(soundcoin);
                        screenMessage("2", 0.7, false);
                        contin = 3;
                    }
                    if (contin == 1)
                    {
                        PlaySound(soundcoin);
                        screenMessage("3", 0.7, false);
                        contin = 2;
                    }
                }
                if (showQuestion)
                {
                    drawQuestion(&showQuestion, preguntas, numPreguntas);
                    continuar = true;
                    contin = 1;
                }

                /*--------------- ? ---------------*/
                timeseconds += GetFrameTime(); // Obtener el tiempo transcurrido en segundos
                totalseconds = timeseconds;
                minutesT = totalseconds / 60;
                secondsT = totalseconds % 60;
                // Dibujar el tiempo transcurrido en pantalla con formato de reloj (00:00)
                DrawText(TextFormat("%02d:%02d", minutesT, secondsT), 20, SCR_HEIGHT - 90, 85, WHITE);
                /*--------------- ? ---------------*/

                Levels(&score, &level, &elapsedTime, &playerPosition, &lives, &totalseconds, &timeseconds);
                /*---------------   -----------------------------------------*/

                if (gameOver)
                {
                    ClearBackground(BLACK);
                    minutesT = 0, secondsT = 0, totalseconds = 0, timeseconds = 0;
                    rotationMeteor = 0;          // Reiniciar rotacion
                    resetItems(&playerPosition); // Reinicia posicion y desactiva objetos

                    saveProgress = true;
                    // Actualiza mejor puntaje
                    if (score > data.score)
                    {
                        data.score = score;
                    }
                    if (level > data.maxLevel)
                    {
                        data.maxLevel = level;
                    }

                    StopMusicStream(gameMusic); // Detener musica partida
                    PlayMusicStream(gameover);  // Reproducir musica gameover
                }
            } /*-------------------- FIN DE PARTIDA --------------------*/
            else
            { /*------------------ GAMEOVER ------------------*/
                // Reproducir musica gameover
                UpdateMusicStream(gameover);

                // Dibuja interfaz
                gameOverInterface(&score, &level);

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

    // Agregar estadisticas al archivo .dat
    if (saveProgress)
    {
        appendScoresToFile("record.dat", data);
    }

    // Descarga de recursos
    unloadTextures();
    unloadSounds();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
