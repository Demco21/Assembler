#include "libraries.h"
#include "constants.h"
#include "utils.h"

/* Read a line from a file stream line by line */
/* Returns null when EOF is reached */
char* getLine(FILE* stream)
{
  if(stream == NULL)
    printError("ERROR: Invalid file stream.\n");

  
  char* lineBuffer = malloc(LINE_MAX*sizeof(char));
  char ch;
  int i = 0;
  
  lineBuffer[0] = '\0';
  while((ch = getc(stream)) != EOF)
  {
    if(ch == '\n')
    {
      break;
    }
    else
    {
      lineBuffer[i] = ch;
      lineBuffer[i+1] = '\0';
      i++;
    }
  }
  
  if(lineBuffer[0] == '\0')
    return NULL;
  
  return lineBuffer;
}
