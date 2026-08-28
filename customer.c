#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <conio.h>

#include "customer.h"
#include "product.h"
#include "transaction.h"
#include "deliveryman.h"

int is_logged_in = 0;
Customer current_customer;

int customer_menu(){   
    int choice;
    while(1)
        {   
        
            int choice;
            system("cls");

            if(is_logged_in == 0)
                {
                    Print_Customer_Main_Page_When_Not_Logged_In();
                }
            else
                {
                    Print_Customer_Main_Page_When_Logged_In();
                }

            scanf("%d", &choice);
            getchar();

            switch(choice)
                {
                    case 1:
                        {
                            int choice;
                            while(1)
                                {   
                                    Print_Medicine_page();
                                    scanf("%d",&choice);
                                    getchar();

                                    switch(choice)
                                        {
                                            case 1:
                                                system("cls");
                                                customer_view_product("MED");
                                                break;

                                            case 2:
                                                system("cls");
                                                customer_search_product("MED");
                                                break;

                                            case 3:
                                                break;

                                            default:
                                                invalid_item_choice();
                                        }

                                        if(choice==3)
                                            break;
                                }
                                    break;
                        }

                    case 2:
                        {
                            int choice;

                            while(1)
                            { 
                                Print_Medical_Accessories();
                                scanf("%d",&choice);
                                getchar();

                                switch(choice)
                                {
                                    case 1:
                                        system("cls");
                                        customer_view_product("ACC");
                                        break;

                                    case 2:
                                        system("cls");
                                        customer_search_product("ACC");
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        invalid_item_choice();
                                }

                                    if(choice==3)
                                        break;
                            }

                            break;
                        }


                    case 3:
                        {
                            int choice;
                            while(1)
                            {   
                                Print_Skin_Care_Products();
                                scanf("%d",&choice);
                                getchar();

                                switch(choice)
                                {
                                    case 1:
                                        system("cls");
                                        customer_view_product("SKN");
                                        break;

                                    case 2:
                                        system("cls");
                                        customer_search_product("SKN");
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        invalid_item_choice();
                                }

                                if(choice==3)
                                    break;
                            }

                            break;
                        }

                    case 4:
                        {
                            int choice;
                            while(1)
                            {   
                                Print_Health_And_Hygiene_Products();
                                scanf("%d",&choice);
                                getchar();

                                switch(choice)
                                {
                                    case 1:
                                        system("cls");
                                        customer_view_product("HH");
                                        break;

                                    case 2:
                                        system("cls");
                                        customer_search_product("HH");
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        invalid_item_choice();
                                }
                                if(choice==3)
                                    break;
                            }
                            break;
                        }


                    case 5:
                        {
                            int choice;

                            while(1)
                            {   
                                Print_Child_Care_Products();
                                scanf("%d",&choice);
                                getchar();

                                switch(choice)
                                {
                                    case 1:
                                        system("cls");
                                        customer_view_product("CC");
                                        break;

                                    case 2:
                                        system("cls");
                                        customer_search_product("CC");
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        invalid_item_choice();
                                }

                                if(choice==3)
                                    break;
                            }

                            break;
                            }


                    case 6:
                        system("cls");
                        about_pharmacy();
                        break;

                    case 7:
                        if(is_logged_in==1)
                            {
                                view_order_history();
                            }
                                else
                            {
                                printf("                                                                                     Please Login First\n");
                                printf("                                                                          Please press Enter to go back to the Customer Menu");
                                getchar();
                            }
                            break;


                    case 8:
                        if(is_logged_in==1)
                            {   
                                system("cls");
                                view_cart();
                            }
                        else
                            {   
                                system("cls");
                                printf("                                                                               +======================================+\n");
                                printf("                                                                               |     Please Login Or Signup First     |\n");
                                printf("                                                                               +======================================+\n");
                                printf("                                                                          Please press Enter to go back to the Customer Menu");
                                getchar();
                            }
                            break;


                    case 9:
                        if(is_logged_in==1)
                            {
                                feedback();
                            }
                        else
                            {
                                printf("                                                                                     Please Login First\n");
                                printf("                                                                          Please press Enter to go back to the Customer Menu");
                                getchar();
                            }  
                        break;


                    case 10:
                        if(is_logged_in == 0)
                            {   
                                system("cls");
                                customer_login();
                            }
                        else
                            {
                                system("cls");
                                printf("                                                                                         You Are Already Logged In\n");
                                printf("                                                                          Please press Enter to go back to the Customer Menu");
                                getchar();
                            } 
                        break;


                    case 11:
                        if(is_logged_in == 0)
                            {   
                                system("cls");
                                customer_signup();
                            }
                        else
                            {
                                system("cls");
                                printf("                                                                                         You Are Already Logged In\n");
                                printf("                                                                          Please press Enter to go back to the Customer Menu");
                                getchar();
                            }
                        break;


                    case 12:
                        system("cls");
                        if (customer_logout()==1)
                            {
                                return 0;
                            }


                    case 0:
                        return 1;


                    default:
                        invalid_item_choice();
        }
    }
}

