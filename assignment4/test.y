%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.c"

extern char * x;
extern int num;
FILE *fp;
int non = 0;
int type = 0;
struct node{
	char *name;
	struct node* child[100];
	struct node* parent;
	int num;
	int id;
	int type; /*int = 1, float = 2, char = 3*/
}*nodes[20000];
int len=0; int check = 0; int nameflag = 0, numflag = 0;
void recurse(struct node * temp, int);
void create_leaf(char * name1, char * name2){
	//printf("1 %s %s %d\n",name1,name2,len);
	struct node* temp1, *temp2;
	int flag = 0,i,k1,k2;
	if(len>0){
		k1=0;k2=0;
		for(i=0;i<len;i++){
			if(strcmp(nodes[i]->name,name1)==0){
				flag = 1;
				temp1 = nodes[i];
				k1 = i;
				break;
			}
		}
		for(i=0;i<len;i++){
			if(strcmp(nodes[i]->name,name2) == 0){
				if(flag == 1)
					flag = 3;
				else
					flag = 2;
				temp2 = nodes[i];
				k2 = i;
				if(k2 == k1){
					if(check == 1)
						flag = 3;
					else
						flag = 2;
				}
				break;
			}
		}
		if(check ==3)
			flag = 0;
	}
	//printf("%d\n",flag);
	if(len == 0 || flag == 0){
		//printf("1\n");
		temp1 = (struct node*)malloc(sizeof(struct node));
		temp1->name = (char*)malloc(100);
		strcpy(temp1->name,name1);
		non++;
		temp1->id = non;
		temp1->type = type;
		temp2 = (struct node*)malloc(sizeof(struct node));
		temp2->name = (char*)malloc(100);
		strcpy(temp2->name,name2);
		non++;
		temp2->id = non;
		temp2->type = type;
		temp1->parent = NULL;
		temp2->parent = temp1;
		temp1->child[temp1->num] = temp2;
		temp1->num = temp1->num + 1;
		nodes[len] =  temp1;
		len++;
	}
	else if(flag == 1){
		//printf("2\n");
		temp2 = (struct node*)malloc(sizeof(struct node));
		temp2->name = (char*)malloc(100);
		strcpy(temp2->name,name2);
		non++;
		temp2->id = non;
		temp2->type = type;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
		temp1->child[temp1->num] = temp2;
		temp1->num = temp1->num + 1;
		temp2->parent = temp1;
	}
	else if(flag == 2){
		//printf("3\n");
		temp1 = (struct node*)malloc(sizeof(struct node));
		temp1->name = (char*)malloc(100);
		strcpy(temp1->name,name1);
		non++;
		temp1->id = non;
		temp1->type = type;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
		temp1->child[temp1->num] = temp2;
		temp2->parent = temp1;
		temp1->num = temp1->num + 1;
		nodes[k2] =  temp1;
	}
	else if(flag == 3){
		//printf("4\n");
		temp1->child[temp1->num] = temp2;
		temp2-> parent = temp1;
		temp1->num = temp1->num + 1;
		for(i=k2;i<len-1;i++)
			nodes[i] = nodes[i+1];
		len--;
		if(temp2->type != temp1->type)
			printf("Error: type mismatch at %d", num);
	}
	if(nameflag == 1 || numflag == 1){
		struct node * temp3;
		temp3 = (struct node*)malloc(sizeof(struct node));
		temp3->name = (char*)malloc(100);
		strcpy(temp3->name,x);
		non++;
		temp3->id = non;
		temp3->type = type;
		temp2->child[temp2->num] = temp3;
		temp2->num = temp2->num + 1;
		temp3->parent = temp2; 
	}
}
void printtree(){
	int i; struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	for(i=0;i<len;i++){
		temp = nodes[i];
		recurse(temp,1);
	}
}
void recurse(struct node * temp, int level){
	int i;
	/*if(temp->parent != NULL)
		printf("Level %d: %s, Root ID: %d, Parent : %s, Parent ID : %d\n",level,temp->name,temp->id,temp->parent->name,temp->parent->id);
	else
		printf("Level %d: %s, Root ID: %d, Parent : NULL, Parent ID: 0\n",level,temp->name,temp->id);*/
	printf("Root ID: %d (%s) -> ",temp->id,temp->name);
	if(temp->num != 0){
		for(i=0;i<temp->num;i++)
			printf("%d, ", temp->child[i]->id);
		printf("\n");
		for(i=0;i<temp->num;i++)
			recurse(temp->child[i],level+1);
	}
	else
		printf("NULL\n");
}
%}

