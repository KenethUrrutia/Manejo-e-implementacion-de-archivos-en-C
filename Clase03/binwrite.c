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



    int tamInt = sizeof(int);
    int i;

    for ( i = 0; i < 10; i++)
    {
        fwrite(&i, tamInt, 1, fd);
        /*
            &i      puntero de el dato que donde que guardaremos en archivo
            tamInt  tamanio de lo que se leera (bytes)
            1       cantidad de elemento que se guardaran
            fd      archivo donde se guardaran
        */
    }
    

    printf("datos escritos");



    fclose(fd);
    
    


    return 0;
}