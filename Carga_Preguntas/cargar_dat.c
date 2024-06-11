#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_PREG 42
#define PREG_ELEG 20

typedef struct _preguntas
{
    char pregunta[90];
    char opciones[4][20];
    int respuestaCorrecta;
} Tpregunta;

void llenarArchivo();
void leerArchivo();
int busqSecuencial(int vect[], int m, int num);

int main()
{
    srand(time(NULL));

    // descomenta esto para llenar el archivo con las preguntas q quieras, para leerlo comentalo
    //llenarArchivo();
    leerArchivo();
}

void llenarArchivo()
{
    Tpregunta preguntasx[TOTAL_PREG] = {
        {"- Cual es el cuarto planeta del sistema solar?  ", // 1
         {"Venus", "Marte", "Jupiter", "Urano"},
         1},
        {"- Cual es el tercer planeta del sistema solar?  ", // 2
         {"Mercurio", "Tierra", "Jupiter", "Marte"},
         1},
        {"- Cual es el quinto planeta del sistema solar?  ", // 3
         {"Marte", "Jupiter", "Tierra", "Saturno"},
         1},
        {"- Cual es el sexto planeta del sistema solar?  ", // 4
         {"Tierra", "Saturno", "Jupiter", "Urano"},
         1},
        {"- Cual es el septimo planeta del sistema solar?  ", // 5
         {"Venus", "Urano", "Neptuno", "Saturno"},
         1},
        {"- Cual es el octavo planeta del sistema solar?  ", // 6
         {"Urano", "Neptuno", "Saturno", "Venus"},
         1},
        {"- Cual es el primer planeta del sistema solar?  ", // 7
         {"Pluton", "Mercurio", "Tierra", "Marte"},
         1},
        {"- Cuantos planetas tiene el sistema solar?  ", // 8
         {"10", "8", "12", "14"},
         1},
        {"- Cual es el planeta mas caliente del sistema solar?  ", // 9
         {"Tierra", "Venus", "Neptuno", "Saturno"},
         1},
        {"- Que planeta es conocido como el 'Gigante de hielo'?  ", // 10
         {"Venus", "Jupiter", "Urano", "Neptuno"},
         1},
        {"- Cuantas lunas tiene marte?  ", // 11
         {"1", "2", "3", "4"},
         1},
        {"- Cual es la estrella mas cercana a la Tierra?  ", // 12
         {"Alfa Centauri", "Sol", "Sirio", "Vega"},
         1},
        {"- Cual es el planeta mas grande del sistema solar?  ", // 13
         {"Marte", "Jupiter", "Urano", "Saturno"},
         1},
        {"- Cual es el planeta mas cercano al Sol?  ", // 14
         {"Venus", "Mercurio", "Tierra", "Marte"},
         1},
        {"- Cual es el nombre de la luna de la Tierra?  ", // 15
         {"Apolo", "Luna", "Ganimedes", "Titan"},
         1},
        {"- Que planeta es conocido como el 'Planeta Rojo'?  ", // 16
         {"Venus", "Marte", "Mercurio", "Jupiter"},
         1},
        {"- Cual es el planeta conocido por sus anillos?  ", // 17
         {"Neptuno", "Saturno", "Urano", "Jupiter"},
         1},
        {"- Cual es el planeta mas chico del sistema solar?  ", // 18
         {"Saturno", "Mercurio", "Urano", "Neptuno"},
         1},
        {"- Que planeta es conocido como el 'Gigante Gaseoso'?  ", // 19
         {"Mercurio", "Jupiter", "Neptuno", "Saturno"},
         1},
        {"- Cual es el planeta mas alejado del Sol?  ", // 20
         {"Pluton", "Neptuno", "Urano", "Saturno"},
         1},
        {"- Cuntas lunas tiene jupiter?  ", // 21
         {"2", "95", "75", "15"},
         1},
        {"- Que planeta tiene la luna mas grande?  ", // 22
         {"Venus", "Jupiter", "Urano", "Neptuno"},
         1},
        {"- Que planeta tiene la luna mas grande?  ", // 23
         {"Venus", "Jupiter", "Urano", "Neptuno"},
         1},
        {"- Cuantas lunas tiene Saturno?  ", // 24
         {"62", "33", "17", "50"},
         1},
        {"- Cual es el nombre de la luna de Marte?  ", // 25
         {"Luna", "Fobos", "Deimos", "Ganimedes"},
         1},
        {"- Cuantas lunas tiene Urano?  ", // 26
         {"13", "27", "9", "4"},
         1},
        {"- Cual es el planeta conocido por sus tormentas?  ", // 27
         {"Saturno", "Neptuno", "Urano", "Jupiter"},
         1},
        {"- Que planeta tiene el periodo de rotacion mas corto?  ", // 28
         {"Jupiter", "Saturno", "Mercurio", "Venus"},
         1},
        {"- Cual es el planeta mas denso del sistema solar?  ", // 29
         {"Tierra", "Jupiter", "Saturno", "Urano"},
         1},
        {"- Cual es el planeta con mayor numero de lunas conocidas?  ", // 30
         {"Jupiter", "Saturno", "Neptuno", "Urano"},
         1},
        {"- Que planeta tiene la mayor excentricidad orbital?  ", // 31
         {"Marte", "Mercurio", "Urano", "Pluton"},
         1},
        {"- Cual es el planeta mas frio del sistema solar?  ", // 32
         {"Venus", "Urano", "Jupiter", "Neptuno"},
         1},
        {"- Cuantos anillos tiene Saturno?  ", // 33
         {"10", "20", "30", "40"},
         1},
        {"- Que planeta tiene la mayor inclinacion axial?  ", // 34
         {"Urano", "Jupiter", "Marte", "Venus"},
         1},
        {"- Cual es el planeta mas brillante en el cielo nocturno?  ", // 35
         {"Marte", "Venus", "Jupiter", "Saturno"},
         1},
        {"- Cual es el periodo orbital de Venus?  ", // 36
         {"225 dias", "365 dias", "687 dias", "1 dia"},
         1},
        {"- Que planeta tiene el mayor numero de satelites naturales?  ", // 37
         {"Saturno", "Jupiter", "Urano", "Neptuno"},
         1},
        {"- Cuantas estrellas hay en el sistema Alfa Centauri?  ", // 38
         {"1", "2", "3", "4"},
         1},
        {"- Cuantos dias terrestres tarda Neptuno en orbitar el Sol?  ", // 39
         {"30,660 dias", "   365 dias", "4,380", "17,520"},
         1},
        {"- Cuantos planetas en el sistema solar tienen anillos?  ", // 40
         {"4", "2", "7", "9"},
         1},
        {"- Cual es la distancia promedio de la Tierra al Sol?  ", // 41
         {"150 millones de km", "100 millones de km", "200 millones de km", "300 millones de km"},
         1},
        {"- Cual es el planeta mas masivo del sistema solar?  ", // 42
         {"Jupiter", "Saturno", "Tierra", "Urano"},
         1},
    };

    FILE *archivo = fopen("preguntas.dat", "wb");
    for (int i = 0; i < TOTAL_PREG; i++)
    {
        fwrite(&preguntasx[i], sizeof(Tpregunta), 1, archivo);
    }
    fclose(archivo);
}