%token	INT BOOL TRUE FALSE VOID REAL CHAR
%token	FOR WHILE DO
%token	IF ELSE SWITCH CASE DEFAULT
%token	NUM ID SEMICOLON COM
%token	OB closedbrac OCB closedcurly COL
%token	PLUS SUB MUL DIV AND OR NEG EQ NEQ GT GE LT LE
%token	RETURN BREAK CONTINUE SCAN PRINT ASSIGN

%%
Start:	global_dec_list					{printtree();}
	;
global_dec_list: global_dec_list decl_set 		{printf("prod 2\n"); create_leaf("global_dec_list", "global_dec_list"); create_leaf("global_dec_list","decl_set"); }
	| decl_set						{printf("prod 3\n"); create_leaf("global_dec_list","decl_set"); }
	;
decl_set: function_definition				{printf("prod 4\n"); create_leaf("decl_set","function_definition");}
	| variable_decl 				{printf("prod 5\n"); create_leaf("decl_set", "variable_decl");}
	;

/* Function Definition */
function_definition: variable_dtype ID OB parameter_list CB statement_block	{printf("prod 6\n"); create_leaf("function_definition","variable_dtype"); nameflag = 1; create_leaf("function_definition","ID"); nameflag = 0; create_leaf("function_definition","OB"); create_leaf("function_definition","parameter_list"); create_leaf("function_definition","CB"); create_leaf("function_definition","statement_block");}
	;
parameter_list: parameter_list COM parameter 		{printf("prod 7\n"); create_leaf("parameter_list","parameter_list"); create_leaf("parameter_list","COM"); create_leaf("parameter_list","parameter");}
	| parameter 					{printf("prod 8\n"); create_leaf("parameter_list","parameter");}
	| 						{printf("prod 9\n");}
	;
parameter: variable_dtype ID				{printf("prod 10\n"); create_leaf("parameter","variable_dtype"); nameflag = 1; create_leaf("parameter","ID"); nameflag = 0;}
	;

/* variable Declaration */
variable_decl: variable_dtype variable_list DEL		{printf("prod 11\n"); create_leaf("variable_decl","variable_dtype"); create_leaf("variable_decl","variable_list"); create_leaf("variable_decl","DEL");}
	;
variable_list: variable_list COM variable		{printf("prod 12\n"); create_leaf("variable_list","variable_list"); create_leaf("variable_list","COM"); create_leaf("variable_list","variable");}
	| variable					{printf("prod 13\n"); create_leaf("variable_list","variable");}
	;
variable: assignment_statement 				{printf("prod 14\n"); create_leaf("variable","assignment_statement");}
	| ID						{printf("prod 15\n"); check = 3; nameflag = 1; create_leaf("variable","ID"); nameflag = 0; check = 0;}
	;
variable_dtype: INT 					{printf("prod 16\n"); check = 3; type = 1; create_leaf("variable_dtype","INT"); check = 0;}
	| BOOL						{printf("prod 17\n"); check = 3; type = 4; create_leaf("variable_dtype","BOOL"); check = 0;}
	| CHAR						{printf("prod 17\n"); check = 3; type = 3; create_leaf("variable_dtype","CHAR"); check = 0;}
	| REAL						{printf("prod 17\n"); check = 3; type = 2; create_leaf("variable_dtype","REAL"); check = 0;}
	;

/* Statememnt Definintions */
statement_block: OCB statement_list CCB			{printf("prod 18\n"); create_leaf("statement_block","OCB"); create_leaf("statement_block","statement_list"); create_leaf("statement_block","CCB");}
	;
statement_list: statement_list statement 		{printf("prod 19\n"); create_leaf("statement_list","statement_list"); create_leaf("statement_list","statement");}
	| statement						{printf("prod 20\n"); create_leaf("statement_list","statement");} 
	;
