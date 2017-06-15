#include "libraries.h"
#include "hashNode.h"
#include "hashFunction.h"


/* Function to insert a node into a hash table. */
void insertHashNode(struct hashNode **table, char *key, int LC, int hashSize) 
{
  /* Create the node to be inserted. */
  struct hashNode *newNode = malloc(sizeof(struct hashNode));
  
  /* Insert the key (symnbol) into the hash function to get the index of the hash table. */
  int index = hashFunction(key, hashSize);
  
  /* Check validity of new hash node */
  if(strlen(key) <= 10 && strlen(key) > 0 && LC >= 0)
  {
    /* Fill the contents of the new node. */
    strcpy(newNode->key, key);
    newNode->LC = LC;
    newNode->next = NULL;
  }
  else
  {
    fprintf(stderr, "Error: Invalid hash node attributes.\n");
    exit(1);
  }
  
  /* If there are currently no nodes at this index (i.e. No collision) */
  if(table[index] == NULL)
  {
    /* Insert the new node as the head of this index. */
    table[index] = newNode;
  }
  else
  { 
    /* COLLISION ENCOUNTERED */
    /* The following will perform chaining... */

    /* Make the new node point to the current head at this index. */
    newNode->next = table[index];
    
    /* Insert the new node as the new head at this index. */
    table[index] = newNode;
  }
}




/* Function to get the LC value for a given key (symbol) in a hash table. */
int getSymbolLC(struct hashNode *table[], char *key, int hashSize)
{
  /* Create two nodes to traverse through the lists.  */
  struct hashNode *searchNode = malloc(sizeof(struct hashNode));
  struct hashNode *nextNode = malloc(sizeof(struct hashNode));
  
  /* Insert the key (symbol) into the hash function to get the index of the hash table. */
  int index = hashFunction(key, hashSize);
  
  /* Set searchNode to the current head at its index. */
  searchNode = table[index];
  
  /* If there exists a node at this index. */
  if(searchNode != NULL)
  {
    /* Set nextNode to whatever the head is currently pointing to. */
    nextNode = searchNode->next;
    
    /* If the keys match return searchNode. */
    if(strcmp(searchNode->key, key) == 0)
    {
      return searchNode->LC;
    }
    /* Else the keys dont match so we have to search through the list at this index */
    else
    {
      /* Keep looping until we reach the end of the list. */
      while(nextNode != NULL)
      {
        /* If the keys match return its node. */
        if(strcmp(nextNode->key, key) == 0)
        {
          return nextNode->LC;
        }
        
        /* If keys dont match then go to the next node in the list. */
        searchNode = nextNode;
        nextNode = searchNode->next;
      }
        /* If we dont return a node then the node does not exist. */
        printf("Symbol '%s' does not exist.\n", key);
        return -1;
    }
  }
  else
  {
    printf("Symbol '%s' does not exist\n.", key);
    return -1;
  }
}




/* Function to print all the keys (symbols) inside a hash table. */
void printHashTable(struct hashNode *table[], int hashSize)
{
  /* Create two nodes to traverse through the lists. */
  struct hashNode *currentNode = malloc(sizeof(struct hashNode));
  struct hashNode *nextNode = malloc(sizeof(struct hashNode));
  
  int i;
  for(i = 0; i < hashSize; i++)
  {
    /* Get the head of the list. */
    currentNode = table[i];
    
    /* If there exists a head */
    if(currentNode != NULL)
    {
      /* Print the head  */
      printf("%d: (Key: %s  LC: %d) -> ", i, currentNode->key, currentNode->LC);
      
      /* Set nextNode to whatever node the head is pointing to */
      nextNode = currentNode->next;
      
      /* Keep looping until we reach the end of the list. */
      while(nextNode != NULL)
      {
        /* Print the contents of the node. */
        printf("(Key: %s  LC: %d) -> ", nextNode->key, nextNode->LC);
        
        /* Go to the next node in the list. */
        nextNode = nextNode->next;
      }
    }
    else
    {
      printf("%d: ", i);
    }
    puts(" NULL");
  }
}



