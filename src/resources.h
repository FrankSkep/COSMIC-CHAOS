/*---------------- PROTOTIPOS ----------------*/
void loadingScreen(const char msg[]);
void loadTextures();
void unloadTextures();
void loadSounds();
void unloadSounds();

/*------ Texturas ------*/
// Fondos
Texture2D menu, levels[3], gameoverT, scoreboardTx, aboutBg;
Texture2D tutotx, tutotx1;

// Iconos interfaz
Texture2D hearthE[6], hearthF[3], shield;

// Nave y relacionados
Texture2D shipTx[3], forceF[6], misil, explosionTx[3];

// Objetos que caen
Texture2D grayMeteor, brownMeteor, coinsTx[6], heartsTx[3], ammoTx, ballE[3];

// Sin usar
Texture2D cinema[8];

/*** Sonidos ***/
Music menuMusic, gameMusic, gameover;
Sound soundcoin, shotSound, burstShotSound;

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

    // Fondos de partida por nivel
    levels[0] = LoadTexture("resources/images/backgrounds/nivel1.png");
    levels[1] = LoadTexture("resources/images/backgrounds/nivel2.png");
    levels[2] = LoadTexture("resources/images/backgrounds/nivel3.png");

    // Fondo gameover
    gameoverT = LoadTexture("resources/images/backgrounds/gameover.png");

    // Imagenes tutorial
    tutotx = LoadTexture("resources/images/backgrounds/tuto00.png");
    tutotx1 = LoadTexture("resources/images/backgrounds/tuto01.png");

    // Corazones de vidas llenos
    hearthF[0] = LoadTexture("resources/images/hearts/hearthF_00.png");
    hearthF[1] = LoadTexture("resources/images/hearts/hearthF_01.png");
    hearthF[2] = LoadTexture("resources/images/hearts/hearthF_02.png");
    loadingScreen("Cargando..");

    // Corazones de Vidas Vacios
    hearthE[0] = LoadTexture("resources/images/hearts/hearthE_00.png");
    hearthE[1] = LoadTexture("resources/images/hearts/hearthE_01.png");
    hearthE[2] = LoadTexture("resources/images/hearts/hearthE_02.png");
    hearthE[3] = LoadTexture("resources/images/hearts/hearthE_03.png");
    hearthE[4] = LoadTexture("resources/images/hearts/hearthE_04.png");
    hearthE[5] = LoadTexture("resources/images/hearts/hearthE_05.png");

    // power ups
    shield = LoadTexture("resources/images/shield/shield.png");
    ballE[0] = LoadTexture("resources/images/shield/ballEnergi_00.png");
    ballE[1] = LoadTexture("resources/images/shield/ballEnergi_01.png");
    ballE[2] = LoadTexture("resources/images/shield/ballEnergi_02.png");
    ammoTx = LoadTexture("resources/images/shot/ammo.png");

    forceF[0] = LoadTexture("resources/images/shield/forceField_00.png");
    forceF[1] = LoadTexture("resources/images/shield/forceField_01.png");
    forceF[2] = LoadTexture("resources/images/shield/forceField_02.png");
    loadingScreen("Cargando...");
    forceF[3] = LoadTexture("resources/images/shield/forceField_03.png");
    forceF[4] = LoadTexture("resources/images/shield/forceField_04.png");
    forceF[5] = LoadTexture("resources/images/shield/forceField_05.png");

    // CINEMATICAS
     cinema[0] = LoadTexture("resources/images/backgrounds/cinema1.png");
     cinema[1] = LoadTexture("resources/images/backgrounds/cinema2.png");
    // cinema[2] = LoadTexture("resources/images/backgrounds/cinema3.png");
    // cinema[3] = LoadTexture("resources/images/backgrounds/cinema4.png");
    // cinema[4] = LoadTexture("resources/images/backgrounds/cinema5.png");     //ESTAS DEJAR
    // cinema[5] = LoadTexture("resources/images/backgrounds/cinema6.png");     //ESTAS DEJAR
    // cinema[6] = LoadTexture("resources/images/backgrounds/cinema7.png");
    // cinema[7] = LoadTexture("resources/images/backgrounds/cinema8.png");
    loadingScreen("Cargando....");

    // Nave
    shipTx[0] = LoadTexture("resources/images/ship/ship01.png");
    shipTx[1] = LoadTexture("resources/images/ship/ship02.png");
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
    UnloadTexture(gameoverT);
    UnloadTexture(misil);
    UnloadTexture(tutotx);
    UnloadTexture(tutotx1);

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(coinsTx[i]);
        UnloadTexture(hearthE[i]);
        UnloadTexture(forceF[i]);
        if (i < 3)
        {
            UnloadTexture(levels[i]);
            UnloadTexture(shipTx[i]);
            UnloadTexture(hearthF[i]);
            UnloadTexture(heartsTx[i]);
            UnloadTexture(explosionTx[i]);
            UnloadTexture(ballE[i]);
        }
    }

    // for (int i = 0; i < 9; i++)
    // {
    //     UnloadTexture(cinema[i]);
    // }
    UnloadTexture(shield);
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
    shotSound = LoadSound("resources/sounds/shot.mp3");            // Sonido misil
    burstShotSound = LoadSound("resources/sounds/burstMisil.mp3"); // Sonido explosion misil
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
    UnloadSound(burstShotSound);
}