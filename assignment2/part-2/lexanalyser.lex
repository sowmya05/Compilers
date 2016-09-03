/* Lexical analyser for a sample c like language. */
%option noyywrap

%Start	BL_CMNT

DIGIT	[0-9]
LETTER	[a-zA-Z]
LETTER_	[a-zA-Z_]
ID 	{LETTER_}({LETTER_}|{DIGIT})*
MATH_EXP	"+"|"*"|"-"|"/"
UNARY	"++"|"--"|"!"
RELATIONAL	"=="|"!="|"<"|">"|"<="|">="
ASSIGN	"="
DT	"int"|"bool"
CONDITIONAL	"if"|"else"|"else if"|"switch"|"case"|"default"
LOOP	"do"|"while"|"for"
BRACKET	"{"|"}"|"("|")"|"["|"]"
IO	"scan"|"print"
DELIMITER ";"
BOOL "TRUE"|"FALSE"
NUMBER {DIGIT}+
KEYWORD "void"|"RETURN"|"BREAK"|"CONTINUE"
COMMA	","

%%
<INITIAL>"/*"	{BEGIN BL_CMNT;}
<BL_CMNT>"*/"	{BEGIN 0;}
<BL_CMNT>.	/* eat up the block comment characters */
<BL_CMNT>\n	/* eat up lines in block comments */
<INITIAL>"*/"	printf("Unmatched end of comment\n");
<INITIAL>{MATH_EXP}	{printf("<MATH_OPERATOR,'%s'>\n",yytext);}
<INITIAL>{UNARY}	{printf("<UNARY_OPERATOR,'%s'>\n",yytext);}
<INITIAL>{RELATIONAL}	{printf("<RELATIONAL_OPERATOR,'%s'>\n",yytext);}
<INITIAL>{ASSIGN}	{printf("<ASSIGN_OPERATOR,'%s'>\n",yytext);}
<INITIAL>{DT}	{printf("<DATATYPE,'%s'>\n",yytext);}
<INITIAL>{CONDITIONAL}	{printf("<CONDITIONAL,'%s'>\n",yytext);}
<INITIAL>{LOOP}	{printf("<LOOP,'%s'>\n",yytext);}
<INITIAL>{BRACKET}	{printf("<BRACKET,'%s'>\n",yytext);}
<INITIAL>{IO}	{printf("<IO,'%s'>\n",yytext);}
<INITIAL>{DELIMITER}	{printf("<DELIMITER,'%s'>\n",yytext);}
<INITIAL>{BOOL}	{printf("<BOOL,'%s'>\n",yytext);}
<INITIAL>{KEYWORD}	{printf("<KEYWORD,'%s'>\n",yytext);}
<INITIAL>{ID}	{printf("<IDENTIFER,'%s'>\n",yytext);}
<INITIAL>{NUMBER}	{printf("<CONSTANT,'%s'>\n",yytext);}
<INITIAL>{COMMA}	{printf("<COMMA,'%s'>\n",yytext);}
<INITIAL>"//"[^\n]*	/* eat up one line comments	*/
<INITIAL>[ \t\n]+	/* eat up white spaces */
<INITIAL>.	printf("Invalid characters: %s\n",yytext);	/* All other erroneous characters */
%%


