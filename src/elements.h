/*--- CONSTANTES ---*/
#define SCR_WIDTH 1600     // ANCHO PANTALLA (X)
#define SCR_HEIGHT 900     // ALTO PANTALLA (Y)
#define MAX_INPUT_CHARS 30 // MAX CARACTERES PARA EL NOMBRE
#define MAX_PLAYERS 100

/*------ OBSTACULOS POR NIVEL ------*/
#define MAX_METEOR_LV1 5
#define MAX_METEOR_LV2 15
#define MAX_METEOR_LV3 30
/* Cantidad inicial */
short MAX_GRAY = MAX_METEOR_LV1;  // Maximos meteoros gris por nivel
short MAX_BROWN = MAX_METEOR_LV1; // Maximos meteoros cafe por nivel

/*------- OBSTACULOS DEL JUEGO -------*/
// Meteoro gris
#define MAX_GRAY_METEORS 40          // Maximos meteoros en pantalla
#define GRAY_METEOR_SPEED 7.0f       // Velocidad de caida
const float GRAY_METEOR_RADIUS = 60; // Tamaño
// Meteoro cafe
#define MAX_BROWN_METEORS 10          // Maximos meteoros en pantalla
#define BROWN_METEOR_SPEED 9.0f       // Velocidad de caida
const float BROWN_METEOR_RADIUS = 40; // Tamaño

/*------- OBJETOS DEL JUEGO -------*/
// Monedas
#define MAX_COINS 2            // Maximas monedas en pantalla
#define COINS_SPEED 8.0f       // Velocidad de caida
const float COINS_RADIUS = 20; // Tamaño
// Corazones
#define MAX_HEARTS 1            // Maximos corazones en pantalla
#define HEARTS_SPEED 9.0f       // Velocidad de caida
const float HEARTS_RADIUS = 20; // Tamaño
// Disparos
#define MAX_SHOTS 1       // Numero máximo de disparos en pantalla
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
    char name[MAX_INPUT_CHARS + 1];
    int maxLevel;
    int score;
    int dia;
    int mes;
    int anio;
} Tdata;

typedef struct
{
    const char *pregunta;
    const char *opciones[4];
    int respuestaCorrecta; // indice de la respuesta correcta (0, 1, 2 o 3)
} Pregunta;

/*--------- INSTANCIAS DE STRUCTs ---------*/
TGameObject grayMeteors[MAX_GRAY_METEORS];
TGameObject brownMeteors[MAX_BROWN_METEORS];
TGameObject coinGold[MAX_COINS];
TGameObject coinRed[MAX_COINS];
TGameObject hearts[MAX_HEARTS];
Tshot shots[MAX_SHOTS];

Pregunta preguntas[] = {
    {"¿Cuál es el cuarto planeta del sistema solar?", // 1
     {"Venus", "Marte", "Jupiter", "Urano"},
     1},
    {"¿Cual es el tercer planeta del sistema solar?", // 2
     {"Mercurio", "Tierra", "Jupiter", "Marte"},
     1},
    {"¿Cuál es el quinto planeta del sistema solar?", // 3
     {"Marte", "Jupiter", "Tierra", "Saturno"},
     1},
    {"¿Cuál es el sexto planeta del sistema solar?", // 4
     {"Tierra", "Saturno", "Jupiter", "Urano"},
     1},
    {"¿Cuál es el séptimo planeta del sistema solar?", // 5
     {"Venus", "Urano", "Neptuno", "Saturno"},
     1},
    {"¿Cuál es el octavo planeta del sistema solar?", // 6
     {"Urano", "Neptuno", "Urano", "Venus"},
     1},
    {"¿Cuál es el primer planeta del sistema solar?", // 7
     {"Plutón", "Mercurio", "Tierra", "Marte"},
     1},
    {"¿Cuantos planetas tiene el sistema solar?", // 8
     {"10", "8", "12", "14"},
     1},
    {"¿Cuál es el planeta mas caliente del sistema solar?", // 9
     {"Tierra", "Venus", "Neptuno", "Saturno"},
     1},
    {"¿Qué planeta es conocido como el 'Gigante de hielo'?", // 10
     {"Venus", "Jupiter", "Urano", "Neptuno"},
     2},
    {"¿Cuantas lunas tiene marte?", // 11
     {"1", "2", "3", "4"},
     1},
    {"¿Cual es la estrella más cercana a la Tierra?", // 12
     {"Alfa Centauri", "Sol", "Sirio", "Vega"},
     1},
    {"¿Cuál es el planeta más grande del sistema solar?", // 13
     {"Marte", "Jupiter", "Urano", "Saturno"},
     1},
    {"¿Cuál es el planeta más cercano al Sol?", // 14
     {"Venus", "Mercurio", "Tierra", "Marte"},
     1},
    {"¿Cuál es el nombre de la luna de la Tierra?", // 15
     {"Apolo", "Luna", "Ganimedes", "Titán"},
     1},
    {"¿Qué planeta es conocido como el 'Planeta Rojo'?", // 16
     {"Venus", "Marte", "Mercurio", "Jupiter"},
     1},
    {"¿Cuál es el planeta conocido por sus anillos?", // 17
     {"Neptuno", "Saturno", "Urano", "Jupiter"},
     1},
    {"¿Cuál es el planeta más pequeño del sistema solar?", // 18
     {"Saturno", "Mercurio", "Urano", "Neptuno"},
     1},
    {"¿Qué planeta es conocido como el 'Gigante Gaseoso'?", // 19
     {"Mercurio", "Jupiter", "Neptuno", "Saturno"},
     1},
    {"¿Cuál es el planeta más alejado del Sol?", // 20
     {"Plutón", "Neptuno", "Urano", "Saturno"},
     1},
    {"¿Cuntas lunas tiene jupiter?", // 21
     {"2", "95", "75", "15"},
     1},
    {"¿Que planeta tiene la luna mas grande?", // 22
     {"Venus", "Jupiter", "Urano", "Neptuno"},
     1},
};
int numPreguntas = sizeof(preguntas) / sizeof(preguntas[0]);
