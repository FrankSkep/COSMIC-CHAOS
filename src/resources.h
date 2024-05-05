/*---------------- PROTOTIPOS ----------------*/
void loadingScreen(const char msg[]);
void loadTextures();
void unloadTextures();
void loadSounds();
void unloadSounds();

/*** Texturas ***/
Texture2D menu, game, gameoverT, scoreboardTx, questionTx, startTx, cinema[9];
Texture2D shipTx[6], coinsTx[6], heartsTx[6], heartsFTx[6], heartsETx[6], misil[6], explosionTx[3];
Texture2D grayMeteor, brownMeteor;

/*** Sonidos ***/
Music gameMusic, gameover;
Sound soundcoin, shotSound, burstMisil;

// ---- Pantalla de carga inicial ----
void loadingScreen(const char msg[])
{
    BeginDrawing();
    const int tam = 80;
    ClearBackground(BLACK);
    DrawText(msg, SCR_WIDTH / 2 - MeasureText(msg, tam) / 2, (SCR_HEIGHT / 2) - 100, tam, WHITE);
    EndDrawing();
}

// ---- Carga texturas ----
void loadTextures()
{
    loadingScreen("Cargando.");
    // Fondo menu principal
    menu = LoadTexture("resources/images/backgrounds/menu.png");

    // Fondo partida
    game = LoadTexture("resources/images/backgrounds/game.png");

    // Fondo gameover
    gameoverT = LoadTexture("resources/images/backgrounds/gameover.png");

    // Fondo tabla de estadisticas
    scoreboardTx = LoadTexture("resources/images/backgrounds/scorebg.png");

    // Fondo pregunta
    questionTx = LoadTexture("resources/images/backgrounds/questionbg.png");

    // Fondo pantalla inicial
    startTx = LoadTexture("resources/images/backgrounds/startbg.png");

    // Presentador
    cinema[0] = LoadTexture("resources/images/backgrounds/cinema1.png");
    loadingScreen("Cargando..");
    cinema[1] = LoadTexture("resources/images/backgrounds/cinema2.png");
    cinema[2] = LoadTexture("resources/images/backgrounds/cinema3.png");
    cinema[3] = LoadTexture("resources/images/backgrounds/cinema4.png");
    cinema[4] = LoadTexture("resources/images/backgrounds/cinema5.png");
    cinema[5] = LoadTexture("resources/images/backgrounds/cinema6.png");
    cinema[6] = LoadTexture("resources/images/backgrounds/cinema7.png");
    loadingScreen("Cargando...");
    cinema[7] = LoadTexture("resources/images/backgrounds/cinema8.png");
    cinema[8] = LoadTexture("resources/images/backgrounds/cinema9.png");

    // Nave
    shipTx[0] = LoadTexture("resources/images/ship/ship01.png");
    shipTx[1] = LoadTexture("resources/images/ship/ship01.png");
    shipTx[2] = LoadTexture("resources/images/ship/ship02.png");
    shipTx[3] = LoadTexture("resources/images/ship/ship02.png");
    loadingScreen("Cargando....");
    shipTx[4] = LoadTexture("resources/images/ship/ship03.png");
    shipTx[5] = LoadTexture("resources/images/ship/ship03.png");

    // Meteoros
    grayMeteor = LoadTexture("resources/images/meteors/grayMeteor.png");
    brownMeteor = LoadTexture("resources/images/meteors/brownMeteor.png");

    // Monedas
    coinsTx[0] = LoadTexture("resources/images/coins/coin_01.png");
    coinsTx[1] = LoadTexture("resources/images/coins/coin_02.png");
    loadingScreen("Cargando.");
    coinsTx[2] = LoadTexture("resources/images/coins/coin_03.png");
    coinsTx[3] = LoadTexture("resources/images/coins/coin_04.png");
    coinsTx[4] = LoadTexture("resources/images/coins/coin_05.png");
    coinsTx[5] = LoadTexture("resources/images/coins/coin_06.png");

    // Corazones
    heartsTx[0] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[1] = LoadTexture("resources/images/hearts/hearth_01.png");
    loadingScreen("Cargando..");
    heartsTx[2] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[3] = LoadTexture("resources/images/hearts/hearth_02.png");
    heartsTx[4] = LoadTexture("resources/images/hearts/hearth_02.png");
    heartsTx[5] = LoadTexture("resources/images/hearts/hearth_02.png");

    // Disparo
    misil[0] = LoadTexture("resources/images/shot/shot01.png");
    misil[1] = LoadTexture("resources/images/shot/shot01.png");
    loadingScreen("Cargando...");
    misil[2] = LoadTexture("resources/images/shot/shot02.png");
    misil[3] = LoadTexture("resources/images/shot/shot02.png");
    misil[4] = LoadTexture("resources/images/shot/shot03.png");
    misil[5] = LoadTexture("resources/images/shot/shot03.png");

    // Explosion misil
    explosionTx[0] = LoadTexture("resources/images/shot/burst01.png");
    explosionTx[1] = LoadTexture("resources/images/shot/burst02.png");
    explosionTx[2] = LoadTexture("resources/images/shot/burst03.png");
}

// ---- Descarga texturas ----
void unloadTextures()
{
    loadingScreen("ADIOS.");
    UnloadTexture(menu);
    UnloadTexture(game);
    UnloadTexture(gameoverT);
    UnloadTexture(scoreboardTx);
    UnloadTexture(questionTx);
    UnloadTexture(startTx);

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(shipTx[i]);
        UnloadTexture(coinsTx[i]);
        UnloadTexture(heartsTx[i]);
        if (i < 3)
        {
            UnloadTexture(explosionTx[i]);
        }
    }

    for (int i = 0; i < 9; i++)
    {
        UnloadTexture(cinema[i]);
    }

    UnloadTexture(grayMeteor);
    UnloadTexture(brownMeteor);
}

// ---- Carga sonidos ----
void loadSounds()
{
    gameMusic = LoadMusicStream("resources/sounds/music.mp3");   // Musica partida
    gameover = LoadMusicStream("resources/sounds/gameover.mp3"); // Musica gameover
    soundcoin = LoadSound("resources/sounds/coin.wav");          // Sonido moneda
    shotSound = LoadSound("resources/sounds/shot.mp3");          // Sonido misil
    burstMisil = LoadSound("resources/sounds/burstMisil.mp3");
}

// ---- Descarga sonidos ----
void unloadSounds()
{
    UnloadMusicStream(gameMusic);
    UnloadMusicStream(gameover);
    UnloadSound(soundcoin);
    UnloadSound(shotSound);
    UnloadSound(burstMisil);
}