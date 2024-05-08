/*---------------- PROTOTIPOS ----------------*/
void loadingScreen(const char msg[]);
void loadTextures();
void unloadTextures();
void loadSounds();
void unloadSounds();

/*** Texturas ***/
Texture2D menu, game, gameoverT, scoreboardTx, questionTx, startTx, cinema[9];
Texture2D hearthE[6], hearthF[3], shield, forceF[6];
Texture2D shipTx[3], coinsTx[6], heartsTx[3], misil, explosionTx[3];
Texture2D grayMeteor, brownMeteor;

/*** Sonidos ***/
Music menuMusic, gameMusic, gameover;
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

    // Corazones de vidas llenos
    hearthF[0] = LoadTexture("resources/images/hearts/hearthF_00.png");
    hearthF[1] = LoadTexture("resources/images/hearts/hearthF_01.png");
    hearthF[2] = LoadTexture("resources/images/hearts/hearthF_02.png");

    // Corazones de Vidas Vacios
    hearthE[0] = LoadTexture("resources/images/hearts/hearthE_00.png");
    hearthE[1] = LoadTexture("resources/images/hearts/hearthE_01.png");
    hearthE[2] = LoadTexture("resources/images/hearts/hearthE_02.png");
    hearthE[3] = LoadTexture("resources/images/hearts/hearthE_03.png");
    hearthE[4] = LoadTexture("resources/images/hearts/hearthE_04.png");
    hearthE[5] = LoadTexture("resources/images/hearts/hearthE_05.png");

    shield = LoadTexture("resources/images/shield/shield.png");

    forceF[0] = LoadTexture("resources/images/shield/forceField_00.png");
    forceF[1] = LoadTexture("resources/images/shield/forceField_01.png");
    forceF[2] = LoadTexture("resources/images/shield/forceField_02.png");
    forceF[3] = LoadTexture("resources/images/shield/forceField_03.png");
    forceF[4] = LoadTexture("resources/images/shield/forceField_04.png");
    forceF[5] = LoadTexture("resources/images/shield/forceField_05.png");

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
    shipTx[1] = LoadTexture("resources/images/ship/ship02.png");
    loadingScreen("Cargando....");
    shipTx[2] = LoadTexture("resources/images/ship/ship03.png");

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
    loadingScreen("Cargando..");
    heartsTx[1] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[2] = LoadTexture("resources/images/hearts/hearth_02.png");

    // Disparo
    misil = LoadTexture("resources/images/shot/shot01.png");
    loadingScreen("Cargando...");

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
    UnloadTexture(misil);

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(coinsTx[i]);
        UnloadTexture(hearthE[i]);
        if (i < 3)
        {
            UnloadTexture(heartsTx[i]);
            UnloadTexture(shipTx[i]);
            UnloadTexture(hearthF[i]);
            UnloadTexture(explosionTx[i]);
        }
    }

    // for (int i = 0; i < 9; i++)
    // {
    //     UnloadTexture(cinema[i]);
    // }

    UnloadTexture(grayMeteor);
    UnloadTexture(brownMeteor);
}

// ---- Carga sonidos ----
void loadSounds()
{
    loadingScreen("Cargando....");
    menuMusic = LoadMusicStream("resources/sounds/mainmenu.mp3"); // Musica menu principal
    gameMusic = LoadMusicStream("resources/sounds/music.mp3");    // Musica partida
    loadingScreen("Cargando.");
    gameover = LoadMusicStream("resources/sounds/gameover.mp3"); // Musica gameover
    soundcoin = LoadSound("resources/sounds/coin.wav");          // Sonido moneda
    loadingScreen("Cargando..");
    shotSound = LoadSound("resources/sounds/shot.mp3");        // Sonido misil
    burstMisil = LoadSound("resources/sounds/burstMisil.mp3"); // Sonido explosion misil
    loadingScreen("Cargando...");
}

// ---- Descarga sonidos ----
void unloadSounds()
{
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameMusic);
    UnloadMusicStream(gameover);
    UnloadSound(soundcoin);
    UnloadSound(shotSound);
    UnloadSound(burstMisil);
}