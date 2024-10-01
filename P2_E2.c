#include <stdio.h>
#include <time.h>

int fibonacci(int n)
{
    if(n<=1)
        return n;
    return fibonacci(n-1)+fibonacci(n-2);
}

int main()
{
    int n,result;
    clock_t start,end;
    double cpu_time_used;
    printf("Ingresa el numero n para calcular el Fibonacci: ");
    scanf("%d", & n);
    start=clock();
    result=fibonacci(n);
    end=clock();
    cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %d\n", n,result);
    printf("Tiempo de ejecucion: %f segundos\n", cpu_time_used);
    return 0;
}