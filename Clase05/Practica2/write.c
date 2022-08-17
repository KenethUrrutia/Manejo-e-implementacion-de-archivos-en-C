
//   buffer jugador --> | nombre | edad |  nacionalidad  |
//                      |   21B  |  4B  |       26B      |    (en x86)

//   buffer equipo  --> | nombre | Puntos |  Posicion  |
//                      |   31B  |   8B   |     4B     |    (en x86)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    //abrir - crear archivo
    
    FILE *fd;
    char *nombrearchivo = "practica2.dat";
    fd = fopen(nombrearchivo, "w+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }

    //struct
    
    char nombreJugador[20];
    int edad;
    char nacionalidad[25];
    
    char nombreEquipo[30];
    double puntos;
    int posicion;

    

    int tamInt = (int) sizeof(int);
    int tamDouble = (int) sizeof(double);
    int tamNombreJugador = (int) sizeof(char)*21;
    int tamNacionalidad = (int) sizeof(char)*26;
    int tamNombreEquipo = (int) sizeof(char)*31;

    int tamBufferJugador = tamNombreJugador +   tamInt  + tamNacionalidad; //tamanio del buffer de jugador
    int tamBufferEquipo  = tamNombreEquipo  + tamDouble + tamInt;   //tamanio del buffer de Equipo

    void *bufferJugador = malloc( tamBufferJugador ); //puntero generico para jugador
    void *bufferEquipo  = malloc( tamBufferEquipo );//puntero generico para equipo


    //cantidad de registros a ingresar
    char aux1[20]; // var auxiliar para guardar ints y doubles


    int cantidadRegistros;
    printf("Ingrese la cantidad de registros que ingresara: ");
    fgets(aux1, 20, stdin);
    cantidadRegistros = atoi(aux1);



    int i;
    for ( i = 0; i < cantidadRegistros; i++)
    {
        //ingreso de datos JUGADOR
        printf("\nIngreso de JUGADOR  #%i\n\n ", i+1 );

        printf("Ingrese el NOMBRE DEL JUGADOR: ");
        fgets(nombreJugador, tamNombreJugador , stdin);   
        

        printf(" Ingrese la EDAD DEL JUGADOR: ");
        fgets(aux1, 20, stdin);
        edad = atoi(aux1);
  
        printf(" Ingrese la NACIONALIDAD DEL JUGADOR: ");
        fgets(nacionalidad, tamNacionalidad, stdin);

        //aritmetica de puteros para JUGADOS
        int *edadP = (int *) bufferJugador;
        *edadP = edad;

        char *nombreJP = (char *)  (edadP + 1);
        strncpy(nombreJP, nombreJugador, tamNombreJugador);
        nombreJP[tamNombreJugador] = 0;

        
        char *nacionalidadP = (char *) (nombreJP + tamNombreJugador);
        strncpy(nacionalidadP, nacionalidad, tamNacionalidad);
        nacionalidadP[tamNacionalidad] = 0;



        fwrite(bufferJugador, tamBufferJugador, 1, fd); //escribir buffer de jugador
        


        printf("\n\nIngreso de Equipo  #%i\n\n ", i+1 );

        printf("Ingrese el NOMBRE DEL EQUIPO: ");
        fgets(nombreEquipo, tamNombreEquipo - 1, stdin);   

        printf(" Ingrese los PUNTOS DEL EQUIPO: ");
        fgets(aux1, 20, stdin);
        puntos = atof(aux1);
  
        printf(" Ingrese la POSICION DEL EQUIPO: ");
        fgets(aux1, 20, stdin);
        posicion = atoi(aux1);



        char *nombreEP = (char*) bufferEquipo;
        strncpy(nombreEP, nombreEquipo, tamNombreEquipo);
        nombreEP[tamNombreEquipo] = 0;

        double *puntosP = (double*) (nombreEP + tamNombreEquipo);
        *puntosP = puntos;

        int *posicionP = (int*) (puntosP + 1);
        *posicionP = posicion;

        

        fwrite(bufferEquipo, tamBufferEquipo, 1, fd); //escribir buffer de EQUIPO



        printf("\n      Datos del registro #%i escritos \n",i+1);
        printf("--------------------------------------------------------------------\n");
    }


    printf("Datos escritos\n\n");


    free(bufferJugador);
    free(bufferEquipo);

    fclose(fd);
    
    


    return 0;
}