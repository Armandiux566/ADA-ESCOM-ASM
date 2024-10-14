#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct punto
{
    int x;
    int y;
}punto;

int distancia_puntos(punto a, punto b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void puntos_cercanos(punto puntos[], int n)
{
    int distancia_minima=INT_MAX;
    int i,j,idx1=0,idx2=0,distancia;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            distancia=distancia_puntos(puntos[i],puntos[j]);
            if(distancia<distancia_minima)
            {
                distancia_minima=distancia;
                idx1=i;
                idx2=j;
            }
        }
    }
    printf("\tPuntos mas cercanos: (%d,%d) y (%d,%d)\n", puntos[idx1].x,puntos[idx1].y,puntos[idx2].x,puntos[idx2].y);
    printf("\tDistancia minima entre puntos (al cuadrado): %d\n", distancia_minima);
}

void generar_puntos(punto puntos[], int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        puntos[i].x=(rand()%20001)-10000;
        puntos[i].y=(rand()%20001)-10000;
    }
}

int main()
{
    int n[]={10,100,1000,10000,100000};
    int n_casos=sizeof(n)/sizeof(n[0]);
    int i,n_puntos;
    double tiempo;
    punto* puntos;
    clock_t inicio,fin;
    srand(time(NULL));
    printf("\tAlgortmo por fuerza bruta\n");
    for(i=0; i<n_casos; i++)
    {
        n_puntos=n[i];
        puntos=(punto*)malloc(n_puntos*sizeof(punto));
        generar_puntos(puntos,n_puntos);
        inicio=clock();
        puntos_cercanos(puntos,n_puntos);
        fin=clock();
        tiempo=(double)(fin-inicio)/CLOCKS_PER_SEC;
        printf("\tTiempo de ejecucion para n=%d: %.6f segundos\n\n", n_puntos,tiempo);
        free(puntos);
    }
    return 0;
}