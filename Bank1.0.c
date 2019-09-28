#include<stdio.h>
#include<string.h>
#define ENTER 13
#define TAB 9
#define BKSP 8
#define SPACE 32

typedef struct bank
{
	long signed accno;
	char name[30];
	double balamt;
	char pass[15];
	char mobno[11];
	char adcno[13];
	char add[100];
}bank;
typedef struct employee
{
	long signed id;
	char ename[30];
	double sal;
	char emobno[11];
	char eadd[100];
}employee;

char fname[]={"eg12.dat"};
char fdel[]={"delacc.dat"};
char femp[]={"emp.dat"};
char fsypass[]={"fypass.dat"};
char fempdel[]={"fempdel.dat"};

long signed deleted()				
{
	FILE *fp;
	bank x;
	long signed d=100000000;
	fp=fopen(fdel,"ab");
	fclose(fp);
	fp=fopen(fdel,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		d++;
	}
	return d;
}

long signed accountno(char adcno[])		
{
	FILE *fp;
	bank x;
	long signed c=1;
	fp=fopen(fname,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		if(strcmp(adcno,x.adcno)==0)
			return 0;
		c++;
	}

	return(c+deleted());
}


void password(char pass[])			
{
	int i=0;
	char ch;
	while(1)
	{
		ch=getch();
		if(ch==ENTER)
		{
			pass[i]='\0';
			break;
		}
		else if(ch==BKSP)
     	{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}	
    	}	
    	else if(ch==TAB||ch==SPACE)
	 		{
				continue;
	 		}
	 		else
	 		{
				pass[i]=ch;
				i++;
				printf("*");
	 		}
	}
}

void create()
{
	FILE *fp;
	bank x;
	
	int i=0;
	char ch;
	long signed c;
	fp=fopen(fname,"ab");
	system("cls");
	fflush(stdin);
	printf("\nenter adhar no.:");
	gets(x.adcno);
	c=accountno(x.adcno);
	
	if(c==0)
	{
		printf("\naccount already exist\n");
		getch();
		return;
	}
	else
	{
		fflush(stdin);
		printf("\nEnter full name:");
		gets(x.name);
		fflush(stdin);
		printf("\nEnter mobile no.:");
		gets(x.mobno);	
		fflush(stdin);
		printf("\nEnter address:");
		gets(x.add);
		printf("\naccount no:56781%d",c);
		x.accno=c;
		printf("\n\ncreate password:");
		password(x.pass);
		printf("\n\nenter amount to deposite:");
		scanf("%lf",&x.balamt);
		printf("\nyour account is created\n");
		fwrite(&x,sizeof(x),1,fp);
		printf("press any key to continue\n");
		getch();
		
	}
	fclose(fp);
}


int login(int accno)		
{
	FILE *fp;
	bank x;
	char pass[15];
	fp=fopen(fname,"rb");
	fflush(stdin);
	printf("\nenter password:");
	password(pass);	
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		if(accno==x.accno)
			return(strcmp(pass,x.pass)==0);
	}
}

void display(long signed accno)
{
	FILE *fp;
	bank x;
	fp=fopen(fname,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))	
			break;	
		if(accno==x.accno)
		{
			printf("\naccount no.:56781%lu\n",x.accno);
			printf("\nadhar no:%s\n",x.adcno);
			printf("\nmobile no:%s\n",x.mobno);
			printf("\naddress:%s\n",x.add);
			printf("\nbalance amount:%lf\n",x.balamt);
			printf("press any key to continue\n");
			getch();
		}
	}
}
void displayAll(int ch)
{
	FILE *fp;
	bank x;
	long signed tamt=0;
	if(ch==1)
	fp=fopen(fname,"rb");
	else
	fp=fopen(fdel,"rb");
	printf("\n========================================================\n\n");
	printf("\t\t All customers details\n\n");
	printf("========================================================\n\n");
	printf("account no\t\tname\t\tmobile no\tbalance\n");
	while(1)
	{
	fread(&x,sizeof(x),1,fp);
	if(feof(fp))	
		break;
	printf("56781%lu\t\t",x.accno);
	printf("%s\t\t",x.name);
	printf("%s\t",x.mobno);
	printf("%lf\n",x.balamt);
	tamt=tamt+x.balamt;
	}
	printf("\n========================================================\n\n");
	if(ch==1)
	printf("total amount in bank:%lu",tamt);
	printf("press any key to continue\n");
	getch();
	fclose(fp);
}

