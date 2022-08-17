//   buffer registro -->| codigo | nombre | precio |  cantidad  |
//                      |  8+1B  |  25+1B |   8B   |     4B     |    (en x86)       

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(){

    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "practica3.dat";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    
    char busqueda[8];
    char *codigo;
    char *nombre;
    double precio;
    int cantidad;

    
    int tamCodigo = (int) sizeof(char) * (8);
    int tamNombre = (int) sizeof(char)* (26);
    int tamPrecio = (int) sizeof(double);
    int tamCantidad = (int) sizeof(int);
    

    int tamBuffer = tamCodigo + tamNombre + tamPrecio + tamCantidad; //tamanio del buffer
 

    void *buffer = malloc( tamBuffer ); //puntero generico 
    
    // Memoria dinamica para strings
    nombre = (char*) malloc(tamNombre); 
    codigo = (char*) malloc(tamCodigo);  
    
    int r = fread(buffer, tamBuffer, 1, fd);
    int contador = 1; //contador de registros.

    //ingreso del codigo a buscar
    printf("Ingrese el CODIGO a buscar: ");
    fgets(busqueda, 8 , stdin);   
    //conversion a llave canonica
    for (int i = 0; i < strlen(busqueda); i++){
        busqueda[i] = toupper(busqueda[i]);
    }

    //avanzar hasta encontrar el codigo y mostrarlo
    int nrr = 1;
    while (r!=0){

        char *codigoP = (char *)  (buffer);
        strncpy(codigo, codigoP, 7);

        if ( strcmp(codigo, busqueda) == 0){
            char *nombreP = (char *)  (codigoP + tamCodigo);
            strncpy(nombre, nombreP, 25);

            double *precioP = (double*) (nombreP + tamNombre);
            precio = *precioP;

            int *cantidadP = (int*) (precioP + 1);
            cantidad = *cantidadP;

            printf("\n\nNumero relativo de registro: %d\n  Codigo: %s\n  Nombre: %s  Precio: %lf\n  Cantidad: %i\n", nrr, codigo, nombre, precio, cantidad);

            free(buffer);
            free(nombre);
            free(codigo);
            fclose(fd);
            return 0;

        } else {

        }
        
        r = fread(buffer, tamBuffer, 1, fd);
        nrr = nrr + 1;
    }
    
    //no encontro coincidencias
    if(r==0){
        printf("sin registros\n");
        return 1;
    }

                


    free(buffer);
    free(nombre);
    free(codigo);
    fclose(fd);
    
    


    return 0;
}


