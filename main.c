#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include "Customer.h"
#include "Shared_Files.h"
struct Products Product;
struct Products* head = NULL;
struct customers customer;

int main(int argc, char* argv[])
{
	int input_code;
	int choice;
	if (argc != 2)
	{
		printf("Usage: %s customer", argv[0]);
		return 1;
	}
	else
	{
		if (_stricmp(argv[1], "admin") == 0)
		{
			printf("welcome admin, please enter the secret code to continue >>");
			scanf("%i", &input_code);
			if (input_code == SECRET_CODE)
			{
				printf("code confirmed!\n");
				load_products_from_file("Items.txt");
				admin_panel();
			}
			else
			{
				printf("code not confirmed!\n");
				return 1;
			}
		}
		if (_stricmp(argv[1], "customer") == 0)
		{
			printf("Hello there and welcome to Higle Trance's Store!\n");
			printf("[1] Sign up\n[2] log_in\n>>");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				sign_up();
				break;
			case 2:
				log_in();
				break;
			default:
				printf("Invalid choice.\n");
				break;
			}
			char filename_balance[100];
			sprintf(filename_balance, "%s_balance.txt", customer.name);
			FILE* balance_file = fopen(filename_balance, "r");
			if (balance_file)
			{
				fscanf(balance_file, "%f", &customer.balance);
				fclose(balance_file);
			}
			else
				customer.balance = 500.00;
			load_products_from_file("Items.txt");
			customer_panel();
		}
	}
	return 0;
}
