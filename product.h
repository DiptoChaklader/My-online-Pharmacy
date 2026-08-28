#ifndef PRODUCT_H
#define PRODUCT_H




typedef struct
{
    int id;
    char name[30];
    char category[30];
    char company[30];
    char description[50];
    char expiry_date[15];
    int pack_size;
    float price;
    int stock;
} Product;

int to_upper_case(char str[]);
int create_product_file();
int product_exists(int id);
int add_product();
int display_product_details(Product p);
int view_product(char category[]);
int search_product(char category[]);
int update_product();
int delete_product();
int update_stock();
int edit_about_pharmacy();
int reduce_product_stock();

/* ui */
int print_fornt_page();
int print_Main_Page();
int Print_Customer_Main_Page_When_Logged_In();
int Print_Customer_Main_Page_When_Not_Logged_In();
int Print_Admin_Main_Page();
int Print_Delivery_Man_Page();
int Print_Medicine_page();
int Print_Medical_Accessories();
int Print_Skin_Care_Products();
int Print_Health_And_Hygiene_Products();
int Print_Child_Care_Products();
int invalid_item_choice();



#endif