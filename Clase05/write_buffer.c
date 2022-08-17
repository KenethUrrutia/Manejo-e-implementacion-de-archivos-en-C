//   buffer --> |entero|double|  char*  |
//              |  4B  |  8B  |    9B   |    (en x86)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    //abrir - crear archivo
    
    FILE *fd;
    char *nombrearchivo = "practica1.dat";
    fd = fopen(nombrearchivo, "w+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }

    //struct
     //asignacion de los valores
    int entero = 57;
    double doble = 3.1416;
    char *cadena = "mi texto";
    char *cadena2 = "elpepepepe";

    //obtencion de los tamaños de variable
    int tamInt = (int) sizeof(int);	
    int tamDoble = (int) sizeof(double);
    int tamString = (int) sizeof(char) * (strlen(cadena) + 1); //+1 para fin de string
    int tamString2 = (int) sizeof(char) * (strlen(cadena2) + 1);

    //el tamaño del bloque es la suma de los campos
    int tamBuffer = tamInt + tamDoble + tamString+ tamString2;
    void *buffer = malloc( tamBuffer );	//reservar memoria dinamica
        
    //puntero tipo int al inicio del bloque
    int *intp = (int*) buffer;
    *intp = entero; //colocar el valor en el bloque

    //puntero tipo double despues del entero
    double *doublep = (double*)(intp + 1); //aritmetica de punteros
    *doublep = doble; //colocar el valor en el bloque

    //puntero tipo char despues del double
    char *strp = (char*)(doublep + 1); //aritmetica de punteros
    strncpy(strp, cadena, strlen(cadena)); //colocar el valor en el bloque
    strp[strlen(cadena)] = 0;

    char *strp2 = (char*)(strp + 1); //aritmetica de punteros
    strncpy(strp2, cadena2, strlen(cadena2)); //colocar el valor en el bloque
    strp2[strlen(cadena2)] = 0;

    fwrite(buffer, tamBuffer, 1, fd); //escritura del bloque completo
    

    printf("Datos escritos\n\n");


    free(buffer);
    fclose(fd);
    
    


    return 0;
}