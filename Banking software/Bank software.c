#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
// function declaration
void register_account();
void login();
void bal_show();
void bal_add();
void bal_withdraw();
void bal_transfer();
struct customer
{
	char name[20];
	char phone[50];
	char acc[50];
	char password[50];
	float balance;
} c;
//global variable for login portal and transfer portal.
char check_number[50]; 
char check_password[50];
int main()
{
	char first_choice;
	while (first_choice != '3')
	{		
		system("cls"); // Main Menu.
		system("color B0");
		printf("\n\t\t\t||===================================================||");
		printf("\n\t\t\t||                                                   ||");
		printf("\n\t\t\t||---------------------------Banking Software--------||");
		printf("\n\t\t\t||                                                   ||");
		printf("\n\t\t\t||===================================================||");
		printf("\n\t\t\t||          1: Register Your Account                 ||");
		printf("\n\t\t\t||---------------------------------------------------||");
		printf("\n\t\t\t||          2: Login      			       	                 ||");
		printf("\n\t\t\t||---------------------------------------------------||");
		printf("\n\t\t\t||          3: Exit    					                 ||");
		printf("\n\t\t\t||===================================================||");
		printf("\n\t\t\t||  Please Enter Your Choice:: ");
		scanf("\t\t\t\t%c", &first_choice);
		printf("\t\t\t||===================================================||");
		switch(first_choice) 
		{
			case '1':
			register_account();// register the user
			break;			
			case '2':
			login();//login user
			break;			
			case '3':
			break;//exit from program			
			default:
			printf("\n\t\t\t|| Enter Correct Option.                             ||");
			printf("\n\t\t\t||===================================================||");
			getch();	
		}//switch end							
	}
}
void register_account()
{
		FILE *fp;
 			system("color 0C");
 			int i;
 			char ch;
			char file_name[50];
			system("cls");			
			printf("\n||===================================================||");
			printf("\n||                                                   ||");
			printf("\n||----------------------------REGISTER YOUR ACCOUNT--||");
			printf("\n||                                                   ||");
			printf("\n||===================================================||");
			printf("\n||          Enter Your Name : ");
			scanf("%s", c.name);			
			fflush(stdin);
			printf("\n||---------------------------------------------------||");
			printf("\n||          Enter Your Phone Number : ");
			scanf("%s", c.phone);
			printf("\n||---------------------------------------------------||");
			printf("\n||          Enter Your Account Number : ");
			scanf("%s", c.acc);
			printf("\n||---------------------------------------------------||");
			printf("\n||          Create Your Password : ");
				while((ch=getch())!='\r')   // '\r' carriage return;
			{
				if(ch=='\b') 			   //'\b' backspace
				{
					if(i>0)
					{
						i--;
						printf("\b \b");
					}
				}
				else
				{
				c.password[i]=ch;
				i++;
				printf("*"); //mask the password
			}
			}
			c.password[i]='\0';
			printf("\n||===================================================||");
			strcpy(file_name, c.phone);
			strcat(file_name, ".txt");
			fp = fopen(file_name, "r"); // use number of user as File Name eg:- 9876543210.txt is file name for user with that nunber
			if (fp != NULL)				// if account is already exist then it output the existed error.
			{
				printf("\n\n Account Already Registered !!!!!");
				fclose(fp);
				getch();
			}
			else
			{
				fclose(fp);
				fp = fopen(file_name, "w");
				if (fp == NULL)
				{
					printf("\n\t\t\t\t Error!!!");
				}
				else
				{
					fwrite(&c, sizeof(struct customer), 1, fp);
					printf("\nYour Account is Successfully Registered ");
					fclose(fp);
				}
				getch();
			}	
}
void login()
{
			FILE *fp;
			system("color 60");
			system("cls");
			char ch;
			int i=0;
			printf("\n||===================================================||");
			printf("\n||----------------------------LOGIN PORTAL-----------||"); // login
			printf("\n||===================================================||");
			printf("\n|| Enter Your Phone Number : ");
			scanf("%s", check_number);
			printf("||---------------------------------------------------||");
			printf("\n|| Enter Your Password : ");						
			//take each character input from keyboard and store each caracter as array in check_password
				while((ch=getch())!='\r')   // '\r' carriage return;
			{
				if(ch=='\b') 			   //'\b' backspace
				{
					if(i>0)
					{
						i--;
						printf("\b \b");
					}
				}
				else
				{
				check_password[i]=ch;
				i++;
				printf("*"); //mask the password
			}
			}
			check_password[i]='\0';
			printf("\n||---------------------------------------------------||");
			strcat(check_number, ".txt");
			fp = fopen(check_number, "r");			
			// if check number and original number is not matched then it display the Not found error.
			if (fp == NULL)
			{
				printf("\n|| Account not found. Please register first.         ||");
				printf("\n||===================================================||");			
			}
			else // if matched then execute the password checking script
			{
				fread(&c, sizeof(struct customer), 1, fp);
				if (strcmp(c.password, check_password) == 0)
				{					
					char second_choice;
					while (second_choice!='5') 
					{
						system("color E5");
						system("cls");
						printf("\n||===================================================||");
						printf("\n||                                                   ||");
						printf("\n||----------------------------DASHBOARD--------------||");
						printf("\n||                                                   ||");
						printf("\n||===================================================||");
						printf("\n||          1: Show Balance                          ||");
						printf("\n||---------------------------------------------------||");
						printf("\n||          2: Add Balance                           ||");
						printf("\n||---------------------------------------------------||");
						printf("\n||          3: Withdraw Balance                      ||");
						printf("\n||---------------------------------------------------||");
						printf("\n||          4: Transfer Balance                      ||");
						printf("\n||---------------------------------------------------||");
						printf("\n||          5: Logout                                ||");
						printf("\n||===================================================||");
						printf("\n||  Please Enter Your choice:: ");
						scanf("%c", &second_choice);
						if(second_choice=='\n')  //prevent the flow of program to go automatically in default case
						{
							continue;
						}	
						switch (second_choice)
						{
						case '1':
							bal_show();
							break;
						case '2':
							bal_add();
							break;
						case '3':
							bal_withdraw();
							break;
						case '4':
							bal_transfer();
							break;
						case '5':
							return;
						default:
							printf("\n|| Please Enter correct option                       ||");
							printf("\n||===================================================||\n");
							getch();
						}
					}
				}				
				else
				{
					printf("\n|| Incorret Password                                 ||");
					printf("\n||===================================================||");
				}
			}
			fclose(fp);
			getch();	
}
void bal_show()
{
	system("color B0");
	FILE *fp;
	system("cls");
	printf("\n||===================================================||");
	printf("\n||-------------------------ACCOUNT BALANCE-----------||");
	printf("\n||===================================================||");
	fp = fopen(check_number, "r"); // open the user file as c.phone and check number is same.
	if (fp == NULL)
	{
		printf("\n Failed To Show Balance ");
	}
	else
	{
		fread(&c, sizeof(struct customer), 1, fp);
		printf("\n|| Balance : %0.2f\t\t\t\t\t\t\t ||",c.balance);
		printf("\n||===================================================||");
		fclose(fp);
		getch();
	}
}
void bal_add() // function to add balance
{
	float adding_amount;
	FILE *fp;
	fp = fopen(check_number, "w");
	system("cls");
	printf("\n||===================================================||");
	printf("\n||------------------------------ADD BALANCE----------||");
	printf("\n||===================================================||");
	printf("\n|| Enter The Amount : ");
	scanf("%f", &adding_amount);
	printf("||---------------------------------------------------||");
	c.balance += adding_amount; // add deposited balance to user balance.
	fwrite(&c, sizeof(struct customer), 1, fp);
	if (fwrite != NULL)
	{
		printf("\n|| Successfully Added %0.2f Amount\t\t\t\t\t ||",adding_amount);		
	}
	else
	{
		printf("\n\t\t\t\t Error Adding Balance");
	}
	printf("\n||===================================================||");
	fclose(fp);
	getch();
}
void bal_withdraw()
{
	system("color C0");
	system("cls");
	printf("\n||===================================================||");
	printf("\n||-------------------------WITHDRAW BALANCE----------||");
	printf("\n||===================================================||");
	float withdraw_balance;
	FILE *fp;
	fp = fopen(check_number, "r");
	if (fp == NULL)
	{
		printf("\n|| Error!!!                                          ||");
		printf("\n||===================================================||");
	}
	else
	{
		fread(&c, sizeof(struct customer), 1, fp);
		printf("\n|| Enter Withdraw Amount : ");
		scanf("%f", &withdraw_balance);
		printf("||---------------------------------------------------||");
		if (withdraw_balance <= c.balance)
		{
			fclose(fp); //close file in read mode and open in write mode
			fp = fopen(check_number, "w");
			c.balance -= withdraw_balance;
			fwrite(&c, sizeof(struct customer), 1, fp); //update the balance of the user in its file.
			if (fwrite != NULL)
			{
				printf("\n|| Successfully withdraw %0.2f Amount", withdraw_balance);
				printf("\n||===================================================||");
				fclose(fp);
			}
			else
			{
				printf("\n|| Failed to Withdraw\n");
				printf("\n||===================================================||");
				fclose(fp);
			}
		}
		else
		{
			printf("\n|| Be Sure You Have Enough Balance                   ||");
			printf("\n||===================================================||");
			fclose(fp);
		}
	}
	getch();
}
void bal_transfer()
{
	system("color 87");
	FILE *fp_sender, *fp_receiver;
	char receiver_number[50];
	float transfer_amount;
	system("cls");
	printf("\n||===================================================||");
	printf("\n||-------------------------BALANCE TRANSFER----------||");
	printf("\n||===================================================||");
	printf("\n|| Enter the Receiver Phone Number : ");
	scanf("%s", receiver_number);
	printf("||---------------------------------------------------||");
	printf("\n|| Enter Amount : ");
	scanf("%f", &transfer_amount);
	printf("||---------------------------------------------------||");
	strcat(receiver_number, ".txt");
	fp_receiver = fopen(receiver_number, "r"); // open the receiver file
	if (fp_receiver == NULL)				   // check wheather there is file of receiver or not if not it print the error message
	{
		printf("\n|| Receiver Account Not Registered 					 ||");
		printf("\n||---------------------------------------------------||");
	}
	else
	{
		if(strcmp(receiver_number,check_number)==0)
		{
			printf("\n|| Cannot Transfer On Same Account         ||");
			printf("\n||---------------------------------------------------||");
		}
		else
		{		
		fclose(fp_receiver);				  // close the receiver file
		fp_sender = fopen(check_number, "r"); // open the sender file in read mode
		fread(&c, sizeof(struct customer), 1, fp_sender);
		if (transfer_amount <= c.balance)
		{
			fclose(fp_sender);					  // close the sender file.
			fp_sender = fopen(check_number, "w"); // open the sender file in write mode
			c.balance -= transfer_amount;		  // deduct the amount from the file of sender .
			fwrite(&c, sizeof(struct customer), 1, fp_sender);
			 if (fwrite != NULL ) // check if the value return by fwrite function  it not NULL.
			{
				fclose(fp_sender);
				fp_receiver = fopen(receiver_number, "r+"); // first open in read mode and in write mode to make the sturcture active to update the file and  to write in the file.
				fread(&c, sizeof(struct customer), 1, fp_receiver);
				c.balance += transfer_amount; // add the amount into receiver file.
				rewind(fp_receiver);
				fwrite(&c, sizeof(struct customer), 1, fp_receiver);
				printf("\n|| Successfully Transfer %0.2f Amount ", transfer_amount);
				printf("\n||---------------------------------------------------||");
				fclose(fp_receiver);
			}
			else
			{
				printf("\n|| Failed to Transfer Balance");
				printf("||---------------------------------------------------||");
				fclose(fp_sender);
			}
		}
		else
		{
			printf("\n|| Insufficient Balance                              || ");
			printf("\n||---------------------------------------------------||");
			fclose(fp_sender);
 		}
	}
	}
	getch();
}
