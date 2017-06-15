#include "libraries.h"
#include "symbolTable.h"
#include "opcodeTree.h"
#include "buildTables.h"
#include "utils.h"
#include "assembler.h"
#include "constants.h"

/* This program will take in command line arguments as follows: firstpass opcodefile programfile hashTableSize */

/* Each line of opcode file will be in the following format: instruction opcode byteFormat (does not handle 4 byte formats) */

/* Each line of program file will be as follows: '\t' instruction [arguments...]
                                                 or
                                                 symbol instruction [arguments...]
                                                 or
                                                 symbol directive argument           */
                                                 
/* This program simulates the first pass of a two pass assembler.
   The opcode file will be used to create the opcode table which will be stored in a binary tree.
   The program file will be used to create the symbol table which will be stored in a hash table. */

void main(int argc, char **argv)
{
  
  if(argc != 4)
    printError("ERROR: Invalid number of command line arguments.\n");

  int hashTableSize = atoi(argv[3]);                /* Fourth command line is the size of the hash table. */
  char *opcodeFileName = malloc(strlen(argv[1]));   /* Name of the opcode file. */
  char *programFileName = malloc(strlen(argv[2]));  /* Name of the program file. */
  FILE *opcodeFile;
  FILE *programFile;
  
  opcodeFileName = argv[1];  /* Second command line argument is the opcode file. */
  programFileName = argv[2]; /* Third command line argument is the program file. */
  
  if(hashTableSize <= 0)
    printError("ERROR: Please input proper hash table size in the command line.\n");
    
  if(strcmp(getExtension(programFileName), PROG_FILE_EXT) != 0)
    printError("ERROR: Program file must have extension .asm\n");
  
  /* File for BST */
  /* Each line of this file must be in the format: <instruction> <opcode> <format> */
  if((opcodeFile = fopen(opcodeFileName, "r")) == NULL)
    printError("Could not open file for reading.\n");
  
  /* File for hash table */
  /* Each line of this file must be in the format: (<label>) <instruction> <arguments...> */
  /*                                           or: (<label>) <directive> <argument>       */
  if((programFile = fopen(programFileName, "r")) == NULL)
    fprintf(stderr, "Could not open file for reading.\n");
  
  /* initialize symbol table of size 'hashTableSize' */
  struct hashNode **symbolTable = calloc(hashTableSize, sizeof(struct bstNode));
  
  /* initialize instruction tree and nullify */
  struct bstNode *tree = NULL;
  
  /* nullify the symbol table */
  int i = 0;
  for(i = 0; i < hashTableSize; i++)
  {
    symbolTable[i] = NULL;
  }

  /* Build the opcode table. */
  tree = (struct bstNode *)buildOpcodeTree(tree, opcodeFile);
  
  /* Build the symbol table. */
  symbolTable = (struct hashNode **)buildSymbolTable(symbolTable, tree, programFile, hashTableSize);
  
  //puts("\nPRINTING INSTRUCTION TREE IN ORDER.");
  //printTreeInOrder(tree);
  //puts("\n");
  
  //printf("Height of tree: %d\n", getTreeHeight(tree));
  
  //puts("\nPRINTING SYMBOL TABLE.");
  //printHashTable(symbolTable, hashTableSize);
  
  /* assemble instructions */
  assemble(tree, symbolTable, hashTableSize, programFile);
  
  fclose(opcodeFile);
  fclose(programFile);
}