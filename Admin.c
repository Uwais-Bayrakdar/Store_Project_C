#define _CRT_SECURE_NO_WARNINGS

#include "Admin.h"
#include "Shared_Files.h"

void admin_panel(void)
{
	char operation_code;
	printf("\n[Admin Panel] Enter Operation Code:\n");
	while (1)
	{

		printf("[i] Insert a Product\n[d] Delete a Product\n[u] Update a Product\n[s] Search a Product\n[p] Print Products\n[q] Quit\n>> ");
		scanf(" %c", &operation_code);
		operation_code = tolower(operation_code);
		switch (operation_code) {
		case 'i':
			insert();
			break;
		case 'd':
			delete();
			break;
		case 'u':
			update();
			break;
		case 's':
			search();
			break;
		case 'p':
			print_list_admin();
			break;
		case 'q':
			printf("Exiting...\n");
			return;
		}
	}
}

void insert(void)
{
	bool duplicate_flag = false;
	struct Products* new_product = (struct Products*)malloc(sizeof(struct Products));
	if (new_product == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	do
	{
		duplicate_flag = false;
		printf("Enter product name: ");
		scanf("%s", new_product->name);
		struct Products* current = head;
		while (current)
		{
			if (_stricmp(new_product->name, current->name) == 0)
			{
				duplicate_flag = true;
				printf("Product with this name already exists. Please enter a different name.\n");
				break;
			}
			current = current->next;
		}

	} while (duplicate_flag);

	do
	{
		duplicate_flag = false;
		printf("Enter product ID: ");
		scanf("%d", &new_product->id);
		struct Products* current = head;
		while (current)
		{
			if (new_product->id == current->id)
			{
				duplicate_flag = true;
				printf("Product with this ID already exists. Please enter a different ID.\n");
				break;
			}
			current = current->next;
		}

	} while (duplicate_flag);

	printf("Enter product price: ");
	scanf("%f", &new_product->price);
	printf("Enter product quantity: ");
	scanf("%d", &new_product->quantity);

	new_product->next = head;
	head = new_product;
	save_products_to_file("Items.txt");
	return;
}

void delete(void)
{
	int id_to_delete;
	printf("Enter the ID of the product to delete: ");
	scanf("%d", &id_to_delete);
	struct Products* previous = NULL;
	struct Products* current = head;
	while (current)
	{
		if (current->id == id_to_delete)
		{
			if (current == head)
				head = current->next;
			else
				previous->next = current->next;
			free(current);
			printf("Product deleted successfully.\n");
			save_products_to_file("Items.txt");
			return;
		}
		previous = current;
		current = current->next;
	}
	printf("Product with ID %d not found.\n", id_to_delete);
	return;
}

void update(void)
{
	int id_to_update;
	int choice;
	printf("Enter the ID of the product to update: ");
	scanf("%d", &id_to_update);
	struct Products* current = head;
	while (current)
	{
		if (current->id == id_to_update)
		{
			while (1)
			{
				printf("what do you want to update:\n[1]Name\n[2]Price\n[3]Quantity\n[0]Exit\n>>");
				scanf("%d", &choice);
				switch (choice)
				{
				case 0:
					return;
				case 1:
					printf("Enter new name: ");
					scanf("%s", current->name);
					break;
				case 2:
					printf("Enter new price: ");
					scanf("%f", &current->price);
					break;
				case 3:
					printf("Enter new quantity: ");
					scanf("%d", &current->quantity);
					break;
				default:
					printf("Invalid choice.\n");
					return;
				}
				printf("Product updated successfully.\n");
				save_products_to_file("Items.txt");
			}
			return;
		}
		current = current->next;
	}
	printf("Product with ID %d not found.\n", id_to_update);
	return;
}

void search(void)
{
	bool is_found = false;
	int choice;
	char entered_name[50];
	int entered_id;
	struct Products* current = head;
	printf("Search by:\n[1]Name\n[2]ID\n>> ");
	scanf("%d", &choice);
	is_found = false;
	switch (choice)
	{
	case 1:
		printf("Enter product name: ");
		scanf("%s", entered_name);
		while (current)
		{
			if (_stricmp(entered_name, current->name) == 0)
			{
				is_found = true;
				printf("Product found!\n");
				printf("Name: %s\n", current->name);
				printf("ID: %d\n", current->id);
				printf("Price: %.2f\n", current->price);
				printf("Quantity: %d\n", current->quantity);
				break;
			}
			current = current->next;
		}
		if (!is_found)
		{
			printf("Product with name %s not found.\n", entered_name);
		}
		break;
	case 2:
		printf("Enter product ID: ");
		scanf("%d", &entered_id);
		while (current)
		{
			if (entered_id == current->id)
			{
				is_found = true;
				printf("Product found!\n");
				printf("Name: %s\n", current->name);
				printf("ID: %d\n", current->id);
				printf("Price: %.2f\n", current->price);
				printf("Quantity: %d\n", current->quantity);
				break;
			}
			current = current->next;
		}
		if (!is_found)
		{
			printf("Product with ID %d not found.\n", entered_id);
		}
		break;
	default: printf("Invalid choice.\n");
		break;
	}
}

void print_list_admin(void) {
	if (head == NULL) {
		printf("No products available.\n");
		return;
	}

	struct Products* current = head;
	printf("%-20s %-10s %-10s %-10s\n", "Name", "ID", "Price", "Quantity");
	printf("<<----------------------------------------------->>\n");
	while (current != NULL) {
		printf("|%-20s %-10d %-10.2f %-10d|\n", current->name, current->id, current->price, current->quantity);
		current = current->next;
	}
}
