//Usar junto con "write_simple_buffer.c"
//Desc: lee tres campos (int, double y string) en desde un archivo
//en una sola operacion de lectura y los coloca en un bloque
//de memoria. Luego extrae los campos individuales a varibles
//por medio de aritmética de punteros
//   buffer --> |entero|double|  char*  |
//              |  4B  |  8B  |    9B   |    (en x86)
#include <stdio.h>

int main()
{
    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "practica1.dat";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("---------------------------------------------------------\n");
    
    int NUMCHARS = 8;	//cantidad de caracteres a leer

    //variables para los campos individuales
    int entero;
    double doble;
    char *cadena;
    char *cadena2;


    //obtencion de los tamaños de variable
    int tamInt = (int) sizeof(int);
    int tamDoble = (int) sizeof(double);
    int tamString = (int) sizeof(char) * (NUMCHARS + 1); //+1 para fin de string
    int tamString2 = (int) sizeof(char) * (10 + 1); //+1 para fin de string
    
    //el tamaño del bloque es la suma de los campos
    int tamBuffer = tamInt + tamDoble + tamString+tamString2;
    void *buffer = malloc( tamBuffer ); //reservar memoria dinamica para el bloque

    cadena = (char*) malloc(tamString); //reservar memoria dinamica para string
    cadena2 = (char*) malloc(tamString2); //reservar memoria dinamica para string


    int r = fread(buffer, tamBuffer, 1, fd); //lectura del bloque completo
    if(r==0){ //leyó bytes (>0)
        return 1;
    }

    //puntero tipo int al inicio del bloque
    int *intp = (int*) buffer;
    entero = *intp; //tomar el valor del bloque

    //puntero tipo double despues del entero
    double *doublep = (double*) (intp + 1); //aritmetica de punteros
    doble = *doublep; //tomar el valor del bloque

    //puntero tipo char despues del double
    char *strp = (char*) (doublep + 1); //aritmetica de punteros
    strncpy(cadena, strp, NUMCHARS); //tomar el valor del bloque

    char *strp2 = (char*) (strp + 1); //aritmetica de punteros
    strncpy(cadena2, strp2, 10); //tomar el valor del bloque

    free(buffer);
    fclose(fd);

    //imprimir campos individuales
    printf("Entero: %d\n", entero);
    printf("Doble: %f\n", doble);
    printf("Cadena: %s\n", cadena);
    printf("Cadena2: %s\n", cadena2);

        
        
    free(cadena);
    free(cadena2);

    fclose(fd);
    return 0;
}
