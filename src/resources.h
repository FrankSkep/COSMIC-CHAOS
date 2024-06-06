/*---------------- PROTOTIPOS ----------------*/
void loadTextures();
void unloadTextures();
void loadSounds();
void unloadSounds();
void loadingScreen(float progress);

/*------ Texturas ------*/
// Fondos
Texture2D menu, levels[3], gameoverT, scoreboardTx, aboutBg, questionTx, scoreLevel, pausebg, loadingscreen;
Texture2D tutotx, tutotx1;

Texture2D shipLoading;

// Iconos interfaz
Texture2D hearthE[6], hearthF[3], shield;

// Nave y relacionados
Texture2D shipTx[4], forceF[6], misil, explosionTx[3];

// Objetos que caen
Texture2D grayMeteor, brownMeteor, coinsTx[6], heartsTx[3], ammoTx, ballE[3];

// Sin usar
const short totalcinema = 11;
Texture2D cinema[totalcinema];

/*** Sonidos ***/
Music menuMusic, gameMusic, gameover;
Sound soundcoin, shotSound, burstShotSound, colision, correct, error, liveX, p_Up, liveFull;

float totalResources = 67.0f; // Total de texturas a cargar

// ---- Carga texturas ----
void loadTextures()
{
    loadingscreen = LoadTexture("resources/images/backgrounds/loading-screen.png");
    shipLoading = LoadTexture("resources/images/backgrounds/shipLoading.png");
    loadingScreen(0.0f); // Mostrar pantalla de carga inicial
    // Fondo menu principal
    menu = LoadTexture("resources/images/backgrounds/menu.png");
    loadingScreen(1 / totalResources);

    // Fondos de partida por nivel
    levels[0] = LoadTexture("resources/images/backgrounds/nivel1.png");
    loadingScreen(2 / totalResources);
    levels[1] = LoadTexture("resources/images/backgrounds/nivel2.png");
    loadingScreen(3 / totalResources);
    levels[2] = LoadTexture("resources/images/backgrounds/nivel3.png");
    loadingScreen(4 / totalResources);

    // Fondo gameover
    gameoverT = LoadTexture("resources/images/backgrounds/gameover.png");
    loadingScreen(5 / totalResources);

    // Fondo pregunta
    questionTx = LoadTexture("resources/images/backgrounds/questionbg.png");
    loadingScreen(6 / totalResources);

    // Corazones de vidas llenos
    hearthF[0] = LoadTexture("resources/images/hearts/hearthF_00.png");
    loadingScreen(7 / totalResources);
    hearthF[1] = LoadTexture("resources/images/hearts/hearthF_01.png");
    loadingScreen(8 / totalResources);
    hearthF[2] = LoadTexture("resources/images/hearts/hearthF_02.png");
    loadingScreen(9 / totalResources);

    // Corazones de vidas vacíos
    hearthE[0] = LoadTexture("resources/images/hearts/hearthE_00.png");
    loadingScreen(10 / totalResources);
    hearthE[1] = LoadTexture("resources/images/hearts/hearthE_01.png");
    loadingScreen(11 / totalResources);
    hearthE[2] = LoadTexture("resources/images/hearts/hearthE_02.png");
    loadingScreen(12 / totalResources);
    hearthE[3] = LoadTexture("resources/images/hearts/hearthE_03.png");
    loadingScreen(13 / totalResources);
    hearthE[4] = LoadTexture("resources/images/hearts/hearthE_04.png");
    loadingScreen(14 / totalResources);
    hearthE[5] = LoadTexture("resources/images/hearts/hearthE_05.png");
    loadingScreen(15 / totalResources);

    // Power ups
    shield = LoadTexture("resources/images/shield/shield.png");
    loadingScreen(16 / totalResources);
    ballE[0] = LoadTexture("resources/images/shield/ballEnergi_00.png");
    loadingScreen(17 / totalResources);
    ballE[1] = LoadTexture("resources/images/shield/ballEnergi_01.png");
    loadingScreen(18 / totalResources);
    ballE[2] = LoadTexture("resources/images/shield/ballEnergi_02.png");
    loadingScreen(19 / totalResources);

    ammoTx = LoadTexture("resources/images/shot/ammo.png");
    loadingScreen(20 / totalResources);

    forceF[0] = LoadTexture("resources/images/shield/forceField_00.png");
    loadingScreen(21 / totalResources);
    forceF[1] = LoadTexture("resources/images/shield/forceField_01.png");
    loadingScreen(22 / totalResources);
    forceF[2] = LoadTexture("resources/images/shield/forceField_02.png");
    loadingScreen(23 / totalResources);
    forceF[3] = LoadTexture("resources/images/shield/forceField_03.png");
    loadingScreen(24 / totalResources);
    forceF[4] = LoadTexture("resources/images/shield/forceField_04.png");
    loadingScreen(25 / totalResources);
    forceF[5] = LoadTexture("resources/images/shield/forceField_05.png");
    loadingScreen(26 / totalResources);

    pausebg = LoadTexture("resources/images/backgrounds/PauseBg.png");
    loadingScreen(27 / totalResources);
    scoreLevel = LoadTexture("resources/images/backgrounds/scoreLevel.png");
    loadingScreen(28 / totalResources);

    // Imágenes tutorial
    tutotx = LoadTexture("resources/images/backgrounds/tuto00.png");
    loadingScreen(29 / totalResources);
    tutotx1 = LoadTexture("resources/images/backgrounds/tuto01.png");
    loadingScreen(30 / totalResources);

    // Cinemáticas
    cinema[0] = LoadTexture("resources/images/backgrounds/cinema1.png");
    loadingScreen(31 / totalResources);
    cinema[1] = LoadTexture("resources/images/backgrounds/cinema2.png");
    loadingScreen(32 / totalResources);
    cinema[2] = LoadTexture("resources/images/backgrounds/cinema3.png");
    loadingScreen(33 / totalResources);
    cinema[3] = LoadTexture("resources/images/backgrounds/cinema4.png");
    loadingScreen(34 / totalResources);
    cinema[4] = LoadTexture("resources/images/backgrounds/cinema5.png");
    loadingScreen(35 / totalResources);
    cinema[5] = LoadTexture("resources/images/backgrounds/cinema6.png");
    loadingScreen(36 / totalResources);
    cinema[6] = LoadTexture("resources/images/backgrounds/cinema7.png");
    loadingScreen(37 / totalResources);
    cinema[7] = LoadTexture("resources/images/backgrounds/cinema8.png");
    loadingScreen(38 / totalResources);
    cinema[8] = LoadTexture("resources/images/backgrounds/cinema10.png");
    loadingScreen(39 / totalResources);
    cinema[9] = LoadTexture("resources/images/backgrounds/cinema11.png");
    loadingScreen(40 / totalResources);
    cinema[10] = LoadTexture("resources/images/backgrounds/cinema12.png");
    loadingScreen(41 / totalResources);
    cinema[11] = LoadTexture("resources/images/backgrounds/cinema13.png");
    loadingScreen(42 / totalResources);

    // Nave
    shipTx[0] = LoadTexture("resources/images/ship/ship01.png");
    loadingScreen(43 / totalResources);
    shipTx[1] = LoadTexture("resources/images/ship/ship02.png");
    loadingScreen(44 / totalResources);
    shipTx[2] = LoadTexture("resources/images/ship/ship03.png");
    shipTx[3] = LoadTexture("resources/images/ship/ship04.png");
    loadingScreen(45 / totalResources);

    // Meteoros
    grayMeteor = LoadTexture("resources/images/meteors/grayMeteor.png");
    loadingScreen(46 / totalResources);
    brownMeteor = LoadTexture("resources/images/meteors/brownMeteor.png");
    loadingScreen(47 / totalResources);

    // Monedas
    coinsTx[0] = LoadTexture("resources/images/coins/coin_01.png");
    loadingScreen(48 / totalResources);
    coinsTx[1] = LoadTexture("resources/images/coins/coin_02.png");
    loadingScreen(49 / totalResources);
    coinsTx[2] = LoadTexture("resources/images/coins/coin_03.png");
    loadingScreen(50 / totalResources);
    coinsTx[3] = LoadTexture("resources/images/coins/coin_04.png");
    loadingScreen(51 / totalResources);
    coinsTx[4] = LoadTexture("resources/images/coins/coin_05.png");
    loadingScreen(52 / totalResources);
    coinsTx[5] = LoadTexture("resources/images/coins/coin_06.png");
    loadingScreen(53 / totalResources);

    // Corazones
    heartsTx[0] = LoadTexture("resources/images/hearts/hearth_01.png");
    loadingScreen(54 / totalResources);
    heartsTx[1] = LoadTexture("resources/images/hearts/hearth_01.png");
    loadingScreen(55 / totalResources);
    heartsTx[2] = LoadTexture("resources/images/hearts/hearth_02.png");
    loadingScreen(56 / totalResources);

    // Disparo
    misil = LoadTexture("resources/images/shot/shot01.png");
    loadingScreen(57 / totalResources);

    // Explosión misil
    explosionTx[0] = LoadTexture("resources/images/shot/burst01.png");
    loadingScreen(58 / totalResources);
    explosionTx[1] = LoadTexture("resources/images/shot/burst02.png");
    loadingScreen(59 / totalResources);
    explosionTx[2] = LoadTexture("resources/images/shot/burst03.png");
    loadingScreen(60 / totalResources);
}

