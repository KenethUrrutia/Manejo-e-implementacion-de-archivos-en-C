#include <stdio.h>
#include <string.h>

int main(){

    //abrir - crear archivo
    
    FILE *fd;
    char *nombrearchivo = "practica1.dat";
    fd = fopen(nombrearchivo, "w+");
    if (fd == NULL){
        printf("No se pudo abrir el archivo %s\n", nombrearchivo);
        return 1;
    }

    //struct
    int TAM = 50;

    struct registro{
        int entero;
        double doble;
        char cadena[TAM];
    } reg;

    
    //cantidad de registros a ingresar
    int cantidadRegistros;
    printf("Ingrese la cantidad de registros que ingresara: ");
    scanf("%i", &cantidadRegistros);

    //cadena de caracteres auxiliar
    char aux[TAM];
    unsigned long tam = (unsigned long) sizeof(struct registro);

    //ciclo para ingresar los registros
    int i;
    for ( i = 0; i < cantidadRegistros; i++)
    {

        printf("Ingrese el ENTERO del registro #%i: ",i+1);
        scanf("%i", &reg.entero);

        printf("Ingrese el DOUBLE del registro #%i: ",i+1);
        scanf("%lf", &reg.doble);

        printf("Ingrese la CADENA del registro #%i (max 50 caracteres): ",i+1);
        fgets(aux, TAM, stdin);
        fgets(aux, TAM, stdin);   //nota: se usaron dos fgets por un problema con un ENTER guardado en el buffer de teclado

        strncpy(reg.cadena, aux,  sizeof(char)*TAM-1); //copia segura de cadena
        reg.cadena[TAM-1] = 0;
        
        fwrite(&reg, tam, 1, fd); //escribir archivos

        printf("\n      Datos del registro #%i escritos \n",i+1);
        printf("--------------------------------------------------------------------\n");
    }
    


    printf("Datos escritos\n\n");



    fclose(fd);
    
    


    return 0;
}