#define _CRT_SECURE_NO_WARNINGS

#include "Customer.h"
#include "Shared_Files.h"

void customer_panel(void)
{
	char operation_code;
	while (1)
	{
		printf("\nEnter Operation Code:\n");
		printf("[v] View Products\n[b] Buy a Product\n[w] Show Balance\n[p] Play a game (earn cash)\n[i] Show Inventory\n[s] Sell a Product\n[q] Quit\n>> ");
		scanf(" %c", &operation_code);
		operation_code = tolower(operation_code);
		switch (operation_code) {
		case 'v':
			print_list();
			break;
		case 'b':
			purchase_product();
			break;
		case 'w':
			show_balance();
			break;
		case 'p':
			trivia_challenge();
			break;
		case 'i':
			show_inventory();
			break;
		case 's':
			sell_product();
			break;
		case 'q':
			printf("Exiting...\n");
			return;
		default:
			printf("Invalid operation code. Please try again.\n");
			break;
		}
	}

}

void purchase_product(void)
{
	char name[50];
	int quantity;
	struct Products* current = head;
	printf("Enter the name of the product you want to buy: ");
	scanf("%s", name);

	while (current)
	{
		if (STRICMP(current->name, name) == 0)
		{
			if (current->quantity == 0)
			{
				printf("Sorry, %s is out of stock.\n", current->name);
				return;
			}

			printf("How many do you want to buy? ");
			scanf("%d", &quantity);

			if (quantity > current->quantity)
			{
				printf("Only %d of %s are available.\n", current->quantity, current->name);
				return;
			}
			if (quantity <= 0) {
				printf("Invalid quantity entered.\n");
				return;
			}
			float total_price = current->price * quantity;
			if (total_price > customer.balance)
			{
				printf("Insufficient balance. Your balance is %.2f and the total is %.2f\n", customer.balance, total_price);
				return;
			}

			current->quantity -= quantity;
			customer.balance -= total_price;
			char filename_balance[100];
			sprintf(filename_balance, "%s_balance.txt", customer.name);
			FILE* balance_file = fopen(filename_balance, "w");
			if (balance_file)
			{
				fprintf(balance_file, "%.2f\n", customer.balance);
				fclose(balance_file);
			}
			save_products_to_file("Items.txt");
			printf("Purchase successful! You bought %d of %s for %.2f.\n", quantity, current->name, total_price);
			add_to_inventory(current->name, quantity);
			printf("Remaining balance: %.2f\n", customer.balance);
			return;
		}
		current = current->next;
	}

	printf("Product not found.\n");
}

void show_balance(void)
{
	char filename_balance[100];
	sprintf(filename_balance, "%s_balance.txt", customer.name);
	FILE* balance_file = fopen(filename_balance, "r");
	if (!balance_file)
	{
		printf("balance_file wasn't been able to open, exiting...");
		exit(EXIT_FAILURE);
	}
	fscanf(balance_file, "%f", &customer.balance);
	printf("Your balance is: %.2f\n", customer.balance);
	fclose(balance_file);
}

void print_list(void) {
	if (head == NULL) {
		printf("No products available.\n");
		return;
	}

	struct Products* current = head;
	printf("Name\t\t\t\t\tPrice\t\t\t\tQuantity\n");
	printf("<<----------------------------------------------------------------------------->>\n");
	while (current != NULL) {
		printf("%|-20s\t\t\t%-10.2f\t\t\t%-10d|\n", current->name, current->price, current->quantity);
		current = current->next;
	}
	printf(" <-----------------------------------------------------------------------------> \n");
}

void show_inventory(void)
{
	bool is_empty = true;
	char filename[100];
	sprintf(filename, "%s_inventory.txt", customer.name);
	FILE* fp = fopen(filename, "r");
	char file_product_name[50];
	int file_product_quantity;
	if (!fp)
	{
		printf("File %s is not opening\n");
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "%d %s\n", &file_product_quantity, file_product_name) == 2)
	{
		if (file_product_quantity == 0)
			continue;
		is_empty = false;
		printf("%d %s\n", file_product_quantity, file_product_name);
	}
	if (is_empty)
		printf("Inventory is empty.\n");
	fclose(fp);
}

