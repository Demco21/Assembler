
/* Prototypes for the functions in buildOpcodeTree.c and buildSymbolTable.c */

struct bstNode* buildOpcodeTree(struct bstNode *root, FILE *opcodeFile);

struct hashNode ** buildSymbolTable(struct hashNode **symbolTable, struct bstNode *tree, FILE * programFile, int hashTableSize);