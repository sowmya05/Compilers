#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */
char* prev = "";
char        *current;

int lex(void){

   static char input_buffer[1024];
  
   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;
	   case '=':
		if(*(++current) == '='){
			yyleng = 2;
			return EQQ; 
			}
	    return EQ;
	   case '<':
		if(*(current+1) == '=')
			return LTE; 
	    return LT;
	   case '>':
		if(*(current+1) == '=')
			return GTE; 
	    return GT;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               fprintf(stderr, "Not alphanumeric <%c>\n", *current);
            else{
		int i = 0;
               while(isalnum(*current))
		{
                  ++current;
		}
		yyleng = current - yytext;
		char str[yyleng];
		memcpy(str,yytext,yyleng);
		str[yyleng] = '\0';
		if(strcmp(str,"if")==0)
			return IF;
		if(strcmp(str,"while")==0)
			return WHILE;
		if(strcmp(str,"then")==0)
			return THEN;
		if(strcmp(str,"do")==0)
			return DO;
		if(strcmp(str,"begin")==0)
			return BEGIN;
		if(strcmp(str,"end")==0)
			return END;		
               return NUM_OR_ID;
            }
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */
	
   if(Lookahead == -1)
	{
	 prev = yytext;
   current = yytext + yyleng; /* Skip current
                                 lexeme        */
      Lookahead = lex();
	}

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */
	 prev = yytext;
   current = yytext + yyleng; /* Skip current
                                 lexeme        */

    Lookahead = lex();
}

void previous(void){
	current = prev;
	Lookahead = lex();
}
