#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_length 50

char expr[max_length], alphabet[max_length], postfix[max_length];
int length,i,alphanum=0,j,flag,start_state=1,final_state=1,current_state=0;

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


// --- define nfa stack --- //
struct nfa_name{
	int start;
	int final;
	char name;		
}nfa_stack[5*max_length],temp_stack[5*max_length];
int nfa_top=0,temp_top=0;
void push_nfa(int start, int final, char name)
{
	nfa_top++;
	nfa_stack[nfa_top].start=start;
	nfa_stack[nfa_top].final=final;
	nfa_stack[nfa_top].name=name;
}

struct nfa_name pop_nfa()
{
	return nfa_stack[nfa_top--];
}
void push_temp(int start, int final, char name)
{
	temp_top++;
	temp_stack[temp_top].start=start;
	temp_stack[temp_top].final=final;
	temp_stack[temp_top].name=name;
}

struct nfa_name pop_temp()
{
	return temp_stack[temp_top--];
}
// -------------------- //

void get_alphabets();
void get_postfix();
int get_precedence(char);
void get_nfa();
struct nfa_name calc_union(struct nfa_name,struct nfa_name);
struct nfa_name calc_concat(struct nfa_name,struct nfa_name);
struct nfa_name calc_recurse(struct nfa_name);
void print_nfa();

int main()
{
printf("Enter Regular expression: ");
scanf("%s",expr);
get_alphabets();
get_postfix();
get_nfa();
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
length = j;
}








// ---------------- postfix expression to nfa conversion -----------------------//
void get_nfa()
{	int k=0;
	for(i=0;i<length;i++)
		push_nfa(0,0,postfix[i]);
	struct nfa_name temp,temp1,temp2;
	while(1){
		//k++;
		if(nfa_top == 1 && nfa_stack[nfa_top].name == '$')
			break;
		else if(nfa_stack[nfa_top].name != '$' && nfa_top == 1)
		{
			temp = pop_nfa();
			printf("%c\n",temp.name);
			temp.start = current_state;
			for(j=0;j<=length;j++)
			{		
				if(temp.name == alphabet[j]){				
					NFA[current_state].state[j] = current_state+1;
					current_state++;
				}
			}
			temp.name = '$';
			temp.final = current_state;
			push_nfa(temp.start,temp.final,temp.name);
			break;
		}
		//printf("%d\n",nfa_top);
		while(nfa_top>0){
			temp = pop_nfa();
			//printf("hi %c\n",temp.name);
			push_temp(temp.start,temp.final,temp.name);
		}
		//printf("%d\n",temp_top);
		while(temp_stack[temp_top].name != '*' && temp_stack[temp_top].name != '+' && temp_stack[temp_top].name != '.')
		{

			temp = pop_temp();
			//printf("%c\n",temp.name);
			push_nfa(temp.start,temp.final,temp.name);	
			if(temp_top == 0)
				break;		
		}
		temp = pop_temp();
		//printf("%c\n",temp.name);
		if(temp.name == '+'){
			temp1 = pop_nfa();
			temp2 = pop_nfa();
			temp = calc_union(temp1,temp2); 
		}
		else if(temp.name == '.'){
			temp1 = pop_nfa();
			temp2 = pop_nfa();
			temp = calc_concat(temp1,temp2);
		}
		else if(temp.name == '*'){
			temp1 = pop_nfa();
			temp = calc_recurse(temp1);
		}
		else if(temp.name == '$'){
			push_nfa(temp.start,temp.final,temp.name);
			break;
		}
		push_nfa(temp.start,temp.final,temp.name);
		while(temp_top > 0){
			temp = pop_temp();
			push_nfa(temp.start,temp.final,temp.name);
			//printf("push %c\n",temp.name);
		}
	}
	print_nfa();	
}

