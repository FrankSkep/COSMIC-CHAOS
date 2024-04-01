#ifndef RESOURCES_H
#define RESOURCES_H
#include "raylib.h"

/*---------------- PROTOTIPOS ----------------*/
void loadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *grayMeteor, Texture2D *brownMeteor, Texture2D *coinsTx, Texture2D *heartsTx, Texture2D *heartsFTx, Texture2D *heartsETx, Texture2D *misil, Texture2D *explosion);
void unloadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *grayMeteor, Texture2D *brownMeteor, Texture2D *coinsTx, Texture2D *heartsTx, Texture2D *heartsFTx, Texture2D *heartsETx, Texture2D *misil, Texture2D *explosion);
void loadSounds(Music *game, Music *gameover, Sound *coin, Sound *shot, Sound *burstMisil);
void unloadSounds(Music *game, Music *gameover, Sound *coin, Sound *shot, Sound *burstMisil);

/*---------------- DESARROLLO ----------------*/

// ---- Carga texturas ----
void loadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *grayMeteor, Texture2D *brownMeteor, Texture2D *coinsTx, Texture2D *heartsTx, Texture2D *heartsFTx, Texture2D *heartsETx, Texture2D *misil, Texture2D *explosion)
{
    // Fondo menu principal
    *menu = LoadTexture("resources/images/backgrounds/menu.png");

    // Fondo partida
    *gamebg = LoadTexture("resources/images/backgrounds/game.png");

    // Fondo gameover
    *gameover = LoadTexture("resources/images/backgrounds/gameover.png");

    // Presentador
    cinema[0] = LoadTexture("resources/images/backgrounds/cinema1.png");
    cinema[1] = LoadTexture("resources/images/backgrounds/cinema2.png");
    cinema[2] = LoadTexture("resources/images/backgrounds/cinema3.png");
    cinema[3] = LoadTexture("resources/images/backgrounds/cinema4.png");
    cinema[4] = LoadTexture("resources/images/backgrounds/cinema5.png");
    cinema[5] = LoadTexture("resources/images/backgrounds/cinema6.png");
    cinema[6] = LoadTexture("resources/images/backgrounds/cinema7.png");
    cinema[7] = LoadTexture("resources/images/backgrounds/cinema8.png");
    cinema[8] = LoadTexture("resources/images/backgrounds/cinema9.png");

    // Nave
    shipTx[0] = LoadTexture("resources/images/ship/ship01.png");
    shipTx[1] = LoadTexture("resources/images/ship/ship01.png");
    shipTx[2] = LoadTexture("resources/images/ship/ship02.png");
    shipTx[3] = LoadTexture("resources/images/ship/ship02.png");
    shipTx[4] = LoadTexture("resources/images/ship/ship03.png");
    shipTx[5] = LoadTexture("resources/images/ship/ship03.png");

    // Meteoros
    *grayMeteor = LoadTexture("resources/images/meteors/grayMeteor.png");
    *brownMeteor = LoadTexture("resources/images/meteors/brownMeteor.png");

    // Monedas
    coinsTx[0] = LoadTexture("resources/images/coins/coin_01.png");
    coinsTx[1] = LoadTexture("resources/images/coins/coin_02.png");
    coinsTx[2] = LoadTexture("resources/images/coins/coin_03.png");
    coinsTx[3] = LoadTexture("resources/images/coins/coin_04.png");
    coinsTx[4] = LoadTexture("resources/images/coins/coin_05.png");
    coinsTx[5] = LoadTexture("resources/images/coins/coin_06.png");

    // Corazones
    heartsTx[0] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[1] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[2] = LoadTexture("resources/images/hearts/hearth_01.png");
    heartsTx[3] = LoadTexture("resources/images/hearts/hearth_02.png");
    heartsTx[4] = LoadTexture("resources/images/hearts/hearth_02.png");
    heartsTx[5] = LoadTexture("resources/images/hearts/hearth_02.png");

    heartsFTx[0] = LoadTexture("resources/images/hearts/heathF_00.png");
    heartsFTx[1] = LoadTexture("resources/images/hearts/heathF_01.png");
    heartsFTx[2] = LoadTexture("resources/images/hearts/heathF_02.png");
    heartsFTx[3] = LoadTexture("resources/images/hearts/heathF_00.png");
    heartsFTx[4] = LoadTexture("resources/images/hearts/heathF_01.png");
    heartsFTx[5] = LoadTexture("resources/images/hearts/heathF_02.png");

    heartsETx[0] = LoadTexture("resources/images/hearts/heathE_00.png");
    heartsETx[1] = LoadTexture("resources/images/hearts/heathE_01.png");
    heartsETx[2] = LoadTexture("resources/images/hearts/heathE_02.png");
    heartsETx[3] = LoadTexture("resources/images/hearts/heathE_03.png");
    heartsETx[4] = LoadTexture("resources/images/hearts/heathE_04.png");
    heartsETx[5] = LoadTexture("resources/images/hearts/heathE_05.png");

    // Disparo
    misil[0] = LoadTexture("resources/images/shot/shot01.png");
    misil[1] = LoadTexture("resources/images/shot/shot01.png");
    misil[2] = LoadTexture("resources/images/shot/shot02.png");
    misil[3] = LoadTexture("resources/images/shot/shot02.png");
    misil[4] = LoadTexture("resources/images/shot/shot03.png");
    misil[5] = LoadTexture("resources/images/shot/shot03.png");

    // Explosion misil
    explosion[0] = LoadTexture("resources/images/shot/burst01.png");
    explosion[1] = LoadTexture("resources/images/shot/burst02.png");
    explosion[2] = LoadTexture("resources/images/shot/burst03.png");
}

// ---- Descarga texturas ----
void unloadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *grayMeteor, Texture2D *brownMeteor, Texture2D *coinsTx, Texture2D *heartsTx, Texture2D *heartsFTx, Texture2D *heartsETx, Texture2D *misil, Texture2D *explosion)
{
    UnloadTexture(*menu);
    UnloadTexture(*gamebg);
    UnloadTexture(*gameover);

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(shipTx[i]);
        UnloadTexture(coinsTx[i]);
        UnloadTexture(heartsTx[i]);
        UnloadTexture(heartsFTx[i]);
        UnloadTexture(heartsETx[i]);
        UnloadTexture(explosion[i]);
    }

    for (int i = 0; i < 9; i++)
    {
        UnloadTexture(cinema[i]);
    }

    UnloadTexture(*grayMeteor);
    UnloadTexture(*brownMeteor);
}

// ---- Carga sonidos ----
void loadSounds(Music *game, Music *gameover, Sound *coin, Sound *shot, Sound *burstMisil)
{
    *game = LoadMusicStream("resources/sounds/music.mp3");        // Musica partida
    *gameover = LoadMusicStream("resources/sounds/gameover.mp3"); // Musica gameover
    *coin = LoadSound("resources/sounds/coin.wav");               // Sonido moneda
    *shot = LoadSound("resources/sounds/shot.mp3");               // Sonido misil
    *burstMisil = LoadSound("resources/sounds/burstMisil.mp3");
}

// ---- Descarga sonidos ----
void unloadSounds(Music *game, Music *gameover, Sound *coin, Sound *shot, Sound *burstMisil)
{
    UnloadMusicStream(*game);
    UnloadMusicStream(*gameover);
    UnloadSound(*coin);
    UnloadSound(*shot);
    UnloadSound(*burstMisil);
}

#endif