#pragma once
#ifndef SHARED_FILES_H
#define SHARED_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define TEXT_LENGTH 100

#ifdef _WIN32
#define STRICMP _stricmp
#else
#define STRICMP strcasecmp
#endif

struct Trivia
{
	char question_text[TEXT_LENGTH * 2 + 1];
	char optionA[TEXT_LENGTH + 1];
	char optionB[TEXT_LENGTH + 1];
	char optionC[TEXT_LENGTH + 1];
	char optionD[TEXT_LENGTH + 1];
	char correct_answer;
	char explanation[TEXT_LENGTH + 1];
};

extern struct Trivia Questions[15];

struct Products {
	char name[50];
	int id;
	float price;
	int quantity;
	struct Products* next;
};

extern struct Products Product;
extern struct Products* head;

void trivia_challenge(void);

void load_products_from_file(const char* file);

void save_products_to_file(const char* file);

void to_lowercase(char str[]);

void add_to_inventory(char name[], int quantity);


#endif