statement: assignment_statement 			{printf("prod 21\n"); create_leaf("statement","assignment_statement");}
	| conditional_statement 			{printf("prod 22\n"); create_leaf("statement","conditional_statement");}
	| loop_statement 				{printf("prod 23\n"); create_leaf("statement","loop_statement");}
	| BREAK DEL 					{printf("prod 24\n"); create_leaf("statement","BREAK");create_leaf("statement","DEL");}
	| CONTINUE DEL 					{printf("prod 25\n"); create_leaf("statement","CONTINUE");create_leaf("statement","DEL");}
	| return_statement 				{printf("prod 26\n"); create_leaf("statement","return_statement");}
	| function_call					{printf("prod 27\n"); create_leaf("statement","function_call");}
	| print_statement				{printf("prod 28\n"); create_leaf("statement","print_statement");}
	| read_statement				{printf("prod 29\n"); create_leaf("statement","read_statement");}
	| variable_decl					{printf("prod 30\n"); create_leaf("statement","variable_decl");}
	;

/* Assignment Statement */
assignment_statement: ID ASSIGN logical_expression DEL	{printf("prod 31\n"); nameflag = 1; create_leaf("assignment_statement","ID"); nameflag = 0; create_leaf("assignment_statement","ASSIGN"); create_leaf("assignment_statement","logical_expression"); create_leaf("assignment_statement","DEL");}
	;
logical_expression            : OB logical_expression OR and_expression CB	{printf("prod 32\n"); create_leaf("logical_expression","OB"); check = 1; create_leaf("logical_expression","logical_expression"); check = 0; create_leaf("logical_expression","OR"); create_leaf("logical_expression","and_expression"); create_leaf("logical_expression","CB");}
                        | and_expression 	{printf("prod 33\n"); create_leaf("logical_expression","and_expression");}
			;

and_expression                : and_expression AND unary_expression	{printf("prod 34\n"); create_leaf("and_expression","and_expression"); create_leaf("and_expression","AND"); create_leaf("and_expression","unary_expression");}
                        | unary_expression		{printf("prod 35\n"); create_leaf("and_expression","unary_expression");}
			 ;

unary_expression: NEG relational_expression			{printf("prod 36\n"); create_leaf("unary_expression", "NEG"); check = 1; create_leaf("unary_expression", "relational_expression"); check = 0;}
                        | relational_expression 	{printf("prod 37\n"); create_leaf("unary_expression", "relational_expression");}
			;

relational_expression: sum_expression GT sum_expression		{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","GT"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression LT sum_expression	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","LT"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression EQ sum_expression	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","EQ"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression GE sum_expression	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","GE"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression LE sum_expression	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","LE"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression NEQ sum_expression	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression"); create_leaf("relational_expression","NEQ"); create_leaf("relational_expression","sum_expression");}
                        | sum_expression 	{printf("prod 38\n"); create_leaf("relational_expression","sum_expression");}
			;

sum_expression: sum_expression sum_operation term	{printf("prod 39\n"); create_leaf("sum_expression","sum_expression"); create_leaf("sum_expression","sum_operation"); create_leaf("sum_expression","term");}
                        | term 	{printf("prod 40\n"); create_leaf("sum_expression","term");}
			;

sum_operation: 	PLUS 	{printf("prod 41\n"); create_leaf("sum_operation","PLUS");}
		| SUB 	{printf("prod 42\n"); create_leaf("sum_operation","SUB");}
		;

term : term mulop unary_expr {printf("prod 43\n"); create_leaf("term","term"); create_leaf("term","mulop"); create_leaf("term","unary_expr");}
	| unary_expr		{printf("prod 44\n"); create_leaf("term","unary_expr");}
	;

mulop                   : MUL 	{printf("prod 45\n"); create_leaf("mulop","MUL");}
			| DIV 	{printf("prod 46\n"); create_leaf("mulop","DIV");}
			;

unary_expr              : mulop unary_expr 	{printf("prod 47\n"); create_leaf("unary_expr","mulop"); create_leaf("unary_expr","unary_expr");}
			| factor 	{printf("prod 48\n"); create_leaf("unary_expr","factor");}
			;


