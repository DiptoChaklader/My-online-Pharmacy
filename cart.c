#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include"customer.h"
#include "transaction.h"

Cart cart[100];
int cart_count = 0;



int add_to_cart(Product product){
        int i;

        for(i = 0; i < cart_count; i++)
        {
            if(cart[i].product.id == product.id)
                {
                    printf("                     +================================================+\n");
                    printf("                     |       This Product Already Added To Cart       |\n");
                    printf("                     +================================================+\n");
                    printf("                        Pass Enter To Continue : ");
                    getchar();
                    return 0;
                }
        }

    cart[cart_count].product = product;
    cart[cart_count].quantity = 1;
    cart_count++;

    printf("                                                                           +================================================+\n");
    printf("                                                                           |       Product Added To Cart Successfully       |\n");
    printf("                                                                           +================================================+\n");
    printf("                                                                                    Please Enter To Continue");
    getchar();
    return 1;
}

int view_cart(){
    int i;
    int choice;
    float total = 0;

    if(cart_count == 0)
    {
        printf("                                                                         +==============================================================+\n");
        printf("                                                                         |                      Your Cart Is Empty                      |\n");
        printf("                                                                         +==============================================================+\n");
        printf("                                                                                                                                          \n");
        printf("                                                                                              Press Enter To Go Back ");
        getchar();
        return 0;
    }

    while(1)
    {
        system("cls");

        total = 0;

        printf("\n");
        printf("                                                 +=============================================================================================================+\n");
        printf("                                                 |                                                 YOUR SHOPPING CART                                          |\n");
        printf("                                                 +=============================================================================================================+\n");
        printf("                                                 | %-8s %-25s %-12s %-10s %-12s                                     |\n", "ID", "Name", "Price/Pack", "Qty/Pack", "Total");
        printf("                                                 +-------------------------------------------------------------------------------------------------------------+\n");

        for(i = 0; i < cart_count; i++)
        {
            printf("                                                 | %-8d %-25s %-12.2f %-10d %-12.2f                                     |\n",
                      cart[i].product.id,
                      cart[i].product.name,
                      cart[i].product.price,
                      cart[i].quantity,
                      cart[i].product.price * cart[i].quantity);
                      total += cart[i].product.price * cart[i].quantity;
        }

        printf("                                                 +-------------------------------------------------------------------------------------------------------------+\n");
        printf("                                                 |  Grand Total : %.2f Tk                                                                                       \n", total);
        printf("                                                 +=============================================================================================================+\n");
        printf("                                                                                                                                                                \n");
        printf("                                                                                 +============================+\n");
        printf("                                                                                 | 1. Update Quantity         |\n");
        printf("                                                                                 | 2. Remove Item             |\n");
        printf("                                                                                 | 3. Clear Cart              |\n");
        printf("                                                                                 | 4. Checkout                |\n");
        printf("                                                                                 | 5. Back                    |\n");
        printf("                                                                                 +============================+\n");
        printf("                                                                                                               \n");    
        printf("                                                                                     Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
                update_cart_quantity();
                break;

            case 2:
                remove_cart_item();
                break;

            case 3:
                clear_cart();
                break;

            case 4:
                checkout();
                break;

            case 5:
                return 1;

            default:
                printf("                                                                                +=================================================+\n");
                printf("                                                                                |                Invalid Choice.                  |\n");
                printf("                                                                                +=================================================+\n");
                printf("                                                                                      Press Enter To Continue : ");
                getchar();
        }
    }
}

