#include <stdio.h>

int main()
{
    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "prueba.dat";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("Archivo %s abierto\n", nombrearchivo);
    

    struct registro{
        int entero;
        double doble;
        char caracter;
    } reg;

    unsigned long tam = (unsigned long) sizeof(struct registro);

    fread(&reg, tam, 1, fd);

    printf("Entero: %i\n Doble: %f\n Char: %c\n Tamanio: %lu\n", reg.entero, reg.doble, reg.caracter, tam);

    
    

    fclose(fd);
    return 0;
}
