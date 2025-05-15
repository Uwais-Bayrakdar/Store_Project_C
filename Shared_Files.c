#define _CRT_SECURE_NO_WARNINGS

#include "Shared_Files.h"
#include "Admin.h"
#include "Customer.h"

struct Trivia Questions[15] = {
		{
		"What gas do plants absorb from the atmosphere?",
		"Oxygen", "Carbon Dioxide", "Hydrogen", "Nitrogen",
		'B',
		"Plants absorb carbon dioxide and use it during photosynthesis."
		},
		{
		"Which ocean is the largest?",
		"Atlantic", "Pacific", "Indian", "Arctic",
		'B',
		"The Pacific Ocean is the largest and deepest of Earth's oceans."
		},
		{
		"How many legs does a spider have?",
		"6", "8", "10", "12",
		'B',
		"Spiders are arachnids and have 8 legs."
		},
		{
		"Which part of the plant conducts photosynthesis?",
		"Roots", "Stem", "Leaves", "Flowers",
		'C',
		"Leaves contain chlorophyll, which is vital for photosynthesis."
		},
		{
		"What is the hardest natural substance on Earth?",
		"Gold", "Iron", "Diamond", "Quartz",
		'C',
		"Diamond is the hardest naturally occurring material known."
		},
		{
		"Which planet has the most moons?",
		"Earth", "Mars", "Jupiter", "Saturn",
		'D',
		"Saturn currently holds the record for the most confirmed moons."
		},
		{
		"Who is known as the father of computers?",
		"Bill Gates", "Alan Turing", "Charles Babbage", "Steve Jobs",
		'C',
		"Charles Babbage designed the first mechanical computer."
		},
		{
		"What is the largest internal organ in the human body?",
		"Heart", "Liver", "Lung", "Stomach",
		'B',
		"The liver is the largest internal organ and performs vital functions."
		},
		{
		"Which metal is liquid at room temperature?",
		"Mercury", "Aluminum", "Lead", "Zinc",
		'A',
		"Mercury is the only metal that is liquid at standard conditions."
		},
		{
		"Which country invented paper?",
		"Egypt", "India", "China", "Greece",
		'C',
		"Paper was invented in ancient China around 105 AD."
		},
		{
		"Which language has the most native speakers?",
		"English", "Mandarin Chinese", "Spanish", "Hindi",
		'B',
		"Mandarin Chinese has the highest number of native speakers globally."
		},
		{
		"Which country is known as the Land of the Rising Sun?",
		"China", "Thailand", "Japan", "Vietnam",
		'C',
		"Japan is traditionally called the Land of the Rising Sun."
		},
		{
		"Who wrote the play 'Romeo and Juliet'?",
		"Charles Dickens", "William Shakespeare", "Jane Austen", "Mark Twain",
		'B',
		"Shakespeare wrote the classic tragedy Romeo and Juliet."
		},
		{
		"Which of these is used to store multiple values in C?",
		"int", "char", "array", "float",
		'C',
		"An array allows storing multiple values of the same type in C."
		},
		{
		"What's an easy trick to remove bad odors from a fridge?",
		"Use vinegar", "Use baking soda", "Use lemon juice", "Use pepper",
		'B',
		"Baking soda absorbs odors and is commonly used in fridges."
		} };

