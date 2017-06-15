#include "libraries.h"
#include "constants.h"
#include <math.h>

/* print error message to stderr */
void printError(char * errorMsg)
{
  fprintf(stderr, errorMsg);
  fflush(stderr);
  exit(1);
}


/* reverse the order of characters in a string */
void reverseString(char * string)
{
  int i = 0;
  int j = strlen(string) - 1;
  char temp;
  
  while(i < j)
  {
    temp = string[i];
    string[i] = string[j];
    string[j] = temp;
    i++;
    j--;
  }
}


/* Returns the extension of a file */
char * getExtension(char * filename)
{
  int filenameLen = strlen(filename);
  char * extension = malloc(filenameLen*sizeof(char));
  int i = 0;
  int j = 0;
  
  /* Start from the end of the string an read backwards until a period is reached */
  for(i = filenameLen - 1; i >= 0; i--)
  {
    j = (filenameLen - 1) - i;
    extension[j] = filename[i];

    if(filename[i] == '.')
    {
      extension[++j] = '\0';
      break;
    }
  }

  reverseString(extension);
  return extension;
}


/* Returns the number of string tokens with delimiter '-' using the file as the string */
int tokenCount(char * string, char delim)
{
  int numTokens = 1;
  int i = 0;
  
  for(i = 0; i < strlen(string); i++)
  {
    if(string[i] == delim)
      numTokens++;
  }
  
  return numTokens;
}


/* Returns an array of string tokens using '-' as the delimitor */
char ** tokenize(char string[], char delimiter)
{

  int numTokens = tokenCount(string, delimiter);
  char ** strTokens = malloc(numTokens*sizeof(char *));
  char delim[2];
  char newString[strlen(string) + 1];
  int i = 0;
  
  /* Make a copy of the string */
  strcpy(newString, string);

  delim[0] = delimiter;
  delim[1] = '\0';

  char * token = strtok(newString, delim);
  strTokens[0] = malloc(strlen(token) + 1);
  strcpy(strTokens[0], token);
  

  i = 1;
  /* fill strTokens[] with each token */
  while((token = strtok(NULL, delim)) != NULL)
  {
    strTokens[i] = malloc(strlen(token) + 1);
    strcpy(strTokens[i], token);
    i++;
  }
  
  return strTokens;
}

/* return x to the power of y */
int Pow(int x, int y)
{
  int i;
  int value = x;
  
  if(y == 0)
  {
    return 1;
  }
  else
  {
  for(i = 0; i < y-1; i++)
    value = value * x;
  }
  return value;
}



/* convert num to binary store it in str */
void getBin(int num, char *str)
{
  int i;
  int size = strlen(str);
  
  for(i = 0; i < size; i++)
    str[i] = '0';
  str[size] = '\0';
  
  for(i = 0; i < size+1; i++)
  {
    int bitVal = Pow(2,size-(i+1));
    if((num/bitVal) >0)
    {
      num = num%bitVal;
      str[i] = '1';
    }
  }
}



