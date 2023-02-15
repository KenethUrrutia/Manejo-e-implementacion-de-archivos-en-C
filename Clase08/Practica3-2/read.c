
//   buffer registro -->| codigo | Separador | nombre | Separador | precio | Separador |  cantidad  | Separador |
//                      |  8+1B  |     1B    | 30+1B  |     1B    |   8B   |     1B    |     4B     |     1B    |    (en x86)  

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
    
    char *codigo;
    char *nombre;
    double precio;
    int cantidad;

    int tamSeparador = (int) sizeof(char) * (1);
    int tamCodigo = (int) sizeof(char) * (8);
    int tamMaxNombre = (int) sizeof(char)* (31);
    int tamPrecio = (int) sizeof(double);
    int tamCantidad = (int) sizeof(int);
    

    int tamBuffer = tamCodigo + tamSeparador + tamMaxNombre + tamSeparador + tamPrecio + tamSeparador + tamCantidad + tamSeparador; //tamanio del buffer
 

    void *buffer = malloc( tamBuffer ); //puntero generico 
    
    // Memoria dinamica para strings
    nombre = (char*) malloc(tamMaxNombre); 
    codigo = (char*) malloc(tamCodigo);  
    
    int r = fread(buffer, tamBuffer, 1, fd);
    int contador = 1; //contador de registros.

    //avanzar hasta encontrar el codigo y mostrarlo
    int nrr = 1;
    while (r != 0){

        char *codigoP = (char *)  (buffer);
        strncpy(codigo, codigoP, 7);

        char *separadorP = (char *) (codigoP + tamCodigo);

        char *nombreP = (char *)  (separadorP + 1);
        strncpy(nombre, nombreP, 30);

        int iterador = 0;
        char auxchar = nombre[iterador];

        while (iterador != 30 ){
            if (auxchar == '$' ){
                break;
            }
            
            iterador ++;
            auxchar = nombre[iterador];
        }
        
        separadorP = (char *) (nombreP + iterador);

        double *precioP = (double*) (separadorP + 1);
        precio = *precioP;

        separadorP = (char *) (precioP + 1);
        
        int *cantidadP = (int*) (separadorP + 1);
        cantidad = *cantidadP;

        separadorP = (char *) (precioP + 1);


        printf("\n\nNumero relativo de registro: %d\n  Codigo: %s\n  Nombre: %s  Precio: %lf\n  Cantidad: %i\n", nrr, codigo, nombre, precio, cantidad);

        free(buffer);
        free(nombre);
        free(codigo);
        fclose(fd);
        return 0;

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


