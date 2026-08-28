#ifndef CUSTOMER_H
#define CUSTOMER_H

#include"product.h"

typedef struct
{
    char name[30];
    char phone[12];
    char password[30];
} Customer;

extern int is_logged_in;
extern Customer current_customer;


int customer_menu();
int about_pharmacy();
int create_customer_file();
int customer_exists(char phone[]);
int customer_signup();
int customer_login();
int customer_view_product(char category[]);
int customer_search_product(char category[]);
int customer_product_details(Product product);
int feedback();
int customer_logout();
int input_password(char password[]);

#endif