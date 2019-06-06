#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <sstream>
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
}X[50];
int length,LOS,start=0; //LENGTH OF SYMTAB
void conver_to_OC(char *object_code,char *OC)
{
	char *ptr,*point;
	point=new char;										
	int count=0;
	ptr=object_code;
	while(count<=2)
	{
		strncpy(point,ptr,4);
		int ans=atoi(point)-atoi("0000");
		switch(ans)
		{
			case 0:	OC[count]='0';
						ptr+=4;
						count++;
						continue;
			case 1:	OC[count]='1';
						ptr+=4;
						count++;
						continue;
			case 10:	OC[count]='2';
							ptr+=4;
							count++;
							continue;
			case 11:	OC[count]='3';
							ptr+=4;
							count++;
							continue;
			case 100:	OC[count]='4';
							ptr+=4;
							count++;
							continue;
			case 101:	OC[count]='5';
							ptr+=4;
							count++;
							continue;
			case 110:	OC[count]='6';
							ptr+=4;
							count++;
							continue;
			case 111:	OC[count]='7';
							ptr+=4;
							count++;
							continue;
			case 1000:	OC[count]='8';
								ptr+=4;
								count++;
								continue;
			case 1001:	OC[count]='9';
								ptr+=4;
								count++;
								continue;
			case 1010:	OC[count]='A';
								ptr+=4;
								count++;
								continue;
			case 1011:	OC[count]='B';
								ptr+=4;
								count++;
								continue;
			case 1100:	OC[count]='C';
								ptr+=4;
								count++;
								continue;
			case 1101:	OC[count]='D';
								ptr+=4;
								count++;
								continue;
			case 1110:	OC[count]='E';
								ptr+=4;
								count++;
								continue;
			case 1111:	OC[count]='F';
								ptr+=4;
								count++;
								continue;
			}
	}
	OC[count]='\0';
	strcat(OC,ptr);
}
void generate_OC(OPTAB *z,int y,char *object_code)
{
	int i;
	for(i=0;i<=1;i++)
	switch(z[y].opcode[i])
	{
		case '0':strcat(object_code,"0000");continue;
		case '1':strcat(object_code,"0001");continue;
		case '2':strcat(object_code,"0010");continue;
		case '3':strcat(object_code,"0011");continue;
		case '4':strcat(object_code,"0100");continue;
		case '5':strcat(object_code,"0101");continue;
		case '6':strcat(object_code,"0110");continue;
		case '7':strcat(object_code,"0111");continue;
		case '8':strcat(object_code,"1000");continue;
		case '9':strcat(object_code,"1001");continue;
		case 'A':strcat(object_code,"1010");continue;
		case 'B':strcat(object_code,"1011");continue;
		case 'C':strcat(object_code,"1100");continue;
		case 'D':strcat(object_code,"1101");continue;
		case 'E':strcat(object_code,"1110");continue;
		case 'F':strcat(object_code,"1111");continue;
	}
	object_code[6]='\0';
}
int add(const char *s,int locctr)
{
	
	stringstream ss;
	static int i=0;
	//~ cout<<"in add\n";
	if(!i)
	{
		//~ cout<<"i = 0\n";
		strcpy(X[i].name,s);
		X[i].locctr=locctr;
		i++;
	}
	else
	{
		//~ for(int j=0;j<=i-1;j++)
		//~ cout<<"label = "<<X[j].name<<"\tlocctr = "<<X[j].locctr<<endl;
		int k=0;
		for(int j=0;j<=i-1;j++)
			if(!strcmp(X[j].name,s))
			{
				//~ cout<<"IN IF\n";
				k=1;
				return 0;
			}
		if(!k)
		{
			strcpy(X[i].name,s);
			X[i].locctr=locctr;
			i++;
			LOS=i;
		}
	}
	return 1; 
}
int search_OP(char *s,const OPTAB *x)
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
int search_SYM(char *s,int &extra)
{
	extra=0;
	int i;
	char *t=s;
	//~ cout<<"\t\t\t\tinstruction = "<<t<<endl;
	if(s[0]=='#' || s[0]=='@')
	t=s+1;
	//~ cout<<"\t\t\t\tinstruction = "<<t<<endl;
	int n=strlen(t);
	char first[n],last[n];
	//~ for(int l=0;t[l]!='\0';l++)
	//~ cout<<" "<<t[l];
	i=0;
		while(t[i]!=',' && i<=n)
		{
			first[i]=t[i];
			i++;
		}
			//~ cout<<"\t\t\t$"<<t[i]<<"$"<<endl;
		first[i]='\0';
		
		if(i<n-1)
		i++;
		
		int k;
		for(k=0;i<=n-1;i++,k++)
			last[k]=t[i];
			last[k]='\0';
		
	//~ cout<<"\tfirst = "<<first<<endl<<"\tlast = "<<last<<endl;
	if(!strcmp(t,first))
	{
		for(i=0;i<=LOS-1;i++)
		if(!strcmp(X[i].name,t))
		{
			return i;
		}
		return -1;
	}
	else
	{
		for(i=0;i<=LOS-1;i++)
		if(!strcmp(X[i].name,last))
				extra=i;
			for(i=0;i<=LOS-1;i++)
		if(!strcmp(X[i].name,first))
			return i;
	}
	return -1;
}
void UPPER(char *s)
{
	int n=strlen(s);
	for(int i=0; i<=n-1;i++)
		if(s[i]>='a' && s[i]<='f')
			s[i]=s[i]-32;
	return ;
}
int pass1()
{
	std::stringstream ss;
	char s[8],line[50],t;
	int k=0,i,j,locctr=0,temp;
	int n,y;
	fstream a,b,c;
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
	
	b.getline(line,40);
	n=strlen(line);
	k=0;
	for(i=0;line[i]!='\t';i++);
	if(line[++i]=='S')				//else part...
	if(line[++i]=='T')
	if(line[++i]=='A')
	if(line[++i]=='R')
	if(line[++i]=='T')
	{
		temp=0;
		for(k=n-1,j=0;k>=i;k--,j++)
	{
		if(line[k]>='0' && line[k]<='9')
		{
			 temp=temp+(line[k]-'0')*pow(16,j);
		}
		if(line[k]>='A' && line[k]<='F')
		{
			temp=temp+(line[k]-'A'+10)*pow(16,j);
		}		
	}
	}
	locctr=start=temp;
	c<<setw(4)<<setfill('0')<<hex<<uppercase<<start<<"\t"<<line<<endl;
	k=1;
	char label[20],opcode[20],operand[20];
	while(b.getline(line,50))
	{
		n=strlen(line);
		
		if(line[0]=='.')
		{
			c<<"\t"<<line<<endl;
			continue;
		}
		
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
		//~ cout<<label<<' '<<opcode<<' '<<operand<<endl;
		
		if(opcode[0]=='+')
			k=1;
		
		y=search_OP(opcode,z);
		if(y>=0)			//if not then....
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
					return 0;
				}
			}
			c<<setw(4)<<setfill('0')<<locctr<<"\t"<<line<<endl;
			locctr=locctr+z[y].format-'0'+k;							//check for format 4
		}
		else if(!strcmp(opcode,"WORD"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
					return 0;
				}
			}
			c<<setw(4)<<setfill('0')<<locctr<<"\t"<<line<<endl;
			locctr=locctr+3;
		}
		else if(!strcmp(opcode,"RESW"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
					return 0;
				}
			}
			c<<setw(4)<<setfill('0')<<locctr<<"\t"<<line<<endl;
			locctr=locctr+3*(atoi(operand));
		}
		else if(!strcmp(opcode,"BYTE"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
					return 0;
				}
			}
			c<<setw(4)<<setfill('0')<<locctr<<"\t"<<line<<endl;
			if(operand[0]=='C' && operand[1]=='\'')
			{
				int t=0;
				//~ cout<<"\t\t\tin BYTE\n";
				for(int r=2;operand[r]!='\'';r++,t++);
				locctr=locctr+t;
			}
			else if(operand[0]=='X' && operand[1]=='\'')
			{
				locctr=locctr+1;
			}
		}
		else if(!strcmp(opcode,"RESB"))
		{
			if(strcmp(label,"\t"))
			{
				if(!add(label,locctr))
				{
					cout<<"ERROR : LABEL DEFINED AGAIN\n";
					return 0;
				}
			}
			c<<setw(4)<<setfill('0')<<locctr<<"\t"<<line<<endl;
			int op=atoi(operand);
			locctr=locctr+op;
		}
		else if(!strcmp(opcode,"END"))
		{
			c<<"\t"<<line;
			length=locctr-start;
			ss<<hex<<length;
			ss>>dec>>length;
			cout<<"length = "<<length<<endl;
		}
		else if(!strcmp(opcode,"BASE"))
		{
			c<<"\t"<<line<<endl;
		}
		else
		{
			cout<<"\tERROR: UNKNOWN OPCODE\n";
			return 0;
		}