int about_pharmacy(){
    FILE *fp;
    char line[300];
    fp = fopen("about.txt", "r");
    if(fp == NULL)
        {
            printf("                                                                                        +===============================================+\n");
            printf("                                                                                        |    About Pharmacy Information Not Available   |\n");
            printf("                                                                                        +===============================================+\n");
            return 0;
        }
    printf("\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
    printf("\n                                                                Press Enter To continue");
    getchar();
    return 1;
}

int create_customer_file(){
    FILE *fp;

    fp = fopen("customer.txt", "r");
    if(fp != NULL)
        {
            fclose(fp);
            return 1;
        }

    fp = fopen("customer.txt", "w");
    if(fp == NULL)
        {
            printf("Error : %s\n", strerror(errno));
            return 0;
        }
    
    fclose(fp);
    return 1;
}

int customer_exists(char phone[]){
    FILE *fp;

    Customer customer;
    char line[200];

    fp = fopen("customer.txt", "r");
    if(fp == NULL)
        {
            printf("Error : %s\n", strerror(errno));
            return 0;
        }

    while(fgets(line, sizeof(line), fp))
        {
            if(sscanf(line,"%29[^|]|%11[^|]|%29[^\n]", customer.name, customer.phone, customer.password) != 3)
            {
                continue;
            }

            if(strcmp(customer.phone, phone) == 0)
            {   
                printf("                                                                          |                                       |\n");
                printf("                                                                          +=======================================+\n");
                printf("                                                                                                                  \n");
                printf("                                                                          +=======================================+\n");
                printf("                                                                          |        Account Already Exists         |\n");
                printf("                                                                          +=======================================+\n");
                printf("                                                                                                                  \n");
                getchar();
                fclose(fp);
                return 1;
            }
        }
    fclose(fp);
    return 0;
}

int input_password(char password[]){
        int i = 0;
        char ch;
        while(1)
        {
            ch = getch();
            if(ch == '\r')      
            {
                password[i] = '\0';
                break;
            }

            else if(ch == '\b') 
            {
                if(i > 0)
                    {
                        i--;
                        printf("\b \b");
                    }
            }

            else if(i < 29)
            {
                password[i++] = ch;
                printf("*");
            }
    }
    printf("\n");

    return 1;
}

int customer_signup(){
        FILE *fp;
        Customer customer;
        create_customer_file();
        fp = fopen("customer.txt", "a");
        if(fp == NULL)
        {
            printf("Error : %s\n", strerror(errno));
            return 0;
        }

    printf("\n");
    printf("                                                                          +=======================================+\n");
    printf("                                                                          |             CUSTOMER SIGN UP          |\n");
    printf("                                                                          +=======================================+\n");
    printf("                                                                          |   Enter Your Name : ");
    fgets(customer.name, sizeof(customer.name), stdin);
    customer.name[strcspn(customer.name, "\n")] = '\0';
    printf("                                                                          |                                       |\n");
    printf("                                                                          |   Enter Phone Number : ");
    fgets(customer.phone, sizeof(customer.phone), stdin);
    customer.phone[strcspn(customer.phone, "\n")] = '\0';
    printf("                                                                          |                                       |\n");
    
    if(strlen(customer.phone) != 11)
    {
        printf("                                                                          +=======================================+\n");
        printf("                                                                          |    Phone Number Must Be 11 Digits.    |\n");
        printf("                                                                          +=======================================+\n");
        fclose(fp);
        printf("                                                                                                                   \n");
        printf("                                                                                   Press Enter To Continue");
        getchar();
        return 0;
    }

    if(customer_exists(customer.phone))
    {
        printf("                                                                      +================================================+\n");
        printf("                                                                      |   An Account Already Created With This Number  |\n");
        printf("                                                                      +================================================+\n");
        fclose(fp);
        printf("                                                                                                                        \n");
        printf("                                                                                   Press Enter To Continue");
        getchar();
        return 0;
    }

    printf("                                                                          |   Enter Password : ");
    input_password(customer.password);

    fprintf(fp,"%s|%s|%s\n",customer.name,customer.phone,customer.password);

    fclose(fp);
    is_logged_in=1;
    current_customer = customer;
    printf("                                                                          |                                       |\n");
    printf("                                                                          +=======================================+\n");
    printf("                                                                                                                   \n");
    printf("                                                                          +=======================================+\n");
    printf("                                                                          |     Account Created Successfully      |\n");
    printf("                                                                          +=======================================+\n");
    printf("                                                                               Press Enter To Continue");
    getchar();
    getchar();
    return 1;
}

int customer_login(){
        FILE *fp;
        Customer customer;

        char phone[12];
        char password[30];

        fp = fopen("customer.txt", "r");
            if(fp == NULL)
            {
                    printf("Error : %s\n", strerror(errno));
                    return 0;
            }

    printf("                                                                                                                \n");
    printf("                                                                           +====================================+\n");
    printf("                                                                           |           CUSTOMER LOGIN           |\n");
    printf("                                                                           +====================================+\n");
    printf("                                                                           |                                    |\n");
    printf("                                                                           | Enter Phone Number : ");
    fgets(phone, sizeof(phone), stdin); 
    phone[strcspn(phone, "\n")] = '\0';
    printf("                                                                           |                                    |\n");
    printf("                                                                           | Enter Password : ");
    input_password(password);

    while(fscanf(fp, " %29[^|]|%11[^|]|%29[^\n]", customer.name, customer.phone, customer.password) == 3)
    {
        if(strcmp(phone, customer.phone) == 0 && strcmp(password, customer.password) == 0)
        {
            is_logged_in = 1;
            current_customer = customer;

            fclose(fp);
            printf("                                                                           +====================================+\n");
            printf("                                                                           |         Login Successful           |\n");
            printf("                                                                           +====================================+\n");
            printf("                                                                           +====================================+\n");
            printf("                                                                                  Welcome %s      \n", current_customer.name);
            printf("                                                                           +====================================+\n");
            printf("\n                                                                                  Press Enter To Continue");
            getchar();
            getchar();
            return 1;
        }

    }

    fclose(fp);

    printf("                                                                                                                       \n");
    printf("                                                                         +==========================================+\n");
    printf("                                                                         |     Invalid Phone Number Or Password     |\n");
    printf("                                                                         +==========================================+\n");
    printf("\n                                                                                 Press Enter To Continue");
    getchar();

    return 0;
}

int customer_view_product(char category[]){
    int choice;
    FILE *fp;
    Product product;

    char line[300];
    int found = 0;

    fp = fopen("product.txt", "r");
    if(fp == NULL)
    {
        printf("Error : %s\n", strerror(errno));
        return 0;
    }

    printf("\n");
    printf("                                                     +=====================================================================================+\n");
    printf("                                                     | %-12s | %-20s | %-15s | %-12s | %-12s |\n",
            "ID",
            "Name",
            "Company",
            "Price/Pack",
            "Stock");
    printf("                                                     +=====================================================================================+\n");

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,"%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%14[^|]|%f|%d|%d",
                    &product.id,
                    product.name,
                    product.category,
                    product.company,
                    product.description,
                    product.expiry_date,
                    &product.price,
                    &product.pack_size,
                    &product.stock) != 9)
        {
            continue;
        }

        if(strcmp(product.category, category) == 0)
        {
            printf("                                                     | %-12d | %-20s | %-15s | %-12.2f | %-12d |\n",
                    product.id,
                    product.name,
                    product.company,
                    product.price,
                    product.stock);

            found = 1;
        }
    }

    printf("                                                     +=====================================================================================+\n");

    fclose(fp);

    if(found == 0)
    {
        system("cls");
        printf("                                                                            +===========================================+\n");
        printf("                                                                            |           No Product Available.           |\n");
        printf("                                                                            +===========================================+\n");
        printf("                                                                                Please try again after adding to cart. ");
        getchar();
        return 0;
    }

    printf("                                                                                     +=====================+\n");
    printf("                                                                                     |  1. Search Product  |\n");
    printf("                                                                                     |  2. Back            |\n");
    printf("                                                                                     +=====================+\n");
    printf("                                                                                       Enter Your Choice :");
    scanf("%d", &choice);
    getchar();

    switch(choice)
        {
            case 1:
                system("cls");
                customer_search_product(category);
                break;

            case 2:
                return 0;

            default:
                invalid_item_choice();
                                                                                  
                break;
        }
    return 1;
}

