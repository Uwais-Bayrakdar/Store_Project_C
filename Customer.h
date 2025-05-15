#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H



struct customers {
	char name[50];
	float balance;
};
extern struct customers customer;	

void show_balance(void);

void show_inventory(void);

void sell_product(void);

void purchase_product(void);

void customer_panel(void);

void print_list(void);

void sign_up(void);

void log_in(void);


#endif // !CUSTOMER_H
