/*
  WHITEWALKER-COMPILER

  Authors: Akash Raj K N
           Ashwin Raghavan
           Sowmya G Kumar
           Anjali Thakur
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
char *ch, *start = NULL, *current = NULL;


//flags
int f1 = 0, f2 = 0, f3 = 0;


//enum
enum tokenType
{
  TK_LP, TK_RP, TK_LB, TK_RB, TK_COM, TK_SEMICOL, TK_PLUS, TK_MINUS, TK_MUL,
  TK_LSB, TK_RSB, TK_COL, TK_DOL, TK_EQ, TK_NOT, TK_GT, TK_LT, TK_GET, TK_LET,
  TK_NEQ, TK_EQEQ, TK_WIF, TK_WINT, TK_WELSE, TK_WFLOAT, TK_ID, TK_WHOD, TK_WFDEF,
  TK_WBOOL, TK_WTRUE, TK_WFLS, TK_WCHAR, TK_WHILE, TK_WRET, TK_VD, TK_VM, TK_DIV

}tokens;


/* function declarations */
void fileInitialize();         //initialize input and output files
int getState(char *);          //dfa states - to tokenize input program
void printToken(int);          //print the token
void printKeyword(int);        //print the keyword
void printerFunc();            //printer function--used in printKeyword, printToken functions
void printIdentifier();        //print the recognised identifier
void printFloat();             //print the floating point number
void printInteger();           //print the integer
void backTrack();              //used to go back 1 position after look-ahead
int isAlpha(char *);           //used to test if current character is an alphabet
int isNumber(char *);          //used to test if current character si a number
int checkSpecialChar(char *);  //check if the current character is a special character
void cleanUp();



