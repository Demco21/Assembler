#include "libraries.h"
#include "bstNode.h"


/* Recursive function to insert a node into a binary search tree. */
struct bstNode * insertBSTNode(struct bstNode *root, char *key, int opcode, int format)
{
  /* BASE CASE: If there is no root here */
  if(root == NULL)
  {
    /* Insert the node as the root. */
    root = malloc(sizeof(struct bstNode));
    
    /* Fill the contents of the root. */
    strcpy(root->key, key);
    root->opcode = opcode;
    root->format = format;
    root->left = NULL;
    root->right = NULL;
    
    return root;
  }
  /* If the node key is less than the root key. */
  if(strcmp(key, root->key) < 0)
  {
    /* Go left recursively. */
    root->left = insertBSTNode(root->left, key, opcode, format);
    return root;
  }
  /* If the node key is greater than the root key. */
  else if(strcmp(key, root->key) > 0)
  {
    /* Go right recursively. */
    root->right = insertBSTNode(root->right, key, opcode, format);
    return root;
  }
}




/* Recursive funtion to get the opcode of a given key (instruction) in the binary search tree. */
int getInstructionOpcode(struct bstNode *root, char *key)
{
  /* BASE CASE: If there is no root here */
  if(root == NULL)
  {
    return NULL;
  }
  /* If the keys match at this node. */
  else if(strcmp(key, root->key) == 0)
  {
    return root->opcode;
  }
  /* If the node key is less than the root key.  */
  else if(strcmp(key, root->key) < 0)
  {
    /* Go left recursively */
    getInstructionOpcode(root->left, key);
  }
  /* If the node key is greater than the root key */
  else if(strcmp(key, root->key) > 0)
  {
    /* Go right recursively */
    getInstructionOpcode(root->right, key);
  }
  else
  {
    return NULL;
  }
}



/* Recursive funtion to get the format of a given key (instruction) in the binary search tree. */
int getInstructionFormat(struct bstNode *root, char *key)
{
  /* BASE CASE: If there is no root here */
  if(root == NULL)
  {
    return NULL;
  }
  /* If the keys match at this node. */
  else if(strcmp(key, root->key) == 0)
  {
    return root->format;
    printf("%s has %u byte format\n", key, root->format);
  }
  /* If the node key is less than the root key.  */
  else if(strcmp(key, root->key) < 0)
  {
    /* Go left recursively */
    getInstructionFormat(root->left, key);
  }
  /* If the node key is greater than the root key */
  else if(strcmp(key, root->key) > 0)
  {
    /* Go right recursively */
    getInstructionFormat(root->right, key);
  }
}


/* returns the height of a binary tree */
int getTreeHeight(struct bstNode *root)
{
  int leftHeight = 0;
  int rightHeight = 0;
  
  /* BASE CASE: If their is no root or if a node has no children */
  if(root == NULL || (root->left == NULL && root->right == NULL))
  {
    return 0;
  }
  else
  {  
    /* Recursively get the height of the left subtree and right subtree */
    leftHeight = getTreeHeight(root->left);
    rightHeight = getTreeHeight(root->right);
    
    /* Return 1 + max(leftHeight, rightHeight) */
    if(leftHeight > rightHeight)
      return (1 + leftHeight);
    else
      return (1 + rightHeight);
  }

}



/* Recursive function to print all the keys (instructions) of a binary tree in alphabetical order */
void printTreeInOrder(struct bstNode *root)
{
  /* BASE CASE: If there is no root here */
  if(root == NULL)
  {
    return;
  }
  
  /* Recursively print: left child, root, right */
  printTreeInOrder(root->left);
  printf("%s ", root->key);
  printTreeInOrder(root->right);
}

