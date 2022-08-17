#include <stdio.h>

int main()
{
    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "prueba.txt";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("Archivo %s abierto\n", nombrearchivo);
    

    char c;
    c = fgetc(fd);

    while (c != EOF)
    {
        putchar( c );	//escribe un char a la salida estandar
        c = fgetc( fd );	//lee el siguiente character
    }
    

    fclose(fd);
    return 0;
}
