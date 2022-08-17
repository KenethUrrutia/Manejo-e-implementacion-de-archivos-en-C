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


    int TAM = 50;
    int cantidadRegistros;

    struct registro{
        int entero;
        double doble;
        char cadena[TAM];
    } reg;

    


    printf("Ingrese la cantidad de registros que ingresara: ");
    scanf("%i", &cantidadRegistros);

    char aux[TAM];
    unsigned long tam = (unsigned long) sizeof(struct registro);

    int i;
    for ( i = 0; i < cantidadRegistros; i++)
    {
        printf("Ingrese el ENTERO del registro #%i: ",i+1);
        scanf("%i", &reg.entero);
        printf("Ingrese el DOUBLE del registro #%i: ",i+1);
        scanf("%lf", &reg.doble);
        printf("Ingrese la CADENA del registro #%i (max 50 caracteres): ",i+1);
        fgets(aux, TAM, stdin);
        fgets(aux, TAM, stdin);
        strncpy(reg.cadena, aux,  sizeof(char)*TAM-1);
        reg.cadena[TAM-1] = 0;
        
        fwrite(&reg, tam, 1, fd);

        printf("Datos del registro #%i escritos \n",i+1);
    }
    


    printf("datos escritos");



    fclose(fd);
    
    


    return 0;
}