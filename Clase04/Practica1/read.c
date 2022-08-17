#include <stdio.h>

int main()
{
    //abrir archivos
    FILE *fd;
    char *nombrearchivo = "practica1.dat";
    fd = fopen(nombrearchivo, "r+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }
    printf("---------------------------------------------------------\n");
    
    //struct
    struct registro{
        int entero;
        double doble;
        char cadena[50];
    } reg;

    //tamano struct
    unsigned long tam = (unsigned long) sizeof(struct registro);

    //leer archivo
    int r = fread(&reg, tam, 1, fd);
    int contador = 1; //contador de registros

    //leer hasta no haber registros
    while (r!=0)
    {
        printf("Registro: #%i \n  Entero: %i\n  Doble: %f\n  Cadena: %s\n\n", contador, reg.entero, reg.doble, reg.cadena);
        contador = contador+1;
        r = fread(&reg, tam, 1, fd);
    }
    

    
    

    fclose(fd);
    return 0;
}
