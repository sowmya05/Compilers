#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM_OR_ID	6	/* Decimal Number or Identifier */
#define MINUS		7	/* -				*/
#define DIV		8	/* /				*/
#define EQ		9	/* =				*/
#define LT		10	/* <				*/
#define GT		11	/* >				*/
#define IF		12	/* if				*/
#define WHILE		13	/* while			*/
#define THEN		14	/* then				*/
#define DO		15	/* do				*/
#define	BEGIN		16	/* begin			*/
#define END		17	/* end				*/
#define EQQ		18	/* equality			*/
#define LTE		19	/* less than or equal to	*/
#define GTE		20	/* greater than or equal to	*/

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
extern char * prev;
