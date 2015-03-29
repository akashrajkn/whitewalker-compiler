/*
  WHITEWALKER-COMPILER

  Authors: Akash Raj K N
           Anjali Thakur
           Ashwin Raghavan
           Sowmya G Kumar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//file pointers
FILE *fin, *fout;


//state variables
int state = 0;


//input buffer
char input[100];
char *ch, *start, *current;


//flags
int f1 = 0, f2 = 0, f3 = 0;


//function declarations
void fileInitialize(); //initialize input and output files
int getState(char *);  //dfa states - to tokenize input program


int main(int argc, char const *argv[])
{
  fileInitialize();

  fprintf(fout, "TYPE                   LEXEME\n", );
  fprintf(fout, "-----------------------------\n", );

  while( (fscanf(fin, "%s", input))!=EOF )
  {
    ch = input;
    start = input;
    current = input;

    while(*current != '\0' || state != 0)
    {
      state = getState(current);      //get the current state
      current++;

      if( f1==1 || f2==1 || f3==1 )
      {
        start = current;
        f1 = 0;
        f2 = 0;
        f3 = 0;
      }
    }
  }

  fprintf(fout, "TK_EOF\n", );

  fcloseall();      //close all- file pointers

  return 0;
}


/* initialize input and output files */
void fileInitialize()
{
  fin = fopen("input.txt", "r");
  fout = fopen("output.txt", "w");

  if(fin==NULL || fout==NULL)
  {
    printf("file initialization error\n");
  }
}


/* get the current state (dfa) of the input program */
int getState(char *ch)
{
  int nextState = 0;

  switch(state)
  {
    case 0:
    {
      switch(*ch)
      {
        case '{': { printToken(1); nextState = 0; start = current; break; }

        case '}': { printToken(2); nextState = 0; start = current; break; }

        case '(': { printToken(3); nextState = 0; start = current; break; }

        case ')': { printToken(4); nextState = 0; start = current; break; }

        case ',': { printToken(5); nextState = 0; start = current; break; }

        case ';': { printToken(6); nextState = 0; start = current; break; }

        case '+': { printToken(7); nextState = 0; start = current; break; }

        case '-': { printToken(8); nextState = 0; start = current; break; }

        case '*': { printToken(9); nextState = 0; start = current; break; }

        case '/': { printToken(10); nextState = 0; start = current; break; }

        case '[': { printToken(11); nextState = 0; start = current; break; }

        case ']': { printToken(12); nextState = 0; start = current; break; }

        case ':': { printToken(13); nextState = 0; start = current; break; }

        case '$': { printToken(14); nextState = 0; start = current; break; }


      }
    }
  }



}




