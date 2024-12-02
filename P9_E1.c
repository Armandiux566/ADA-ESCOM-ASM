#include <stdio.h>
#include <stdlib.h>

void triangulo_pascal(int numFilas)
{
    int **triangulo;
    int i,j,fila,espacio;

    triangulo=(int **)malloc(numFilas*sizeof(int *));
    for(i=0; i<numFilas; i++)
        triangulo[i]=(int *)malloc((i+1)*sizeof(int));

    for(fila=0; fila<numFilas; fila++)
    {
        triangulo[fila][0]=1;
        triangulo[fila][fila]=1;

        for(j=1; j<fila; j++)
            triangulo[fila][j]=triangulo[fila-1][j-1]+triangulo[fila-1][j];
    }

    printf("Triangulo generado (%d filas):\n", numFilas);
    for(fila=0; fila<numFilas; fila++)
    {
        for(espacio=0; espacio<numFilas-fila-1; espacio++)
            printf("   ");

        for(j=0; j<=fila; j++)
            printf("%5d ", triangulo[fila][j]);
        printf("\n");
    }

    for(i=0; i<numFilas; i++)
        free(triangulo[i]);
    free(triangulo);
}

int main()
{
    int n;

    do
    {
        printf("Ingrese el numero de filas para el triangulo de Pascal (1-30): ");
        scanf("%d", & n);
        if(n<1 || n>30)
        {
            printf("Error, numero fuera de rango\n");
        }
    }while(n<1 || n>30);

    triangulo_pascal(n);

    return 0;
}