#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>
#include<errno.h>

#include "transaction.h"
#include "customer.h"
#include "product.h"
#include "deliveryman.h"


int checkout(){
        Deliveryinfo delivery;

        float item_total = 0;
        float delivery_charge = 0;
        float grand_total = 0;

        int i;

        if(cart_count == 0)
        {
            printf("                                          +==============================+\n");
            printf("                                          |      Your Cart Is Empty      |\n");
            printf("                                          +==============================+\n");
            printf("                                            Please add some products to your cart first. Press Enter to Go back");
            return 0;

        }

    
        for(i = 0; i < cart_count; i++)
        {
         
            item_total += cart[i].product.price * cart[i].quantity;
        }

    system("cls");

    printf("\n");
    printf("                                                                                 +====================================+\n");
    printf("                                                                                 |        DELIVERY INFORMATION        |\n");
    printf("                                                                                 +====================================+\n");
    printf("                                                                                 |  Customer Name : %s\n", current_customer.name);
    printf("                                                                                 |  Phone Number  : %s\n", current_customer.phone);
    printf("                                                                                 |  Enter District : ");
    fgets(delivery.district, sizeof(delivery.district), stdin);
    delivery.district[strcspn(delivery.district, "\n")] = '\0';
    to_upper_case(delivery.district);

    printf("                                                                                 |  Enter Area : ");
    fgets(delivery.area, sizeof(delivery.area), stdin);
    delivery.area[strcspn(delivery.area, "\n")] = '\0';

    printf("                                                                                 |  Enter House/Road : ");
    fgets(delivery.house, sizeof(delivery.house), stdin);
    delivery.house[strcspn(delivery.house, "\n")] = '\0';

    
    if(strcmp(delivery.district, "DHAKA") == 0)
    {
        delivery_charge = 60;
    }    
    else{
            delivery_charge = 120;
        }    

    grand_total = item_total + delivery_charge;

    printf("                                                                                 +=====================================+\n");
    printf("                                                                                 |            ORDER SUMMARY            |\n");
    printf("                                                                                 +=====================================+\n");
    printf("                                                                                 | Total By Item  : %.2f Tk\n", item_total);
    printf("                                                                                 | Delivery Charge : %.2f Tk\n", delivery_charge);
    printf("                                                                                 +-------------------------------------+\n");
    printf("                                                                                 | Grand Total     : %.2f Tk\n", grand_total);
    printf("                                                                                 +=====================================+\n");
    printf("                                                                                    Press Enter to Confirm Order");
    getchar();

    return payment(delivery, item_total, delivery_charge,grand_total);
}

int generate_order_id(){
    FILE *fp;
    char line[500];
    int order_id = 1000;

    fp = fopen("order.txt","r");

    if(fp == NULL)

    {

        return 1001;
    }

    while(fgets(line,sizeof(line),fp))
    

    {

        if(sscanf(line,"Order ID : %d",&order_id) != 1)

        {
            continue;

        }

    }

    fclose(fp);

    return order_id + 1;
}

int receipt(Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total,char payment_method[]){
    int order_id;
    int i;

    Deliveryman deliveryman;

    order_id = generate_order_id();

    deliveryman = assign_delivery_man();

    system("cls");
    printf("\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      |                        ZENPHARMA                            |\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      | Order ID : %d\n",order_id);
    printf("                                                                      | Customer Name : %s\n",current_customer.name);
    printf("                                                                      | Phone Number  : %s\n",current_customer.phone);
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      |                         Products                            |\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      | %-5s %-25s %-8s %-10s %-10s\n","ID","Name","Qty","Price","Total");

    for(i=0;i<cart_count;i++)
    {
        printf("                                                                      | %-5d %-25s %-8d %-10.2f %-10.2f\n",
                cart[i].product.id,
                cart[i].product.name,
                cart[i].quantity,
                cart[i].product.price,
                cart[i].product.price*cart[i].quantity);
    }

    printf("                                                                      +=============================================================+\n");
    printf("                                                                      | Items Total      : %.2f Tk\n",item_total);
    printf("                                                                      | Delivery Charge  : %.2f Tk\n",delivery_charge);
    printf("                                                                      | Grand Total      : %.2f Tk\n",grand_total);
    printf("                                                                      | Payment Method   : %s\n",payment_method);
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      |               Delivery Address                              |\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      | District    : %s\n",delivery.district);
    printf("                                                                      | Area        : %s\n",delivery.area);
    printf("                                                                      | House/Road  : %s\n",delivery.house);
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      |               Deliveryman Information                       |\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      | Deliveryman ID      : %d\n",deliveryman.id);
    printf("                                                                      | Deliveryman Name    : %s\n",deliveryman.name);
    printf("                                                                      | Deliveryman Phone   : %s\n",deliveryman.phone);
    printf("                                                                      | Status  : PENDING\n");
    printf("                                                                      +=============================================================+\n");
    printf("                                                                      |                    THANK YOU FOR SHOPPING                   |\n");
    printf("                                                                      +=============================================================+\n");

    save_order(order_id,delivery,item_total,delivery_charge,grand_total,payment_method,deliveryman);

    reduce_product_stock();

    cart_count = 0;
    printf("                                                                             +=========================================+\n");
    printf("                                                                             |        Order Placed Successfully        |\n");
    printf("                                                                             +=========================================+\n");
    printf("                                                                                      Press Enter to Continue");
    getchar();

    return 1;
}

