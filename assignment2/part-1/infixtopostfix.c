#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_length 50

char expr[max_length], alphabet[max_length], postfix[max_length];
int length,i,alphanum=0,j,flag,start_state=0,final_state=0,current_state=0;

struct nfa{
	int state[max_length];
	int eps[max_length];
	int len;		
}NFA[5*max_length];

// --- define stack --- //
char stack[max_length];
int top=0;
void push(int val)
{
	stack[++top]=val;
}

char pop()
{
	return stack[top--];
}
// -------------------- //

void get_alphabets();
void get_postfix();
int get_precedence(char);
void get_nfa();


int main()
{
printf("Enter Regular expression: ");
scanf("%s",expr);
get_alphabets();
get_postfix();
}

void get_alphabets(){
length = strlen(expr);
for(i=0;i<length;i++){
	push(expr[i]);
	if(expr[i] != '*' && expr[i] != '+' && expr[i] != '(' && expr[i] != ')' && expr[i] != ' ' && expr[i] != '.'){
		flag = 0;
		if(alphanum == 0){
			alphabet[0] = expr[i];
			alphanum++;
		}
		else{
			for(j=0;j<alphanum;j++){
				if(alphabet[j] == expr[i])
					flag = 1;
			}
			if(flag == 0){
				alphabet[alphanum] = expr[i];
				alphanum++;
			}
		}
	}
}
}

int get_precedence(char a)
{
if(a == '*')
	return 3;
if(a == '.')
	return 2;
if(a == '+')
	return 1;
if(a == '(' || a == ')')
	return 0;
}

void get_postfix()
{
top = 0;
j = 0;
int k = 0;
for(i=0;i<length;i++){
	if(expr[i] == '*' || expr[i] == '.' || expr[i] == '+')
	{
		if(top == 0)
			push(expr[i]);
		else{
			if(get_precedence(stack[top]) <= get_precedence(expr[i]))
				push(expr[i]);
			else{
				while(get_precedence(stack[top]) > get_precedence(expr[i])){
					postfix[j] = pop();
					j++;
				}
				push(expr[i]);
			}
		}
	}
	else if(expr[i] == '('){
		push(expr[i]);
	}
	else if(expr[i] == ')'){
		while(stack[top] != '('){
			postfix[j] = pop();
			j++;
			if(top == 0){
				printf("Error in regular expression\n");
				break;
			}
		}
		if(stack[top] == '(')
			pop();
	}
	else{
		postfix[j] = expr[i];
		j++;
	}
}
if(top != 0)
{
while(top > 0){
	if(stack[top] == '('){
		printf("Error in regular expression\n");
		break;
	}
	postfix[j] = pop();
	j++;
}
}
printf("%s\n",postfix);
}


// -------------- POSTFIX EXPRESSION TO NFA CONVERSION ---------------------------------//

