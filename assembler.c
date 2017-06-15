#include "libraries.h"
#include "input.h"
#include "utils.h"
#include "opcodeTree.h"
#include "symbolTable.h"

/* Given a register, returns the corresponding binary value */
char * getRegBits(char * reg)
{
    
  char rA[5] = "0000";
  char rX[5] = "0001";
  char rL[5] = "0010";
  char rB[5] = "0011";
  char rS[5] = "0100";
  char rT[5] = "0101";
  char rF[5] = "0110";
  char rPC[5] = "1000";
  char rSW[5] = "1001";
  
  char * regBits = malloc(5*sizeof(char));

  if(strcmp(reg, "A") == 0)
    strcpy(regBits, rA);
  else if(strcmp(reg, "X") == 0)
    strcpy(regBits, rX);
  else if(strcmp(reg, "L") == 0)
    strcpy(regBits, rL);
  else if(strcmp(reg, "B") == 0)
    strcpy(regBits, rB);
  else if(strcmp(reg, "S") == 0)
    strcpy(regBits, rS);
  else if(strcmp(reg, "T") == 0)
    strcpy(regBits, rT);
  else if(strcmp(reg, "F") == 0)
    strcpy(regBits, rF);
  else if(strcmp(reg, "PC") == 0)
    strcpy(regBits, rPC);
  else if(strcmp(reg, "SW") == 0)
    strcpy(regBits, rSW);
  else
    printError("ERROR: Invalid register.\n");
    
  return regBits;
}


