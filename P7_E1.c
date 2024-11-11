#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_LENGTH 1
#define MAX_LENGTH 200000
#define MAX_INPUT 200000
#define MAX_GROUP 9

int count_digits(int num)
{
    int count;

    if(num==0)
        return 1;

    count=0;

    while(num>0)
    {
        count++;
        num/=10;
    }

    return count;
}

char *fill_random_word(int length)
{
    int i;
    char *random_string=(char *)malloc((length+1) * sizeof(char));

    if(!random_string)
        return NULL;

    for(i=0; i<length; i++)
        random_string[i]='a'+(rand()%26);
    
    random_string[length]='\0';

    return random_string;
}

char *compress_string(const char* word, int length)
{
    int i,comp_i,count;
    char current;
    char *comp;

    if(!word || length<=0)
        return NULL;

    comp=(char *)malloc((length*10+1) * sizeof(char));
    if(!comp)
        return NULL;

    i=0;
    comp_i=0;

    while(i<length)
    {
        current=word[i];
        count=0;

        while(i<length && word[i]==current)
        {
            count++;
            i++;

            if(count==MAX_GROUP)
            {
                comp_i+=sprintf(&comp[comp_i],"%d%c",MAX_GROUP,current);
                count=0;
            }
        }

        if(count>0)
            comp_i+=sprintf(&comp[comp_i],"%d%c",count,current);
    }
    comp=realloc(comp,(comp_i+1) * sizeof(char));

    return comp;
}

void process_random_strings()
{
    int i,n;
    int length[]={10,20,30,40,50,100};
    char *word,*compressed_word;
    
    n=sizeof(length)/sizeof(length[0]);
    for(i=0; i<n; i++)
    {
        word=fill_random_word(length[i]);
        if(!word)
        {
            printf("\tError: No se pudo asignar memoria para la palabra\n");
            continue;
        }

        printf("\n\tCadena %d (%d caracteres): %s\n", i+1,length[i],word);

        compressed_word=compress_string(word,length[i]);
        if(!compressed_word)
        {
            printf("\tError: No se pudo comprimir la cadena\n");
            free(word);
            continue;
        }

        printf("\tCadena comprimida: %s\n", compressed_word);
        free(word);
        free(compressed_word);
    }
}

void process_manual_input()
{
    char *input=(char *)malloc((MAX_INPUT+1) * sizeof(char));
    char *compressed_word;
    int length;

    if(!input)
    {
        printf("\tError: No se pudo asignar memoria para la entrada\n");
        return;
    }
    
    printf("\n\tIntroduce la cadena a comprimir (máximo %d caracteres): ", MAX_INPUT);
    fgets(input,MAX_INPUT,stdin);
    input[strcspn(input,"\n")]='\0';

    length=strlen(input);
    printf("\n\tCadena introducida (%d caracteres): %s\n", length, input);

    compressed_word=compress_string(input,length);
    if(!compressed_word)
    {
        printf("\tError: No se pudo comprimir la cadena\n");
        free(input);
        return;
    }

    printf("\tCadena comprimida: %s\n", compressed_word);
    free(input);
    free(compressed_word);
}

int main()
{
    int opcion;

    srand(time(NULL));

    do
    {
        printf("\n\t=== Algoritmo de compresion de cadenas ===\n");
        printf("\t1. Usar cadenas aleatorias predefinidas\n");
        printf("\t2. Introducir cadena manualmente\n");
        printf("\t3. Salir\n");
        printf("\tIntroduce una opcion: ");

        if(scanf("%d", & opcion)!=1)
        {
            printf("\tError, entrada invalida\n");
            while(getchar()!='\n');
            continue;
        }

        while(getchar()!='\n');

        switch(opcion)
        {
            case 1:
                process_random_strings();
                sleep(7);
                system("clear");
                break;

            case 2:
                process_manual_input();
                sleep(7);
                system("clear");
                break;

            case 3:
                printf("\tSaliendo...\n");
                break;

            default:
                printf("\tOpción invalida, intentelo de nuevo\n");
        }
    }while(opcion!=3);

    return 0;
}