factor                  : ID	{printf("prod 49\n"); check = 3; nameflag = 1; create_leaf("factor","ID"); nameflag = 0; check = 0;}
                        | OB logical_expression CB	{printf("prod 50\n"); create_leaf("factor","OB"); create_leaf("factor","logical_expression"); create_leaf("factor","CB");}
                        | NUM	{printf("prod 51\n"); numflag = 1; create_leaf("factor","NUM"); numflag = 0;}
			;

/* Conditional Statement */
conditional_statement: if_statement 			{printf("prod 58\n"); create_leaf("conditional_statement","if_statement");}
	| switch_statement				{printf("prod 59\n"); create_leaf("conditional_statement","switch_statement");}
	;
if_statement: IF OB unary_expression CB statements else_cond	{printf("prod 60\n"); create_leaf("if_statement","IF"); create_leaf("if_statement","OB"); create_leaf("if_statement","unary_expression"); create_leaf("if_statement","CB"); create_leaf("if_statement","statements"); create_leaf("if_statement","else_cond");}
	;
else_cond: ELSE statements				{printf("prod 61\n"); create_leaf("else_cond","ELSE"); create_leaf("else_cond","statements");}
	|						{printf("prod 62\n");}
	; 
statements: statement_block 				{printf("prod 63\n"); create_leaf("statements","statement_block");}
	| statement					{printf("prod 64\n"); create_leaf("statements","statement");}
	;
switch_statement: SWITCH OB unary_expression CB OCB switch_cases CCB	{printf("prod 65\n"); create_leaf("switch_statement","SWITCH");}
	;
switch_cases: switch_case 				{printf("prod 66\n"); create_leaf("switch_cases","switch_case");}
	| switch_cases switch_case			{printf("prod 67\n"); create_leaf("switch_cases","switch_cases"); create_leaf("switch_cases","switch_case");}
	;
switch_case: switch_labels statements			{printf("prod 68\n"); create_leaf("switch_case","switch_labels"); create_leaf("switch_case","statements");}
	;
switch_labels: switch_label 				{printf("prod 69\n"); create_leaf("switch_labels","switch_label");}
	| switch_labels switch_label			{printf("prod 70\n"); create_leaf("switch_labels","switch_labels"); create_leaf("switch_labels","switch_label");}
	;
switch_label: CASE NUM COL 				{printf("prod 71\n"); create_leaf("switch_label","CASE"); numflag = 1; create_leaf("switch_label","NUM"); numflag = 0; create_leaf("switch_label","COL");}
	| DEFAULT COL					{printf("prod 72\n"); create_leaf("switch_label","DEFAULT"); create_leaf("switch_label","COL");}
	;

/* Looping Statements */
loop_statement: for_loop 				{printf("prod 73\n"); create_leaf("loop_statement","for_loop");}
	| while_loop 					{printf("prod 74\n"); create_leaf("loop_statement","while_loop");}
	| do_while_loop					{printf("prod 75\n"); create_leaf("loop_statement","do_while_loop");}
	;
for_loop: FOR OB init_condition DEL term_condition DEL iterator CB statements	{printf("prod 76\n"); create_leaf("for_loop","FOR"); create_leaf("for_loop","OB"); create_leaf("for_loop","init_condition"); create_leaf("for_loop","DEL"); create_leaf("for_loop","term_condition"); create_leaf("for_loop","DEL"); create_leaf("for_loop","iterator"); create_leaf("for_loop","CB"); create_leaf("for_loop","statements");}
	;
init_condition: ID ASSIGN unary_expression init_list 	{printf("prod 77\n"); nameflag = 1; create_leaf("init_condition","ID"); nameflag = 0; create_leaf("init_condition","ASSIGN"); create_leaf("init_conditon","unary_expression"); create_leaf("init_condition","init_list");}
	| 						{printf("prod 78\n");}
	;
init_list: COM init_condition 				{printf("prod 79\n"); create_leaf("init_list","COM"); create_leaf("init_condition","init_condition");}
	| 						{printf("prod 80\n");}
	;
term_condition: unary_expression term_condition_list 	{printf("prod 81\n"); create_leaf("term_condition","unary_expression"); create_leaf("term_condition","term_condition_list");}
	| 						{printf("prod 82\n");}
	;
