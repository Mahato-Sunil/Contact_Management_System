/*Simple Contact Management System*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void menu();
void contact_list();
void search_contact();
void add_contact();
void edit_contact();
void delete_contact();
void exit_message();
void clear_screen();
void return_to_menu();

struct contact
{
	char contact_fname[20];
	char contact_lname[20];
	char number[10];
};
struct contact user;

long int offsetposition;
int flag = 0;
int ch = 0;
char temp_request[100] = {0};
char has_record = 'n';

FILE *fp, *temp;

// main function
void main()
{
	char exit_program = 'n';
	do
	{
		menu();
		int user_request;
		printf("\n Enter Your choice : \t");
		scanf("%d", &user_request);
		switch (user_request)
		{
		case 1:
			contact_list();
			break;
		case 2:
			search_contact();
			break;
		case 3:
			add_contact();
			break;
		case 4:
			edit_contact();
			break;
		case 5:
			delete_contact();
			break;
		case 6:
			exit_program = 'y';
			break;
		default:
			printf("\n The request is cancelled : Invalid choice !");
		}
	}
	 while (exit_program != 'y');
	exit_message();
}

// function to show menu
void menu()
{
	clear_screen();
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	printf("\n############################################################");
	printf("\n\t #########\t [ 1 ] >> [  LIST ]\t#########");
	printf("\n\t #########\t [ 2 ] >> [ SEARCH ]\t#########");
	printf("\n\t #########\t [ 3 ] >> [ ADD ]\t#########");
	printf("\n\t #########\t [ 4 ] >> [ EDIT]\t#########");
	printf("\n\t #########\t [ 5 ] >> [ DELETE ]\t#########");
	printf("\n\t #########\t [ 6 ] >> [ EXIT ]\t#########");
	printf("\n************************************************************");
	printf("\n############################################################");
}

// functions to add contacts
void add_contact()
{
	clear_screen();
	char file_ch = 'y';
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	printf("\n Add your Contact details here :\n");
	fp = fopen("/storage/emulated/0/HOME/Contact Management System/contact.dat", "a");
	if (fp == NULL)
	{
		fprintf(stderr, "\n\t Error :  %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while (file_ch != 'n')
	{
		printf("\n First Name : \t");
		scanf("%s", user.contact_fname);
		printf(" Last Name : \t");
		scanf("%s", user.contact_lname);
		printf(" Contact Number  : \t");
		scanf("%s", user.number);
		fwrite(&user, sizeof(user), 1, fp);
		printf(" Do you want to continue ?\t");
		scanf("%s", &file_ch);
	}
	fclose(fp);
	return_to_menu();
}

//function to show contact list
void contact_list()
{
	clear_screen();
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Contact Management System/contact.dat", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		rewind(fp);
		printf("\n Preparing to read the data ! \n");
		printf("\n \t Name : \t\t Number : ");
		printf("\n\t________________________________________");
		while (fread(&user, sizeof(user), 1, fp))
		{
			printf("\n\t %s  %s \t\t %s ", user.contact_fname, user.contact_lname, user.number);
			printf("\n\t________________________________________");
		}
	}
	else
	{
		printf("\n The contact list is empty. Please add new contacts to show in the list .");
	}
	fclose(fp);
	return_to_menu();
}

//function to search contact
void search_contact()
{
	clear_screen();
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Contact Management System/contact.dat", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the  name to search :\t");
		scanf("%s", temp_request);
		printf("\n Searching for possible result....");
		rewind(fp);
		while (fread(&user, sizeof(user), 1, fp))
		{
			if (strcmp(temp_request, user.contact_fname) == 0)
			{
				printf("\n\t %s  %s \t %s", user.contact_fname, user.contact_lname, user.number);
				has_record = 'y';
			}
		}
		if (has_record == 'n')
			printf("\n Sorry the Number you are trying to search is not found in the list");
	}
	fclose(fp);
	return_to_menu();
}

//function to edit contact
void edit_contact()
{
	clear_screen();
	struct contact edit;
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Contact Management System/contact.dat", "r");
	temp = fopen("/storage/emulated/0/HOME/Contact Management System/temp.dat", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the number to edit :\t");
		scanf("%s", temp_request);
		rewind(fp);
		while (fread(&user, sizeof(user), 1, fp))
		{
			if (strcmp(temp_request, user.number) == 0)
			{
				printf("\n Do you want to edit the following record :\n 1 : Yes , 0 :No?");
				printf("\n%s %s \t%s \t", user.contact_fname, user.contact_lname, user.number);
				scanf("%d", &ch);
				if (ch == 1)
				{
					printf("\n New First Name : \t");
					scanf("%s", edit.contact_fname);
					printf(" New Last Name : \t");
					scanf("%s", edit.contact_lname);
					printf(" New Contact Number (if any) : \t");
					scanf("%s", edit.number);
					fwrite(&edit, sizeof(edit), 1, temp);
				}
				else
					return;
			}
			else
				fwrite(&user, sizeof(user), 1, temp);
		}
	}
	fclose(fp);
	fclose(temp);
	remove("contact.dat");
	rename("temp.dat", "contact.dat");
	return_to_menu();
}

//function to remove contact
void delete_contact()
{
	clear_screen();
	errno = 0;
	printf("\n************************************************************");
	printf("\n\t Welcome to Contact Management System ");
	printf("\n************************************************************");
	fp = fopen("/storage/emulated/0/HOME/Contact Management System/contact.dat", "r");
	temp = fopen("/storage/emulated/0/HOME/Contact Management System/temp.dat", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "\n Error :  %s", strerror(errno));
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	offsetposition = ftell(fp);
	if (offsetposition > 0)
	{
		printf("\n Enter the number to delete :\t");
		scanf("%s", temp_request);
		rewind(fp);
		while (fread(&user, sizeof(user), 1, fp))
		{
			if (strcmp(temp_request, user.number) == 0)
			{
				has_record = 'y';
				printf("\n Do you want to delete the following record :\n 1 : Yes , 0 :No?");
				printf("\n%s %s \t%s \t", user.contact_fname, user.contact_lname, user.number);
				scanf("%d", &ch);
				if (ch == 1)
				{
					flag = 1;
		//			continue;
				}
				else
					return;
			}
		}
		if (has_record == 'n')
			printf("\n Sorry the Number you are trying to delete is not found in the list");
		if (flag == 1)
		{
			rewind(fp);
			while (fread(&user, sizeof(user), 1, fp))
			{
				if (strcmp(temp_request, user.number) != 0)
				{
					fwrite(&user, sizeof(user), 1, temp);
				}
			}
			printf("\n One record deleted ! ");
		}
	}
	else
		printf("\n The file is empty.");
	fclose(fp);
	fclose(temp);
	remove("contact.dat");
	rename("temp.dat", "contact.dat");
	return_to_menu();
}

//function to exit from the program
void exit_message()
{
	clear_screen();
	printf("******************************************\n");
	printf("   THANK YOU FOR USING THE PROGRAM!\n");
	printf("        CREATOR : SUNIL MAHATO     \n");
	printf("******************************************\n");
	fclose(fp);
}
// function to clear screen
void clear_screen()
{
	printf("\e[1;1H\e[2J");
}

//function ti return to main menu
void return_to_menu()
{
	getchar();
	printf("\nPress ENTER to return on main menu ");
	ch = getchar();
	return;
}