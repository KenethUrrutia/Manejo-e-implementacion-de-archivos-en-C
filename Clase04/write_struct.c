#include <stdio.h>
#include <string.h>
int main(){

    //abrir - crear archivo

    FILE *fd;
    char *nombrearchivo = "prueba.dat";
    fd = fopen(nombrearchivo, "w+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("Archivo %s creado\n", nombrearchivo);



    struct registro{
        int entero;
        double doble;
        char caracter;
    } reg;

    reg.entero  = 331;
    reg.doble = 3.1416;
    reg.caracter = 'X';


    unsigned long tam = (unsigned long) sizeof(struct registro);
    printf("El registro mide %lu bytes.\n", tam);
    
    fwrite(&reg, tam, 1, fd);

    printf("datos escritos");



    fclose(fd);
    
    


    return 0;
}