// ---- Descarga texturas ----
void unloadTextures()
{
    ClearBackground(BLACK);
    DrawText("ADIOS", SCR_HEIGHT / 2 - MeasureText("ADIOS", 90) / 2, SCR_HEIGHT / 2, 90, WHITE);
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

    for (int i = 0; i < totalcinema; i++)
    {
        UnloadTexture(cinema[i]);
    }
    UnloadTexture(shield);
    UnloadTexture(grayMeteor);
    UnloadTexture(brownMeteor);
    UnloadTexture(questionTx);
    UnloadTexture(scoreLevel);
    UnloadTexture(pausebg);
}

// ---- Carga sonidos ----
void loadSounds()
{
    // ---- Carga sonidos ----
    menuMusic = LoadMusicStream("resources/sounds/mainmenu.mp3"); // Musica menu principal
    loadingScreen(61 / totalResources);
    gameMusic = LoadMusicStream("resources/sounds/music.mp3");   // Musica partida
    gameover = LoadMusicStream("resources/sounds/gameover.mp3"); // Musica gameover
    loadingScreen(62 / totalResources);
    soundcoin = LoadSound("resources/sounds/coin.wav"); // Sonido moneda
    shotSound = LoadSound("resources/sounds/shot.mp3"); // Sonido misil
    loadingScreen(63 / totalResources);
    burstShotSound = LoadSound("resources/sounds/burstMisil.mp3"); // Sonido explosion misil
    colision = LoadSound("resources/sounds/colision.mp3");
    loadingScreen(64 / totalResources);
    correct = LoadSound("resources/sounds/correct.mp3");
    error = LoadSound("resources/sounds/error.mp3");
    loadingScreen(65 / totalResources);
    liveX = LoadSound("resources/sounds/liveX.mp3");
    p_Up = LoadSound("resources/sounds/pUp.mp3");
    loadingScreen(66 / totalResources);
    liveFull = LoadSound("resources/sounds/liveFull.mp3");

    // Descargar texturas de pantalla de carga
    UnloadTexture(shipLoading);
    UnloadTexture(loadingscreen);
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
    UnloadSound(colision);
    UnloadSound(correct);
    UnloadSound(error);
    UnloadSound(liveX);
    UnloadSound(p_Up);
    UnloadSound(liveFull);
}

// ---- Pantalla de carga inicial ----
void loadingScreen(float progress)
{
    BeginDrawing();
    DrawTexture(loadingscreen, 0, 0, WHITE);
    DrawText("COSMIC CHAOS", SCR_WIDTH / 2 - MeasureText("COSMIC CHAOS", 100) / 2, 120, 100, WHITE);
    DrawText("Cargando...", SCR_WIDTH / 2 - MeasureText("Cargando...", 70) / 2, SCR_HEIGHT / 2 + 100, 70, WHITE);

    // Ajuste de la posición y tamaño de la barra de carga
    int barWidth = 500;
    int barHeight = 30;
    int barX = SCR_WIDTH / 2 - barWidth / 2;
    int barY = SCR_HEIGHT / 2 + 190;
    DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);
    DrawRectangle(barX, barY, (int)(barWidth * progress), barHeight, SKYBLUE);
    DrawTexture(shipLoading, (barX + (int)(barWidth * progress)) - 20, barY + (30 / 2 - shipLoading.height / 2), WHITE);

    EndDrawing();
}