#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "lex.c"
#include "name.c"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );

extern char *newname( void       );
extern void freename( char *name );

char    *expression();
char    *term();
char    *factor();
char 	*statements();
char  	*relational();

int ifarray[20],whilearray[20],doarray[20];
int n = 0, ifstack = 0,whilestack=0,dostack=0;

begin()
{
	n = 0;
	char *tempvar;
	int flag = 0;
	if(match(BEGIN)){
		printf("BEGIN\nLabel Label%d:\n",n);
		advance();
		while(!match(EOI)){
			tempvar = statements();
			freename(tempvar);
			if( match( SEMI ) )
		    		advance();
			else
		    		fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );
			if(match(END)){
				flag = 1;
				printf("END\n");
				break;
			}
		}
	}
	if(flag == 0)
		fprintf( stderr, "END statement not found until end of file\n");
}


char *statements()
{
    /*  statements -> expression SEMI  |  expression SEMI statements  */

    char *tempvar;
	if(match(IF)){
		advance();
		tempvar = relational();
		n++;
		printf("IFZ %s GOTO Label%d\n",tempvar,n);
		ifarray[ifstack] = n;
		ifstack = ifstack + 1;
		freename(tempvar);
		if(match(THEN)){
			advance();
			tempvar = statements();
		}
		else{
			fprintf(stderr,"%d:No matching 'then' statement\n", yylineno);
		}
		ifstack = ifstack - 1;
		printf("Label Label%d:\n",ifarray[ifstack]);
		return tempvar;
	}
	if(match(WHILE)){
		advance();
		n++;
		printf("Label Label%d:\n",n);
		whilearray[whilestack] = n;
		whilestack = whilestack + 1;
		tempvar = relational();
		n++;
		printf("IFZ %s GOTO Label%d\n",tempvar,n);
		doarray[dostack] = n;
		dostack = dostack + 1;
		freename(tempvar);
		if(match(DO)){
			advance();
			tempvar = statements();
			whilestack = whilestack - 1;
			printf("GOTO Label%d\n",whilearray[whilestack]);
		}
		else{
			fprintf( stderr, "%d:No matching 'do' statement\n", yylineno);
		}
		dostack = dostack - 1;
		printf("Label Label%d:\n",doarray[dostack]);
		return tempvar;
	}
	if( match(NUM_OR_ID)){
		char temp[yyleng];
		memcpy(temp,yytext,yyleng);
		temp[yyleng] = '\0'; 
		advance();
		if(match(EQ)){
		advance();
		tempvar = statements();
		printf("    %s = %s\n",temp,tempvar);
		}
		else{
		  previous();
		  tempvar = relational();
		}
		return tempvar;
	}
}

char  	*relational()
{
	char * tempvar, *tempvar2;
	int flag;
	tempvar = expression();
	while(match(EQQ)||match(LT)||match(GT))
	{
		if(match(EQQ))
			flag = 0;
		else if(match(LT))
			flag = 1;
		else
			flag = 2;
		advance();
		tempvar2 = expression();
		if(flag == 0)
			printf("    %s = %s == %s\n", tempvar,tempvar, tempvar2 );
		else if(flag == 1)
			printf("    %s = %s < %s\n", tempvar, tempvar, tempvar2 );
		else
			printf("    %s = %s > %s\n",tempvar, tempvar, tempvar2 );
		freename(tempvar2);
	}
	return tempvar;
}

char    *expression()
{
    /* expression -> term expression'
     * expression' -> PLUS term expression' |  epsilon
     */

    char  *tempvar, *tempvar2;
    int flag;

    tempvar = term();
    while( match( PLUS ) || match (MINUS) )
    {
	if(match(PLUS))
        	flag = 1;
	else
		flag = 0;
        advance();
        tempvar2 = term();
	if(flag == 1)
        	printf("    %s += %s\n", tempvar, tempvar2 );
	else
		printf("    %s -= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *term()
{
    char  *tempvar, *tempvar2 ;
    int flag;

    tempvar = factor();
    while( match( TIMES ) || match(DIV))
    {
	if(match(TIMES))
		flag = 1;
	else
		flag = 0;
        advance();
        tempvar2 = factor();
	if(flag == 1)
        	printf("    %s *= %s\n", tempvar, tempvar2 );
	else
		printf("    %s /= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *factor()
{
    char *tempvar;

    if( match(NUM_OR_ID) )
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */

        printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();
    }
    else if( match(LP) )
    {
        advance();
        tempvar = relational();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
	fprintf( stderr, "%d: Number or identifier expected\n", yylineno );

    return tempvar;
}