struct nfa_name calc_union(struct nfa_name temp1, struct nfa_name temp2){
	struct nfa_name temp;
	if(temp1.start == 0 && temp2.start == 0)
	{
		current_state++;
		temp.start = current_state;
		NFA[current_state].eps[NFA[current_state].len] = current_state + 1;
		NFA[current_state].len++;
		current_state++;
		for(j=0;j<=length;j++)
		{		
			if(temp2.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		NFA[current_state].eps[NFA[current_state].len] = current_state + 1;
		NFA[current_state].len++;
		current_state++;
		temp.final = current_state;
		NFA[temp.start].eps[NFA[temp.start].len] = current_state + 1;
		NFA[temp.start].len++;
		current_state++;
		for(j=0;j<=length;j++)
		{		
			if(temp1.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		NFA[current_state].eps[NFA[current_state].len] = temp.final;
		NFA[current_state].len++;
		temp.name = '$';		
	}
	if(temp1.start != 0 && temp2.start == 0)
	{
		temp.start = temp1.start;
		temp.final = temp1.final;
		temp.name = '$';
		NFA[temp.start].eps[NFA[temp.start].len] = current_state + 1;
		NFA[temp.start].len++;
		current_state++;
		for(j=0;j<=length;j++)
		{		
			if(temp2.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		NFA[current_state].eps[NFA[current_state].len] = temp.final;
		NFA[current_state].len++;
	}
	if(temp2.start != 0 && temp1.start == 0)
	{
		temp.start = temp2.start;
		temp.final = temp2.final;
		temp.name = '$';
		NFA[temp.start].eps[NFA[temp.start].len] = current_state + 1;
		NFA[temp.start].len++;
		current_state++;
		for(j=0;j<=length;j++)
		{		
			if(temp1.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		NFA[current_state].eps[NFA[current_state].len] = temp.final;
		NFA[current_state].len++;
	}
	if(temp1.start != 0 && temp2.start != 0)
	{
		current_state++;
		temp.start = current_state;
		NFA[current_state].eps[NFA[current_state].len] = temp1.start;
		NFA[current_state].len++;
		NFA[current_state].eps[NFA[current_state].len] = temp2.start;
		NFA[current_state].len++;
		current_state++;
		temp.final = current_state;
		NFA[temp1.final].eps[NFA[temp1.final].len] = temp.final;
		NFA[temp1.final].len++;
		NFA[temp2.final].eps[NFA[temp2.final].len] = temp.final;
		NFA[temp2.final].len++;
		temp.name = '$';
	}
	return temp;
}

struct nfa_name calc_concat(struct nfa_name temp1, struct nfa_name temp2){
	struct nfa_name temp;
	if(temp1.start == 0 && temp2.start == 0)
	{
		current_state++;
		temp.start = current_state;
		for(j=0;j<=length;j++)
		{		
			if(temp2.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		for(j=0;j<=length;j++)
		{		
			if(temp1.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		temp.final = current_state;
		temp.name = '$';
	}
	else if(temp1.start != 0 && temp2.start == 0)
	{
		current_state++;
		for(j=0;j<=length;j++)
		{
		if(temp2.name == alphabet[j]){				
			NFA[current_state].state[j] = temp1.start;
		}
		}
		temp.final = temp1.final;
		temp.name = '$';
		temp.start = current_state;
	}
	else if(temp2.start != 0 && temp1.start == 0)
	{
		current_state++;
		for(j=0;j<=length;j++)
		{
		if(temp1.name == alphabet[j]){				
			NFA[temp2.final].state[j] = current_state;
		}
		}
		temp.final = current_state;
		temp.name = '$';
		temp.start = temp2.start;
	}
	else if(temp1.start != 0 && temp2.start != 0)
	{
		temp.start = temp2.start;
		NFA[temp2.final].eps[NFA[temp2.final].len] = temp1.start;
		NFA[temp2.final].len++;
		temp.final = temp1.final;
		temp.name = '$';
	}
	return temp;
}

struct nfa_name calc_recurse(struct nfa_name temp1){
	struct nfa_name temp;
	if(temp1.start == 0){
		current_state++;
		temp.start = current_state;
		NFA[current_state].eps[NFA[current_state].len] = current_state + 1;
		NFA[current_state].len++;
		current_state++;
		for(j=0;j<=length;j++)
		{		
			if(temp1.name == alphabet[j]){				
				NFA[current_state].state[j] = current_state+1;
				current_state++;
			}
		}
		NFA[current_state].eps[NFA[current_state].len] = current_state - 1;
		NFA[current_state].len++;
		NFA[current_state].eps[NFA[current_state].len] = current_state + 1;
		NFA[current_state].len++;
		current_state++;
		temp.final = current_state;
		NFA[temp.start].eps[NFA[temp.start].len] = temp.final;
		NFA[temp.start].len++;
		temp.name = '$';
	}
	else if(temp1.start != 0){
		current_state++;
		temp.start = current_state;
		NFA[current_state].eps[NFA[current_state].len] = temp1.start;
		NFA[current_state].len++;
		current_state++;
		temp.final = current_state;
		NFA[temp1.final].eps[NFA[temp1.final].len] = temp.final;
		NFA[temp1.final].len++;
		NFA[temp.start].eps[NFA[temp.start].len] = temp.final;
		NFA[temp.start].len++;
		NFA[temp1.final].eps[NFA[temp1.final].len] = temp1.start;
		NFA[temp1.final].len++;
		temp.name = '$';
	}
	return temp;
}

void print_nfa(){
	i = 1;
	struct nfa_name temp = pop_nfa();
	start_state = temp.start;
	final_state = temp.final;
	printf("State");
	for(j=0;j<alphanum;j++){
			printf("\t%c",alphabet[j]);
	}
	printf("\tEpsilon\n");
	while(i <= current_state){
		if(i == start_state)
			printf("-> %d",i);
		else if(i == final_state)
			printf("* %d",i);
		else
			printf("%d",i);
		for(j=0;j<alphanum;j++){
			if(NFA[i].state[j] == start_state)
				printf("\t-");
			else
				printf("\t%d",NFA[i].state[j]);
		}
		printf("\t{");
		for(j=0;j<NFA[i].len;j++)
			printf("%d, ",NFA[i].eps[j]);
		printf("}\n");
		i++;
	}
}




// ------ construct DFA from NFA ------ //
