#ifndef SLIST
#define SLIST
typedef int element;
typedef struct nodeSL
{
    element e;
    struct nodeSL *next;
}nodeSL;
typedef nodeSL* SList;
typedef struct HeapNode
{
    SList list;
    int index;
}HeapNode;

void createSL(SList *first);
int is_emptySL(SList first);
void insert_at_first(SList *first, element e);
void deleteSL(SList *first);
void printSL(SList first);
SList splitSL(SList head);
SList mergeSL(SList left, SList right);
SList merge_sortSL(SList head);
void sortSL(SList *first);
void swap(HeapNode* a, HeapNode* b);
void heapify(HeapNode heap[], int size, int i);
void fusionSL(SList lists[], int n_listas);

#include "P5_E2slist.c"
#endif