#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int size)
{
    int i;

    printf("[");
    for(i=0; i<size; i++)
    {
        printf("%d", arr[i]);
        if(i<size-1)
            printf(", ");
    }
    printf("]\n");
}

void printSubarray(int arr[], int start, int size)
{
    int i;

    printf("[");
    for(i=start; i<start+size; i++)
    {
        printf("%d", arr[i]);
        if(i<start+size-1)
            printf(", ");
    }
    printf("] ");
}

void generateRandomArray(int arr[], int size)
{
    int i;

    for(i=0; i<size; i++)
        arr[i]=rand()%10001;
}

int countSubarrays(int arr[], int n, int k, int threshold)
{
    int i,count=0,current_sum=0;

    for(i=0; i<k; i++)
        current_sum+=arr[i];

    if(current_sum/(double)k>=threshold)
    {
        printf("Subarreglo encontrado: ");
        printSubarray(arr,0,k);
        printf("(promedio: %.2f)\n", current_sum/(double)k);
        count++;
    }

    for(i=k; i<n; i++)
    {
        current_sum=current_sum-arr[i-k]+arr[i];
        if(current_sum/(double)k>=threshold)
        {
            printf("Subarreglo encontrado: ");
            printSubarray(arr,i-k+1,k);
            printf("(promedio: %.2f)\n", current_sum/(double)k);
            count++;
        }
    }

    return count;
}

int main()
{
    int main_option,entry_option,n,k,threshold,size_option,i,result;
    int *arr;

    srand(time(NULL));

    while(1)
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Ejecutar algoritmo\n");
        printf("2. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", & main_option);

        if(main_option==2)
        {
            printf("Terminando ejecucion...\n");
            break;
        }

        if(main_option!=1)
        {
            printf("Opcion invalida\n");
            continue;
        }

        printf("1. Entrada manual\n");
        printf("2. Entrada aleatoria\n");
        printf("Seleccione el modo de entrada: ");
        scanf("%d", & entry_option);

        if(entry_option==2)
        {
            printf("Seleccione el tamaño del arreglo:\n");
            printf("1. 10\t\t2. 100\t\t3. 1000\t\n4. 10000\t5. 100000\t6. 1000000\n");
            scanf("%d", & size_option);

            switch(size_option)
            {
                case 1:
                    n=10;
                break;
                case 2:
                    n=100;
                break;
                case 3:
                    n=1000;
                break;
                case 4:
                    n=10000;
                break;
                case 5:
                    n=100000;
                break;
                case 6:
                    n=1000000;
                break;
                default:
                    printf("Opcion invalida\n");
                continue;
            }
        }
        else if(entry_option==1)
        {
            printf("Ingrese el tamaño del arreglo (max 100000): ");
            scanf("%d", & n);
            if(n<1 || n>100000)
            {
                printf("Tamaño invalido\n");
                continue;
            }
        }
        else
        {
            printf("Opcion invalida, intentelo de nuevo\n");
            continue;
        }

        arr=(int *)malloc(n*sizeof(int));
        if(arr==NULL)
        {
            printf("Error de asignacion de memoria\n");
            continue;
        }

        if(entry_option==1)
        {
            printf("Ingrese los elementos del arreglo:\n");
            for(i=0; i<n; i++)
            {
                scanf("%d", & arr[i]);
                if(arr[i]<1 || arr[i]>10000)
                {
                    printf("Valor fuera de rango, debe estar entre 1 y 10000\n");
                    free(arr);
                    arr=NULL;
                    break;
                }
            }
            if(arr==NULL)
                continue;
        }
        else
            generateRandomArray(arr,n);

        printf("\nArreglo de entrada:\n");
        if(n<=100)
            printArray(arr,n);
        else
            printf("Arreglo muy grande para mostrar\n");

        printf("Ingrese el tamaño de los subarreglos (k): ");
        scanf("%d", & k);
        if(k<1 || k>n)
        {
            printf("Valor de k invalido\n");
            free(arr);
            continue;
        }

        printf("Ingrese el valor del umbral (threshold): ");
        scanf("%d", & threshold);
        if(threshold<0 || threshold>10000)
        {
            printf("Valor de threshold invalido\n");
            free(arr);
            continue;
        }

        printf("\nBuscando subarreglos...\n");
        result=countSubarrays(arr,n,k,threshold);
        printf("\nNumero total de subarreglos encontrados: %d\n", result);
        free(arr);
    }

    return 0;
}