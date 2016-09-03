/* Lexical analyser for a sample c like language. */
%{
	#include<string.h>
	#include "test.c"
	extern char * x;
	extern int num;
%}
%option noyywrap

%Start	BL_CMNT

DIGIT	[0-9]
LETTER	[a-zA-Z]
LETTER_	[a-zA-Z_]
ID 	{LETTER_}({LETTER_}|{DIGIT})*
MATH_EXP	"+"|"*"|"-"|"/"
UNARY	"++"|"--"
LOGICAL	"!"
RELATIONAL	"=="|"!="|"<"|">"|"<="|">="
ASSIGN	"="
DT	"int"|"bool"
CONDITIONAL	"if"|"else"|"switch"|"case"|"default"
LOOP	"do"|"while"|"for"
BRACKET	"{"|"}"|"("|")"|"["|"]"
IO	"scan"|"print"
DELIMITER ";"
BOOL "TRUE"|"FALSE"
NUMBER {DIGIT}+
KEYWORD "void"|"return"|"break"|"continue"
COMMA	","

%%
<INITIAL>"/*"	{BEGIN BL_CMNT;}
<BL_CMNT>"*/"	{BEGIN 0;}
<BL_CMNT>.	/* eat up the block comment characters */
<BL_CMNT>\n	/* eat up lines in block comments */
<INITIAL>"*/"	printf("Unmatched end of comment\n");
<INITIAL>"+"	{printf("<MATH_OP,'%s'>\n",yytext); return PLUS; }
<INITIAL>"-"	{printf("<MATH_OP,'%s'>\n",yytext); return SUB; }
<INITIAL>"*"	{printf("<MATH_OP,'%s'>\n",yytext); return MUL; }
<INITIAL>"/"	{printf("<MATH_OP,'%s'>\n",yytext); return DIV; }
<INITIAL>"&&"	{printf("<UNARY,'%s'>\n",yytext); return AND; }
<INITIAL>"||"	{printf("<UNARY,'%s'>\n",yytext); return OR; }
<INITIAL>{LOGICAL}	{printf("<LOGICAL_OPERATOR,'%s'>\n",yytext); return NEG;}
<INITIAL>"=="	{printf("<RELATIONAL,'%s'>\n",yytext); return EQ; }
<INITIAL>"!="	{printf("<RELATIONAL,'%s'>\n",yytext); return NEQ; }
<INITIAL>"<"	{printf("<RELATIONAL,'%s'>\n",yytext); return LT; }
<INITIAL>"<="	{printf("<RELATIONAL,'%s'>\n",yytext); return LE; }
<INITIAL>">"	{printf("<RELATIONAL,'%s'>\n",yytext); return GT; }
<INITIAL>">="	{printf("<RELATIONAL,'%s'>\n",yytext); return GE; }
<INITIAL>{ASSIGN}	{printf("<ASSIGN_OPERATOR,'%s'>\n",yytext); return ASSIGN;}
<INITIAL>"int"	{printf("<DATATYPE,'%s'>\n",yytext); return INT; } 
<INITIAL>"bool"	{printf("<DATATYPE,'%s'>\n",yytext); return BOOL; }
<INITIAL>"if"	{printf("<CONDITIONAL,'%s'>\n",yytext); return IF; }
<INITIAL>"else"	{printf("<CONDITIONAL,'%s'>\n",yytext); return ELSE; }
<INITIAL>"switch"	{printf("<CONDITIONAL,'%s'>\n",yytext); return SWITCH; }
<INITIAL>"case"	{printf("<CONDITIONAL,'%s'>\n",yytext); return CASE; }
<INITIAL>"default"	{printf("<CONDITIONAL,'%s'>\n",yytext); return DEFAULT; }
<INITIAL>"do"	{printf("<LOOP,'%s'>\n",yytext); return DO; }
<INITIAL>"while"	{printf("<LOOP,'%s'>\n",yytext); return WHILE; }
<INITIAL>"for"	{printf("<LOOP,'%s'>\n",yytext); return FOR; }
<INITIAL>"("	{printf("<OPEN BRACKET,'%s'>\n",yytext); return OB; }
<INITIAL>")"	{printf("<CLOSED BRACKET,'%s'>\n",yytext); return closedbrac; }
<INITIAL>"{"	{printf("<OPEN BRACES,'%s'>\n",yytext); return OCB; }
<INITIAL>"}"	{printf("<CLOSED BRACES,'%s'>\n",yytext); return closedcurly; }
<INITIAL>":"	{printf("<COLON,'%s'>\n",yytext); return COL; }
<INITIAL>"print"	{printf("<IO,'%s'>\n",yytext); return PRINT; }
<INITIAL>"scan"	{printf("<IO,'%s'>\n",yytext); return SCAN; }
<INITIAL>{DELIMITER}	{printf("<DELIMITER,'%s'>\n",yytext); return SEMICOLON;}
<INITIAL>"true"	{printf("<BOOLEAN,'%s'>\n",yytext); return TRUE; }
<INITIAL>"false"	{printf("<BOOLEAN,'%s'>\n",yytext); return FALSE; }
<INITIAL>"void"	{printf("<KEYWORD,'%s'>\n",yytext); return VOID; }
<INITIAL>"return"	{printf("<KEYWORD,'%s'>\n",yytext); return RETURN; }
<INITIAL>"break"	{printf("<KEYWORD,'%s'>\n",yytext); return BREAK; }
<INITIAL>"continue"	{printf("<KEYWORD,'%s'>\n",yytext); return CONTINUE; }
<INITIAL>"\n"	{num = num + 1;}
<INITIAL>{ID}	{printf("<IDENTIFER,'%s'>\n",yytext); x = (char*)malloc(100); strcpy(x,yytext); return ID;}
<INITIAL>{NUMBER}	{printf("<CONSTANT,'%s'>\n",yytext); x = (char*)malloc(100); strcpy(x,yytext); return NUM;}
<INITIAL>{COMMA}	{printf("<COMMA,'%s'>\n",yytext); return COM;}
<INITIAL>"//"[^\n]*	/* eat up one line comments	*/
<INITIAL>[ \t\n]+	/* eat up white spaces */
<INITIAL>.	{printf("Invalid characters: %s\n",yytext);}	/* All other erroneous characters */
%%
