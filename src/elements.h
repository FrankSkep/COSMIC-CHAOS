/*--- CONSTANTES ---*/
#define SCR_WIDTH 1600     // ANCHO PANTALLA (X)
#define SCR_HEIGHT 900     // ALTO PANTALLA (Y)
#define MAX_INPUT_CHARS 30 // MAX CARACTERES PARA EL NOMBRE

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
#define MAX_SHOTS 1       // Número máximo de disparos en pantalla
#define SHOT_SPEED 900.0f // Velocidad del misil
#define SHOT_RADIUS 6     // Tamaño

/*--------- STRUCTS ---------*/
typedef struct
{
    Vector2 position;
    bool active;
} GameObject;

typedef struct
{
    Vector2 position;
    bool active;
    bool collided;        // Bandera colision misil
    float explosionTimer; // Duracion de la animación de explosión
} Shot;

/*--------- INSTANCIAS DE STRUCTs ---------*/
GameObject grayMeteors[MAX_GRAY_METEORS];
GameObject brownMeteors[MAX_BROWN_METEORS];
GameObject coinGold[MAX_COINS];
GameObject coinRed[MAX_COINS];
GameObject hearts[MAX_HEARTS];
Shot shots[MAX_SHOTS];