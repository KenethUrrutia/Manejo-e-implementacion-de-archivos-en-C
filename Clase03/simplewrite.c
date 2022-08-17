#include <stdio.h>
#include <string.h>
int main(){

    //abrir - crear archivo

    FILE *fd;
    char *nombrearchivo = "prueba.txt";
    fd = fopen(nombrearchivo, "w+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("Archivo %s creado\n", nombrearchivo);




    char *cadena = "HOla desde c";
    
    int tam = strlen(cadena);
    int i;

    for ( i = 0; i < tam; i++)// escribe cada char en el file
    {
        fputc(cadena[i], fd); 
    }

    printf("datos escritos");



    fclose(fd);
    
    


    return 0;
}