int customer_search_product(char category[]){
    FILE *fp;
    Product product;

    char line[300];
    char input[100];

    int id;
    int isID;

    fp = fopen("product.txt", "r");

    if(fp == NULL)
    {
        printf("Error : %s\n", strerror(errno));
        return 0;
    }

    printf("\n                                                                         Enter Product ID Or Product Name (0 = Back) : ");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    to_upper_case(input);

    if(strcmp(input, "0") == 0)
    {
        fclose(fp);
        return 0;
    }

    isID = (sscanf(input, "%d", &id) == 1);
    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,"%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%14[^|]|%f|%d|%d",
                    &product.id,
                    product.name,
                    product.category,
                    product.company,
                    product.description,
                    product.expiry_date,
                    &product.price,
                    &product.pack_size,
                    &product.stock) != 9)
                        {
                            continue;
                        }

        if(strcmp(product.category, category) != 0)
            continue;

        if(isID)
        {
            if(product.id == id)
            {   
                system("cls");
                customer_product_details(product);

                fclose(fp);
                return 1;
            }
        }
        else
        {
            to_upper_case(product.name);

            if(strcmp(product.name, input) == 0)
            {
                customer_product_details(product);

                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);

    printf("                                                                                +=================================+\n");
    printf("                                                                                |        Product Not Found        |\n");
    printf("                                                                                +=================================+\n");
    printf("                                                                                  Please press Enter to go back");
    getchar();

    return 0;
}

