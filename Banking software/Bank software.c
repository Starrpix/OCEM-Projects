#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void bal_show();
void bal_add();
void bal_withdraw();
void bal_transfer();
struct customer
{
	char name[20],phone[50],acc[50],password[50];
	float balance;
}c;
char check_number[50];
char check_password[50];
int main()
{
	FILE *fp;
	int first_choice;
	while(first_choice!=3)
	{
		//level for goto control structure 
		dash:	
	system("cls");
	printf("\n\t\t\t\t------------Banking Software------------\n");
	printf("\n\t\t\t\t 1: Register Your Account\n");
	printf("\n\t\t\t\t 2: Login\n");
	printf("\n\t\t\t\t 3: Exit\n");
	printf("\n\t\t\t\t Enter your Choice : ");
	scanf("%d",&first_choice);

	if(first_choice==1)
	{
	char file_name[50];
	system("cls");
	printf("\n\t\t\t\t------------REGISTER YOUR ACCOUNT------------\n");	
	printf("\n\t\t\t\t Enter Your Name : ");
	scanf("%s",c.name);
	printf("\n\t\t\t\t Enter Your Phone Number : ");
	scanf("%s",c.phone);
	printf("\n\t\t\t\t Enter Your Account Number : ");
	scanf("%s",c.acc);
	printf("\n\t\t\t\t Create Your Password : ");
	scanf("%s",c.password);
	
	strcpy(file_name,c.phone);
	strcat(file_name,".txt");
	fp=fopen(file_name,"r");
	if(fp!=NULL)
	{
		printf("\n\n\t\t\t\t Account Already Registered !!!!!");
		fclose(fp);
		getch();
	}
	else
	{
	fclose(fp);
		
	fp=fopen(file_name,"w");
	if(fp==NULL)
	{
		printf("\n\t\t\t\t Error!!!");
	}
	else
	{


	fwrite(&c,sizeof(struct customer),1,fp);	//writes into the file 
	printf("\n\t\t\t\t Your Account is Successfully Registered ");
	fclose(fp);
	}
	getch();
	}
	}
	if(first_choice==2)
	{
	
	
		system("cls");
		printf("\n\t\t\t\t------------LOGIN PORTAL------------\n");
		printf("\n\t\t\t\t Enter Your Phone Number : ");
		scanf("%s",check_number);
		printf("\n\t\t\t\t Enter Your Password : ");
		scanf("%s",check_password);
		strcat(check_number,".txt");
		fp=fopen(check_number,"r");
	
		  if(fp==NULL)
            {
                printf("\n\t\t\t\t Account not found. Please register first.\n");
                getch();
                continue;
            }
           else 
			{
			fread(&c,sizeof(struct customer),1,fp); // it will take data from file to structure
			if(strcmp(c.password,check_password)==0)
			{
				int second_choice;
					   		 //char ans='\t';
				while(1) 		// (ans!='\n') //use this condition to eliminate the use of goto statement.
					{
				
				system("cls");
				printf("\n\t\t\t\t------------DASHBOARD------------\n");
				printf("\n\t\t\t\t 1: Show Balance\n");
				printf("\n\t\t\t\t 2: Add Balance\n");
				printf("\n\t\t\t\t 3: Withdraw Balance\n");
				printf("\n\t\t\t\t 4: Transfer Balance\n");
				printf("\n\t\t\t\t 5: exit\n");
				printf("\n\t\t\t\t Enter your choice : ");
				scanf("%d",&second_choice);
				
				switch(second_choice)
					{
					case 1:
						bal_show();
						break;
					case 2:
						bal_add();
						break;
					case 3:
						bal_withdraw();
						break;
					case 4:
						bal_transfer();
						break;	
					case 5:
					goto dash;
				    	
					default:
						printf("\n\t\t\t\t Please Enter correct option");
					}
				//	printf("\n\n\n\t\t\t\t DO YOU WANT TO CONTINUE TRANSACTION [Y/N]");
				//	ans=getch(); 
				}
			}
			else
			{
				printf("\n\t\t\t\t Incorret Password");
			}
		}
		fclose(fp);//point to noted	
		getch();
	}
	}
	
	
}

void bal_show()
{
		FILE *fp;
		system("cls");
		printf("\n\t\t\t\t------------ACCOUNT BALANCE------------\n");
		fp=fopen(check_number,"r");
		if(fp==NULL)
		{
			printf("\n\t\t\t\t Failed To Show Balance ");
		}
		else
		{
		fread(&c,sizeof(struct customer),1,fp);
		printf("\n\t\t\t\t Balance : %0.2f",c.balance);
		fclose(fp);
		getch();
		}
}

