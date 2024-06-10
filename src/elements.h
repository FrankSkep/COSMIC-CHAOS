#define SCR_WIDTH 1600  // ANCHO PANTALLA (X)
#define SCR_HEIGHT 900  // ALTO PANTALLA (Y)
#define MAX_PLAYERS 100 // MAXIMOS JUGADORES A GUARDAR
#define MAX_LEN_NAME 30 // LONGITUD MAXIMA DEL NICK
#define PREG_SELEC 20
#define TOTAL_PREG 22

#define PTS_LEVEL_UP 80
/*----- CANTIDAD DE OBJETOS POR NIVEL -----*/
#define MAX_METEOR_LV1 5
#define MAX_METEOR_LV2 15
#define MAX_METEOR_LV3 30
#define MAX_HEART_LV1 1
#define MAX_HEART_LV2 2
#define MAX_HEART_LV3 3

/*---- METEORO GRIS ----*/
short MAX_GRAY = MAX_METEOR_LV1;     // Maximos meteoros gris por nivel
#define GRAY_METEOR_SPEED 7.0f       // Velocidad de caida
const float GRAY_METEOR_RADIUS = 60; // Tamaño

/*---- METEORO CAFE ----*/
short MAX_BROWN = MAX_METEOR_LV1;     // Maximos meteoros cafe por nivel
#define BROWN_METEOR_SPEED 9.0f       // Velocidad de caida
const float BROWN_METEOR_RADIUS = 40; // Tamaño

/*---- MONEDAS ----*/
#define MAX_COINS 2            // Maximas monedas en pantalla
#define COINS_SPEED 8.0f       // Velocidad de caida
const float COINS_RADIUS = 20; // Tamaño

#define MAX_OBJECT 1      // Maximas POWER-UPS
#define AMMO_SPEED 6.5f   // Velocidad de caida
#define SHIELD_SPEED 5.0f // Velocidad de caida

/*---- CORAZONES ----*/
short MAX_HEART = MAX_HEART_LV1;
#define HEARTS_SPEED 9.0f       // Velocidad de caida
const float HEARTS_RADIUS = 20; // Tamaño

/*---- DISPAROS ----*/
#define MAX_SHOTS 10      // Maximos disparos en pantalla
#define SHOT_SPEED 900.0f // Velocidad del misil
#define SHOT_RADIUS 6     // Tamaño

// ENUM Estados del juego
typedef enum
{
    MAIN_MENU,
    IN_GAME,
    GAME_OVER,
    HOW_TO_PLAY,
    ABOUT_GAME,
    HISTORY_SCORE,
    PAUSE
} GameState;

/*--------- STRUCTS ---------*/

typedef struct
{
    short lives;
    int score;
    short level;
    short rachaAciertos;
    short totalMunicion;
    float timeseconds;
} GameStats;

typedef struct _object
{
    Vector2 position;
    bool active;
} TGameObject;

typedef struct _ball
{
    Vector2 position;
    bool active;
    bool collided;        // Bandera colision misil
    float explosionTimer; // Duracion de la animación de explosión
} Tshot;

typedef struct _playerData
{
    char name[MAX_LEN_NAME];
    int maxLevel;
    int score;
    int rachaAciertos;
    int dia;
    int mes;
    int anio;
} Tdata;

typedef struct _preguntas
{
    char pregunta[90];
    char opciones[4][20];
    int respuestaCorrecta;
} Tpregunta;

/*--------- INSTANCIAS DE STRUCTs ---------*/
TGameObject grayMeteors[MAX_METEOR_LV3];  // Meteoros gris
TGameObject brownMeteors[MAX_METEOR_LV3]; // Meteoros cafe
TGameObject coinGold[MAX_COINS];          // Monedas
TGameObject shieldB[MAX_OBJECT];          // Escudos
TGameObject municiones[MAX_OBJECT];       // Municiones
TGameObject hearts[MAX_HEART_LV3];        // Corazones (vidas)
Tshot shots[MAX_SHOTS];                   // Misiles
Tpregunta preguntas[TOTAL_PREG];          // Preguntas