// try using map or hash for optab and symtab
	}
	add("A",0);
	add("X",1);
	add("L",2);
	add("B",3);
	add("S",4);
	add("T",5);
	add("F",6);
	add("PC",8);
	add("SW",9);
return 1;
}
int pass2()
{
	int PC;
	stringstream ss;
	char modification[50][10];
	char s[10],line[50],object_code[33];
	char OC[10];
	fstream a,b,c;
	int n,k,i,y,t,base=-1,address,COUNT=0;
	char op_add[10];
	a.open("intermediate file.txt",ios::in);
	b.open("object program.txt",ios::out);
	c.open("assembler listing.txt",ios::out);
	a>>s;
	c<<s<<'\t';
	a>>s;
	s[6]='\0';
	c<<s<<'\t';
	b<<"H^"<<setiosflags(ios::left)<<setw(6)<<s<<"^";
	a>>s;
	c<<s;
	a.getline(s,10);
	c<<"\t\t"<<s<<endl;
	char *next=s;
	next=s+1;
	PC=atoi(next);
	b<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<next<<"^"<<setw(6)<<setfill('0')<<length<<endl;
	
	char label[20],opcode[20],operand[20];
	char record[70],temporary[10];
	strcpy(record,"\0");
	
	strcpy(op_add,"\0");
	strcpy(op_add,next);
	//char len[5];
	int size=0,L=0;
	char previous[10];
	strcpy(previous,op_add);
	while(a.getline(line,50))
	{
		strcpy(opcode,"\0");
		strcpy(operand,"\0");
		strcpy(label,"\0");
		n=strlen(line);
		for(i=0;line[i]!='\t';i++)
		{
			s[i]=line[i];
		}
		s[i]='\0';
		i++;
		if(line[i]=='.')
		{
			c<<line<<endl;
			continue;
		}
		else if(line[i]=='\t')
			{
				label[0]='\t';
				label[1]='\0';
				i++;
			}
		else
		{	
			for(k=0;line[i]!='\t';i++,k++)
				label[k]=line[i];
				label[k]='\0';
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
		if(!strcmp(op_add,"-1") && strcmp(opcode,"RESB") && strcmp(opcode,"RESW"))
		{
			strcpy(op_add,s);
		}
			
		if(size>30)
		{
			char q[5];
			sprintf(q,"%X",L);
			UPPER(q);
			b<<"T^"<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<previous<<"^"<<setw(2)<<q<<record<<endl;
			strcpy(previous,op_add);
			strcpy(record,"\0");
			strcpy(record,"^");
			strcat(record,temporary);
			size=strlen(temporary)/2;
			L=0;
		}
		else if(size)
		{			
			if(strcmp(temporary,"\0"))
			strcat(record,"^");
			strcat(record,temporary);
			strcpy(temporary,"\0");
		}
		else
		{
			strcpy(previous,s);
		}
		k=0;
		
		if(opcode[0]=='+')
		k=1;
		
		y=search_OP(opcode,z);
		if(y>=0)			//if not then....
		{
			if(strcmp(operand,"\t"))
			{
				int ee;
				t=search_SYM(operand,ee);
				if(t>=0)
				{
					int m;
					switch(z[y].format)
					{
						case '1'://check what to do
										break;
						case '2':	
										strcpy(object_code,z[y].opcode);
										m=strlen(object_code);
										object_code[m]=X[t].locctr+'0';
										object_code[m+1]=X[ee].locctr+'0';
										object_code[m+2]='\0';
										strcpy(OC,object_code);
										UPPER(OC);
										c<<line<<"\t\t"<<OC<<endl;
										strcpy(temporary,OC);
										L=size;
										size+=strlen(OC)/2;
										if(size>30)
										strcpy(op_add,s);
										break;
						case '3': if(!k)
										{
											strcpy(object_code,"\0");
											int n=1,i=1,x=0,b,p,e=0,disp;
											generate_OC(z,y,object_code);
											if(operand[0]=='#')
											{
												n=0;
												i=1;
												x=0;
											}
											else if(operand[0]=='@')
											{
												n=1;
												i=0;
												x=0; 				
											}
											if(X[ee].locctr==1)
											x=1;
											stringstream aa(s);
											aa>>hex>>address;
											PC=address+z[y].format-'0';
											disp=X[t].locctr-PC;
											
											if(disp >=-2048 && disp<=2047)
											{
												p=1;
												b=0;
											}
											else
											{
												p=0;
												b=1;
												if(base==-1)
												cout<<"ERROR : BASE ADDRESS NOT INITIALISED\n";
												else
												disp=X[t].locctr-base;
											}
											char displacement[10];
											char *pointer=displacement;
											sprintf(displacement,"%X",disp);
											//~ cout<<"\tdisp = "<<disp<<endl<<"\tdisplacement = "<<displacement<<endl;
											if(strlen(displacement)>=3)
											pointer=displacement+strlen(displacement)-3;
											
											strcpy(displacement,pointer);
											//~ cout<<"displ = "<<displacement<<"\t"<<n<<' '<<i<<' '<<x<<' '<<b<<' '<<p<<' '<<e<<endl;
											int m=strlen(object_code);
											object_code[m]=n+'0';
											object_code[m+1]=i+'0';
											object_code[m+2]=x+'0';
											object_code[m+3]=b+'0';
											object_code[m+4]=p+'0';
											object_code[m+5]=e+'0';
											object_code[m+6]='\0';
											if(strlen(displacement)==1)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='\0';
											}
											if(strlen(displacement)==2)
											{
												object_code[m+6]='0';
												object_code[m+7]='\0';
											}
											strcat(object_code,displacement);
											conver_to_OC(object_code,OC);
											UPPER(OC);
											c<<line<<"\t\t"<<OC<<endl;
											strcpy(temporary,OC);
											L=size;
											size+=strlen(OC)/2;
											if(size>30)
											strcpy(op_add,s);
										}
										else
										{
											//~ cout<<"\tREACHED\n";
											strcpy(object_code,"\0");
											int n=1,i=1,x=0,b=0,p=0,e=1,disp;
											generate_OC(z,y,object_code);
											i=1;
											disp=X[t].locctr;
											if(operand[0]=='#')
											{
												n=0;
												i=1;
												x=0;
											}
											else if(operand[0]=='@')
											{
												n=1;
												i=0;
												x=0;   //check
											}
											if(X[ee].locctr==1)
											x=1;
											disp=X[t].locctr;
											char displacement[10];
											sprintf(displacement,"%X",disp);
											//~ cout<<"displ = "<<displacement<<"\t"<<n<<' '<<i<<' '<<x<<' '<<b<<' '<<p<<' '<<e<<endl;
											int m=strlen(object_code);
											object_code[m]=n+'0';
											object_code[m+1]=i+'0';
											object_code[m+2]=x+'0';
											object_code[m+3]=b+'0';
											object_code[m+4]=p+'0';
											object_code[m+5]=e+'0';
											object_code[m+6]='\0';
											if(strlen(displacement)==1)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='0';
												object_code[m+9]='0';
												object_code[m+10]='\0';
											}
											if(strlen(displacement)==2)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='0';
												object_code[m+9]='\0';
											}
											if(strlen(displacement)==3)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='\0';
											}
											if(strlen(displacement)==4)
											{
												object_code[m+6]='0';
												object_code[m+7]='\0';
											}
											strcat(object_code,displacement);
											conver_to_OC(object_code,OC);
											UPPER(OC);
											c<<line<<"\t\t"<<OC<<endl;
											int number;
											stringstream dd(s);
											dd>>hex>>number;
											sprintf(modification[COUNT++],"%X",number+1);
											strcpy(temporary,OC);
											L=size;
											size+=strlen(OC)/2;
											if(size>30)
											strcpy(op_add,s);
										}
					}
				}
				else
				{
					//#4096 case
					if(operand[0]=='#')
					{
						int n=0,i=1,x=0,b=0,p=0,e=k;
						int value;
						char *t=operand+1;
						char pointer[10];
						stringstream ss(t);
						ss>>dec>>value;
						sprintf(pointer,"%X",value);
									strcpy(object_code,"\0");
											generate_OC(z,y,object_code);
											int m=strlen(object_code);
											object_code[m]=n+'0';
											object_code[m+1]=i+'0';
											object_code[m+2]=x+'0';
											object_code[m+3]=b+'0';
											object_code[m+4]=p+'0';
											object_code[m+5]=e+'0';
											object_code[m+6]='\0';
											if(strlen(pointer)==1 && e)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='0';
												object_code[m+9]='0';
												object_code[m+10]='\0';
											}
											if(strlen(pointer)==2 && e)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='0';
												object_code[m+9]='\0';
											}
											if(strlen(pointer)==3 && e)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='\0';
											}
											if(strlen(pointer)==4 && e)
											{
												object_code[m+6]='0';
												object_code[m+7]='\0';
											}
											if(strlen(pointer)==1 && !e)
											{
												object_code[m+6]='0';
												object_code[m+7]='0';
												object_code[m+8]='\0';
											}
											if(strlen(pointer)==2 && !e)
											{
												object_code[m+6]='0';
												object_code[m+7]='\0';
											}
											strcat(object_code,pointer);
											conver_to_OC(object_code,OC);
											UPPER(OC);
											c<<line<<"\t\t"<<OC<<endl;
											strcpy(temporary,OC);
											L=size;
											size+=strlen(OC)/2;
											if(size>30)
											strcpy(op_add,s);
					}
				}
			}
			else if(!strcmp(opcode,"RSUB"))
			{
				strcpy(object_code,"\0");
				generate_OC(z,y,object_code);
				strcat(object_code,"11");
				conver_to_OC(object_code,OC);
				UPPER(OC);
				c<<line<<"\t"<<OC<<endl;
				strcpy(temporary,OC);
				L=size;
				size+=strlen(OC)/2;
				if(size>30)
				strcpy(op_add,s);
			}
			else
			{
				cout<<"ERROR : OPERAND NOT PRESENT\n";
			}
		}
					else if(!strcmp(opcode,"BASE"))
					{
						base=search_SYM(operand,base);
						if(base>=0)
						{
							base=X[base].locctr;
						}
					}
					else if(!strcmp(opcode,"NOBASE"))
					{
						base=-1;
					}
					else if(!strcmp(opcode,"BYTE"))
					{
						if(operand[0]=='C')
						{
							strcpy(OC,"\0");
							char *t=operand+2;
							char constant[3];
							for(i=0;t[i]!='\'';i++)
							{
								sprintf(constant,"%X",t[i]);
								strcat(OC,constant);
							}
							UPPER(OC);
							c<<line<<"\t\t"<<OC<<endl;
							strcpy(temporary,OC);
							L=size;
							size+=strlen(OC)/2;
							if(size>30)
							strcpy(op_add,s);
						}
						else if(operand[0]=='X')
						{			
							int i;				
							char *t=operand+2;
							for(i=0;t[i]!='\'';i++)
							OC[i]=t[i];
							OC[i]='\0';
							UPPER(OC);
							c<<line<<"\t\t"<<OC<<endl;
							strcpy(temporary,OC);
							L=size;
							size+=strlen(OC)/2;
							if(size>30)
							strcpy(op_add,s);
						}
					}
					else if(!strcmp(opcode,"WORD"))
					{
						stringstream ss(operand);
						char constant[10];
						int temp;
						ss>>hex>>temp;
						sprintf(constant,"%X",temp);
						strcpy(OC,constant);
						UPPER(OC);
						c<<line<<"\t\t"<<OC<<endl;
						strcpy(temporary,OC);
						L=size;
						size+=strlen(OC)/2;

						if(size>30)
						strcpy(op_add,s);
					}
					else if(!strcmp(opcode,"RESW") || !strcmp(opcode,"RESB"))
					{
						c<<line<<"\t\t"<<endl;
						if(strcmp(op_add,"-1"))
						{
							L=size;
							char q[5];
							sprintf(q,"%X",L);
							UPPER(q);
							b<<"T^"<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<previous<<"^"<<setw(2)<<q<<record<<endl;
							strcpy(previous,s);
						}
						strcpy(record,"\0");
						strcpy(op_add,"-1");
						strcpy(temporary,"\0");
						L=0;
						size=0;
					}
					else if(!strcmp(opcode,"END"))
					{
						c<<line<<'\t'<<endl;
						L=size;
						char q[5];
						sprintf(q,"%X",L);
						UPPER(q);
						b<<"T^"<<setiosflags(ios::right)<<setw(6)<<setfill('0')<<op_add<<"^"<<setw(2)<<q<<record<<endl;
						for(int u=0;u<=COUNT-1;u++)
						{
							UPPER(modification[u]);
							b<<"M^"<<setfill('0')<<setw(6)<<modification[u]<<"^05"<<endl;
						}
						b<<"E^"<<setw(6)<<setfill('0')<<hex<<start;
					}
					else
					{
						cout<<"ERROR : INVALID OPCODE\n";
					}
				}
return 1;
}
int main()
{
	int status1,status2;
	status1=pass1();
	//~ for(int o=0;o<=LOS-1;o++)
	//~ cout<<X[o].name<<'\t'<<X[o].locctr<<endl;
	if(status1)
	{
		cout<<"SUCESSFUL\n";
		status2=pass2();
		if(status2)
		{
			cout<<"OBJECT PROGRAM GENERATED\n";
		}
		else
		cout<<"\tERROR\n";
	}
	else
	cout<<"\tERROR\n";
	return 0;
}
