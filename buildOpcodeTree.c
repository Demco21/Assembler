#include "libraries.h"
#include "bstNode.h"

struct bstNode* buildOpcodeTree(struct bstNode *root, FILE *opcodeFile)
{
  char instruction[6];    /* Instruction read from file. */
  int opcode;             /* Opcode for each BST node. */
  int format;             /* Format for each hash node. */
  
  /* The following code block will insert the contents of opcodeFile into a binary tree. */
  /* Read the first line and make that the root node. */
  if(fscanf(opcodeFile, "%s%d%d", instruction, &opcode, &format) == 3)
  {
    if(strlen(instruction) <= 5 && opcode >= 0 && format > 0 && format <= 3)
      root = (struct bstNode *)insertBSTNode(root, instruction, opcode, format); /* Root node */
    else
      printError("Error: Invalid format in the opcode file.\n");

    /* Keep reading each line and add the contentes into the tree until EOF is reached. */
    while(fscanf(opcodeFile, "%s%d%d", instruction, &opcode, &format) == 3)
      insertBSTNode(root, instruction, opcode, format);
  }
  rewind(opcodeFile);
  return root;
}