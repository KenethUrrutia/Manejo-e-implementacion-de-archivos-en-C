
//   buffer registro -->| codigo | Separador | nombre | Separador | precio | Separador |  cantidad  | Separador |
//                      |  8+1B  |     1B    | 30+1B  |     1B    |   8B   |     1B    |     4B     |     1B    |    (en x86)



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

    char separador = '$';
    char *nombre;
    char codigo[7];
    double precio;
    int cantidad;
    char *codigoLectura;
    
    int tamSeparador = (int) sizeof(char) * (1);
    int tamCodigo = (int) sizeof(char) * (7 + 1);
    int tamMaxNombre = (int) sizeof(char)* (30+ 1);
    int tamPrecio = (int) sizeof(double);
    int tamCantidad = (int) sizeof(int);

    int tamBuffer = tamCodigo + tamSeparador + tamMaxNombre + tamSeparador + tamPrecio + tamSeparador + tamCantidad + tamSeparador; //tamanio del buffer
 

    void *buffer = malloc( tamBuffer ); //puntero generico 
    void *bufferLectura = malloc( tamBuffer ); //puntero generico para lectura
    codigoLectura = (char*) malloc(tamCodigo);  //puntero char para el codigo que se leera
    nombre = (char*) malloc(30); 
    
    char aux[20]; //cadena auxiliar para leer de teclado los Int y Double


    printf("Ingrese el CODIGO: ");
    fgets(codigo, 8 , stdin);   
    //ciclo para crear una llave canonica del codigo y para verificar la estructura
    for (int i = 0; i < 7; i++){
        if (i<4){
            codigo[i] = toupper(codigo[i]);
            if (!isalpha(codigo[i])){
                printf("Error: El codigo %s no tiene la estructura necesaria (4 letras y 3 numeros)\n", codigo);      
                free(bufferLectura);
                free(buffer);
                free(codigoLectura);

                fclose(fd);
                return 1;
            }
            
        } else {
            if (!isdigit(codigo[i])){
                printf("Error: El codigo %s no tiene la estructura necesaria (4 letras y 3 numeros)\n", codigo);      
                free(bufferLectura);
                free(buffer);
                free(codigoLectura);
                
                fclose(fd);
                return 1;
            }
        }


        
    }

    printf(" Ingrese el NOMBRE DEL PRODUCTO: ");
    fgets(nombre, tamMaxNombre, stdin);
    fgets(nombre, tamMaxNombre, stdin);


    printf(" Ingrese el PRECIO: ");
    fgets(aux, 20, stdin);
    precio = atof(aux);   

    printf(" Ingrese la CANTIDAD: ");
    fgets(aux, 20, stdin);
    cantidad = atoi(aux);

    int tamRealNombre = sizeof(nombre);
    printf("Tam %i", tamRealNombre);

    fseek(fd, 0, SEEK_END); //ir al final del archivo para escribir

    //aritmetica de puteros
    char *codigoP = (char *)  (buffer);
    strncpy(codigoP, codigo, tamCodigo);
    codigoP[tamCodigo] = 0;

    char *separadorP = (char *) (codigoP + tamCodigo);
    *separadorP = separador;

    char *nombreP = (char *)  (separadorP + tamSeparador);
    strncpy(nombreP, nombre, tamRealNombre);
    nombreP[tamRealNombre] = 0;

    separadorP = (char *) (nombreP + tamRealNombre);
    *separadorP = separador;

    double *precioP = (double*) (separadorP + tamSeparador);
    *precioP = precio;

    separadorP = (char *) (precioP + 1);
    *separadorP = separador;

    int *cantidadP = (int*) (separadorP + tamSeparador);
    *cantidadP = cantidad;

    separadorP = (char *) (cantidadP + 1);
    *separadorP = separador;  



    fwrite(buffer, tamBuffer, 1, fd); //escribir buffer en archivo
    
    free(buffer);
    free(bufferLectura);
    free(codigoLectura);


    fclose(fd);


    return 0;
}

