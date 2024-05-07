#define SCR_WIDTH 1600  // ANCHO PANTALLA (X)
#define SCR_HEIGHT 900  // ALTO PANTALLA (Y)
#define MAX_PLAYERS 100 // MAXIMOS JUGADORES A GUARDAR
#define MAX_LEN_NAME 30 // LONGITUD MAXIMA DEL NICK
#define PREG_SELEC 15
#define TOTAL_PREG 22

/*----- CANTIDAD DE OBJETOS POR NIVEL -----*/
#define MAX_METEOR_LV1 5
#define MAX_METEOR_LV2 15
#define MAX_METEOR_LV3 30

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

/*---- CORAZONES ----*/
#define MAX_HEARTS 1            // Maximos corazones en pantalla
#define HEARTS_SPEED 9.0f       // Velocidad de caida
const float HEARTS_RADIUS = 20; // Tamaño

/*---- DISPAROS ----*/
#define MAX_SHOTS 1       // Maximos disparos en pantalla
#define SHOT_SPEED 900.0f // Velocidad del misil
#define SHOT_RADIUS 6     // Tamaño

/*--------- STRUCTS ---------*/
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
    int maxCorrectAnswers;
    int dia;
    int mes;
    int anio;
} Tdata;

typedef struct _preguntas
{
    char pregunta[60];
    char opciones[4][20];
    int respuestaCorrecta;
} Tpregunta;

/*--------- INSTANCIAS DE STRUCTs ---------*/
TGameObject grayMeteors[MAX_METEOR_LV3];
TGameObject brownMeteors[MAX_METEOR_LV3];
TGameObject coinGold[MAX_COINS];
TGameObject coinRed[MAX_COINS];
TGameObject hearts[MAX_HEARTS];
Tshot shots[MAX_SHOTS];
Tpregunta preguntas[TOTAL_PREG];