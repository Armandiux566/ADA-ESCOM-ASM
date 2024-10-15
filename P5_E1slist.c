#include "P5_E1slist.h"

void createSL(SList *first)
{
    *first=NULL;
}

int is_emptySL(SList first)
{
    if(first==NULL)
        return 1;
    else
        return 0;
}

void insert_at_first(SList *first, element e)
{
    nodeSL *new;
    new=(nodeSL *)malloc(sizeof(nodeSL));
    new->e=e;
    new->next=*first;
    *first=new;
}

void deleteSL(SList *first)
{
    nodeSL *aux;
    while(*first!=NULL)
    {
        aux=*first;
        *first=aux->next;
        //printf("Elemento eliminado: %d\n", aux->e);
        free(aux);
    }
    printf("Lista eliminada correctamente\n");
}

void printSL(SList first)
{
    nodeSL *current;
    if(is_emptySL(first))
        printf("La lista esta vacia\n");
    else
    {
        current=first;
        printf("Elementos de la lista:\n");
        while(current!=NULL)
        {
            printf("%d ", current->e);
            current=current->next;
        }
        printf("\n");
    }
}

void sortSL(SList *first)
{
    int swapped,temp;
    SList ptr1;
    SList lptr = NULL;
    if(is_emptySL(*first) || (*first)->next==NULL)
        return;
    do
    {
        swapped=0;
        ptr1=*first;
        while(ptr1->next!=lptr)
        {
            if(ptr1->e>ptr1->next->e)
            {
                temp=ptr1->e;
                ptr1->e=ptr1->next->e;
                ptr1->next->e=temp;
                swapped=1;
            }
            ptr1=ptr1->next;
        }
        lptr=ptr1;
    }while(swapped);
}

void insert_sorted(SList *first, element e)
{
    SList new_node=(SList)malloc(sizeof(nodeSL));
    SList current;
    new_node->e=e;
    new_node->next=NULL;
    if(is_emptySL(*first) || (*first)->e>=e)
    {
        new_node->next=*first;
        *first=new_node;
    }
    else
    {
        current=*first;
        while(current->next!=NULL && current->next->e<e)
            current=current->next;
        new_node->next=current->next;
        current->next=new_node;
    }
}

void fusionSL(SList listas[], int n_listas)
{
    SList fusioned_list,actual;
    int i;
    createSL(&fusioned_list);
    for(i=0; i<n_listas; i++)
    {
        actual=listas[i];
        while(actual!=NULL)
        {
            insert_sorted(&fusioned_list,actual->e);
            actual=actual->next;
        }
    }
    printf("Lista fusionada correctamente:\n");
    printSL(fusioned_list);
    deleteSL(&fusioned_list);
}