void delacc(long signed accno)
{
	FILE *fp,*fp1,*fp2;
	bank x,x1;
	int flag=1;
	char pass[15];
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
	fp2=fopen(fdel,"ab");
	
	fflush(stdin);
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		if(x.accno==accno)
		{
			fwrite(&x,sizeof(x),1,fp2);
		}
		else
		{
			flag=0;
			fwrite(&x,sizeof(x),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(fname,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp1);
		if(feof(fp1))
			break;
		fwrite(&x,sizeof(x),1,fp);
	}
	if(flag==0)
		printf("\naccount not exist\n");
	else
		printf("\nyour account now deleted\n");
	printf("press any key to continue\n");	
	getch();
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}

void deposit(long signed accno)
{
	FILE *fp,*fp1;
	bank t,t1;
	double deamt;
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(t.accno==accno)
		{		
			printf("\nEnter amount to deposit:");
			scanf("%lf",&deamt);
			t.balamt=t.balamt+deamt;
			printf("\n%lf is deposited\n",deamt);
			printf("\nbalance amount:%lf\n",t.balamt);
			printf("press any key to continue\n");
			getch();
			fwrite(&t,sizeof(t),1,fp1);
		}
		else	
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(fname,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp1);
		if(feof(fp1))	
			break;	
		fwrite(&t,sizeof(t),1,fp);
	}
	fclose(fp);
	fclose(fp1);
}

void withdraw(long signed accno)
{
	FILE *fp,*fp1;
	bank t,t1;
	double wdamt;
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");

	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(t.accno==accno)
		{	
			printf("\nbalance amount:%lf\n",t.balamt);	
			printf("\nEnter amount to withdraw:");
			scanf("%lf",&wdamt);
			if(wdamt<=t.balamt)
			{
				t.balamt=t.balamt-wdamt;
				printf("\n%lf is withdraw\n",wdamt);
				printf("\nbalance amount:%lf\n",t.balamt);
				printf("press any key to continue\n");
				getch();
				fwrite(&t,sizeof(t),1,fp1);
			}
			else
			{
				printf("\nlow balance in account\n");
				printf("press any key to continue\n");	
				getch();
				return;
			}
		}
		else	
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(fname,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp1);
		if(feof(fp1))	
			break;	
		fwrite(&t,sizeof(t),1,fp);
	}
	fclose(fp);
	fclose(fp1);
}

void transfer(long signed accno)
{
	FILE *fp,*fp1;
	bank t,t1;
	double tfamt;
	long signed tfacc;
	int flag=0;
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(t.accno==accno)
		{
			printf("balance amount:%lf",t.balamt);
			break;
		}
	}
	fclose(fp);
	printf("\nin which account you want to tranfer money:56781");
	scanf("%d",&tfacc);
	fp=fopen(fname,"rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(tfacc==t.accno)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
		}
	}
	fclose(fp);

	if(flag==1)	
	{
			printf("enter amount to transfer:");
	scanf("%lf",&tfamt);
	fp=fopen(fname,"rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(t.accno==accno)
		{
			if(t.balamt>=tfamt)
			{
				t.balamt=t.balamt-tfamt;
				printf("%lf transfered\n",tfamt);
				printf("balance amount:%lf\n",t.balamt);
				printf("press any key to continue\n");
				getch();
				fwrite(&t,sizeof(t),1,fp1);
			}
			else
			{
				printf("low balance\n");
				printf("press any key to continue\n");
				getch();
				return;
			}
		}
		else
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
		fp=fopen(fname,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp1);
		if(feof(fp1))	
			break;	
		fwrite(&t,sizeof(t),1,fp);
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(t.accno==tfacc)
		{
			t.balamt=t.balamt+tfamt;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(fname,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp1);
		if(feof(fp1))	
			break;	
		fwrite(&t,sizeof(t),1,fp);
	}
	fclose(fp);
	fclose(fp1);
	}
	else
	{
		printf("account does not exist\n");
		printf("press any key to continue\n");
		getch();
	}
}