int customer_product_details(Product product){
    int choice;

    while(1)
    {
        display_product_details(product);
        printf("                                                                                                                           \n");
        printf("                                                                           +==============================================+\n");
        printf("                                                                           |       1. Add To Cart                         |\n");
        printf("                                                                           |       0. Back                                |\n");
        printf("                                                                           +==============================================+\n");
        printf("                                                                                                                           \n");
        printf("                                                                                    Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:

                if(is_logged_in == 0)
                {   system("cls");
                    printf("                                                                           +==============================================+\n");
                    printf("                                                                           |              Please Login First              |\n");
                    printf("                                                                           +==============================================+\n");
                    printf("                                                                           |                                              |\n");
                    printf("                                                                           |    1. Login                                  |\n");
                    printf("                                                                           |    2. Sign Up                                |\n");
                    printf("                                                                           |    0. Back                                   |\n");
                    printf("                                                                           +==============================================+\n");
                    printf("\n                                                                                Enter Your Choice : ");
                    scanf("%d",&choice);
                    getchar();

                    switch(choice)
                    {
                        case 1:
                            customer_login();
                            break;

                        case 2:
                            customer_signup();
                            break;

                        case 0:
                            break;

                        default:
                            printf("                                                       +==========================+\n");
                            printf("                                                       |      Invalid Choice      |\n");
                            printf("                                                       +==========================+\n");
                            printf("                                                          Press Enter To Continue  \n");
                            getchar();
                    }
                    if (choice==0)
                    {
                        break;
                    }
                    
                    
                }
                add_to_cart(product);
                return 1;

                case 0:

                    return 1;

                default:
                    printf("                                                             Invalid Choice\n");
                    printf("                                                           Press Enter To Continue\n");
        }
    }
}

int feedback(){
    FILE *fp;
    char feedback[300];

    fp = fopen("feedback.txt", "a");
    if(fp == NULL)
    {
        printf("Error: %s", strerror(errno));
        printf("Press Enter To Continue");
        getchar();
        return 0;
    }

    system("cls");
    printf("\n");
    printf("                                                  =========================================\n");
    printf("                                                              GIVE FEEDBACK\n");
    printf("                                                  =========================================\n");
    printf("                                                  Customer Name : %s\n", current_customer.name);
    printf("                                                  Phone Number  : %s\n", current_customer.phone);
    printf("                                                  Enter Your Feedback : ");

    fgets(feedback,sizeof(feedback),stdin);
    feedback[strcspn(feedback, "\n")] = '\0';

    if(strlen(feedback) == 0)
    {
        printf("                                              Feedback Cannot Be Empty\n");
        fclose(fp);
        printf("                                              Press Enter To Continue");
        getchar();
        return 0;
    }

    fprintf(fp,"=============================================================\n");
    fprintf(fp, "Customer Name : %s\n",current_customer.name);
    fprintf(fp,"Phone Number  : %s\n",current_customer.phone);
    fprintf(fp,"Feedback      : %s\n",feedback);
    fprintf(fp,"=============================================================\n");
    fprintf(fp, "\n");
    fclose(fp);

    printf("                                                  Feedback Submitted Successfully\n");
    printf("                                                      Press Enter To Continue");
    getchar();

    return 1;
}

int customer_logout(){
    is_logged_in = 0;
    current_customer.name[0] = '\0';
    current_customer.phone[0] = '\0';
    current_customer.password[0] = '\0';
    printf("                                                                          +==============================================+\n");
    printf("                                                                          |       Customer Logged Out Successfully.      |\n");
    printf("                                                                          +==============================================+\n");
    printf("                                                                                Press Enter To Return To Main Menu: ");
    getchar();

    return 1;
}