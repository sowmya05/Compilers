#include<stdio.h>
#include<string.h>
#include<ctype.h>
char *assign_register(char* a);
int carry=0, zero=0;
void main()
{
	char a[20],b[20],c[20];
	char *reg1, *reg2;
	int i,j=0;
	int length = 0;
	FILE *fp;
	if(( fp = fopen("intermediate", "r")) != 0)
	{
		while(fscanf(fp,"%s", a) != EOF)
		{
			if(strcmp(a,"=")==0)
				{
					fscanf(fp,"%s", a);
					reg2 = assign_register(a);
					fscanf(fp,"%s",b);
					length = strlen(b);
					if(strcmp(b,"<")==0)
					{	
						fscanf(fp,"%s",a);
						printf("\tCMP AH, AL\n");
						fscanf(fp,"%s",a);
						if(strcmp(a,"IFZ") == 0){
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							printf("\tJGE %s\n",a);
						}
					}
					else if(strcmp(b,">")==0)
					{	
						fscanf(fp,"%s",a);
						printf("\tCMP AH, AL\n");
						fscanf(fp,"%s",a);
						if(strcmp(a,"IFZ") == 0){
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							printf("\tJLE %s\n",a);
						}
					}
					else if(strcmp(b,"==")==0)
					{	
						fscanf(fp,"%s",a);
						printf("\tCMP AH, AL\n");
						fscanf(fp,"%s",a);
						if(strcmp(a,"IFZ") == 0){
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							fscanf(fp,"%s",a);
							printf("\tJNE %s\n",a);
						}
					}
					else{
						fseek ( fp , -1*length , SEEK_CUR );
						printf("\tMOV %s, %s\n",reg1,reg2);
					}
				}
			else if(strcmp(a,"+=")==0)
				{
					fscanf(fp,"%s", a);
					reg2 = assign_register(a);
					printf("\tADD %s, %s\n",reg1,reg2);
				}
			else if(strcmp(a,"-=")==0)
				{
					fscanf(fp,"%s", a);
					reg2 = assign_register(a);
					printf("\tSUB %s, %s\n",reg1,reg2);
				}
			else if(strcmp(a,"*=")==0)
				{
					fscanf(fp,"%s", a);
					reg2 = assign_register(a);
					printf("\tMUL %s, %s\n",reg1,reg2);
				}
			else if(strcmp(a,"/=")==0)
				{
					fscanf(fp,"%s", a);
					reg2 = assign_register(a);
					printf("\tDIV %s, %s\n",reg1,reg2);
				}
			else if(strcmp(a,"Label")==0)
				{
					fscanf(fp,"%s",b);
					printf("%s\n",b);
				}
			else if(strcmp(a,"GOTO")==0)
				{
					fscanf(fp,"%s",b);
					printf("\tJMP %s\n",b);
				}	
			else{
				length = strlen(a);
				fseek ( fp , -1*length , SEEK_CUR );
				fscanf(fp,"%s", c);
				reg1 = assign_register(c);		
			}
				
		}
	}

}

char *assign_register(char* a)
{
	char * reg;
	if(strcmp(a,"t0")==0)
		reg = "AH";
	else if(strcmp(a,"t1")==0)
		reg = "AL";
	else if(strcmp(a,"t2")==0)
		reg = "BH";
	else if(strcmp(a,"t3")==0)
		reg = "BL";
	else if(strcmp(a,"t4")==0)
		reg = "CH";
	else if(strcmp(a,"t5")==0)
		reg = "CL";
	else if(strcmp(a,"t6")==0)
		reg = "DH";
	else if(strcmp(a,"t7")==0)
		reg = "DL";
	else
		reg = a;
	return reg;
}
