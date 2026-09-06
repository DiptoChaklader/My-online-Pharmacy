#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "product.h"
#include "customer.h"
#include "transaction.h"

int  admin_login(){
    system("cls");
    char username[20];
    char password[20];
    printf("\n\n\n");
    printf("                                                           +===================================================================================+\n");
    printf("                                                           |                                                                                   |\n");
    printf("                                                           |                    Welcome to ZenPharma Admin Login System                        |\n");
    printf("                                                           |                                                                                   |\n");
    printf("                                                           +===================================================================================+\n");
    printf("                                                           |                                                                                   |\n");
    printf("                                                           | Enter Username : ");
    scanf("%s",username);
    getchar();
    printf("                                                           |                                                                                   |\n");
    printf("                                                           | Enter Password : ");
    input_password(password);
    printf("                                                           |                                                                                   |\n");
    printf("                                                           +===================================================================================+\n");


    if (strcmp(username,"admin")==0 && strcmp(password,"1234")==0)
    {
        printf("                                                                                        +===========================+\n");
        printf("                                                                                        |   [V]  Login  Successful  |\n");
        printf("                                                                                        +===========================+\n");
        printf("                                                                                           Press Enter To Continue");
        getchar();
        return 1;

    }else{
        printf("                                                                                        +===========================+\n");
        printf("                                                                                        |   [X] Login Unsuccessful  |\n");
        printf("                                                                                        +===========================+\n");
        printf("                                                                                           Press Enter To Go Back");
        getchar();
        return 0;
    }

}

int admin_menu(){
    int choice;
    printf("\n\n\n");
    
    while (1)
    {
        Print_Admin_Main_Page();
        scanf("%d", &choice);
        getchar();
                        
        switch (choice)
            {
                case 1:
                        {
                            system("cls");
                            add_product();                
                            break;
                        }        
                case 2:
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
                                                    view_product("MED");
                                                    break;

                                            case 2:
                                                    system("cls");
                                                    search_product("MED");
                                                    break;

                                            case 3:
                                                    break;

                                            default:
                                                    invalid_item_choice();
                                        }
                                            if(choice==3)
                                                {
                                                    break;
                                                }
                                }
                            break;
                        }

                        case 3:
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
                                                        view_product("ACC");
                                                        break;

                                                case 2:
                                                        system("cls");
                                                        search_product("ACC");
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
                                        Print_Skin_Care_Products();
                                        scanf("%d",&choice);
                                        getchar();

                                        switch(choice)
                                            {
                                                case 1:
                                                        system("cls");
                                                        view_product("SKN");
                                                        break;

                                                case 2:
                                                        system("cls");
                                                        search_product("SKN");
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
                                Print_Health_And_Hygiene_Products();
                                scanf("%d",&choice);
                                getchar();

                                switch(choice)
                                {
                                case 1:
                                    system("cls");
                                    view_product("HH");
                                    break;

                                case 2:
                                    system("cls");
                                    search_product("HH");
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
                                    view_product("CC");
                                    break;

                                case 2:
                                    system("cls");
                                    search_product("CC");
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

                        case 7: 
                            system("cls");
                            update_product();
                            break;

                        case 8:
                            system("cls");
                            update_stock();
                            break;

                        case 9:
                            system("cls");
                            delete_product();
                            break;

                        case 10:
                            view_feedback();
                            break;

                        case 11:
                            admin_view_orders();
                            break;

                        case 12:
                            system("cls");
                            edit_about_pharmacy();
                            break;

                        case 13:     
                            if (admin_logout()==1)
                            {
                                return 0;
                            }
                            break;

                        default:
                            invalid_item_choice();
                        
                        }
                        }
                        return 0; 
}

int admin_view_orders(){
    FILE *fp;
    char line[300];

    fp = fopen("order.txt","r");
    if(fp == NULL)
    {
        printf("                                                                 +========================================+\n");
        printf("                                                                 |             No Orders Found            |\n");
        printf("                                                                 +========================================+\n");
        printf("                                                       Press Enter To Continue");
        getchar();
        return 0;
    }

    system("cls");
    printf("                                                                                  \n");
    printf("                                                      +===========================================================+\n");
    printf("                                                      |                      ALL ORDERS                           |\n");
    printf("                                                      +===========================================================+\n\n");

    while(fgets(line,sizeof(line),fp))
    {
        printf("                                                      %s",line);
    }

    fclose(fp);
    printf("                                                       Press Enter To Continue");
    getchar();
    return 1;
}          

int view_feedback(){
    FILE *fp;
    char line[300];

    fp = fopen("feedback.txt", "r");
    if(fp == NULL)
    {
        printf("\n                                                                             No Feedback Found.\n");
        printf("                                                                               Press Enter To Return: ");
        getchar();
        return 0;
    }

    system("cls");
    printf("\n");
    printf("                                                           +=============================================================+\n");
    printf("                                                           |                      CUSTOMER FEEDBACK                      |\n");
    printf("                                                           +=============================================================+\n\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("                                                            %s", line);
    }
    fclose(fp);
    printf("                                                                           Press Enter To Return ");
    getchar();
    return 1;
}

int admin_logout(){
    system("cls");
    printf("                                                                                      +==================================+\n");
    printf("                                                                                      |        Log Out Successfully      |\n");
    printf("                                                                                      +==================================+\n");
    printf("                                                                                             Press Enter To Go Back ");
    getchar();
    return 1;
}
