
//   buffer  --> | nombreJ | edad |  nacionalidad  | nombreE | Puntos |  Posicion  |
//               |    21B  |  4B  |       26B      |    31B  |   8B   |     4B     |    (en x86)
              

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "practica2.dat";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    
    
    
    char *nombreJugador;
    int edad;
    char *nacionalidad;
    
    char *nombreEquipo;
    double puntos;
    int posicion;

    

    int tamInt = (int) sizeof(int);
    int tamDouble = (int) sizeof(double);
    int tamNombreJugador = (int) sizeof(char)*21;
    int tamNacionalidad = (int) sizeof(char)*26;
    int tamNombreEquipo = (int) sizeof(char)*31;


    int tamBuffer = tamNombreJugador +   tamInt  + tamNacionalidad + tamNombreEquipo + tamDouble + tamInt;

    
    void *buffer = malloc( tamBuffer ); //puntero generico para el buffer
    
    // Memoria dinamica para strings
    nombreJugador = (char*) malloc(tamNombreJugador); 
    nacionalidad = (char*) malloc(tamNacionalidad); 
    nombreEquipo = (char*) malloc(tamNombreEquipo); 
    
    int r = fread(buffer, tamBuffer, 1, fd);
    int contador = 1; //contador de registros.

     if(r==0){ //leyó bytes (>0)
        printf("sin registros\n");
        return 1;
    }

    //leer hasta no haber registros
    while (r!=0)
    {
        printf("\n---------------------------------------------------------\n");

        
        int *edadP = (int*) buffer;
        edad = *edadP;

        char *nombreJP = (char*) (edadP + 1);
        strncpy(nombreJugador, nombreJP , 20);

        char *nacionalidadP = (char*) (nombreJP + tamNombreJugador);
        strncpy(nacionalidad, nacionalidadP, 25);


        char *nombreEP = (char*) (nacionalidadP + tamNacionalidad);
        strncpy(nombreEquipo, nombreEP, 30);

        double *puntosP = (double*) (nombreEP + tamNombreEquipo);
        puntos = *puntosP;

        int *posicionP = (int*) (puntosP + 1);
        posicion = *posicionP;

    
        printf("\n        REGISTRO #%d \n", contador);
        printf("JUGADOR\n  Nombre Jugador: %s  Edad: %d\n  Nacionalidad: %s\n", nombreJugador, edad, nacionalidad);
        printf("EQUIPO\n  Nombre Equipo: %s  Puntos: %lf\n  Posicion: %d\n", nombreEquipo, puntos, posicion);
        
        contador = contador+1;
        r=0;
        r = fread(buffer, tamBuffer, 1, fd);
    }
    

    free(buffer);
    free(nombreJugador);
    free(nacionalidad);
    free(nombreEquipo);
    fclose(fd);
    
    


    return 0;
}