int main()
{
  fileInitialize();

  fprintf(fout, "TYPE                   LEXEME\n" );
  fprintf(fout, "-----------------------------\n" );

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

  //fprintf(fout, "TK_EOF\n");

  fcloseall();      //close all- file pointers

  cleanUp();

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


/**/
void cleanUp()
{
  int k, idx;

  fout = fopen("output.txt", "r");

  FILE *flexout = fopen("lexerOutput.txt", "w");
  
  if(fout==NULL || flexout==NULL)
  {
    printf("file init error\n");
  }

  char buf[500], fbuf[500];

  while( fgets(buf, 500, fout)!=NULL )
  {
    if(strstr(buf, "ValarMorghulis")!=NULL)
    {
      fbuf[0] = 'T';fbuf[1] = 'K';fbuf[2] = '_';
      fbuf[3] = 'V';fbuf[4] = 'M';
      idx = 5;
      for(k=5; k<strlen(buf); ++k)
      {
        fbuf[idx++] = buf[k];
      }
      fbuf[idx] = '\0';

      //fputs(fbuf, flexout);
    }
    else if(strstr(buf, "ValarDohaeris")!=NULL)
    {
      fbuf[0] = 'T';fbuf[1] = 'K';fbuf[2] = '_';
      fbuf[3] = 'V';fbuf[4] = 'D';
      idx = 5;
      for(k=5; k<strlen(buf); ++k)
      {
        fbuf[idx++] = buf[k];
      }
      fbuf[idx] = '\0';

      //fputs(fbuf, flexout); 
    }
    else
    {
      strcpy(fbuf, buf);
    }

    fputs(fbuf, flexout);
  }

  fcloseall();
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

        case 'H': { nextState = 46; break; }

        case '=': { nextState = 51; break; }

        case '!': { nextState = 52; break; }

        case '>': { nextState = 53; break; }

        case '<': { nextState = 54; break; }

        case '"': { nextState = 55; break; }

        default : if(isAlpha(ch))
                  {  
                    nextState = 5;
                  }
                  else if(isNumber(ch))
                  {
                    nextState = 56;  
                    break;
                  }
                  else
                  {
                    fprintf(fout, "TK_ERR       %d           ", -1);

                    while( *current!=EOF && *current!='$' && *current!='\0' && *current!=0 )
                    {
                      fprintf(fout, "%c", *current);
                      current++;
                    }

                    fprintf(fout, "\n");
                    backTrack();
                    break;
                  }
      }

      break;
    }

    case 1:
    {
      switch(*ch)
      {
        case 'n': { nextState = 2; break; } //current recognised is "in"

        case 'f': { nextState = 3; break; } //current recognised is "if"

        default : { if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; } }
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 3:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(2); //prints "if" keyword
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
    }

    case 4: //this case prints the identifier -- > identifier recognized
    {
      backTrack();
      printIdentifier();
      nextState = 0;
      break;
    }

    case 5: //current string being read maybe an identifier
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printIdentifier();
        nextState = 0;
        break;
      }
      else if( *ch=='_' || (*ch>='0' && *ch<='9') || isAlpha(ch) )
      {
        nextState = 5; //still a part of identifier
        break;
      }

      break;
    }

    case 6:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(1); //print the keyword "int"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
    }

    case 7:
    {
      switch(*ch)
      {
        case 'l': { nextState = 8; break; }  //current = "fl"

        case 'd': { nextState = 9; break; }  //current = "fd"

        case 'a': { nextState = 10; break; } //current = "fa"

        default : { if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; } }
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 13:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(3); //print the keyword "float"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 15:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(4); //print the keyword "fdef"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 18:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(5); //print the keyword "false"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 22:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(6); //print the keyword "else"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 26:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(7); //print the keyword "char"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 30:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(8); //print the keyword "bool"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 34:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(9); //print the keyword "true"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 39:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(10); //print the keyword "true"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
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
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }  

    case 43:
    {
      if(*ch=='r') // "retur"
      {
        nextState = 44;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 44:
    {
      if(*ch=='n')  // "return"
      {
        nextState = 45;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 45:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(11); //print the keyword "return"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
    }

    case 46:
    {
      if(*ch=='o')  // "Ho"
      {
        nextState = 47;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 47:
    {
      if(*ch=='d')  // "Hod"
      {
        nextState = 48;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 48:
    {
      if(*ch=='o')  // "Hodo"
      {
        nextState = 49;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 49:
    {
      if(*ch=='r')  // "Hodor"
      {
        nextState = 50;
        break;
      }
      else
      {
        if(checkSpecialChar(ch)){ nextState = 4;backTrack(); break; } else{ nextState = 5; break; }
      }

      break;
    }

    case 50:
    {
      if(checkSpecialChar(ch))
      {
        backTrack();
        printKeyword(12); //print the keyword "Hodor"
        nextState = 0;
        break;
      }
      else
      {
        nextState = 5;
        break;
      }

      break;
    }

    case 51:
    {
      if(*ch=='=')
      {
        printToken(22);
        nextState = 0;
        break;
      }
      else
      {
        printToken(15);
        backTrack();
        nextState = 0;
        break;
      }

      break;
    }

    case 52:
    {
      if(*ch=='=')
      {
        printToken(21);
        nextState = 0;
        break;
      }
      else
      {
        printToken(16);
        backTrack();
        nextState = 0;
        break;
      }

      break;
    }

    case 53:
    {
      if(*ch=='=')
      {
        printToken(19);
        nextState = 0;
        break;
      }
      else
      {
        printToken(17);
        backTrack();
        nextState = 0;
        break;
      }

      break;
    }

    case 54:
    {
      if(*ch=='=')
      {
        printToken(20);
        nextState = 0;
        break;
      }
      else
      {
        printToken(18);
        backTrack();
        nextState = 0;
        break;
      }

      break;
    }

    case 55:
    {
      if(*(ch-1)=='"')
      {
        fprintf(fout, "TK_STRING          ");
      }

      if(*(ch)=='"')
      {
        fprintf(fout, "\n" );
        nextState = 0;
        break;
      }
      else
      {
        fprintf(fout, "%c", *ch );
        nextState = 54;
        break;
      }

      break;
    }

    case 56:
    {
      if(*ch == '.')
      {
        nextState = 57;
        break;
      }
      else if(isNumber(ch))
      {
        nextState = 56;
        break;
      }
      else
      {
        backTrack();
        nextState = 58;
        break;
      }

      break;
    }

    case 57:
    {
      if(!isNumber(ch))
      {
        backTrack();
        printFloat();
        nextState = 0;
        break;
      }
      else
      {
        nextState = 57;
        break;
      }

      break;
    }

    case 58:
    {
      backTrack();
      printInteger();
      nextState = 0;
      break;
    }


  }//switch statement for state variable ends here

  return nextState;
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

    case 12: fprintf(fout, "TK_WHOD       %d        Hodor\n", TK_WHOD); break;
  }

  f3 = 1;
}


/* print the identifiers */
void printIdentifier()
{
  fprintf(fout, "TK_ID        %d         ", TK_ID);

  printerFunc();
}


/* print integers */
void printInteger()
{
  fprintf(fout, "TK_WINT      %d       ", TK_WINT);

  printerFunc();
}


/* print floating point numbers */
void printFloat()
{
  fprintf(fout, "TK_WFLOAT    %d       ", TK_WFLOAT);

  printerFunc(); 
}


/* print the string into the file */
void printerFunc()
{
  while(start!=current)
  {
    fprintf(fout, "%c", *start);
    start++;
  }

  fprintf(fout, "%c\n", *start );

  f2 = 1;
}


/* this function prints token */
void printToken(int choice)
{
  switch(choice)
  {
    case 1: fprintf(fout, "TK_LP         {        %d\n", TK_LP); 
            break;

    case 2: fprintf(fout, "TK_RP         }        %d\n", TK_RP);
            break;

    case 3: fprintf(fout, "TK_LB         (        %d\n", TK_LB);
            break;

    case 4: fprintf(fout, "TK_RB         )        %d\n", TK_RB);
            break;

    case 5: fprintf(fout, "TK_COM        ,        %d\n", TK_COM);
            break;

    case 6: fprintf(fout, "TK_SEMICOL    ;        %d\n", TK_SEMICOL);
            break;

    case 7: fprintf(fout, "TK_PLUS       +        %d\n", TK_PLUS);
            break;

    case 8: fprintf(fout, "TK_MINUS      -        %d\n", TK_MINUS);
            break;

    case 9: fprintf(fout, "TK_MUL        *        %d\n", TK_MUL);
            break;

    case 10: fprintf(fout, "TK_DIV        /        %d\n", TK_DIV);
            break;

    case 11: fprintf(fout, "TK_LSB        [        %d\n", TK_LSB);;
            break;

    case 12: fprintf(fout, "TK_RSB        ]        %d\n", TK_RSB);
            break;

    case 13: fprintf(fout, "TK_COL        :        %d\n", TK_COL);
            break;

    case 14: fprintf(fout, "TK_DOL        $        %d\n", TK_DOL);
            break;

    case 15: fprintf(fout, "TK_EQ         =        %d\n", TK_EQ);
            break;

    case 16: fprintf(fout, "TK_NOT        !        %d\n", TK_NOT);
            break;

    case 17: fprintf(fout, "TK_GT         >        %d\n", TK_GT);
            break;

    case 18: fprintf(fout, "TK_LT         <        %d\n", TK_LT);
            break;

    case 19: fprintf(fout, "TK_GET        >=       %d\n", TK_GET);
            break;

    case 20: fprintf(fout, "TK_LET        <=       %d\n", TK_LET);
            break;

    case 21: fprintf(fout, "TK_NEQ        !=       %d\n", TK_NEQ);
            break;

    case 22: fprintf(fout, "TK_EQEQ       ==       %d\n", TK_EQEQ);
            break;
  }

  f1 = 1;
}


/* this function brings the pointer back 1 position---for backtracking */
void backTrack()
{
  current--;
}


/* find if the current character is a number */
int isNumber( char* s)
{
  if(*s >= '0' && *s <='9')
  {
    return 1;
  }

  return 0;
}


/* finds if the current character is an alphabet */
int isAlpha(char *s)
{
  if( (*s>='a' && *s<='z') || (*s>='A' && *s<='Z') )
  {
    return 1;
  }

  return 0;
}


/* check if current character is a special character or not */
int checkSpecialChar(char *s)
{
  switch(*s)
  {
    case ';':
    case '$':
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case 0:
    case '<':
    case '>':
    case ':':
    case '=':
    case ',':
    case '!':
    case '*':
    case '+':
    case '-':
    case '/':
    case '%':
    case EOF: return 1; break;
  }

  return 0;
}