void trivia_challenge(void)
{
	srand(time(NULL));
	int indexes[3];
	int count = 0;

	while (count < 3) {
		int r = rand() % 15;
		bool is_duplicate = false;

		for (int i = 0; i < count; i++) {
			if (indexes[i] == r) {
				is_duplicate = true;
				break;
			}
		}

		if (!is_duplicate) {
			indexes[count] = r;
			count++;
		}
	}
	int score = 0;
	char choice;
	printf("Welcome to Trivia Challenge!\n");
	printf("You will be asked 3 multiple-choice questions.\n");
	printf("Each correct answer gives you 20.00 in extra cash!\n");

	printf("1st question:\n");
	printf("%s\n", Questions[indexes[0]].question_text);
	printf("A)%s\n", Questions[indexes[0]].optionA);
	printf("B)%s\n", Questions[indexes[0]].optionB);
	printf("C)%s\n", Questions[indexes[0]].optionC);
	printf("D)%s\n", Questions[indexes[0]].optionD);
	printf("What's your answer?\n");
	printf(">>");
	scanf(" %c", &choice);
	if (toupper(choice) == Questions[indexes[0]].correct_answer)
	{
		printf("you got the question correct!\n");
		printf("%s\n", Questions[indexes[0]].explanation);
		score++;
	}
	else
	{
		printf("you got the question wrong!\n");
		printf("%c\n", Questions[indexes[0]].correct_answer);
		printf("%s\n", Questions[indexes[0]].explanation);
	}
	printf("\n2nd question:\n");
	printf("%s\n", Questions[indexes[1]].question_text);
	printf("A)%s\n", Questions[indexes[1]].optionA);
	printf("B)%s\n", Questions[indexes[1]].optionB);
	printf("C)%s\n", Questions[indexes[1]].optionC);
	printf("D)%s\n", Questions[indexes[1]].optionD);
	printf("What's your answer?\n");
	printf(">>");
	scanf(" %c", &choice);
	if (toupper(choice) == Questions[indexes[1]].correct_answer)
	{
		printf("you got the question correct!\n");
		printf("%s\n", Questions[indexes[1]].explanation);
		score++;
	}
	else
	{
		printf("you got the question wrong!\n");
		printf("%c\n", Questions[indexes[1]].correct_answer);
		printf("%s\n", Questions[indexes[1]].explanation);
	}
	printf("\n3rd question:\n");
	printf("%s\n", Questions[indexes[2]].question_text);
	printf("A)%s\n", Questions[indexes[2]].optionA);
	printf("B)%s\n", Questions[indexes[2]].optionB);
	printf("C)%s\n", Questions[indexes[2]].optionC);
	printf("D)%s\n", Questions[indexes[2]].optionD);
	printf("What's your answer?\n");
	printf(">>");
	scanf(" %c", &choice);
	if (toupper(choice) == Questions[indexes[2]].correct_answer)
	{
		printf("you got the question correct!\n");
		printf("%s\n", Questions[indexes[2]].explanation);
		score++;
	}
	else
	{
		printf("you got the question wrong!\n");
		printf("%c\n", Questions[indexes[2]].correct_answer);
		printf("%s\n", Questions[indexes[2]].explanation);
	}
	printf("you got %d/3 questions correct\nyou gained %d extra cash into your balance!", score, score * 20);
	char filename[100];
	sprintf(filename, "%s_balance.txt", customer.name);
	FILE* balance_file = fopen(filename, "w");
	customer.balance += score * 20;
	fprintf(balance_file, "%.2f", customer.balance);

	printf("would you like to play again?(y/n)\n");
	printf(">>");
	scanf(" %c", &choice);
	if (tolower(choice) == 'y')
	{
		trivia_challenge();
	}
}

void add_to_inventory(char name[], int quantity)
{
	char file_product_name[50];
	int file_product_quantity;
	bool found = false;
	char filename[100];
	sprintf(filename, "%s_inventory.txt", customer.name);
	FILE* fp = fopen(filename, "r");
	FILE* temp_fp = fopen("temp.txt", "w");
	if (!fp)
	{
		printf("file didn't open.");
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp, "%d %s\n", &file_product_quantity, file_product_name) == 2)
	{
		if (strcmp(file_product_name, name) == 0)
		{
			file_product_quantity += quantity;
			fprintf(temp_fp, "%d %s\n", file_product_quantity, file_product_name);
			found = true;
		}
		else
		{
			fprintf(temp_fp, "%d %s\n", file_product_quantity, file_product_name);
		}
	}
	if (!found)
	{
		file_product_quantity = quantity;
		fprintf(temp_fp, "%d %s\n", file_product_quantity, name);
	}
	fclose(fp);
	fclose(temp_fp);
	remove(filename);
	rename("temp.txt", filename);
}

void to_lowercase(char str[])
{
	for (int i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
	}
}

void load_products_from_file(const char* file)
{
	FILE* fp = fopen(file, "r");
	if (!fp)
	{
		printf("can't open %s\n", file);
		exit(EXIT_FAILURE);
	}

	while (fscanf(fp, "%s %d %f %d", Product.name, &Product.id, &Product.price, &Product.quantity) == 4)
	{
		bool product_duplication = false;  // Reset here for each product

		struct Products* new_node = malloc(sizeof(struct Products));
		if (new_node == NULL)
		{
			printf("failed to allocate memory\n");
			exit(EXIT_FAILURE);
		}

		struct Products* current = head;
		while (current != NULL)
		{
			if (current->id == Product.id)
			{
				product_duplication = true;
				printf("Product with ID %d already exists. Skipping...\n", Product.id);
				break;
			}
			current = current->next;
		}

		if (product_duplication)
		{
			free(new_node);
			continue;
		}

		strcpy(new_node->name, Product.name);
		new_node->id = Product.id;
		new_node->price = Product.price;
		new_node->quantity = Product.quantity;
		new_node->next = head;
		head = new_node;
	}

	fclose(fp);
}

void save_products_to_file(const char* file)
{
	FILE* fp = fopen(file, "w");
	if (!fp)
	{
		printf("can't open %s\n", file);
		exit(EXIT_FAILURE);
	}
	struct Products* current = head;
	while (current)
	{
		fprintf(fp, "%s %d %.2f %d\n", current->name, current->id, current->price, current->quantity);
		current = current->next;
	}
	fclose(fp);
}

