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
    

    int tamInt = sizeof(int);
    printf("%i\n", tamInt);
    int i;

    int r = fread(&i, tamInt, 1, fd);

    while (r != 0)
    {
        printf("Numero %d leido\n", i);
        r = fread(&i, tamInt, 1, fd);	//lee el siguiente entero
        /*
            &i      puntero de el dato que donde guardaremos lo leido
            tamInt  tamanio de lo que se leera (byte)
            1       cantidad de elemento que se leeran
            fd      archivo del que se leeran
        */
    }
    

    
    

    fclose(fd);
    return 0;
}