void sell_product(void)
{
	bool is_found = false;
	char filename[100];
	sprintf(filename, "%s_inventory.txt", customer.name);
	FILE* fp = fopen(filename, "r");
	FILE* tfp = fopen("temp.txt", "w");
	char product_name[50];
	int quantity;
	char inv_name[50];
	int inv_quantity;
	if (!fp)
	{
		printf("File %s didn't open, exiting...", filename);
		exit(EXIT_FAILURE);
	}
	printf("Enter the product you want to sell: ");
	scanf("%s", product_name);
	while (fscanf(fp, "%d %s", &inv_quantity, inv_name) == 2)
	{
		if (_stricmp(product_name, inv_name) == 0)
		{
			strcpy(product_name, inv_name);
			is_found = true;
			struct Products* current = head;
			while (current)
			{
				if (strcmp(current->name, product_name) == 0)
					break;
				current = current->next;
			}
			printf("How many do you want to sell: ");
			scanf("%d", &quantity);
			if (quantity <= inv_quantity)
			{
				printf("You sold %d of %s\n", quantity, product_name);
				inv_quantity -= quantity;
				customer.balance += quantity * (current->price / 2);
				char filename_balance[100];
				sprintf(filename_balance, "%s_balance.txt", customer.name);
				FILE* bfp = fopen(filename_balance, "w");
				if (bfp) {
					fprintf(bfp, "%.2f\n", customer.balance);
					fclose(bfp);
				}
				fprintf(tfp, "%d %s\n", inv_quantity, inv_name);
				current->quantity += quantity;
				save_products_to_file("Items.txt");
			}
			else
			{
				printf("You don't have enough %s in your inventory.\n", product_name);
				fclose(fp);
				fclose(tfp);
				return;
			}
		}
		else
			fprintf(tfp, "%d %s\n", inv_quantity, inv_name);
	}
	if (!is_found)
	{
		printf("Product %s not found in inventory", product_name);
		return;
	}
	fclose(fp);
	fclose(tfp);
	remove(filename);
	rename("temp.txt", filename);
}

void sign_up(void)
{
	printf("Enter your name: ");
	scanf("%s", customer.name);
	char filename_balance[100];
	char filename_inventory[100];
	sprintf(filename_balance, "%s_balance.txt", customer.name);
	sprintf(filename_inventory, "%s_inventory.txt", customer.name);
	FILE* check = fopen(filename_balance, "r");
	if (check)
	{
		printf("An account with that username already exists\n");
		fclose(check);
		exit(EXIT_FAILURE);
	}
	FILE* user_balance_file = fopen(filename_balance, "w");
	FILE* user_inventory_file = fopen(filename_inventory, "w");
	fprintf(user_balance_file, "%.2f\n", 500.00);
	printf("Account created successfully!\n");
	customer.balance = 500.00;
	printf("Hello %s, your balance is %.2f\n", customer.name, customer.balance);
	fclose(user_balance_file);
	fclose(user_inventory_file);
	return;
}

void log_in(void)
{
	printf("Enter your account name: ");
	scanf("%s", customer.name);
	char filename_balance[100];
	char filename_inventory[100];
	sprintf(filename_balance, "%s_balance.txt", customer.name);
	sprintf(filename_inventory, "%s_inventory.txt", customer.name);
	FILE* check_balance = fopen(filename_balance, "r");
	FILE* check_inventory = fopen(filename_inventory, "r");
	if (!check_balance || !check_inventory) {
		printf("Account not found\n");
		if (check_balance)
			fclose(check_balance);
		if (check_inventory)
			fclose(check_inventory);
		exit(EXIT_FAILURE);
	}

	fscanf(check_balance, "%f", &customer.balance);
	printf("Welcome back %s, your balance is %.2f\n", customer.name, customer.balance);
	fclose(check_balance);
	fclose(check_inventory);
	return;
}
