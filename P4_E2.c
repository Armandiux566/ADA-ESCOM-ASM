#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

typedef struct punto
{
    int x;
    int y;
}punto;

typedef struct resultado
{
    punto p1,p2;
    long long distancia_minima;
} resultado;

long long distancia_puntos(punto a, punto b)
{
    long long dx=(long long)a.x-b.x;
    long long dy=(long long)a.y-b.y;
    return dx*dx+dy*dy;
}

int comparar_x(const void* a, const void* b)
{
    punto* p1=(punto*)a;
    punto* p2=(punto*)b;
    return (p1->x > p2->x)-(p1->x < p2->x);
}

int comparar_y(const void* a, const void* b)
{
    punto* p1=(punto*)a;
    punto* p2=(punto*)b;
    return (p1->y > p2->y)-(p1->y < p2->y);
}

resultado fuerza_bruta(punto* puntos, int n)
{
    resultado res;
    long long distancia;
    int i,j;
    res.distancia_minima=LLONG_MAX;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            distancia=distancia_puntos(puntos[i],puntos[j]);
            if(distancia<res.distancia_minima)
            {
                res.distancia_minima=distancia;
                res.p1=puntos[i];
                res.p2=puntos[j];
            }
        }
    }
    return res;
}

resultado puntos_cercanos_recursivo(punto* puntos_x, punto* puntos_y, int n)
{
    punto punto_medio;
    punto* puntos_y_izq;
    punto* puntos_y_der;
    punto* franja;
    resultado res;
    resultado res_izq,res_der;
    int mitad,li=0,ri=0;
    int i=0,j=0,k=0;
    long long distancia;
    if(n<=3)
        return fuerza_bruta(puntos_x,n);
    mitad=n/2;
    punto_medio=puntos_x[mitad];
    puntos_y_izq=(punto*)malloc(mitad*sizeof(punto));
    puntos_y_der=(punto*)malloc((n-mitad)*sizeof(punto));
    for(i=0; i<n; i++) 
    {
        if(puntos_y[i].x<punto_medio.x || (puntos_y[i].x==punto_medio.x && puntos_y[i].y<punto_medio.y))
        {
            if(li<mitad)
                puntos_y_izq[li++]=puntos_y[i];
        }
        else
        {
            if(ri<(n-mitad))
                puntos_y_der[ri++]=puntos_y[i];
        }
    }
    res_izq=puntos_cercanos_recursivo(puntos_x,puntos_y_izq,li);
    res_der=puntos_cercanos_recursivo(puntos_x+mitad,puntos_y_der,ri);
    if(res_izq.distancia_minima<res_der.distancia_minima)
        res=res_izq;
    else
        res=res_der;
    franja=(punto*)malloc(n*sizeof(punto));
    for(i=0; i<n; i++)
    {
        if(abs(puntos_y[i].x-punto_medio.x)<res.distancia_minima)
            franja[j++]=puntos_y[i];
    }
    for(i=0; i<j; i++)
    {
        for(k=i+1; k<j && (franja[k].y-franja[i].y)<res.distancia_minima; k++)
        {
            distancia=distancia_puntos(franja[i],franja[k]);
            if(distancia<res.distancia_minima)
            {
                res.distancia_minima=distancia;
                res.p1=franja[i];
                res.p2=franja[k];
            }
        }
    }
    free(puntos_y_izq);
    free(puntos_y_der);
    free(franja);
    return res;
}

resultado puntos_cercanos(punto* puntos, int n)
{
    punto* puntos_x=(punto*)malloc(n*sizeof(punto));
    punto* puntos_y=(punto*)malloc(n*sizeof(punto));
    resultado res;
    int i;
    for(i=0; i<n; i++)
    {
        puntos_x[i]=puntos_y[i]=puntos[i];
    }
    qsort(puntos_x,n,sizeof(punto),comparar_x);
    qsort(puntos_y,n,sizeof(punto),comparar_y);
    res=puntos_cercanos_recursivo(puntos_x, puntos_y, n);
    free(puntos_x);
    free(puntos_y);
    return res;
}

void generar_puntos(punto* puntos, int n)
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
    clock_t inicio,fin;
    punto* puntos;
    resultado res;
    srand(time(NULL));
    printf("\tAlgoritmo por divide y vencerás\n");
    for(i=0; i<n_casos; i++)
    {
        n_puntos=n[i];
        puntos=(punto*)malloc(n_puntos*sizeof(punto));
        generar_puntos(puntos,n_puntos);
        inicio=clock();
        res=puntos_cercanos(puntos,n_puntos);
        fin=clock();
        tiempo=(double)(fin-inicio)/CLOCKS_PER_SEC;
        printf("\tPuntos mas cercanos: (%d,%d) y (%d,%d)\n", res.p1.x,res.p1.y,res.p2.x,res.p2.y);
        printf("\tDistancia minima entre puntos (al cuadrado): %lld\n", res.distancia_minima);
        printf("\tTiempo de ejecucion para n=%d: %.6f segundos\n\n", n_puntos,tiempo);
        free(puntos);
    }
    return 0;
}