int save_order(int order_id,Deliveryinfo delivery,float item_total,float delivery_charge,float grand_total,char payment_method[],Deliveryman deliveryman){
    FILE *fp;

    int i;

    fp = fopen("order.txt","a");

    if(fp==NULL)
    {
        printf("Error Opening File.\n");
        return 0;
    }

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"                        ZENPHARMA\n");

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"Order ID : %d\n",order_id);

    fprintf(fp,"Customer Name : %s\n",current_customer.name);

    fprintf(fp,"Phone Number  : %s\n",current_customer.phone);

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"                         Products\n");

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"%-5s %-25s %-8s %-10s %-10s\n",
            "ID","Name","Qty","Price","Total");

    for(i=0;i<cart_count;i++)
    {
        fprintf(fp,
                "%-5d %-25s %-8d %-10.2f %-10.2f\n",

                cart[i].product.id,

                cart[i].product.name,

                cart[i].quantity,

                cart[i].product.price,

                cart[i].product.price*cart[i].quantity);
    }

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"Items Total      : %.2f Tk\n",item_total);

    fprintf(fp,"Delivery Charge  : %.2f Tk\n",delivery_charge);

    fprintf(fp,"Grand Total      : %.2f Tk\n",grand_total);

    fprintf(fp,"Payment Method   : %s\n",payment_method);

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"               Delivery Address\n");

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"District    : %s\n",delivery.district);

    fprintf(fp,"Area        : %s\n",delivery.area);

    fprintf(fp,"House/Road  : %s\n",delivery.house);

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"               Deliveryman Information\n");

    fprintf(fp,"=============================================================\n");

    fprintf(fp,"Deliveryman ID : %d\n",deliveryman.id);

    fprintf(fp,"Deliveryman Name : %s\n",deliveryman.name);

    fprintf(fp,"Deliveryman Phone : %s\n",deliveryman.phone);

    fprintf(fp,"Status  : PENDING\n");

    fprintf(fp,"=============================================================\n");
    fprintf(fp,"================ END ORDER ================\n");
    fprintf(fp,"\n");

    fclose(fp);

    return 1;
}

int view_order_history(){
        FILE *fp;
        char line[300];
        char receipt[6000];
        char phone_text[50];
        int found = 0;


    fp = fopen("order.txt", "r");

        if(fp == NULL)
        {
                printf("\nNo Order History Found.\n");
                printf("Press Enter to Continue");
                getchar();
                return 0;

        }


    system("cls");

    printf("\n");
    printf("                                                  *************************************************************\n");
    printf("                                                                    -----ORDER HISTORY-----\n");
    printf("                                                  *************************************************************\n\n");


    sprintf(phone_text,"Phone Number  : %s",current_customer.phone);


    receipt[0] = '\0';


    while(fgets(line, sizeof(line), fp))
    {   
        strcat(receipt,"                                                  ");
        strcat(receipt, line);


        if(strcmp(line,
                  "================ END ORDER ================\n") == 0)
        {
            if(strstr(receipt, phone_text) != NULL)
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
        printf("                                              No Order History Found.\n");
    }
    printf("                                                  Press Enter to Continue");
    getchar();

    return 1;
}