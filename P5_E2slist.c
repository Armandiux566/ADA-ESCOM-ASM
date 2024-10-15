#include "P5_E2slist.h"

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

SList splitSL(SList head)
{
    SList slow=head;
    SList fast=head->next;
    SList middle;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
    }
    middle=slow->next;
    slow->next=NULL;
    return middle;
}

SList mergeSL(SList left, SList right)
{
    if(left==NULL)
        return right;
    if(right==NULL)
        return left;
    if(left->e<right->e)
    {
        left->next=mergeSL(left->next,right);
        return left;
    }
    else
    {
        right->next=mergeSL(left,right->next);
        return right;
    }
}

SList merge_sortSL(SList head)
{
    SList middle,left,right;
    if(head==NULL || head->next==NULL)
        return head;
    middle=splitSL(head);
    left=merge_sortSL(head);
    right=merge_sortSL(middle);
    return mergeSL(left,right);
}

void sortSL(SList *first)
{
    *first=merge_sortSL(*first);
}

void swap(HeapNode* a, HeapNode* b)
{
    HeapNode temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(HeapNode heap[], int size, int i)
{
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<size && heap[left].list->e<heap[smallest].list->e)
        smallest=left;
    if(right<size && heap[right].list->e<heap[smallest].list->e)
        smallest=right;
    if(smallest!=i)
    {
        swap(&heap[i],&heap[smallest]);
        heapify(heap,size,smallest);
    }
}

void fusionSL(SList lists[], int n_listas)
{
    HeapNode* heap=(HeapNode*)malloc(n_listas*sizeof(HeapNode));
    SList lista_fusionada=NULL;
    SList* last=&lista_fusionada;
    SList min_node;
    int i,heap_size=0;
    for(i=0; i<n_listas; i++)
    {
        if(lists[i]!=NULL)
        {
            heap[heap_size].list=lists[i];
            heap[heap_size].index=i;
            heap_size++;
        }
    }
    for(i=(heap_size-1)/2; i>=0; i--)
    {
        heapify(heap,heap_size,i);
    }
    while(heap_size>0)
    {
        min_node=heap[0].list;
        nodeSL* new_node=(nodeSL*)malloc(sizeof(nodeSL));
        new_node->e=min_node->e;
        new_node->next=NULL;
        *last=new_node;
        last=&((*last)->next);
        if(min_node->next!=NULL)
            heap[0].list=min_node->next;
        else
        {
            heap[0]=heap[heap_size-1];
            heap_size--;
        }
        heapify(heap,heap_size,0);
    }
    printf("Lista fusionada:\n");
    printSL(lista_fusionada);
    deleteSL(&lista_fusionada);
    free(heap);
}