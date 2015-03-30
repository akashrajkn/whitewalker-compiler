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


//enum
enum tokenType
{
  TK_LP, TK_RP, TK_LB, TK_RB, TK_COM, TK_SEMICOL, TK_PLUS, TK_MINUS, TK_MUL,
  TK_LSB, TK_RSB, TK_COL, TK_DOL, TK_EQ, TK_NOT, TK_GT, TK_LT, TK_GET, TK_LET,
  TK_NEQ, TK_EQEQ, TK_WIF, TK_WINT, TK_WELSE, TK_WFLOAT, TK_ID, TK_WWIC, TK_WFDEF,
  TK_WBOOL, TK_WTRUE, TK_WFLS

}tokens;


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

        case 'i': { nextState = 1; break; }

        case 'f': { nextState = 7; break; }

        case 'r': { nextState = 4; break; }

        case 's': { nextState = 5; break; }

        case 'w': { nextState = 1; break; }

        case 't': { nextState = 1; break; }

        case '=': { nextState = 1; break; }

        case '!': { nextState = 1; break; }

        case '>': { nextState = 1; break; }

        case '<': { nextState = 1; break; }

        case '"': { nextState = 1; break; }

        default : if(isAlpha(ch))
                  {  

                  }
                  else if(isNum(ch))
                  {
 
                     break;
                  }
                  else
                  {
                    fprintf(fout, "TK_ERR       %d   \n", -1);


                  }
      }
    }
  }

  case 1:
    {
      switch(*ch)
      {
        case 'n': { nextState = 2; break; } //current recognised is "in"

        case 'f': { nextState = 3; break; } //current recognised is "if"

        default : { if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; } }
      }

      break;
    }

    case 2:
    {
      if(*ch=='t')
      {
        nextState = 6;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 3:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(2); //prints "if" keyword
        break;
      }
      else
      {
        nextState = 10;
        break;
      }
    }

    case 4: //this case prints the identifier -- > identifier recognized
    {
      retract();
      printID();
      nextState = 0;
      break;
    }

    case 5: //current string being read maybe an identifier
    {
      if(checkID(ch))
      {
        retract();
        printID();
        nextState = 0;
        break;
      }
      else if( *ch=='_' || (*ch>='0' && *ch<='9') || isAlpha(ch) )
      {
        nextState = 10; //still a part of identifier
        break;
      }
    }

    case 6:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(1); //print the keyword "int"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 10;
        break;
      }
    }

    case 7:
    {
      switch(*ch)
      {
        case 'l': { nextState = 8; break; }  //current = "fl"

        case 'd': { nextState = 9; break; }  //current = "fd"

        case 'a': { nextState = 10; break; } //current = "fa"

        default : { if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; } }
      }

      break;
    }

    case 8:
    {
      if(*ch=='o')  // "flo"
      {
        nextState = 11;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }

    }

    case 9:
    {

    }

    case 10:
    {

    }

    case 11:
    {
      if(*ch=='a')
      {
        nextState = 12;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }

    }

    case 12:
    {
      if(*ch=='t')
      {
        nextState = 13;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 13:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(3); //print the keyword "float"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 10;
        break;
      }
    }

  }

}


/* print the corresponding keyword */
void printKeyword(int choice)
{
  switch(choice)
  {
    case 1: fprintf(fout, "TK_WINT       %d        int\n", TK_WINT); break;

    case 2: fprintf(fout, "TK_WIF        %d        if\n", TK_WIF); break;


  }

  f3 = 1;
}

