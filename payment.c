#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include<stdlib.h>

#include "transaction.h"
#include "customer.h"

int payment(Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total){
    int choice;

    char payment_method[30];

    while(1)
    {
        system("cls");
        printf("                                                                                                                         \n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          |                PAYMENT METHOD               |\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          | 1. Cash On Delivery                         |\n");
        printf("                                                                          | 2. Bkash                                    |\n");
        printf("                                                                          | 3. Nagad                                    |\n");
        printf("                                                                          | 0. Cancel                                   |\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          | Grand Total : %.2f Tk                      |\n", grand_total);
        printf("                                                                          +=============================================+\n");
        printf("                                                                              Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                strcpy(payment_method, "Cash On Delivery");
                return cash_on_delivery(delivery,item_total,delivery_charge,grand_total,payment_method);
            case 2:
                strcpy(payment_method, "Bkash");
                return bkash_payment(delivery,item_total,delivery_charge,grand_total,payment_method);
            case 3:
                strcpy(payment_method, "Nagad");
                return nagad_payment(delivery,item_total,delivery_charge,grand_total,payment_method);
            case 0: 

                return 0;

            default:

                printf("\n                                                                            Invalid Choice.\n");
                printf("                                                                          Press Enter to continue");
                getchar();
        }
    }
}



int cash_on_delivery(Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total,char payment_method[]){
    int choice;

    while(1)
    {
        system("cls");
        printf("                                                                                                                         \n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          |          CASH ON DELIVERY                   |\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          | Items Total      : %.2f Tk\n", item_total);
        printf("                                                                          | Delivery Charge  : %.2f Tk\n", delivery_charge);
        printf("                                                                          +---------------------------------------------+\n");
        printf("                                                                          | Grand Total      : %.2f Tk\n", grand_total);
        printf("                                                                          +=============================================+\n\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          | 1. Confirm Order                            |\n");
        printf("                                                                          | 0. Back                                     |\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                             Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:


                return receipt(delivery,item_total,delivery_charge,grand_total,payment_method);

            case 0:

                return 0;

            default:

                printf("\n                                                                            Invalid Choice.\n");
                printf("                                                                          Press Enter to continue");
                getchar();
        }
    }
}


int bkash_payment(Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total,char payment_method[]){
    char number[20];
    float paid_amount;
    int i;

    while(1)
    {
        system("cls");
        printf("                                                                                                                       \n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                          |                BKASH PAYMENT                |\n");
        printf("                                                                          +=============================================+\n");
        printf("                                                                             Grand Total : %.2f Tk\n", grand_total);
        printf("                                                                          +=============================================+\n");
        printf("                                                                             Enter bKash Number : ");
        fgets(number,sizeof(number),stdin);
        number[strcspn(number,"\n")] = '\0';

        if(strlen(number) != 11)
        {
            printf("                                                                             \nInvalid Mobile Number.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }

        if(number[0] != '0' || number[1] != '1')
        {
            printf("                                                                             \nInvalid Mobile Number.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }

        for(i = 0; number[i] != '\0'; i++)
        {
            if(!isdigit(number[i]))
            {
                printf("                                                                             \nInvalid Mobile Number.\n");
                printf("                                                                             Press Enter to continue");
                getchar();
                break;
            }
        }

        if(number[i] != '\0')
        {
            continue;
        }
            

        printf("                                                                             Enter Paid Amount : ");
        scanf("%f",&paid_amount);
        getchar();

        if(paid_amount != grand_total)
        {
            printf("                                                                             \nInvalid Payment Amount.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }

            return receipt(delivery,item_total,delivery_charge,grand_total,payment_method);
       
    }
}


int nagad_payment(Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total,char payment_method[]){
    char number[20];
    float paid_amount;
    int i;
    while(1)
    {
        system("cls");
        printf("\n");
        printf("                                                                          +==============================================+\n");
        printf("                                                                          |                 NAGAD PAYMENT                |\n");
        printf("                                                                          +==============================================+\n");
        printf("                                                                             Grand Total : %.2f Tk\n", grand_total);
        printf("                                                                          +==============================================+\n");
        printf("\n                                                                             Enter Nagad Number : ");
        fgets(number,sizeof(number),stdin);
        number[strcspn(number,"\n")] = '\0';

        if(strlen(number) != 11)
        {
            printf("\n                                                                             Invalid Mobile Number.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }

        if(number[0] != '0' || number[1] != '1')
        {
            printf("\n                                                                             Invalid Mobile Number.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }

        for(i = 0; number[i] != '\0'; i++)
        {
            if(!isdigit(number[i]))
            {
                printf("\n                                                                             Invalid Mobile Number.\n");
                printf("                                                                             Press Enter to continue");
                getchar();
                break;
            }
        }

        if(number[i] != '\0')
        {
            continue;
        }

        printf("\n                                                                             Enter Paid Amount : ");
        scanf("%f",&paid_amount);
        getchar();

        if(paid_amount != grand_total)
        {
            printf("\n                                                                             Invalid Payment Amount.\n");
            printf("                                                                             Press Enter to continue");
            getchar();
            continue;
        }
            return receipt(delivery,item_total,delivery_charge,grand_total,payment_method);   
    }
}