term_condition_list: COM term_condition 		{printf("prod 83\n"); create_leaf("term_condition_list","COM"); create_leaf("term_condition_list","term_condition");}
	| 						{printf("prod 84\n");}
	;
iterator: init_condition				{printf("prod 85\n"); create_leaf("iterator","init_condition");}
	;
while_loop: WHILE OB unary_expression CB statements	{printf("prod 86\n"); create_leaf("while_loop","WHILE"); create_leaf("while_loop","OB"); create_leaf("while_loop","unary_expression"); create_leaf("while_loop","CB"); create_leaf("while_loop","statements");}
	;
do_while_loop: DO statement_block WHILE OB unary_expression CB DEL	{printf("prod 87\n"); create_leaf("do_while_loop","DO"); create_leaf("do_while_loop","statement_block"); create_leaf("do_while_loop","WHILE"); create_leaf("do_while_loop","OB"); create_leaf("do_while_loop","unary_expression"); create_leaf("do_while_loop","CB"); create_leaf("do_while_loop","DEL");}
	;

/*Return Statement */
return_statement: RETURN return_value DEL		{printf("prod 88\n"); create_leaf("return_statement","RETURN"); create_leaf("return_statement","return_value"); create_leaf("return_statement","DEL");}
	;
return_value: unary_expression 				{printf("prod 89\n"); create_leaf("return_value","unary_expression");}
	| 						{printf("prod 90\n");}
	;

/*Function Call */
function_call: ID OB argument_list CB DEL 		{printf("prod 91\n"); nameflag = 1; create_leaf("function_call","ID"); nameflag = 0; create_leaf("function_call","OB"); create_leaf("function_call","argument_list"); create_leaf("function_call","CB"); create_leaf("function_call","DEL");}
	| assign_function_call 				{printf("prod 92\n"); create_leaf("function_call","assign_function_call");}
	;
assign_function_call: variable_dtype ID ASSIGN ID OB argument_list CB DEL	{printf("prod 93\n"); create_leaf("assign_function_call","variable_dtype"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","ASSIGN"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","OB"); create_leaf("assign_function_call","argument_list"); create_leaf("assign_function_call","CB"); create_leaf("assign_function_call","DEL");} 
	| ID ASSIGN ID OB argument_list CB DEL		{printf("prod 94\n"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0;  create_leaf("assign_function_call","ASSIGN"); nameflag = 1; create_leaf("assign_function_call","ID"); nameflag = 0; create_leaf("assign_function_call","OB"); create_leaf("assign_function_call","argument_list"); create_leaf("assign_function_call","CB"); create_leaf("assign_function_call","DEL");}
	;
argument_list: argument arg_list			{printf("prod 95\n"); create_leaf("argument_list","argument"); create_leaf("argument_list","arg_list");}	
	;
arg_list: COM argument_list 					{printf("prod 96\n"); create_leaf("arg_list","COM"); create_leaf("arg_list","argument_list");}
	|
	;
argument: ID 						{printf("prod 98\n"); check = 3; nameflag = 1; create_leaf("argument","ID"); nameflag = 0; check = 0;}
	| NUM						{printf("prod 99\n"); check = 3; numflag = 1; create_leaf("argument","NUM"); numflag = 0; check = 0;}
	;

/* Print Statement */
print_statement: PRINT unary_expression DEL		{printf("prod 100\n"); create_leaf("print_statement","PRINT"); create_leaf("print_statement","unary_expression"); create_leaf("print_statement","DEL");}
	;

/* Read Statement */
read_statement: SCAN ID DEL				{printf("prod 101\n"); create_leaf("read_statement","SCAN"); nameflag = 1; create_leaf("read_statement","ID"); nameflag = 0; create_leaf("read_statement","DEL");}
	;

/* */
DEL : SEMICOLON
	|error			{printf("1\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing semicolon in line %d\n", num); fclose(fp);}
	;
CCB : closedcurly
	|error			{printf("2\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing } in line %d\n", num); fclose(fp);}
	;
CB : closedbrac
	|error			{printf("3\n"); fp = fopen("error.txt", "a+"); fprintf(fp,"Warning: Missing ) in line %d\n", num); fclose(fp);}
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
