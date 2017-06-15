#include "libraries.h"
#include "constants.h"
#include "bstNode.h"
#include "hashNode.h"
#include "input.h"
#include "utils.h"

struct hashNode ** buildSymbolTable(struct hashNode **symbolTable, struct bstNode *tree, FILE * programFile, int hashTableSize)
{
  char * currentLine;     /* Memory to store one line of the program file. */
  int LC = 0;            /* LC value of each line being read. */
  int format = 0;        /* Byte format of the instruction being read. (used to increment LC) */
  
  /* Keep looping while there are bytes to be read in the program file. */
  while((currentLine = getLine(programFile)) != NULL)
  {
    /* Handles lines without any symbols in the label field. */
    /* This means the first string in the line will be an instruction. */
    /* Just need to increment the LC value and move on */
    if(currentLine[0] == '\t' || currentLine[0] == ' ')
    {
      char delimiters[] = " \t";   /* Delimiters to tokenize each line read. */
      /* lineInstruction will be the first token (an instruction) */
      /* Must remove the tab character as well */
      char * lineInstruction = strtok(currentLine, delimiters);
        
      /* Get the byte format of the instruction and add it to the LC value. */
      if((format = getInstructionFormat(tree, lineInstruction)) != NULL)
        LC += format;
      else
        printError("ERROR: Undefined instruction in the program file.\n");
    }
    /* Handles line with symbols in the label field. */
    /* This means the first string in the line will be a symbol. */
    else
    {
      /* Tokenize the line by spaces. */
      /* lineSymbol will be the first token (a symbol) */
      char ** tokens = tokenize(currentLine, ' ');
      char * lineSymbol = tokens[0];
      char * lineInstruction = tokens[1];
        
      /* If the instruction is "word" */
      if(strcmp(lineInstruction, WORD) == 0)
      {
        /* Insert the symbol into the hash table and increment the LC value by 3 */
        insertHashNode(symbolTable, lineSymbol, LC, hashTableSize);
        LC += 3;
      }  
      /* If the instruction is resw */
      else if(strcmp(lineInstruction, RESW) == 0)
      {
        /* Insert the symbol into the hash table */
        insertHashNode(symbolTable, lineSymbol, LC, hashTableSize);
          
        /* lineInstruction will now be set to the third token (the number of words) */
        /* Increment the LC value by (3*the number of words) */
        char * value = tokens[2];
        LC += 3*atoi(value);
      }        
      /* If the instruction is "resb" */
      else if(strcmp(lineInstruction, RESB) == 0)
      {
        /* Insert the symbol into the hash table */
        insertHashNode(symbolTable, lineSymbol, LC, hashTableSize);
          
        /* lineInstruction will now be set to the third token (number of bytes) */
        /* Increment the LC value by the number of bytes */
        char * value = tokens[2];
        LC += atoi(lineInstruction);
      }
      /* If this is reached then the instruction must be defined in the opcode tree. */
      /* Get the byte format of the instruction. */
      else if((format = getInstructionFormat(tree, lineInstruction)) != NULL)
      {
        /* Insert the symbol into the symbol table and increment the LC value by the byte format */
        insertHashNode(symbolTable, lineSymbol, LC, hashTableSize);
        LC += format;
      }
      else
      {
        /* Print an error if the instruction didn't return a format value */
        printError("Undefined instruction in the program file.\n");
      }
    }  
  } /* end while loop */
  
  rewind(programFile);
  return symbolTable;
}