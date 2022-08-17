
//   buffer registro -->| codigo | nombre | precio |  cantidad  |
//                      |  8+1B  |  25+1B |   8B   |     4B     |    (en x86)



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){

    //abrir - crear archivo
    
    FILE *fd;
    char *nombrearchivo = "practica3.dat";
    fd = fopen(nombrearchivo, "r");
    if (fd == NULL){
        printf("Archivo creado\n");
        fd = fopen(nombrearchivo, "w+");

    } else {
        fclose(fd);

        fd = fopen(nombrearchivo, "r+");
        
    }



    //struct
    
    char codigo[7];
    char nombre[25];
    double precio;
    int cantidad;
    char *codigoLectura;
    
    int tamCodigo = (int) sizeof(char) * (7 + 1);
    int tamNombre = (int) sizeof(char)* (25+ 1);
    int tamPrecio = (int) sizeof(double);
    int tamCantidad = (int) sizeof(int);
    

    int tamBuffer = tamCodigo + tamNombre + tamPrecio + tamCantidad; //tamanio del buffer
 

    void *buffer = malloc( tamBuffer ); //puntero generico 
    void *bufferLectura = malloc( tamBuffer ); //puntero generico para lectura
    codigoLectura = (char*) malloc(tamCodigo);  //puntero char para el codigo que se leera

    char aux[20]; //cadena auxiliar para leer de teclado los Int y Double

    //ingreso de datos 
    printf("\n           Ingreso de DATOS\n\n " );

    //Ingreso de codigo
    printf("Ingrese el CODIGO: ");
    fgets(codigo, 8 , stdin);   

    //ciclo para crear una llave canonica del codigo y para verificar la estructura
    for (int i = 0; i < 7; i++){
        if (i<4){
            codigo[i] = toupper(codigo[i]);
            if (!isalpha(codigo[i])){
                printf("Error: El codigo %s no tiene la estructura necesaria (4 letras y 3 numeros)\n", codigo);      
                free(buffer);
                free(bufferLectura);
                free(codigoLectura);

                fclose(fd);
                return 1;
            }
            
        } else {
            if (!isdigit(codigo[i])){
                printf("Error: El codigo %s no tiene la estructura necesaria (4 letras y 3 numeros)\n", codigo);      
                free(buffer);
                free(bufferLectura);
                free(codigoLectura);

                fclose(fd);
                return 1;
            }
        }


        
    }

    //ciclo para verificar que el codigo no es repetido
    int r = fread(bufferLectura, tamBuffer, 1, fd);
    while (r!=0){
        
        char *codigoLP = (char *)  (bufferLectura);
        strncpy(codigoLectura, codigoLP, 7);

        //Si el codigo es repetido imprime error y sale del programa
        if ( strcmp(codigo, codigoLectura) == 0){
            printf("Error: ya existe un registro con el codigo %s\n", codigo);      
            free(buffer);
            free(bufferLectura);
            free(codigoLectura);

            fclose(fd);
            return 1;
        }
        
        r = fread(bufferLectura, tamBuffer, 1, fd);

    }
    

    printf(" Ingrese el NOMBRE DEL PRODUCTO: ");
    fgets(nombre, sizeof(nombre) + 1, stdin);
    fgets(nombre, sizeof(nombre) + 1, stdin);

    printf(" Ingrese el PRECIO: ");
    fgets(aux, 20, stdin);
    precio = atof(aux);   

    printf(" Ingrese la CANTIDAD: ");
    fgets(aux, 20, stdin);
    cantidad = atoi(aux);
            
    fseek(fd, 0, SEEK_END); //ir al final del archivo para escribir

    //aritmetica de puteros
    char *codigoP = (char *)  (buffer);
    strncpy(codigoP, codigo, tamCodigo);
    codigoP[tamCodigo] = 0;

    char *nombreP = (char *)  (codigoP + tamCodigo);
    strncpy(nombreP, nombre, tamNombre);
    nombreP[tamNombre] = 0;

    double *precioP = (double*) (nombreP + tamNombre);
    *precioP = precio;

    int *cantidadP = (int*) (precioP + 1);
    *cantidadP = cantidad;



    fwrite(buffer, tamBuffer, 1, fd); //escribir buffer en archivo

    printf("Datos escritos\n\n");
        
    


    free(buffer);
    free(bufferLectura);
    free(codigoLectura);

    fclose(fd);
    
    


    return 0;
}

