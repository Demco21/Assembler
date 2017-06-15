
/* Prototypes for functions in symbolTable.c */
#include "hashNode.h"

void insertHashNode(struct hashNode **table, char *key, int LC, int hashSize);

int getSymbolLC(struct hashNode *table[], char *key, int hashSize);

void printHashTable(struct hashNode *table[], int hashSize);
