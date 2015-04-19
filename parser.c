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

void fileInitialize();         		//initialize input and output files
void mapping();
void parsing();

FILE *fin, *fout;

char line[300];
char token[300];
int stack[1000];
int top, row, column, val;
int inputProceed = 1;

enum rulesTokens
{
  program, body, construct, statement, varDec, varList, dataType, assignment, loop, rep, 
  whileCond, condition, elseCond, condExpr, relation, expr, expr1, term, term1, factor, literal,
  TK_VM, TK_WFDEF, TK_ID, TK_COL, TK_LP, TK_RP, TK_VD, TK_SEMICOL, TK_COM, 
  TK_WINT, TK_WFLOAT, TK_BOOL, TK_EQ, TK_WHOD, TK_LB, TK_RB, TK_WHILE, 
  TK_WIF, TK_WELSE, TK_EQEQ, TK_NEQ, TK_GT, TK_LT, TK_GET, TK_LET, 
  TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_WTRUE, TK_WFLS, $

} rt;

int parseTable[21][33] = 
	{{0,1,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,46},
	{0,47,47,2,47,47,3,47,47,47,2,2,2,47,2,47,47,2,2,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,4,47,47,46,47,47,47,4,4,4,47,5,47,47,5,6,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,8,47,47,46,47,47,47,7,7,7,47,46,47,47,46,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,46,47,47,47,9,9,9,47,46,47,47,46,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,47,47,47,47,47,11,10,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,47,47,47,47,12,13,14,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,15,47,47,46,47,47,47,46,46,46,47,46,47,47,46,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,46,47,47,47,46,46,46,47,16,47,47,17,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,46,47,47,47,46,46,46,47,18,47,47,46,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,46,47,47,47,46,46,46,47,46,47,47,19,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,46,47,47,46,47,47,47,46,46,46,47,46,47,47,46,20,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,22,47,47,22,47,47,47,22,22,22,47,22,47,47,22,22,21,47,47,47,47,47,47,47,47,47,47,47,47,47},
	{0,47,47,23,47,47,47,47,47,47,23,23,47,47,47,23,46,47,47,47,47,47,47,47,47,47,47,23,47,47,23,23,47},
	{0,47,47,46,47,47,47,47,47,47,46,46,47,47,47,46,47,47,47,47,24,25,26,27,28,29,47,46,47,47,46,46,47},
	{0,47,47,30,47,47,47,47,46,47,30,30,47,47,47,30,46,47,47,47,46,46,46,46,46,46,47,30,47,47,30,30,47},
	{0,47,47,47,47,47,47,47,33,47,47,47,47,47,47,47,33,47,47,47,33,33,33,33,33,33,31,32,47,47,47,47,47},
	{0,47,47,34,47,47,47,47,46,47,34,34,47,47,47,34,46,47,47,47,46,46,46,46,46,46,46,34,47,47,34,34,47},
	{0,47,47,47,47,47,47,47,37,47,47,47,47,47,47,47,37,47,47,47,37,37,37,37,37,37,37,37,35,36,47,47,47},
	{0,47,47,38,47,47,47,47,46,47,39,39,47,47,47,40,46,47,47,47,46,46,46,46,46,46,46,41,46,46,39,39,47},
	{0,47,47,47,47,47,47,47,46,47,42,43,47,47,47,47,46,47,47,47,46,46,46,46,46,46,46,46,46,46,44,45,47}};


int main()
{
  
  fileInitialize();
  int lineNo = 0;

  stack[top] = program;

  while ( fgets(line, 300, fin) != NULL && inputProceed)
  {
  	
  	if (lineNo > 1)
  	{
  		int i=0;

  		while (line[i] != ' ')
  			i++;

  		strncpy(token, line, i);
  		token[i] = '\0';

  		fprintf(fout, "%s\n", token);
  		
  		inputProceed = 0;

  		mapping();
  		parsing();

  	}

  	lineNo++; 
  	// printf("%d\n", lineNo);

  }

  if (strcmp(token,"TK_VD"))
  	fprintf(fout, "\nERROR\n");

  else
  	fprintf(fout, "\nDONE\n");

  fcloseall();      				//close all- file pointers

  return 0;

}

