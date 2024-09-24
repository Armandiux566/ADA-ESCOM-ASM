#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANIO_1 1875
#define TAMANIO_2 2334

void insertion_sort(int *A, int n)       //O(n cuadrada)
{
    int i,j;
    int key;
    for(i=1; i<n; i++)                    //n
    {
        key=A[i];                         //n-1
        j=i-1;                            //n-1
        while(j>=0 && key<A[j])           //[n(n+1)/2]-1
        {
            A[j+1]=A[j];                  //n(n-1)/2
            j--;                          //n(n-1)/2
        }
        A[j+1]=key;                       //n-1
    }
}

void imprimir_array(int *A, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void generar_array_random(int r1, int r2, int *A, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        A[i]=r1+rand()%(r2-r1+1);
    }
}

void fusionar_arreglos(int *A, int n1, int *B, int n2, int *C)
{
    int i=0,j=0,k=0;
    while(i<n1 && j<n2)
    {
        if(A[i]>=B[j])
        {
            C[k++]=A[i++];
        }
        else
        {
            C[k++]=B[j++];
        }
    }
    while(i<n1)
    {
        C[k++]=A[i++];
    }
    while(j<n2)
    {
        C[k++]=B[j++];
    }
}

float mediana_array(int *A, int n)
{
    if(n%2==0)
    {
        return (A[n/2-1] + A[n/2]) / 2.0;
    }
    else
    {
        return A[n/2];
    }
}

int main()
{
    int ran_1,ran_2;
    int array_1[TAMANIO_1],array_2[TAMANIO_2],array_f[TAMANIO_1+TAMANIO_2];
    float mediana,t;
    printf("Define el rango de nuemeros aleatorios a generar\n(Inserta 2 numeros): ");
    scanf("%d %d", &ran_1, &ran_2);
    srand(time(NULL));
    clock_t start_time=clock();
    generar_array_random(ran_1,ran_2,array_1,TAMANIO_1);
    printf("Arreglo 1:\n");
    insertion_sort(array_1,TAMANIO_1);
    imprimir_array(array_1,TAMANIO_1);
    generar_array_random(ran_1,ran_2,array_2,TAMANIO_2);
    printf("Arreglo 2:\n");
    insertion_sort(array_2,TAMANIO_2);
    imprimir_array(array_2,TAMANIO_2);
    fusionar_arreglos(array_1,TAMANIO_1,array_2,TAMANIO_2,array_f);
    printf("Arreglo fusionado:\n");
    insertion_sort(array_f,TAMANIO_1+TAMANIO_2);
    imprimir_array(array_f,TAMANIO_1+TAMANIO_2);
    mediana=mediana_array(array_f,TAMANIO_1+TAMANIO_2);
    printf("Mediana del arreglo fusionado: %.2f\n", mediana);
    clock_t end_time=clock();
    t=((float)(end_time-start_time))/CLOCKS_PER_SEC;
    printf("Tiempo total del algoritmo en ejecucion: %.2f seg\n", t);
    return 0;
}