int sylogin()
{
	FILE *fp;
	bank x;
	char pass[15];
	int i;
	fflush(stdin);
	printf("\nenter admin password:");
	password(pass);
	fp=fopen(fsypass,"rb");
	for(i=1;i==1;i++)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
		{
			return 1;
			
		}
		return(strcmp(pass,x.pass)==0);
	}
}

void newsypass()
{
	FILE *fp;
	bank x;
	if(sylogin())
	{
		fp=fopen(fsypass,"wb");
		printf("\nenter new password:");
		password(x.pass);
		fwrite(&x,sizeof(x),1,fp);
		fclose(fp);
		printf("\npassword updated\n");
		printf("press any key to continue\n");
		getch();
	}
	else
		printf("\nwroung password\n");
		printf("press any key to continue\n");
	getch();
}

long signed empdeleted()				
{
	FILE *fp;
	employee x;
	long signed d=0;
	fp=fopen(fempdel,"ab");
	fclose(fp);
	fp=fopen(fempdel,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		d++;
	}
	return d;
}


long signed empid()
{
	FILE *fp;
	employee x;
	long signed c=1;
	fp=fopen(femp,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		c++;
	}

	return(c+empdeleted());
}
void newemployee()
{
	FILE *fp;
	employee t1;

	fp=fopen(femp,"ab");

	fflush(stdin);
	printf("\nEnter name:");
	gets(t1.ename);
	printf("enter mobile no.:");
	gets(t1.emobno);
	printf("enter address:");
	gets(t1.eadd);
	t1.id=empid();
	printf("employee id:%d",t1.id);
	
	printf("\nenter salary:");
	scanf("%lf",&t1.sal);
	fwrite(&t1,sizeof(t1),1,fp);
	printf("\nnew employee info recorded\n");
	printf("press any key to continue\n");
	getch();
	fclose(fp);
}

void empdisplayAll(int ch)
{
	FILE *fp;
	employee x;
	if(ch==1)
	fp=fopen(femp,"rb");
	else
	fp=fopen(fempdel,"rb");
	printf("\n========================================================\n\n");
	printf("\t\t All employee details\n\n");
	printf("========================================================\n\n");
	printf("Id\t\tname\t\tmobile no\tsalary\n");
	while(1)
	{
	fread(&x,sizeof(x),1,fp);
	if(feof(fp))	
		break;
	printf("%lu\t\t",x.id);
	printf("%s\t\t",x.ename);
	printf("%s\t",x.emobno);
	printf("%lf\n",x.sal);
	
	}
	printf("\n========================================================\n\n");
	
	printf("press any key to continue\n");
	getch();
	fclose(fp);
}

void delemp()
{
	FILE *fp,*fp1,*fp2;
	employee x,x1;
	int flag=1,id;
	
	fp=fopen(femp,"rb");
	fp1=fopen("temp.dat","wb");
	fp2=fopen(fempdel,"ab");
	
	fflush(stdin);
	printf("enter employee id to delete:");
	scanf("%d",&id);
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		if(x.id==id)
		{
			flag=1;
			fwrite(&x,sizeof(x),1,fp2);
		}
		else
		{
			flag=0;
			fwrite(&x,sizeof(x),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	fp=fopen(femp,"wb");
	fp1=fopen("temp.dat","rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp1);
		if(feof(fp1))
			break;
		fwrite(&x,sizeof(x),1,fp);
	}
	if(flag==0)
		printf("\nid not found\n");
	else
		printf("\nemployee details deleted\n");
	printf("press any key to continue\n");
	getch();
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}

void empdisplay()
{
	FILE *fp;
	employee x;
	int id,flag=0;
	fp=fopen(femp,"rb");
	printf("\nenter employee id:");
	scanf("%d",&id);
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))	
			break;	
		if(id==x.id)
		{	
			flag=1;
			printf("\nID.:%lu\n",x.id);
			printf("\nname:%s\n",x.ename);
			printf("\nmobile no:%s\n",x.emobno);
			printf("\naddress:%s\n",x.eadd);
			printf("\nsalary:%lf\n",x.sal);
			printf("press any key to continue\n");
			getch();
		}
	}
	if(flag==0)
	{
		printf("\nid not found\n");
		printf("press any key to continue\n");
		getch();
	}	
}