/* reads each line of the program file and assembles them into their binary value */
void assemble(struct bstNode *root, struct hashNode **symbolTable, int hashSize, FILE * programFile)
{
  char * linebuffer;
  int line = 1;
  int LCval = 0;

  FILE* outFile;
  
  if((outFile = fopen("mycode.obj", "w")) == NULL)
  {
    fprintf(stderr, "Could not open output file for writing.\n");
    exit(1);
  }

  /* Keep reading until end of file is reached */
  while((linebuffer = getLine(programFile)) != NULL)
  {
    char opcode6Bit[7] = "000000";    /* Binary opcode for 3 byte instructions */
    char opcode8Bit[9] = "00000000";  /* Binary opcode for 2 and 1 byte instructions */
    char LCbin[13] = "000000000000";  /* Binary LC value for 3 byte instructions */
    char * nixbpe;                    /* Opcode for 3 byte instructions */

    int numTokens = 0;
    numTokens = tokenCount(linebuffer, ' ');

    /* Tokenize each line */
    char ** tokens = malloc(numTokens*sizeof(char *));
    tokens = tokenize(linebuffer, ' ');
 
    /* If the first token contains a tab then there is no symbol being defined */
    if(tokens[0][0] == '\t')
    {
      char instr[strlen(tokens[0])];
      int i;
      for(i = 0; i < strlen(tokens[0]); i++)
        instr[i] = tokens[0][i+1];
      i = 0;
      
      /* Assembles 1 byte instructions */
      if(getInstructionFormat(root, instr) == 1)
      {
        getBin(getInstructionOpcode(root, instr),opcode8Bit);
        
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s%c", line, LCval, opcode8Bit, '\n');
        LCval += 1;
      }
      /* Assembles 2 byte instructions */
      else if(getInstructionFormat(root, instr) == 2)
      {
        char * r1 = getRegBits(tokens[1]);
        char * r2 = getRegBits(tokens[2]);
          
        getBin(getInstructionOpcode(root, instr), opcode8Bit);
        
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s %s %s%c", line, LCval, opcode8Bit, r1, r2, '\n');
        LCval += 2;
      }
      /* Assembles 3 byte instructions */
      else if(getInstructionFormat(root, instr) == 3)
      {
        char symbol[strlen(tokens[1])];
        int op = getInstructionOpcode(root, instr);
        
        /* If @ is in front of the symbol then n bit is on, else n bit is off and i bit is on*/
        if(tokens[1][0] == '@')
        {
          nixbpe = "100000";
          for(i = 0; i < strlen(tokens[1]); i++)
            symbol[i] = tokens[1][i+1];
          int LCint = getSymbolLC(symbolTable, symbol, hashSize);
          getBin(LCint, LCbin);
        }
        /* If # is in front of the symbol then it is an immediate */
        else if(tokens[1][0] == '#')
        {
          nixbpe = "010000";
          for(i = 0; i < strlen(tokens[1]); i++)
            symbol[i] = tokens[1][i+1];
          getBin(atoi(symbol), LCbin);
        }
        /* Assemble normally */
        else
        {
          nixbpe = "000000";
          strcpy(symbol, tokens[1]);
          int LCint = getSymbolLC(symbolTable, symbol, hashSize);
          getBin(LCint, LCbin);
        }
        getBin(op, opcode6Bit);
        
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s %s %s%c", line, LCval, opcode6Bit, nixbpe, LCbin, '\n');
        LCval += 3;
      }
    }
    
    
    
    
    /* If the first token contains no tab then there is a symbol being defined */
    /* This is the only case that we find "word", "resw", or "resb" */
    else
    {
      int i = 0;
      /* Assembles 1 byte instructions */
      if(getInstructionFormat(root, tokens[1]) == 1)
      {
        int op = getInstructionOpcode(root, tokens[1]);
        getBin(op, opcode8Bit);
        
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s%c", line, LCval, opcode8Bit, '\n');
        LCval += 1;
      }
      /* Assembles 2 byte instructions */
      else if(getInstructionFormat(root, tokens[1]) == 2)
      {
        int op = getInstructionOpcode(root, tokens[1]);
        
        getBin(op, opcode8Bit);
        char * r1 = getRegBits(tokens[2]);
        char * r2 = getRegBits(tokens[3]);
        
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s %s %s%c", line, LCval, opcode8Bit, r1, r2, '\n');
        LCval += 2;
      }
      /* Assembles 3 byte instructions */
      else if(getInstructionFormat(root, tokens[1]) == 3)
      {
        char symbol[strlen(tokens[1])];
        int op = getInstructionOpcode(root, tokens[1]);

        /* If @ is in front of the symbol then n bit is on, else n bit is off and i bit is on*/
        if(tokens[2][0] == '@')
        {
          nixbpe = "100000";
          for(i = 0; i < strlen(tokens[2]); i++)
            symbol[i] = tokens[2][i+1];
          int LCint = getSymbolLC(symbolTable, symbol, hashSize);
          getBin(LCint, LCbin);
        }
        /* If # is in front of the symbol then it is an immediate */
        else if(tokens[2][0] == '#')
        {
          nixbpe = "010000";
          for(i = 0; i < strlen(tokens[2]); i++)
            symbol[i] = tokens[2][i+1];
          getBin(atoi(symbol), LCbin);
        }
        /* Assemble normally */
        else
        {
          nixbpe = "000000";
          strcpy(symbol, tokens[2]);
          int LCint = getSymbolLC(symbolTable, symbol, hashSize);
          getBin(LCint, LCbin);
        }
        getBin(op, opcode6Bit);

        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s %s %s%c", line, LCval, opcode6Bit, nixbpe, LCbin, '\n');
        LCval += 3;
      }
      /* Assembles word allocation */
      else if(strcmp(tokens[1], "word") == 0)
      {
        int value = atoi(tokens[2]);
        char assembled[25] = "000000000000000000000000";
        getBin(value, assembled);

        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s%c", line, LCval, assembled, '\n');
        LCval += 3;
      }
      /* Assembles resw allocation */
      else if(strcmp(tokens[1], "resw") == 0)
      {
        int numBytes = atoi(tokens[2])*3;
        int size = atoi(tokens[2])*24;
        char assembled[size+1];
        
        int i;
        for(i = 0; i < size; i++)
          assembled[i] = '0';
        assembled[size] = '\0';
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s%c", line, LCval, assembled, '\n');
        LCval += numBytes;
      }
      /* Assembles resb allocation */
      else if(strcmp(tokens[1], "resb") == 0)
      {
        int numBytes = atoi(tokens[2]);
        int size = numBytes*8;
        char assembled[size+1];
        
        int i;
        for(i = 0; i < size; i++)
          assembled[i] = '0';
        assembled[size] = '\0';
        fprintf(outFile, "Line:%d   LC:%d   Assembled:%s%c", line, LCval, assembled, '\n');
        LCval += numBytes;
      }
    }
    line++;
  }
}


