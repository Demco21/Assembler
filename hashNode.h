
/* Hash table structure definition */

struct hashNode
{
  char key[11];             /* The key represents the symbol */
  int LC;                   /* The corresponding LC value of the symbol */
  struct hashNode *next;    /* used for chaining */
};