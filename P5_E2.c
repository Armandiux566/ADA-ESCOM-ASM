#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "P5_E2slist.h"
#define N_LISTAS 20
#define K_LONGITUD_LISTA 500
#define LONGITUD_LISTA_FUSIONADA 10000

int main()
{
    SList listas[N_LISTAS];
    element e;
    int i,j;
    double exec_time;
    clock_t start,end;
    srand(time(NULL));
    for(i=0; i<N_LISTAS; i++)
    {
        createSL(&listas[i]);
        for(j=0; j<K_LONGITUD_LISTA; j++)
        {
            e=(rand()%20001)-10000;
            insert_at_first(&listas[i],e);
        }
    }
    /*for(i=0; i<N_LISTAS; i++)                 //Impresión de listas de pequeño tamaño
    {
        printf("Lista %i:\n",i+1);
        printSL(listas[i]);
    }*/
    start=clock();
    for(i=0; i<N_LISTAS; i++)
    {
        sortSL(&listas[i]);
    }
    fusionSL(listas,N_LISTAS);
    end=clock();
    exec_time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion del algoritmo: %.6f segundos\n\n", exec_time);
    for(i=0; i<N_LISTAS; i++)
    {
        deleteSL(&listas[i]);
    }
    return 0;
}