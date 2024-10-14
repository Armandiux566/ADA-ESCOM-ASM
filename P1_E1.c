#include <stdio.h>

void imprimir_arreglo(int *A, int n);
int eliminar_duplicados(int *A, int n);

int main()
{
    int numeros[9]={1,1,2,2,3,3,4,5,5};
    int k;

    printf("Arreglo original:\n");
    imprimir_arreglo(numeros,9);
    k=eliminar_duplicados(numeros,9);
    printf("Cantidad de elementos unicos en el arreglo: %d\n", k);
    printf("Arreglo con elementos unicos:\n");
    imprimir_arreglo(numeros,9);
    return 0;
}





void imprimir_arreglo(int *A, int n)                // O(n)
{
    int i;
    for(i=0; i<n; i++)
    {
        if(A[i]==-1)
            printf("- ");
        else
            printf("%d ", A[i]);
    }
    printf("\n");
}

int eliminar_duplicados(int *A, int n)              // O(n cuadrada)
{
    int i,j,k=0;
    int duplicado;
    if(n==0)
        return 0;
    for(i=0; i<n; i++)
    {
        duplicado=0;
        for(j=0; j<k; j++)
        {
            if(A[i]==A[j])
            {
                duplicado=1;
                break;
            }
        }
        if(!duplicado)
        {
            A[k]=A[i];
            k++;
        }
    }
    for(i=k; i<n; i++)
    {
        A[i]=-1;
    }
    return k;
}
