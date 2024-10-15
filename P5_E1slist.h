#ifndef SLIST
#define SLIST
typedef int element;
typedef struct nodeSL
{
    element e;
    struct nodeSL *next;
}nodeSL;
typedef nodeSL* SList;

void createSL(SList *first);
int is_emptySL(SList first);
void insert_at_first(SList *first, element e);
void deleteSL(SList *first);
void printSL(SList first);
void sortSL(SList *first);
void insert_sorted(SList *first, element e);
void fusionSL(SList listas[], int n_listas);

#include "P5_E1slist.c"
#endif