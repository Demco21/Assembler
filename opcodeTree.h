
/* Prototypes for functions in opcodeTable.c */
#include "bstNode.h"

struct bstNode * insertBSTNode(struct bstNode *root, char *key, unsigned char opcode, unsigned char format);

unsigned char getInstructionOpcode(struct bstNode *root, char *key);

unsigned char getInstructionFormat(struct bstNode *root, char *key);

int getTreeHeight(struct bstNode *root);

void printTreeInOrder(struct bstNode *root);