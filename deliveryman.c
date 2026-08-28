#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "deliveryman.h"
#include "customer.h"
#include "transaction.h"
#include "product.h"

int current_deliveryman_id = 0;

char current_deliveryman_name[30];

char current_deliveryman_phone[15];


Deliveryman assign_delivery_man(){
    FILE *fp;

    Deliveryman deliveryman[100];
    Deliveryman selected;
    

    char line[200];

    int count = 0;
    int random_index;

    fp = fopen("deliverymaninfo.txt","r");

    if(fp == NULL)
    {
        printf("Error : %s\n", strerror(errno));

        selected.id = 0;

        return selected;
    }

    while(fgets(line,sizeof(line),fp))
    {
        if(sscanf(line, "%d|%29[^|]|%14[^|]|%19[^\n]",
            &deliveryman[count].id,
            deliveryman[count].name,
            deliveryman[count].phone,
            deliveryman[count].pasword) == 4)
        {
            count++;
        }
    }

    fclose(fp);

    if(count == 0)
    {
        selected.id = 0;
        return selected;
    }

    srand(time(NULL));

    random_index = rand() % count;

    selected = deliveryman[random_index];

    return selected;
}

int delivery_man_login(){
    FILE *fp;
    char line[200];
    Deliveryman deliveryman;
    char phone[15];
    char password[20];
    
    while (getchar() != '\n' && getchar() != EOF);

    fp = fopen("deliverymaninfo.txt", "r");

    if(fp == NULL)
    {
        printf("Error: %s", strerror(errno));
        printf("Press Enter to Continue");
        return 0;
    }

    system("cls");
    printf("\n");
    printf("                                                                                                                     \n");
    printf("                                                                          +=========================================+\n");
    printf("                                                                          |           DELIVERYMAN LOGIN             |\n");
    printf("                                                                          +=========================================+\n");
    printf("                                                                          |                                           \n");
    printf("                                                                          |  Phone Number : ");

    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    printf("                                                                          |  Password     : ");

    input_password(password);

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,
                    "%d|%29[^|]|%14[^|]|%19[^\n]",
                    &deliveryman.id,
                    deliveryman.name,
                    deliveryman.phone,
                    deliveryman.pasword) != 4)
        {
            continue;
        }

        if(strcmp(phone, deliveryman.phone) == 0 &&
            strcmp(password, deliveryman.pasword) == 0)
        {
            current_deliveryman_id = deliveryman.id;
            strcpy(current_deliveryman_name,deliveryman.name);
            strcpy(current_deliveryman_phone,deliveryman.phone);

            fclose(fp);

            printf("                                                                          |                                          \n");
            printf("                                                                          +=========================================+\n");
            printf("                                                                          |              Login Successful           |\n");
            printf("                                                                          +=========================================+\n");
            printf("                                                                                                                     \n");
            printf("                                                                                  Press Enter to Continue");
            getchar();
            return 1;
        }
    }

    fclose(fp);
    printf("                                                                          |                                          \n");
    printf("                                                                          +=========================================+\n");
    printf("                                                                          |    Invalid Phone Number or Password     |\n");
    printf("                                                                          +=========================================+\n");
    printf("                                                                                                                     \n");
    printf("                                                                                  Press Enter to Continue");
    getchar();
    return 0;
}


int delivery_man_menu(){
    int choice;

    while(1)
    {
        Print_Delivery_Man_Page();
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                view_assigned_orders();
                break;

            case 2:
                update_order_status();
                break;

            case 3:
                delivery_man_logout();
                return 1;

            default:

                printf("                                                                          +=========================================+\n");
                printf("                                                                          |              Invalid Choice             |\n");
                printf("                                                                          +=========================================+\n");
                printf("                                                                                                                     \n");
                printf("                                                                                  Press Enter to Continue");
                getchar();
        }
    }

    return 0;
}



