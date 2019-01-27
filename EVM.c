#include<stdio.h>
#include"conio.h"
#include"conio.c"
#include<string.h>
#include<math.h>
#include<stdlib.h>

void find_id();
void admin();
void find_pass();
void confirm();
void display();

int found,curpos;
int votes[4],temp;
int adminid=9597;
char adminpass[20]="Admin4444";

struct voter
{
    char name[101];
    int id;
    char password[101];
    char address[401];
    int count;
}v1;

void main()
{
    clrscr();
    printf("---------------------------Welcome to the EVM Machine---------------------------\n\n\n");
    admin();
    clrscr();
    main();
}

void admin()
{
	char pass[20];
	int ch,id;
	FILE *v;
	v=fopen("Voters","a+");
	fseek(v,0,0);
	printf("Enter Administrator's ID:");
	scanf("%d",&id);
	if(id==adminid)
	{
		printf("Enter Admin's password:");
		scanf("%s",pass);
		if(strcmp(adminpass,pass)==0)
		{
			gotoxy(30,6);
			printf("\nWelcome Administrator.\nWhat you want to do. Make a choice.\n");
			printf("1. Press the ballot button\n2. Add Voter\n3. Edit a Voter\n4. Display all Voters\n5. Stop the EVM and display the result.\n");
			scanf("%d",&ch);
			switch(ch)
			{
			case 1:
			clrscr();
			find_id();
			break;

			case 2:
			fseek(v,0,2);
			printf("Enter Voter Name:");
			scanf("%s",&v1.name);
			printf("Enter Voter ID:");
			scanf("%d",&v1.id);
			printf("Enter Voter Password:");
			scanf("%s",&v1.password);
			printf("Enter Voter Address:");
			scanf("%s",&v1.address);
			fwrite(&v1,sizeof(v1),1,v);
			printf("Voter Entered successfully.\n");
			break;

			case 3: //edit voter
			printf("Enter Voter ID to edit:");
			scanf("%d",&id);
			fseek(v,0,0);
			curpos=0;
			while(fread(&v1,sizeof(v1),1,v)==1)
			{
				if(v1.id==id)
				{
					printf("Enter Voter name:");
					scanf("%s",v1.name);
					printf("Enter Voter's Password:");
					scanf("%d",&v1.password);
					printf("Enter Voter Address:");
					scanf("%s",v1.address);
					v1.count=1;
					fseek(v,curpos,0);
					fwrite(&v1,sizeof(v1),1,v);
					printf("Voter's details updated successfully.\n");
				}
			}

			case 4://display all voters
			while(fread(&v1,sizeof(v1),1,v)==1)
			{
				printf("Voter's Name: %s\nVoter's ID: %d\nVoter's Password: %s\nVoter's Address: %s\nVoter's chance for voting: %d\n",v1.name,v1.id,v1.password,v1.address,v1.count);
			}
			printf("All displayed successfully.");
			getch(); getch();
			break;

			case 5:
			display();
			exit(0);
			break;

			default:
			printf("Make proper choice.");
			admin();
			}
		}
		else
		{
			printf("Entered Password is incorrect.");
			admin();
		}
	}
	else
	{
		printf("ADMINISTRATOR ID INCORRECT.");
		admin();
	}
}

void find_id()
{
	int i,j;
	FILE *v;
	v=fopen("Voters","a+");
	fseek(v,0,0);
	printf("Enter a voter's ID:");
	scanf("%d",&i);

	fseek(v,0,0);
		while(fread(&v1,sizeof(v1),1,v)==1)
		{
		     if(v1.id==i)
			{
				if(v1.count==1)
				{
					printf("\n\nVoter Name=%s\nVoter ID:%d\nVoter Address:%s",v1.name,v1.id,v1.address);
					fwrite(&v1,sizeof(v1),1,v);
					found=1;
					confirm();
					break;
				}
				else
				{
					printf("\nSorry you cannot vote twice.");
					admin();
				}
				break;
			}
		}
	 fclose(v);
}

void confirm()
{
    char c,t;

    if(found==1)
    {
	printf("\n\nAre you sure you are the above person?\n\t\tYes:y\t\tNo:n\n");
	getchar();
	scanf("%c",&c);

	if(c=='y')
	{
		find_pass();
	}
	 else if(c=='n')
	{
		find_id();
	}
    }
    else
    {
	printf("Enter Proper ID:");
	find_id();
    }
}

void find_pass()
{
	char pass[101];
	FILE *v;
	v=fopen("Voters","a+");
	fseek(v,curpos,0);
	printf("\nEnter your password:");
	scanf("%s",&pass);
	if(strcmp(v1.password,pass)==0)
	{

		int vote;
		clrscr();
		gotoxy(30,6);
		gotoxy(10,1);
		printf("The Different Parties Fighting Elections are As follows:");
		gotoxy(15,3);
		printf("<1> Spidy Baba Party 	-	 \"KUNAL JAIN\"");
		gotoxy(15,5);
		printf("<2> Jigga Baka Party 	-	 \"JAGDISH PATIL\"");
		gotoxy(15,7);
		printf("<3> Bhai Bhai Party 	-	 \"PARTH PATEL\"");
		gotoxy(15,9);
		printf("<4> Har Har Modi Party 	-	 \"ZEEL MODI\"");
		gotoxy(15,15);
		printf("	PLEASE ENTER AN ASSIGNED NUMBER TO VOTE ===> ");
		scanf("%d",&vote);
		v1.count=0;
		fwrite(&v1,sizeof(v1),1,v);
		if(vote==1)
		{
		votes[0]++;
		}
		else if(vote==2)
		{
		votes[1]++;
		}
		else if(vote==3)
		{
		votes[2]++;
		}
		else if(vote==4)
		{
		votes[3]++;
		}
		clrscr();
		gotoxy(15,10);
		printf("Your Vote Has been saved.THANK YOU for Voting.\n");
	}
	else
	{
		printf("Wrong Password !\nTry Again.");
		find_id();
	}
}

void display()
{
	printf("Votes of Respected Parties:");
	printf("Spidy Baba Party - %d\nJigga Baka Party - %d\nBhai Bhai Party - %d\nHar Har Modi Party - %d",votes[0],votes[1],votes[2],votes[3]);
	getch();
}