void parsing()
{
	while (! inputProceed)
	{
		row = stack[top];
		//printf("%d %d\n", row, val);

		if (row == val)
		{
			top--;
			inputProceed = 1;
			//printf("Pop\n");
		}

		else
		{

			int operation = parseTable[row][column];

			switch (operation)
			{
				case 1:

					stack[top] = TK_VD; top++;
					stack[top] = TK_RP; top++;
					stack[top] = body; top++;
					stack[top] = TK_LP; top++;
					stack[top] = TK_COL; top++;
					stack[top] = TK_ID; top++;
					stack[top] = TK_WFDEF; top++;
					stack[top] = TK_VM;

					fprintf(fout,"program → TK_VM TK_WFDEF TK_ID TK_COL TK_LP body TK_RP TK_VD\n\n");

					break;

				 case 2:

				 	stack[top] = body; top++;
				 	stack[top] = construct;

				 	fprintf(fout, "body → construct body\n\n");

				 	break;

				 case 3:

				 	top--;

				 	fprintf(fout, "body → ε\n\n");

				 	break;

				 case 4:

				 	stack[top] = statement;

				 	fprintf(fout, "construct → statement\n\n");

				 	break;

				 case 5:

				 	stack[top] = loop;

				 	fprintf(fout, "construct → loop\n\n");

				 	break;

				 case 6:

				 	stack[top] = condition;

				 	fprintf(fout, "construct → condition\n\n");

				 	break;

				 case 7:

				 	stack[top] = varDec;

				 	fprintf(fout, "statement → varDec\n\n");

				 	break;

				 case 8:

				 	stack[top] = assignment;

				 	fprintf(fout, "statement → assignment\n\n");

				 	break;

				 case 9:

				 	stack[top] = TK_SEMICOL; top++;
				 	stack[top] = varList; top++;
				 	stack[top] = TK_ID; top++;
				 	stack[top] = dataType;

				 	fprintf(fout, "varDec → dataType TK_ID varList TK_SEMICOL\n\n");

				 	break;

				 case 10:

				 	stack[top] = varList; top++;
				 	stack[top] = TK_ID; top++;
				 	stack[top] = TK_COM;

				 	fprintf(fout, "varList → TK_COM TK_ID varList\n\n");

				 	break;

				 case 11:

				 	top--;

				 	fprintf(fout, "varList → ε\n\n");

				 	break;

				 case 12:

				 	stack[top] = TK_WINT;

				 	fprintf(fout, "dataType → TK_WINT\n\n");

				 	break;

				 case 13:

				 	stack[top] = TK_WFLOAT;

				 	fprintf(fout, "dataType → TK_WFLOAT\n\n");

				 	break;

				 case 14:

				 	stack[top] = TK_BOOL;

				 	fprintf(fout, "dataType → TK_BOOL\n\n");

				 	break;

				 case 15:

				 	stack[top] = TK_SEMICOL; top++;
				 	stack[top] = expr; top++;
				 	stack[top] = TK_EQ; top++;
				 	stack[top] = TK_ID;

				 	fprintf(fout, "assignment → TK_ID TK_EQ expr TK_SEMICOL\n\n");

				 	break;

				 case 16:

				 	stack[top] = rep;

				 	fprintf(fout, "loop → rep\n\n");

				 	break;

				 case 17:

				 	stack[top] = whileCond;

				 	fprintf(fout, "loop → whileCond\n\n");

				 	break;

				 case 18:

				 	stack[top] = TK_RP; top++;
				 	stack[top] = body; top++;
				 	stack[top] = TK_LP; top++;
				 	stack[top] = TK_RB; top++;
				 	stack[top] = TK_WINT; top++;
				 	stack[top] = TK_COM; top++;
				 	stack[top] = TK_WINT; top++;
				 	stack[top] = TK_COM; top++;
				 	stack[top] = TK_ID; top++;
				 	stack[top] = TK_LB; top++;
				 	stack[top] = TK_WHOD;

				 	fprintf(fout, "rep → TK_WHOD TK_LB TK_ID TK_COM TK_WINT TK_COM TK_WINT TK_RB TK_LP body TK_RP\n\n");

				 	break;

				 case 19:

				 	stack[top] = TK_RP; top++;
				 	stack[top] = body; top++;
				 	stack[top] = TK_LP; top++;
				 	stack[top] = TK_RB; top++;
				 	stack[top] = condExpr; top++;
				 	stack[top] = TK_LB; top++;
				 	stack[top] = TK_WHILE;

				 	fprintf(fout, "whileCond → TK_WHILE TK_LB condExpr TK_RB TK_LP body TK_RP\n\n");

				 	break;

				 case 20:

				 	stack[top] = elseCond; top++;
				 	stack[top] = TK_RP; top++;
				 	stack[top] = body; top++;
				 	stack[top] = TK_LP; top++;
				 	stack[top] = TK_RB; top++;
				 	stack[top] = condExpr; top++;
				 	stack[top] = TK_LB; top++;
				 	stack[top] = TK_WIF;

				 	fprintf(fout, "condition → TK_WIF TK_LB condExpr TK_RB TK_LP body TK_RP elseCond\n\n");

				 	break;

				 case 21:

				 	stack[top] = TK_RP; top++;
				 	stack[top] = body; top++;
				 	stack[top] = TK_LP; top++;
				 	stack[top] = TK_WELSE;

				 	fprintf(fout, "elseCond → TK_WELSE TK_LP body TK_RP\n\n");

				 	break;

				 case 22:

				 	top--;

				 	fprintf(fout, "elseCond → ε\n\n");

				 	break;

				 case 23:

				 	stack[top] = expr; top++;
				 	stack[top] = relation; top++;
				 	stack[top] = expr;

				 	fprintf(fout, "condExpr → expr relation expr\n\n");

				 	break;

				 case 24:

				 	stack[top] = TK_EQEQ;

				 	fprintf(fout, "relation → TK_EQEQ\n\n");

				 	break;

				 case 25:

				 	stack[top] = TK_NEQ;

				 	fprintf(fout, "relation → TK_NEQ\n\n");

				 	break;

				 case 26:

				 	stack[top] = TK_GT;

				 	fprintf(fout, "relation → TK_GT\n\n");

				 	break;

				 case 27:

				 	stack[top] = TK_LT;

				 	fprintf(fout, "relation → TK_LT\n\n");

				 	break;

				 case 28:

				 	stack[top] = TK_GET;

				 	fprintf(fout, "relation → TK_GET\n\n");

				 	break;

				 case 29:

				 	stack[top] = TK_LET;

				 	fprintf(fout, "relation → TK_LET\n\n");

				 	break;

				 case 30:

				 	stack[top] = expr1; top++;
				 	stack[top] = term;

				 	fprintf(fout, "expr → term expr1\n\n");

				 	break;

				 case 31:

				 	stack[top] = expr; top++;
				 	stack[top] = TK_PLUS;

				 	fprintf(fout, "expr1 → TK_PLUS expr\n\n");

				 	break;

				 case 32:

				 	stack[top] = expr; top++;
				 	stack[top] = TK_MINUS;

				 	fprintf(fout, "expr1 → TK_MINUS expr\n\n");

				 	break;

				 case 33:

				 	top--;

				 	fprintf(fout, "expr1 → ε\n\n");

				 	break;

				 case 34:

				 	stack[top] = term1; top++;
				 	stack[top] = factor;

				 	fprintf(fout, "term → factor term1\n\n");

				 	break;

				 case 35:

				 	stack[top] = term; top++;
				 	stack[top] = TK_MUL;

				 	fprintf(fout, "term1 → TK_MUL term\n\n");

				 	break;

				 case 36:

				 	stack[top] = term; top++;
				 	stack[top] = TK_DIV;

				 	fprintf(fout, "term1 → TK_DIV term\n\n");

				 	break;

				 case 37:

				 	top--;

				 	fprintf(fout, "term1 → ε\n\n");

				 	break;

				 case 38:

				 	stack[top] = TK_ID;

				 	fprintf(fout, "factor → TK_ID\n\n");

				 	break;

				 case 39:

				 	stack[top] = literal;

				 	fprintf(fout, "factor → literal\n\n");

				 	break;

				 case 40:

				 	stack[top] = TK_RB; top++;
				 	stack[top] = expr; top++;
				 	stack[top] = TK_LB;

				 	fprintf(fout, "factor → TK_LB expr TK_RB\n\n");

				 	break;

				 case 41:

				 	stack[top] = factor; top++;
				 	stack[top] = TK_MINUS;

				 	fprintf(fout, "factor → TK_MINUS factor\n\n");

				 	break;

				 case 42:

				 	stack[top] = TK_WINT;

				 	fprintf(fout, "literal → TK_WINT\n\n");

				 	break;

				 case 43:

				 	stack[top] = TK_WFLOAT;

				 	fprintf(fout, "literal → TK_WFLOAT\n\n");

				 	break;

				 case 44:

				 	stack[top] = TK_WTRUE;

				 	fprintf(fout, "literal → TK_WTRUE\n\n");

				 	break;

				 case 45:

				 	stack[top] = TK_EQ; top++;
				 	stack[top] = TK_WFLS;

				 	fprintf(fout, "literal → TK_WFLS\n\n");

				 	break;

				 case 46:

				 	fprintf(fout, "\nERROR\n");
				 	exit(0);

				 	break;

				 case 47:

				 	fprintf(fout, "\nERROR\n");
				 	exit(0);

				 	break;

				 default:
				 	fprintf(fout, "\nERROR\n");
				 	exit(0);

			}
		}
	}
}