int view_assigned_orders(){
        FILE *fp;

        char line[300];
        char receipt[6000];
        char id_text[50];
        int found = 0;

        fp = fopen("order.txt", "r");
        if(fp == NULL)
        {
            printf("\n                                                                   No Order Found.\n");
            printf("                                                                    Press Enter to Continue");
            return 0;
        }

    system("cls");
    printf("\n");
    printf("                                                                       +=========================================+\n");
    printf("                                                                       |             ASSIGNED ORDERS             |\n");
    printf("                                                                       +=========================================+\n");
    printf("                                                                                                                     \n");
    sprintf(id_text,"Deliveryman ID : %d",current_deliveryman_id);

    receipt[0] = '\0';

    while(fgets(line, sizeof(line), fp))
    {
        strcat(receipt,"                                                                 ");
        strcat(receipt, line);
        if(strcmp(line,"================ END ORDER ================\n") == 0)
        {
            if(strstr(receipt, id_text) != NULL)
            {
                printf("%s\n", receipt);
                found = 1;
            }

            receipt[0] = '\0';
        }
    }

    fclose(fp);

    if(found == 0)
    {
        printf("                                                                          +=========================================+\n");
        printf("                                                                          |        No Assigned Orders Found.        |\n");
        printf("                                                                          +=========================================+\n");
    }
    printf("                                                                              Press Enter to Continue");
    getchar();
    return 1;
}


int update_order_status(){
    FILE *fp;
    FILE *temporary;
    char line[300];
    char receipt[6000];
    char order_id_text[50];
    char deliveryman_id_text[50];
    char input_order_id[20];
    int found = 0;


    fp = fopen("order.txt", "r");

    if(fp == NULL)
    {
        printf("                                                                         +================================+\n");
        printf("                                                                         |         No Orders Found        |\n");
        printf("                                                                         +================================+\n");
        printf("                                                                            Please Create Order First.\n");
        getchar();
        return 0;
    }


    temporary = fopen("temporary.txt", "w");

    if(temporary == NULL)
    {
        fclose(fp);
        printf("                                                                         +=====================================+\n");
        printf("                                                                         |   Error Opening Temporary File      |\n");
        printf("                                                                         +=====================================+\n");
        printf("                                                                            Please Try Again.\n");
        getchar();
        return 0;
    }


    system("cls");
    printf("\n");
    printf("                                                                             +=========================================+\n");
    printf("                                                                             |           UPDATE ORDER STATUS           |\n");
    printf("                                                                             +=========================================+\n");
    printf("                                                                             |                                         |\n");
    printf("                                                                             |  Enter Order ID : ");
    fgets(input_order_id,
          sizeof(input_order_id),
          stdin);

    input_order_id[strcspn(input_order_id, "\n")] = '\0';


    sprintf(order_id_text,
            "Order ID : %s",
            input_order_id);


    sprintf(deliveryman_id_text,
            "Deliveryman ID : %d",
            current_deliveryman_id);


    receipt[0] = '\0';


    while(fgets(line, sizeof(line), fp))
    {
        strcat(receipt, line);


        if(strcmp(line,"================ END ORDER ================\n") == 0)
        {
            if(strstr(receipt, order_id_text) != NULL && strstr(receipt, deliveryman_id_text) != NULL)
            {
                char *status;
                char new_receipt[6000];
                int before_status;
                status = strstr(receipt,"Status  : PENDING");

                if(status != NULL)
                {
                    before_status = status - receipt;

                    strncpy(new_receipt,receipt,before_status);

                    new_receipt[before_status] = '\0';

                    strcat(new_receipt,"Status  : DELIVERED");
                    strcat(new_receipt,status + strlen("Status  : PENDING"));
                    strcpy(receipt,new_receipt);

                    found = 1;
                }
            }

            fprintf(temporary,"%s",receipt);
            receipt[0] = '\0';
        }
    }


    fclose(fp);
    fclose(temporary);


    if(found == 1)
    {
        remove("order.txt");
        rename("temporary.txt","order.txt");
        printf("                                                                             +=========================================+\n");
        printf("                                                                             |    Order Status Updated Successfully    |\n");
        printf("                                                                             +=========================================+\n");
    }
    else
        {
            remove("temporary.txt");
            printf("                                                                             +============================================+\n");
            printf("                                                                             |   Order Not Found or Not Assigned to You.  |\n");
            printf("                                                                             +============================================+\n");
        }

    printf("                                                                                  Press Enter to Continue");
    getchar();
    return 1;
}


int delivery_man_logout(){
    current_deliveryman_id = 0;
    strcpy(current_deliveryman_name,"");
    strcpy(current_deliveryman_phone,"");
    printf("                                                                             +=========================================+\n");
    printf("                                                                             |             Logout Successful           |\n");
    printf("                                                                             +=========================================+\n");
    printf("                                                                                  Press Enter to Continue");
    getchar();
    return 1;
}