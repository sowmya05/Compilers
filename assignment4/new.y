%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.c"
#include <bits/stdc++.h>
using namespace std;
extern char * x;
extern int num;
FILE *fp;
int non = 0;
int type = 0;
typedef struct nodes{
	int l;
        string type;
        vector<int> lid;
	int val;
	char* values;
	int args;
	struct nodes **list;
} node;

int scope=0;


node* createleaf(char* x, int num, ... ) {
	va_list ap;
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->values = strdup(x);
	int i;
	temp->args = num;
	temp->list = (node**)malloc(num*sizeof(node*));
	va_start(ap, num);
	for (i = 0; i < num; i++) {
		(*temp).list[i] = va_arg(ap, node*);
	}
	va_end(ap);
	return temp;
	
}

void traverse(node* x) {
       if(x->values){
	queue<node*> q;
	x->l=0;
	q.push(x);
	node* temp;
	int i;
	while(!q.empty()) {
		temp = q.front();
		q.pop();
		printf("\n%d %s -> ",temp->l, temp->values);
		for (i = 0; i < temp->args; i++)
		{
			printf(" %s", (*temp).list[i]->values);
			(*temp).list[i]->l = (temp->l) + 1;
			if((*temp).list[i]->args > 0) q.push((*temp).list[i]);
		}
	}
     }
}
%}

%union {
	int numvalue;
	char *varname;
	struct nodes *treenode;
       };


%token	INT BOOL TRUE FALSE VOID REAL CHAR
%token	FOR WHILE DO
%token	IF ELSE SWITCH CASE DEFAULT
%token	NUM ID SEMICOLON COM
%token	OB closedbrac OCB closedcurly COL
%token	PLUS SUB MUL DIV AND OR NEG EQ NEQ GT GE LT LE
%token	RETURN BREAK CONTINUE SCAN PRINT ASSIGN

%%
Start			:	global_dec_list
			;
global_decl_list	:	global_dec_list decl_set		{ traverse($2);}
			|	decl_set				{ traverse($1);}
			;
decl_set		:	variable_declaration
			;
variable_declaration	:	variable_dtype variable_list DEL
			;
variable_list		:	variable_list COM variable
			|	variable
			;
variable		:	assignment_statement
			|	ID
			;
variable_dtype		:	INT
			|	BOOL
			|	FLOAT
			|	CHAR
			|	VOID
			;

%%
#include"lex.yy.c"
#include<ctype.h>
int count=0;

int main(int argc, char *argv[])
{
	fp = fopen("error.txt","w");
	fclose(fp);
	yyin = fopen(argv[1], "r");
	
   if(!yyparse())
		printf("\nParsing complete\n");
	else
		printf("\nParsing failed\n");
	
	fclose(yyin);
    return 0;
}
         
yyerror(char *s) {
	//fp = fopen("error.txt", "a+"); fprintf(fp,"%d : %s %s\n", num + 1, s, yytext ); fclose(fp);
}
