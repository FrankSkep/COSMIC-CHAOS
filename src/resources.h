#ifndef RESOURCES_H
#define RESOURCES_H
#include "raylib.h"

/*---------------- PROTOTIPOS ----------------*/
void loadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *coinsTx, Texture2D *heartsTx);
void unloadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *coinsTx, Texture2D *heartsTx);
void loadSounds(Music *game, Music *gameover, Sound *coin);
void unloadSounds(Music *game, Music *gameover, Sound *coin);

/*---------------- DESARROLLO ----------------*/

// ---- Carga texturas ----
void loadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *coinsTx, Texture2D *heartsTx)
{
    // Fondo menu principal
    *menu = LoadTexture("images/backgrounds/menu.png");

    // Fondo partida
    *gamebg = LoadTexture("images/backgrounds/game.png");

    // Fondo gameover
    *gameover = LoadTexture("images/backgrounds/gameover.png");

    // presentador
    cinema[0] = LoadTexture("images/backgrounds/cinema1.png");
    cinema[1] = LoadTexture("images/backgrounds/cinema2.png");
    cinema[2] = LoadTexture("images/backgrounds/cinema3.png");
    cinema[3] = LoadTexture("images/backgrounds/cinema4.png");
    cinema[4] = LoadTexture("images/backgrounds/cinema5.png");
    cinema[5] = LoadTexture("images/backgrounds/cinema6.png");
    cinema[6] = LoadTexture("images/backgrounds/cinema7.png");
    cinema[7] = LoadTexture("images/backgrounds/cinema8.png");

    // Nave
    shipTx[0] = LoadTexture("images/ship/ship01.png");
    shipTx[1] = LoadTexture("images/ship/ship01.png");
    shipTx[2] = LoadTexture("images/ship/ship02.png");
    shipTx[3] = LoadTexture("images/ship/ship02.png");
    shipTx[4] = LoadTexture("images/ship/ship03.png");
    shipTx[5] = LoadTexture("images/ship/ship03.png");

    // Monedas
    coinsTx[0] = LoadTexture("images/coins/coin_01.png");
    coinsTx[1] = LoadTexture("images/coins/coin_02.png");
    coinsTx[2] = LoadTexture("images/coins/coin_03.png");
    coinsTx[3] = LoadTexture("images/coins/coin_04.png");
    coinsTx[4] = LoadTexture("images/coins/coin_05.png");
    coinsTx[5] = LoadTexture("images/coins/coin_06.png");

    // Corazones
    heartsTx[0] = LoadTexture("images/hearts/hearth_01.png");
    heartsTx[1] = LoadTexture("images/hearts/hearth_01.png");
    heartsTx[2] = LoadTexture("images/hearts/hearth_01.png");
    heartsTx[3] = LoadTexture("images/hearts/hearth_02.png");
    heartsTx[4] = LoadTexture("images/hearts/hearth_02.png");
    heartsTx[5] = LoadTexture("images/hearts/hearth_02.png");
}

// ---- Descarga texturas ----
void unloadTextures(Texture2D *menu, Texture2D *gamebg, Texture2D *gameover, Texture2D *cinema, Texture2D *shipTx, Texture2D *coinsTx, Texture2D *heartsTx)
{
    UnloadTexture(*menu);
    UnloadTexture(*gamebg);
    UnloadTexture(*gameover);
    UnloadTexture(cinema[1]);
    UnloadTexture(cinema[2]);

    for (int i = 0; i < 6; i++)
    {
        UnloadTexture(shipTx[i]);
        UnloadTexture(coinsTx[i]);
        UnloadTexture(heartsTx[i]);
    }
}

// ---- Carga sonidos ----
void loadSounds(Music *game, Music *gameover, Sound *coin)
{
    *game = LoadMusicStream("sounds/music.mp3");        // Musica partida
    *gameover = LoadMusicStream("sounds/gameover.mp3"); // Musica gameover
    *coin = LoadSound("sounds/coin.wav");               // Sonido moneda
}

// ---- Descarga sonidos ----
void unloadSounds(Music *game, Music *gameover, Sound *coin)
{
    UnloadMusicStream(*game);
    UnloadMusicStream(*gameover);
    UnloadSound(*coin);
}

#endif