void bankdetails()
{
	FILE *fp;
	bank x;
	employee t;
	long signed tacc=0; 
	double tamt;
	fp=fopen(fname,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		tacc++;
		tamt=tamt+x.balamt;
	}
	printf("\ntotal no. of accounts present:%lu\n",tacc);
	printf("\ntotal amount present in bank:%lf\n",tamt);
	fclose(fp);
	tacc=0;
	fp=fopen(fdel,"rb");
	while(1)
	{
		fread(&x,sizeof(x),1,fp);
		if(feof(fp))
			break;
		tacc++;
	}
	printf("\ntotal no. of deleted accounts:%lu\n",tacc);
	fclose(fp);
	printf("press any key to continue\n");
	getch();
}

void main()
{
	int ch;
	int accno,c=0;
	char ch1;
	system("color f0");
	while(1)
	{
		system("cls");
		printf("1:create an account\n\n2:customer login\n\n3:system login\n\n4:exit\n\nenter your choice: ");
		scanf("%d",&ch);
		if(ch==4)
			break;
		switch(ch)
		{
			case 1:create();
				break;
			case 2:while(1)
					{
						system("cls");
						printf("\nenter account no:56781");
						scanf("%d",&accno);
						c=login(accno);
						if(c==1)
						{
							while(1)
							{
								system("cls");
								printf("1:deposit amount\n\n2:withdraw amount\n\n3:transfer\n\n4:account details\n\n5:delete account\n\n6:log out\n\nenter your choice:");
								scanf("%d",&ch);
								if(ch==6)
									break;
								switch(ch)
								{
									case 1:system("cls");
										deposit(accno);
										break;
									case 2:system("cls");
										withdraw(accno);
										break;
									case 3:system("cls");
										transfer(accno);
										break;
									case 4:system("cls");
										display(accno);
										break;
									case 5:system("cls");
										printf("you want to delete your account(y/n):");
										fflush(stdin);
										scanf("%c",&ch1);
										if(ch1=='y')
											delacc(accno);
										goto lb;
										break;
									default:printf("invalid choice\n");
								}
							}
						lb:	break;
						}
						else
							printf("\n\naccount no. and password not matching\n");
							printf("press any key to continue\n");
						getch();
					}
				break;
			case 3:while(1)
				{
					system("cls");
					if(sylogin())
					{
						while(1)
						{
							system("cls");
							printf("1:display all accounts\n\n2:display all deleted accounts\n\n3:new system password\n\n4:add new employee\n\n5:remove employee\n\n");
							printf("6:employee details\n\n7:display all employee details\n\n8:display all removed employee details\n\n9:bank details\n\n10:logout\n\n");
							printf("enter your choice:");
							scanf("%d",&ch);
							if(ch==10)
								break;
							switch(ch)
							{
								case 1:system("cls");
									displayAll(ch);
									break;
								case 2:system("cls");
									displayAll(ch);
									break;
								case 3:system("cls");
									newsypass();							
									break;
								case 4:system("cls");
									newemployee();
									break;
								case 5:system("cls");
									delemp();
									break;
								case 6:system("cls");
									empdisplay();
									break;
								case 7:system("cls");
									empdisplayAll(1);
									break;
								case 8:system("cls");
									empdisplayAll(2);
									break;
								case 9:system("cls");
									bankdetails();
									break;
								default:printf("invalid choice\n");
							}
						}
						break;
					}
					else
						printf("\nwroung password\n");
					getch();
				}
				break;
			default:printf("invalid choice\n");
		}
	}
}
