
/* Binary tree structure definition */

struct bstNode
{
  char key[6];           /* The key represents the instruction. */
  int opcode;            /* The corresonding opcode of the instruction. */
  int format;            /* 1byte 2byte or 3byte format */
  struct bstNode *left;  /* Left child */
  struct bstNode *right; /* Right child */
};