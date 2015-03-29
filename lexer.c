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


//function declarations
void fileInitialize(); //initialize input and output files


int main(int argc, char const *argv[])
{
  fileInitialize();

  fprintf(fout, "TYPE                   LEXEME\n", );
  fprintf(fout, "-----------------------------\n", );

  while( (fscanf(fin, "%s", input))!=EOF )
  {
    ch = input;
  }







  return 0;
}


void fileInitialize()
{
  fin = fopen("input.txt", "r");
  fout = fopen("output.txt", "w");

  if(fin==NULL || fout==NULL)
  {
    printf("file initialization error\n");
  }
}