void bal_add()   //function to add balance
{
		float adding_amount;	
		FILE *fp;
		fp=fopen(check_number,"w");   
		system("cls");
		printf("\n\t\t\t\t------------ADD BALANCE------------\n");
		printf("\n\t\t\t\t Enter The Amount : ");
		scanf("%f",&adding_amount);
		c.balance+=adding_amount;
		
		fwrite(&c,sizeof(struct customer),1,fp);
		if(fwrite!=NULL)
		{
			printf("\n\t\t\t\t Successfully Added %0.2f Amount ",adding_amount);
		}
		else
		{
			printf("\n\t\t\t\t Error Adding Balance");
		}
		
		fclose(fp);
		
				getch();
}

void bal_withdraw()
{
		system("cls");
		printf("\n\t\t\t\t------------WITHDRAW BALANCE------------\n");
		float withdraw_balance;
		FILE *fp;
		fp=fopen(check_number,"r");
		if(fp==NULL)
		{
			printf("\n\t\t\t\t Error!!!\n");
		}
		else
		{
			fread(&c,sizeof(struct customer),1,fp);//whatever was in file it is stored in structure
			printf("\n\t\t\t\t Enter Withdraw Amount : ");
			scanf("%f",&withdraw_balance);
			if(withdraw_balance<=c.balance)
			{
				
				fclose(fp);
				fp=fopen(check_number,"w");
				c.balance-=withdraw_balance;
				fwrite(&c,sizeof(struct customer),1,fp);
				if(fwrite!=NULL)
				{
					printf("\n\t\t\t\t Successfully withdraw %0.2f Amount",withdraw_balance);
					fclose(fp);
				}
				else
				{
					printf("\n\t\t\t\t Failed to Withdraw\n");
					fclose(fp);
				}
			
			}
			else
			{
				printf("\n\t\t\t\t Be Sure You Have Enough Balance\n");
				fclose(fp);
			}
			
			
		}
		getch();
}

void bal_transfer()
{
    FILE *fp_sender, *fp_receiver;
    char receiver_number[50];
    float transfer_amount;
    system("cls");
    printf("\n\t\t\t\t------------BALANCE TRANSFER------------\n");
    printf("\n\t\t\t\t Enter the Receiver Phone Number : ");
    scanf("%s", receiver_number);    
    printf("\n\t\t\t\t Enter Amount : ");
    scanf("%f", &transfer_amount);
    strcat(receiver_number, ".txt");
    fp_receiver = fopen(receiver_number, "r");//open the receiver file
    if(fp_receiver == NULL)   //check wheather there is file of receiver or not if not it print the error message
    {
        printf("\n\t\t\t\t Receiver Account Not Registered ");
    }
    else
    {   
        fclose(fp_receiver); //close the receiver file
        fp_sender = fopen(check_number, "r");//open the sender file in read mode
        fread(&c, sizeof(struct customer), 1, fp_sender);
        if(transfer_amount <= c.balance)
        {
            fclose(fp_sender);//close the sender file.
            fp_sender = fopen(check_number, "w");//open the sender fiel in write mode
            c.balance -= transfer_amount; //deduct the amount from the file of sender .
            fwrite(&c, sizeof(struct customer), 1, fp_sender);
            if(fwrite != NULL && fwrite(&c, sizeof(struct customer), 1, fp_sender) == 1)  //check if the value return by fwrite function is equal to number of element of structure named customer or not, and it not NULL.
            {
                fclose(fp_sender);
                fp_receiver = fopen(receiver_number, "r+"); //first open in read mode and in write mode to make the sturcture active to update the file and  to write in the file. 
                fread(&c, sizeof(struct customer), 1, fp_receiver);
                c.balance += transfer_amount; //add the amount into receiver file.
                rewind(fp_receiver);
                fwrite(&c, sizeof(struct customer), 1, fp_receiver);
                printf("\n\t\t\t\t Successfully Transfer %0.2f Amount ", transfer_amount);
                fclose(fp_receiver);
            }
            else
            {
                printf("\n\t\t\t\t Failed to Transfer Balance ");
                fclose(fp_sender);
            }
        }
        else
        {
            printf("\n\t\t\t\t Insufficient Balance ");
            fclose(fp_sender);
        }
    }
    getch();
}