void leerArchivo()
{
    FILE *pregsArch = fopen("preguntas.dat", "rb");

    if (pregsArch == NULL)
    {
        printf("Error al abrir\n");
    }

    // Posiciones aleatorias para elegir las preguntas
    int posiciones[PREG_ELEG];
    int pos;
    for (int i = 0; i < PREG_ELEG; i++)
    {
        do
        {
            pos = rand() % TOTAL_PREG;
        } while (busqSecuencial(posiciones, i, pos) != -1);
        posiciones[i] = pos;
        printf("Posicion: %d\n", posiciones[i]);
    }

    Tpregunta preg;
    printf("TOTAL PREGUNTAS:\n");
    int i = 1;
    while (fread(&preg, sizeof(Tpregunta), 1, pregsArch))
    {
        printf("%d : Pregunta: %s | Respuesta : %d\n", i++, preg.pregunta, preg.respuestaCorrecta);
    }
    // Tpregunta preg[PREG_ELEG]; // Arreglo para las preguntas elegidas
    // for (int i = 0; i < PREG_ELEG; i++)
    // {
    //     fseek(pregsArch, posiciones[i] * sizeof(Tpregunta), SEEK_SET);
    //     fread(&preg[i], sizeof(Tpregunta), 1, pregsArch);
    // }

    // printf("PREGUNTAS SELECCIONADAS DEL TOTAL:\n");
    // for (int i = 0; i < PREG_ELEG; i++)
    // {
    //     printf("Pregunta: %s\n", preg[i].pregunta);
    // }

    fclose(pregsArch);
}

int busqSecuencial(int vect[], int m, int num)
{
    for (int i = 0; i < m; i++)
    {
        if (vect[i] == num)
        {
            return i;
        }
    }
    return -1;
}
