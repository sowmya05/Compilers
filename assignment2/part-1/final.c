#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>     //Adding library for alphanum comparison 

#define max_length 50

char expr[max_length], alphabet[max_length], postfix[max_length],dfa_final[max_length],input[5*max_length];
int length,i,alphanum=0,j,flag,start_state=1,final_state=1,current_state=0,dfa_pos=0,dfa_start,final_len=0;

struct nfa{
	int state[max_length];
	int eps[max_length];
	int len;		
}NFA[5*max_length];

struct dfa{
	int state[max_length];
	int name[max_length];
	int len;
}DFA[5*max_length];

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
void insert(int val)
{
	int flag = 0;
	for(j=0;j<=top;j++)
	{
		printf("hi");
		if(stack[j] == val)
			flag = 1;
	}
	if(flag == 0)
		push(val);
	i = 0;
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
void get_dfa();
void print_dfa();
void calc_closure(int);
int equal_check(int[],int[],int,int);
int get_transitions(int);
void sort(int,int);
void minimize_dfa();
void simulate_dfa();

int main()
{
printf("Enter Regular expression: ");
scanf("%s",expr);
printf("Enter String: ");
scanf("%s",input);
int s;
get_alphabets();
get_postfix();
printf("NFA Transition table:\n");
get_nfa();
printf("DFA Transition table:\n");
get_dfa();
simulate_dfa();
printf("Minimized-NFA Transition table:\n");
minimize_dfa();
print_dfa();
}

void get_alphabets(){
length = strlen(expr);
for(i=0;i<length;i++){
	push(expr[i]);
	if(expr[i] != '*' && expr[i] != '|' && expr[i] != '(' && expr[i] != ')' && expr[i] != ' ' && expr[i] != '.'){
		if(isalpha(expr[i])==0  && isdigit(expr[i])==0){					 //testing for invalid symbol input
			printf("Invalid symbol in input\n");
			exit(0);
		}                                    
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
if(a == '|')
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
	if(expr[i] == '*' || expr[i] == '.' || expr[i] == '|')
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
				exit(0);
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
		exit(0);
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
			//printf("%c\n",temp.name);
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
		while(temp_stack[temp_top].name != '*' && temp_stack[temp_top].name != '|' && temp_stack[temp_top].name != '.')
		{

			temp = pop_temp();
			//printf("%c\n",temp.name);
			push_nfa(temp.start,temp.final,temp.name);	
			if(temp_top == 0)
				break;		
		}
		temp = pop_temp();
		//printf("%c\n",temp.name);
		if(temp.name == '|'){
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
			if(NFA[i].state[j] == 0)
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
void get_dfa()
{
	top=0;
	/*for(i=1;i<=current_state;i++){
		get_transitions(i);
	}*/
	get_transitions(start_state);
	/*calc_closure(start_state);
	print_dfa();*/
	print_dfa();
}

void print_dfa()
{
	int l=0;int flag=0;
	printf("\nNum\tName\t");
	for(j=0;j<alphanum;j++){
			printf("\t%c",alphabet[j]);
	}
	printf("\n");
	for(i=0;i<dfa_pos;i++)
	{
		if(i==0)
			printf("-> ");
		for(j=0;j<DFA[i].len;j++){
			if(DFA[i].name[j] == final_state)
			{
				printf("* ");
			}
		}
		printf("%d\t{",i);
		for(j=0;j<DFA[i].len;j++){
			if(DFA[i].name[j] == final_state)
			{
				if(final_len == 0)
				{
					dfa_final[0] = i;
					final_len++;
				}
				else{
					for(l=0;l<final_len;l++)
						if(dfa_final[l] == i)
							flag = 1;
					if(flag == 0)
					{
						dfa_final[final_len] = i;
						final_len++;
					}
				}
			}
			printf("%d, ",DFA[i].name[j]);
		}
		printf("}\t");
		for(l=0;l<alphanum;l++){
			if(DFA[i].state[l] == 0)
				printf("-\t");
			else
				printf("%d\t",DFA[i].state[l]);
		}
		printf("\n");
	}
}

int get_transitions(int state)
{
	int k,l,s,r,flag1,cur=0;
	if(dfa_pos == 0){
		calc_closure(state);
		k=0;
		while(top != 0)
		{
			DFA[dfa_pos].name[k] = pop();
			k++;
		}
		DFA[dfa_pos].len = k;
		sort(dfa_pos,k);
		dfa_pos++;
		cur = dfa_pos;
		int temp = dfa_pos;
		l=0, s=0;
		while(l<DFA[temp-1].len){
		for(s=0;s<alphanum;s++){
			if(NFA[DFA[temp-1].name[l]].state[s] != 0){
				//printf("start %d\t%d\n",DFA[temp-1].name[l],l);
				DFA[temp-1].state[s] = get_transitions(NFA[DFA[temp-1].name[l]].state[s]);
			}
		}
			l++;
		}
	}
	else{
		top = 0;
		calc_closure(state);
		k=0;
		while(top != 0)
		{
			DFA[dfa_pos].name[k] = pop();
			k++;
		}
		DFA[dfa_pos].len = k;
		sort(dfa_pos,k);
		flag1 = 0;
		for(r=0;r<dfa_pos;r++)
		{
			if(equal_check(DFA[dfa_pos].name,DFA[r].name,DFA[dfa_pos].len,DFA[r].len) == 1)
			{
				cur = r;
				//printf("e %d\n", cur);
				flag1 = 1;
				break;
			}
		}
		if(flag1 == 0)
		{
			dfa_pos++;
			cur = dfa_pos-1;
			//printf("e1 %d \n", cur);
			int temp = dfa_pos;
			l=0, s=0;
			while(l<k){
			for(s=0;s<alphanum;s++){
				if(NFA[DFA[temp-1].name[l]].state[s] != 0){
					DFA[temp-1].state[s] = get_transitions(NFA[DFA[temp-1].name[l]].state[s]);
				}
			}
				l++;
			}
		}
	}
	return cur;
}

void calc_closure(int state)
{
	int k=0;
	while(k<NFA[state].len)
	{
		if(NFA[state].eps[k] != state)
			calc_closure(NFA[state].eps[k]);
		k++;
	}
	int flag = 0;
	for(j=0;j<=top;j++){
		if(stack[j] == state)
			flag = 1;
	}
	if(flag == 0)
		push(state);
	return;
}

int equal_check(int a[],int b[],int len1, int len2)
{
	int k=0;
	if(len1 != len2)
		return 0;
	else{
		for(k=0;k<len1;k++)
			if(a[k] != b[k])
				return 0;
	}
	return 1;
}

void sort(int pos,int n)
{
	int c,d;
	int swap;
	for (c = 0 ; c < ( n - 1 ); c++)
	  {
	    for (d = 0 ; d < n - c - 1; d++)
	    {
	      if (DFA[pos].name[d] > DFA[pos].name[d+1])
	      {
		swap       = DFA[pos].name[d];
		DFA[pos].name[d]   = DFA[pos].name[d+1];
		DFA[pos].name[d+1] = swap;
	      }
	    }
	  }
}

// -------------------------- MINIMIZE DFA USING HOPCROFT ALGORITHM ---------------------//
void minimize_dfa()
{
	int arr[dfa_pos][dfa_pos];
	for(j=0;j<dfa_pos;j++)
	{
		flag = 0;
		for(i=0;i<final_len;i++)
			if(j==dfa_final[i])
				flag = 1;
		if(flag == 0)
			for(i=0;i<final_len;i++)
			{
				//printf("%d\n",j);
				arr[dfa_final[i]][j] = 1;
			}
	}

	int mark,k;
	do{
		mark = 0;
		for(i=0;i<dfa_pos;i++)
		{
			for(j=0;j<i;j++)
			{
				if(arr[i][j] != 1)
				{
					for(k=0;k<alphanum;k++){
						if(DFA[i].state[k] != 0 || DFA[j].state[k] != 0){
						if(arr[DFA[i].state[k]][DFA[j].state[k]] == 1 || arr[DFA[j].state[k]][DFA[i].state[k]]==1){
							arr[i][j] = 1;
							mark = 1;
							break;
						}
					}}
				}
			}
		}
	}while(mark == 1);

	int l;
	for(i=0;i<dfa_pos;i++){
		for(j=0;j<i;j++){
			if(arr[i][j] != 1){
				mark = 0;
				for(k=0;k<dfa_pos;k++){
					if(k>=i)
						mark = 1;
					else
						mark = 0;
					for(l=0;l<alphanum;l++){
						//printf("mark %d\n",mark);
						if(mark == 0)
							if(DFA[k].state[l] == i)
								DFA[k].state[l] = j;
						else if(mark == 1){
							//printf("mark %d %d\n",mark,k);
							DFA[k-1].state[l] = DFA[k].state[l];
							if(DFA[k].state[l] == i)
								DFA[k].state[l] = j;
						}
					}
				}
				dfa_pos--;
			}
		}
	}
	/*for(i=0;i<dfa_pos;i++)
	{
		for(j=0;j<dfa_pos;j++)
			printf("%d\t",arr[i][j]);
		printf("\n");
	}*/
}

// ------------------- simulate dfa ------------------------------------//
void simulate_dfa(){
	int l = strlen(input),c=0,m;
	for(i=0;i<l;i++){
		m=0;
		for(j=0;j<alphanum;j++){
			if(alphabet[j] == input[i]){
				m = 1;
				if(DFA[c].state[j] != 0)
					c = DFA[c].state[j];
				else{
					c = -1;
					break;
				}
			}
		}
		if(m == 0){
			c = -1;
			break;
		}
	}
	if(c == -1){
		printf("\nSTRING IS NOT IN LAGUAGE\n\n");
		return;
	}
	else{
		for(i=0;i<final_len;i++)
		{
			if(c == dfa_final[i]){
			printf("\nSTRING IS IN LAGUAGE\n\n");
			return;
			}
		}
		printf("\nSTRING IS NOT IN LAGUAGE\n\n");
		return;
	}
}

