#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
using namespace std;
struct OPTAB
{
	char name[10];
	char format;
	char opcode[3];
}z[59];
struct SYMTAB
{
	char name[10];
	int locctr;
}x[5];

int add(char *s,const int &locctr)
{
	static int i=0;
	cout<<"in add\n";
	if(!i)
	{
		cout<<"i = 0\n";
		strcpy(x[i].name,s);
		x[i].locctr=locctr;
		i++;
	}
	else
	{
		for(int j=0;j<=i-1;j++)
		cout<<"label = "<<x[j].name<<"\tlocctr = "<<x[j].locctr<<endl;
		int k=0;
		for(int j=0;j<=i-1;j++)
			if(!strcmp(x[j].name,s))
			{
				cout<<"IN IF\n";
				k=1;
				return 0;
			}
		if(!k)
		{
			strcpy(x[i].name,s);
			x[i].locctr=locctr;
			i++;
		}
	}
	return 1; 
}
int search(char *s,const OPTAB *x)
{
	char *t=s;
	
	if(s[0]=='+')
	t=s+1;
	
	for(int i=0;i<=58;i++)
	if(!strcmp(t,x[i].name))
	{
		if(s[0]=='+' && x[i].format!='3')
		{
			cout<<"ERROR (in search): \n";
		}
		else
		return i;
	}
		return -1;
}
int pass1()
{
	char s[8],*line,t,name[10];
	int k=0,i,j,start=0,locctr=0;
	int n,y,length;
	OPTAB z[59];
	fstream a,b,c;
	line=new char;
	a.open("OPTAB.txt",ios::in);
	b.open("assembler program.txt",ios::in);
	c.open("intermediate file.txt",ios::out);
	while(a>>s)
	{
		strcpy(z[k].name,s);
		a>>t;
		z[k].format=t;
		a>>s;
		strcpy(z[k].opcode,s);
		k++;
	}
	a.close();
	b.getline(line,20);
	n=strlen(line);
	for(i=0;line[i]!='\t';i++)
		name[i]=line[i];
	name[6]='\0';
	k=1;
	if(line[++i]=='S')				//else part...
	if(line[++i]=='T')
	if(line[++i]=='A')
	if(line[++i]=='R')
	if(line[++i]=='T')
	{
		for(j=i+2;j<=n-1;j++)
		{
			start=k*start+(line[j]-'0');
			k*=10;
		}
		locctr=start;
	}
	c<<start<<"\t"<<line<<endl;
	locctr=start;
	char label[20],opcode[20],operand[20];
	while(b.getline(line,20))
	{
		n=strlen(line);
		
		if(line[0]=='.')
		c<<line<<endl;
		
		else if(line[0]=='\t')
			{
				label[0]='\t';
				label[1]='\0';
				i=1;
			}
		
		else
		{	
			for(i=0;line[i]!='\t';i++)
				label[i]=line[i];
				label[i]='\0';
				i++;
		}
		for(k=0;line[i]!='\t';i++,k++)
		opcode[k]=line[i];
		opcode[k]='\0';
		i++;
		
		for(k=0;i<=n-1;i++,k++)
		operand[k]=line[i];
		operand[k]='\0';	
		
		k=0;
		cout<<label<<' '<<opcode<<' '<<operand<<endl;
		
		if(opcode[0]=='+')
			k=1;
		
		y=search(opcode,z);
		if(y>=0)			//if not then....
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
				}
			}
			c<<locctr<<"\t"<<line<<endl;
			locctr=locctr+z[y].format-'0'+k;							//check for format 4
		}
		else if(!strcmp(opcode,"WORD"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
				}
			}
			c<<locctr<<"\t"<<line<<endl;
			locctr=locctr+3;
		}
		else if(!strcmp(opcode,"RESW"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
				}
			}
			c<<locctr<<"\t"<<line<<endl;
			locctr=locctr+3*(atoi(operand));
		}
		else if(!strcmp(opcode,"BYTE"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
				}
			}
			c<<locctr<<"\t"<<line<<endl;
			locctr=locctr+strlen(operand);
		}
		else if(!strcmp(opcode,"RESB"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
				}
			}
			c<<locctr<<"\t"<<line<<endl;
			locctr=locctr+atoi(operand);
		}
		else if(!strcmp(opcode,"END"))
		{
			c<<"\t"<<line<<endl;
			length=locctr-start;
			cout<<"\tlength = "<<length<<endl;
		}
// try using map or hash for optab and symtab
	}
return 0;
}
int main()
{
	int status1;//status2=-1;
	status1=pass1();
	if(status1)
	{
		cout<<"SUCESSFUL\n";
	}
	else
	cout<<"\tERROR\n";
	return 0;
}
