/*------------- CONSTANTES -------------*/
/*--- DIMENSIONES PANTALLA ---*/
#define SCR_WIDTH 1600 // ANCHO  (X)
#define SCR_HEIGHT 900 // ALTO (Y)
#define MAX_INPUT_CHARS 20

/* Ajustes Niveles */
#define MAX_METEOR_LV1 5
#define MAX_METEOR_LV2 15
#define MAX_METEOR_LV3 30
/* Cantidad inicial */
short MAX_GRAY = MAX_METEOR_LV1; // Maximos meteoros por nivel
short MAX_BROWN = MAX_METEOR_LV1;

/*------- Atributos  -------*/
/*--- Meteoros ---*/
#define MAX_GRAY_METEORS 40          // Maximos meteoros en pantalla
#define GRAY_METEOR_SPEED 7.0f       // Velocidad de caida
const float GRAY_METEOR_RADIUS = 60; // Tamaño
#define MAX_BROWN_METEORS 10
#define BROWN_METEOR_SPEED 9.0f
const float BROWN_METEOR_RADIUS = 40;
/*--- Objetos ---*/
// Monedas
#define MAX_COINS 2            // Maximas monedas en pantalla
#define COINS_SPEED 8.0f       // Velocidad de caida
const float COINS_RADIUS = 20; // Tamaño
// Corazones
#define MAX_HEARTS 1            // Maximos corazones en pantalla
#define HEARTS_SPEED 9.0f       // Velocidad de caida
const float HEARTS_RADIUS = 20; // Tamaño
// Disparos
#define MAX_SHOTS 1 // Número máximo de disparos en pantalla
#define SHOT_SPEED 900.0f
#define SHOT_RADIUS 6 // Radio de los disparos

/*--------- STRUCT ELEMENTOS DEL JUEGO ---------*/
typedef struct
{
    Vector2 position;
    bool active;
} GameObject;

typedef struct
{
    Vector2 position;
    bool active;
    bool collided;
    float explosionTimer; // Duracion de la animación de explosión
} Shot;

/*--------- INSTANCIAS DE STRUCT 'GameObject' ---------*/
GameObject grayMeteors[MAX_GRAY_METEORS];
GameObject brownMeteors[MAX_BROWN_METEORS];
GameObject coinGold[MAX_COINS];
GameObject coinRed[MAX_COINS]; // Coin 2
GameObject hearts[MAX_HEARTS];
Shot shots[MAX_SHOTS];