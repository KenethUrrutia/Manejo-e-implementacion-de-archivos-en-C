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
        char cadena[50];
    } reg;

    unsigned long tam = (unsigned long) sizeof(struct registro);

    int r = fread(&reg, tam, 1, fd);
    int contador = 1;
    while (r!=0)
    {
        printf("Registro: #%i \nEntero: %i\n Doble: %f\n Cadena: %s\n", contador, reg.entero, reg.doble, reg.cadena);
        contador = contador+1;
        r = fread(&reg, tam, 1, fd);
    }
    

    
    

    fclose(fd);
    return 0;
}