void mapping()
{
	//printf("%s\n",token);

	if (strcmp(token,"TK_VM") == 0)
	{
		column = 1;
		val = 21;
	}

	else if (strcmp(token,"TK_WFDEF") == 0)
	{
		column = 2;
		val = 22;
	}

	else if (strcmp(token,"TK_ID") == 0)
	{
		column = 3;
		val = 23;
	}

	else if (strcmp(token,"TK_COL") == 0)
	{
		column = 4;
		val = 24;
	}

	else if (strcmp(token,"TK_LP") == 0)
	{
		column = 5;
		val = 25;
	}

	else if (strcmp(token,"TK_RP") == 0)
	{
		column = 6;
		val = 26;
	}

	else if (strcmp(token,"TK_VD") == 0)
	{
		column = 7;
		val = 27;
	}

	else if (strcmp(token,"TK_SEMICOL") == 0)
	{
		column = 8;
		val = 28;
	}

	else if (strcmp(token,"TK_COM") == 0)
	{
		column = 9;
		val = 29;
	}

	else if (strcmp(token,"TK_WINT") == 0)
	{
		column = 10;
		val = 30;
	}

	else if (strcmp(token,"TK_WFLOAT") == 0)
	{
		column = 11;
		val = 31;
	}

	else if (strcmp(token,"TK_BOOL") == 0)
	{
		column = 12;
		val = 32;
	}

	else if (strcmp(token,"TK_EQ") == 0)
	{
		column = 13;
		val = 33;
	}

	else if (strcmp(token,"TK_WHOD") == 0)
	{
		column = 14;
		val = 34;
	}

	else if (strcmp(token,"TK_LB") == 0)
	{
		column = 15;
		val = 35;
	}

	else if (strcmp(token,"TK_RB") == 0)
	{
		column = 16;
		val = 36;
	}

	else if (strcmp(token,"TK_WHILE") == 0)
	{
		column = 17;
		val = 37;
	}

	else if (strcmp(token,"TK_WIF") == 0)
	{
		column = 18;
		val = 38;
	}

	else if (strcmp(token,"TK_WELSE") == 0)
	{
		column = 19;
		val = 39;
	}

	else if (strcmp(token,"TK_EQEQ") == 0)
	{
		column = 20;
		val = 40;
	}

	else if (strcmp(token,"TK_NEQ") == 0)
	{
		column = 21;
		val = 41;
	}

	else if (strcmp(token,"TK_GT") == 0)
	{
		column = 22;
		val = 42;
	}

	else if (strcmp(token,"TK_LT") == 0)
	{
		column = 23;
		val = 43;
	}

	else if (strcmp(token,"TK_GET") == 0)
	{
		column = 24;
		val = 44;
	}

	else if (strcmp(token,"TK_LET") == 0)
	{
		column = 25;
		val = 45;
	}

	else if (strcmp(token,"TK_PLUS") == 0)
	{
		column = 26;
		val = 46;
	}

	else if (strcmp(token,"TK_MINUS") == 0)
	{
		column = 27;
		val = 47;
	}

	else if (strcmp(token,"TK_MUL") == 0)
	{
		column = 28;
		val = 48;
	}

	else if (strcmp(token,"TK_DIV") == 0)
	{
		column = 29;
		val = 49;
	}

	else if (strcmp(token,"TK_WTRUE") == 0)
	{
		column = 30;
		val = 50;
	}

	else if (strcmp(token,"TK_WFLS") == 0)
	{
		column = 31;
		val = 51;
	}

	else if (strcmp(token,"$") == 0)
	{
		column = 32;
		val = 52;
	}

	else
	{
		printf("Unrecognized Token\n");
	}

}

void fileInitialize()
{
  fin = fopen("lexerOutput.txt", "r");
  fout = fopen("parserOutput.txt", "w");

  if(fin==NULL || fout==NULL)
  {
    printf("File Initialization ERROR\n");
  }
}