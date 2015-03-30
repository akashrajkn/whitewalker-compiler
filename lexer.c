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
  TK_WBOOL, TK_WTRUE, TK_WFLS, TK_WCHAR, TK_WHILE, TK_WRET

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

        case 'e': { nextState = 19; break; }

        case 'c': { nextState = 23; break; }

        case 'b': { nextState = 27; break; }

        case 't': { nextState = 31; break; }

        case 'w': { nextState = 35; break; }

        case 'r': { nextState = 40; break; }

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
        nextState = 5;
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
        nextState = 5;
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
      if(*ch=='e')  // "fde"
      {
        nextState = 14;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 10:
    {
      if(*ch=='l')  // "fal"
      {
        nextState = 16;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
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
        nextState = 5;
        break;
      }
    }

    case 14:
    {
      if(*ch=='f')  // "fdef"
      {
        nextState = 15;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 15:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(4); //print the keyword "fdef"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 16:
    {
      if(*ch=='s')  // "fals"
      {
        nextState = 17;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 17:
    {
      if(*ch=='e')  // "false"
      {
        nextState = 18;
        break; 
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 18:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(5); //print the keyword "false"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 19:
    {
      if(*ch=='l')  // "el"
      {
        nextState = 20;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 20:
    {
      if(*ch=='s')  //"els"
      {
        nextState = 21;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 21:
    {
      if(*ch=='e') //"else"
      {
        nextState = 22;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 22:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(6); //print the keyword "else"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 23:
    {
      if(*ch=='h')  // "ch"
      {
        nextState = 24;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 24:
    {
      if(*ch=='a')  // "cha"
      {
        nextState = 25;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 25:
    {
      if(*ch=='r')  // "char"
      {
        nextState = 26;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 26:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(7); //print the keyword "char"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 27:
    {
      if(*ch=='o')  // "bo"
      {
        nextState = 28;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 28:
    {
      if(*ch=='o')  // "boo"
      {
        nextState = 29;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 29:
    {
      if(*ch=='l')  // "bool"
      {
        nextState = 30;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 30:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(8); //print the keyword "bool"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 31:
    {
      if(*ch=='r')
      {
        nextState = 32;  // "tr"
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 32:
    {
      if(*ch=='u')  // "tru"
      {
        nextState = 33;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 33:
    {
      if(*ch=='e')  // "true"
      {
        nextState = 34;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 34:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(9); //print the keyword "true"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 35:
    {
      if(*ch=='h')  // "wh"
      {
        nextState = 36;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 36:
    {
      if(*ch=='i')  // "whi"
      {
        nextState = 37;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 37:
    {
      if(*ch=='l')  // "whil"
      {
        nextState = 38;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 38:
    {
      if(*ch=='e')  // "while"
      {
        nextState = 39;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 39:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(10); //print the keyword "true"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }

    case 40:
    {
      if(*ch=='e')   // "re"
      {
        nextState = 41;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 41:
    {
      if(*ch=='t')  // "ret"
      {
        nextState = 42;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 42:
    {
      if(*ch=='u')  // "retu"
      {
        nextState = 43;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }  

    case 42:
    {
      if(*ch=='r') // "retur"
      {
        nextState = 43;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 43:
    {
      if(*ch=='n')  // "return"
      {
        nextState = 44;
        break;
      }
      else
      {
        if(checkID(ch)){ nextState = 4;retract(); break; } else{ nextState = 5; break; }
      }
    }

    case 44:
    {
      if(checkID(ch))
      {
        retract();
        printKeyword(11); //print the keyword "return"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }
    }
    

  }//switch statement for state variable ends here

}


/* print the corresponding keyword */
void printKeyword(int choice)
{
  switch(choice)
  {
    case 1: fprintf(fout, "TK_WINT       %d        int\n", TK_WINT); break;

    case 2: fprintf(fout, "TK_WIF        %d        if\n", TK_WIF); break;

    case 3: fprintf(fout, "TK_WFLOAT     %d        float\n", TK_WFLOAT); break;

    case 4: fprintf(fout, "TK_WFDEF      %d        fdef\n", TK_WFDEF); break;

    case 5: fprintf(fout, "TK_WFLS       %d        false\n", TK_WFLS); break;

    case 6: fprintf(fout, "TK_WELSE      %d        else\n", TK_WELSE); break;

    case 7: fprintf(fout, "TK_WCHAR      %d        char\n", TK_WCHAR); break;

    case 8: fprintf(fout, "TK_WBOOL      %d        bool\n", TK_WBOOL); break;

    case 9: fprintf(fout, "TK_WTRUE      %d        true\n", TK_WTRUE); break;

    case 10: fprintf(fout, "TK_WHILE      %d        while\n", TK_WHILE); break;

    case 11: fprintf(fout, "TK_WRET       %d        return\n", TK_WRET); break;


  }

  f3 = 1;
}