int update_cart_quantity(){
        int id;
        int quantity;
        int i;

    if(cart_count == 0)
    {
        printf("                                                  +=================================================+\n");
        printf("                                                  |               Your Cart Is Empty.               |\n");
        printf("                                                  +=================================================+\n");
        printf("                                                                Press Enter To Continue  ");
        return 0;
    }
    printf("                                                 +=================================================+\n");
    printf("                                                     Enter Product ID (0 = Back) : ");
    scanf("%d",&id);
    getchar();

    if(id == 0)
    {
        printf("Please press Enter to continue.");
        getchar();    
        return 0;
    }
        

    for(i = 0; i < cart_count; i++)
    {
        if(cart[i].product.id == id)
        {   
            printf("                                                 +====================================+\n");
            printf("                                                    Current Quantity   : %d\n", cart[i].quantity);
            printf("                                                    Enter New Quantity : ");
            scanf("%d",&quantity);
            getchar();

            if(quantity <= 0)
            {
                printf("                                                                                 +======================+\n");
                printf("                                                                                 |   Invalid Quantity   |\n");
                printf("                                                                                 +======================+\n");
                printf("                                                                                  Press Enter To Continue");
                getchar();
                return 0;
            }

            if(quantity > cart[i].product.stock)
            {
                printf("                                                                              +=====================================+\n");
                printf("                                                                              |   Only %d Items Available In Stock  |\n",cart[i].product.stock);
                printf("                                                                              +=====================================+\n");
                printf("                                                                                   Press Enter To Continue");
                getchar();
                return 0;
            }

            cart[i].quantity = quantity;
            printf("                                                                                    +=====================================+\n");
            printf("                                                                                    |    Quantity Updated Successfully    |\n");
            printf("                                                                                    +=====================================+\n");
            printf("                                                                                          Press Enter To Continue");
            getchar();                               
            return 1;
        }
    }
    printf("                                                                                    +=====================================+\n");
    printf("                                                                                    |   Product Not Found In Cart.         \n");
    printf("                                                                                    +=====================================+\n");
    printf("                                                                                          Press Enter To Continue");
    getchar();

    return 0;
}


int remove_cart_item(){
        int id;
        int i, j;

        if(cart_count == 0)
        {  
                printf("                                                  +===============================+\n");
                printf("                                                  |      Your Cart Is Empty       |\n");
                printf("                                                  +===============================+\n");
                printf("                                                       Press Enter To Continue : ");
                getchar();
                return 0;

        }
        printf("                                                 +=================================================+\n");
        printf("                                                     Enter Product ID To Remove (0 = Back) : ");
        scanf("%d", &id);
        getchar();

        if(id == 0){
        return 0;
        }

        for(i = 0; i < cart_count; i++)
        {
            if(cart[i].product.id == id)
            {
                    for(j = i; j < cart_count - 1; j++)
                {
                        cart[j] = cart[j + 1];
                }   

                cart_count--;
                printf("                                                 +==========================================+\n");
                printf("                                                 |  Product Removed From Cart Successfully  |\n");
                printf("                                                 +==========================================+\n");
                printf("                                                      Press Enter To Continue : ");
                getchar();

                return 1;
            }
        }
        printf("                                                 +=========================================+\n");
        printf("                                                 |        Product Not Found In Cart        |\n");
        printf("                                                 +=========================================+\n");
        printf("                                                        Press Enter To Continue :");
        getchar();

    return 0;
}


int clear_cart(){
        char choice;

        if(cart_count == 0)
        {
            printf("                                                 +====================================+\n");
            printf("                                                 |     Your Cart Is Already Empty     |\n");
            printf("                                                 +====================================+\n");
            printf("                                                        Press Enter To Continue");
            getchar();
            return 0;

        }
        printf("                                                 +========================================================+\n");
        printf("                                                      Are You Sure You Want To Clear The Cart? (Y/N) : ");
        scanf(" %c", &choice);
        getchar();

        choice = toupper(choice);

        if(choice == 'Y')
        {
            cart_count = 0;
            printf("                                                  +========================================+\n");
            printf("                                                  |       Cart Cleared Successfully        |\n");
            printf("                                                  +========================================+\n");


        }

        else if(choice == 'N')
        {
            printf("                                                 +===================================+\n");
            printf("                                                 |        Operation Cancelled        |\n");
            printf("                                                 +===================================+\n");

        }
        else
        {
            printf("                                                  +==================================+\n");
            printf("                                                  |          Invalid Choice          |\n");
            printf("                                                  +==================================+\n");

        }

        printf("                                                        Press Enter To Continue :");
        getchar();

        return 1;
}