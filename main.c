#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOMBRE 50 /** Usamos define para definir el valor máximo de caracteres para el nombre en la estructura Boleto de cine**/
#define MAX_APELLIDO 50 /**Al igual que el anterior, define el valor máximo de caracteres para el apellido en la estructura Boleto de cine**/
#define MAX_CEDULA 20 /** Este define el valor máximo de caracteres para el número de cédula en la estructura Boleto de cine**/
#define MAX_PELICULA 100 /** Y por ultimo tenemos a este que define el valor máximo de caracteres para el nombre de la película en la estructura Boleto de cine**/

/** Luego se define de la estructura para almacenar los datos del boleto**/
typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char cedula[MAX_CEDULA];
    int sala;
    char puesto[3]; /**Lo utilizmaos para almacenar la letra y el número del puesto**/
    char hora[10];
    char pelicula[MAX_PELICULA];
} Boleto;

int main() {
    /** Creamos una instancia de la estructura Boleto de cine para almacenar los datos del boleto**/
    Boleto boleto;

    /**Imprimimos para sollicitar los datos del usuario**/
    printf("Ingrese su nombre: ");
    fgets(boleto.nombre, sizeof(boleto.nombre), stdin); /**Utilizamos el fgets para leer cadenas de texto (nombre, apellido, cédula, película) y stdin para leer los datos ingresados por el usuario desde la consola**/
    boleto.nombre[strcspn(boleto.nombre, "\n")] = 0; /** Eliminamos el salto de línea y utilizamos el strcspn para eliminar el carácter de salto de línea (\n) que se agrega automáticamente cuando se lee una cadena con fgets **/

    /**Al igual que con el nombre lo empleamos tambien con los datos restantes para colocarlos en el boleto**/
    printf("Ingrese su apellido: ");
    fgets(boleto.apellido, sizeof(boleto.apellido), stdin);
    boleto.apellido[strcspn(boleto.apellido, "\n")] = 0;

    printf("Ingrese su numero de cedula: ");
    fgets(boleto.cedula, sizeof(boleto.cedula), stdin);
    boleto.cedula[strcspn(boleto.cedula, "\n")] = 0;

    printf("Ingrese el numero de sala: ");
    scanf("%d", &boleto.sala);

    printf("Ingrese la letra del puesto (A-Z): ");
    scanf(" %c", &boleto.puesto[0]); /**Lo ponemos para leer la letra del puesto**/

    printf("Ingrese el numero del puesto (1-99): ");
    scanf("%s", &boleto.puesto[1]); /** Lo ponemos para el número del puesto **/

    printf("Ingrese la hora de la funcion (HH:MM): "); /** El HH:MM para colocar los 2 digitos de la hora y los 2 digitos de los minutos**/
    scanf("%s", boleto.hora);

    printf("Ingrese el nombre de la pelicula: ");
    getchar(); /**Limpiamos el buffer de entrada antes de leer la cadena**/
    fgets(boleto.pelicula, sizeof(boleto.pelicula), stdin);
    boleto.pelicula[strcspn(boleto.pelicula, "\n")] = 0; /** Eliminamos el salto de línea nuevamente**/

    /** Generamos el archivo de texto para el boleto**/
    FILE *archivo_boleto;
    archivo_boleto = fopen("boleto_cine.txt", "w"); /**Se utiliza FILE y fopen para abrir un archivo de texto en modo escritura ("w")**/

    if (archivo_boleto != NULL) {
        /** Obtenemos la fecha y hora actual**/
        /**Obtenemos la fecha y hora actual usando time y localtime **/
        time_t ahora;
        time(&ahora);
        char fecha_hora[50];
        strftime(fecha_hora, sizeof(fecha_hora), "%Y-%m-%d %H:%M:%S", localtime(&ahora)); /** Con "%Y-%m-%d %H:%M:%S" Representamos los dias de 1 a 31,los meses de 1 a 12 y el año con 4 digitos, y las horas en formato de 24 con 2 digitos y por utlimos con un maximo de 59 minutos y segundos. Y luego usamos strftime para formatear una estructura de tiempo**/

        /** Escribimos todos los datos del boleto en el archivo**/
        fprintf(archivo_boleto, "---------------------------------\n"); /**Se usa fprintf para escribir los datos del boleto en el archivo de texto**/
        fprintf(archivo_boleto, "        Boleto de Cine\n");
        fprintf(archivo_boleto, "---------------------------------\n");
        fprintf(archivo_boleto, "Fecha y hora: %s\n", fecha_hora);
        fprintf(archivo_boleto, "Nombre: %s %s\n", boleto.nombre, boleto.apellido);
        fprintf(archivo_boleto, "Cédula: %s\n", boleto.cedula);
        fprintf(archivo_boleto, "Sala: %d\n", boleto.sala);
        fprintf(archivo_boleto, "Puesto: %c%s\n", boleto.puesto[0], boleto.puesto + 1); /**Imprimimos la letra y el número del puesto**/
        fprintf(archivo_boleto, "Hora de la función: %s\n", boleto.hora);
        fprintf(archivo_boleto, "Película: %s\n", boleto.pelicula);
        fprintf(archivo_boleto, "---------------------------------\n");

        printf("Boleto generado correctamente. Se ha creado el archivo 'boleto_cine.txt'.\n");

        fclose(archivo_boleto);
    } else {
        printf("Hubo un error al crear el archivo de boleto.\n"); /**Si los datos no estan bien colocados aparecera esto**/
    }

    return 0;
}
