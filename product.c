#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "product.h"
#include "transaction.h"
#include "customer.h"

int to_upper_case(char str[]){
    int i = 0;
    while(str[i] != '\0')
    {
        str[i] = toupper(str[i]);
        i++;
    }
    return 1;
}



int create_product_file(){
    FILE *fp;
    fp = fopen("product.txt", "r");
    if(fp != NULL)
    {
        fclose(fp);
        return 1;
    }

    fp = fopen("product.txt", "w");
    if(fp == NULL)
    {
        printf("Unable To Create Product File.\n");
        return 0;
    }

    fclose(fp);
    return 1;
}


int product_exists(int id){
    FILE *fp;
    Product product;
    char line[300];

    fp = fopen("product.txt","r");
    if(fp == NULL)
    {
        return 0;
    }

    while(fgets(line,sizeof(line),fp))
    {
        if(sscanf(line, "%d|", &product.id) != 1)
            {
                continue;
            }
        if(product.id == id)
        {   
            printf("                                                     +====================================+\n");
            printf("                                                     |    This Product Already Exists.    |\n");
            printf("                                                     +====================================+\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


int add_product(){
    FILE *fp;

    Product product;

    create_product_file();

    fp = fopen("product.txt", "a");

    if(fp == NULL)
    {
        printf("\n                                                                            Unable To Open Product File.\n");
        return 0;
    }

    printf("                                                                            +=========================================+\n");
    printf("                                                                            |                ADD PRODUCT              |\n");
    printf("                                                                            +=========================================+\n");
    printf("                                                                               Enter Product ID : ");
    scanf("%d", &product.id);
    getchar();

    if(product_exists(product.id))
    {

        fclose(fp);
        printf("                                                                            Press Enter To Return");
        getchar();
        return 0;
    }
    printf("                                                                               Enter Product Name : ");
    fgets(product.name, sizeof(product.name), stdin);
    product.name[strcspn(product.name, "\n")] = '\0';
    to_upper_case(product.name);

    printf("                                                                               Enter Company Name : ");
    fgets(product.company, sizeof(product.company), stdin);
    product.company[strcspn(product.company, "\n")] = '\0';
    to_upper_case(product.company);

    printf("                                                                               Enter Category (MED/ACC/SKN/HH/CC) : ");
    fgets(product.category, sizeof(product.category), stdin);
    product.category[strcspn(product.category, "\n")] = '\0';
    to_upper_case(product.category);

    printf("                                                                               Enter Description : ");
    fgets(product.description, sizeof(product.description), stdin);
    product.description[strcspn(product.description, "\n")] = '\0';

    printf("                                                                               Enter Expiry Date (DD-MM-YYYY) : ");
    fgets(product.expiry_date, sizeof(product.expiry_date), stdin);
    product.expiry_date[strcspn(product.expiry_date, "\n")] = '\0';

    printf("                                                                               Enter Pack Size : ");
    scanf("%d",&product.pack_size);
    getchar();

    printf("                                                                               Enter Price Per Pack : ");
    scanf("%f",&product.price);
    getchar();

    printf("                                                                               Enter Stock : ");
    scanf("%d",&product.stock);
    getchar();

    fprintf(fp, "%d|%s|%s|%s|%s|%s|%.2f|%d|%d\n",
                product.id,
                product.name,
                product.category,
                product.company,
                product.description,
                product.expiry_date,
                product.price,
                product.pack_size,
                product.stock);
    printf("                                                                            +=========================================+\n\n");
    printf("                                                                            +=========================================+\n");
    printf("                                                                            |        Product Added Successfully       |\n");
    printf("                                                                            +=========================================+\n");
    fclose(fp);
    printf("\n                                                                                Press Enter to go back");
    getchar(); 
    
    
    return 1;    

   
}


int display_product_details(Product product){   
    char category[30];

    if(strcmp(product.category,"MED")==0)
        strcpy(category,"Medicine");

    else if(strcmp(product.category,"ACC")==0)
        strcpy(category,"Medical Accessories");

    else if(strcmp(product.category,"SKN")==0)
        strcpy(category,"Skin Care");

    else if(strcmp(product.category,"HH")==0)
        strcpy(category,"Health & Hygiene");

    else if(strcmp(product.category,"CC")==0)
        strcpy(category,"Child Care");

    else
        strcpy(category,"Unknown");

    system("cls");
    printf("\n");
    printf("                                                                           +============================================+\n");
    printf("                                                                           |                Product Details             |\n");
    printf("                                                                           +============================================+\n");
    printf("                                                                              Product ID   : %d\n",product.id);
    printf("                                                                              Name         : %s\n",product.name);
    printf("                                                                              Company      : %s\n",product.company);
    printf("                                                                              Category     : %s\n",category);
    printf("                                                                              Description  : %s\n",product.description);
    printf("                                                                              Expiry Date  : %s\n",product.expiry_date);
    printf("                                                                              Pack Size    : %d\n",product.pack_size);
    printf("                                                                              Price/Pack   : %.2f Tk\n",product.price);
    printf("                                                                              Stock        : %d\n",product.stock);
    printf("                                                                           +============================================+\n");
    return 1;
}

int view_product(char category[]){
    int choice;
    FILE *fp;
    Product product;
    char line[300];
    int found = 0;
    fp = fopen("product.txt", "r");
    if(fp == NULL)
    {
        printf("                                                      +=======================================+\n");
        printf("                                                      |      Unable To Open Product File.     |\n");
        printf("                                                      +=======================================+\n");
        return 0;
    }


    printf("\n");
    printf("                                                      +=====================================================================================+\n");
    printf("                                                      |%-12s | %-20s | %-15s | %-12s | %-14s|\n",
       "ID",
       "Name",
       "Company",
       "Price/pack",
       "Stock");
    printf("                                                      +=====================================================================================+\n");

    while(fgets(line, sizeof(line), fp))
    {
    if(sscanf(line,
        "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%14[^|]|%f|%d|%d",
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
            printf("                                                      |%-12d | %-20s | %-15s | %-12.2f | %-14d|\n",
        product.id,
        product.name,
        product.company,
        product.price,
        product.stock);

            found = 1;
        }
    }

    printf("                                                      +======================================================================================+\n");

    if(found == 0)
    {   fclose(fp);
        printf("                                                                                              +===================================+\n");
        printf("                                                                                              |       No Product Available        |\n");
        printf("                                                                                              +===================================+\n");
        printf("                                                                                   Press Enter To Continue\n");
        getchar();
        return 0;
    }
    fclose(fp);
    printf("\n1. Search Product\n");
    printf("2. Back\n");

    printf("\nEnter Your Choice : ");
    scanf("%d", &choice);
    getchar();

    switch(choice)
    {
    case 1:

        

        search_product(category);

        break;

    case 2:

        return 0;

    default:

        invalid_item_choice();
        
        break;
    }

    return 1;
}


int search_product(char category[])
{   
    FILE *fp;
    Product product;

    char line[300];
    char input[100];
    int id;
    int isID;

    fp = fopen("product.txt", "r");
    if(fp == NULL)
    {
        printf("                                                      +=====================================+\n");
        printf("                                                      |     Unable To Open Product File     |\n");
        printf("                                                      +=====================================+\n");
        return 0;
    }
    printf("                                                        +====================================================+\n");
    printf("                                                             Enter Product ID Or Product Name (0 = Back) : ");
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
            if(sscanf(line, "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%14[^|]|%f|%d|%d",
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

        if(strcmp(product.category, category) != 0){
                    continue;
            }

        if(isID)
        {
            if(product.id == id)
            {   
    
                display_product_details(product);
                printf("                                                                                 +===============================+\n");
                printf("                                                                                 |    Press Enter To Go Back     |\n");
                printf("                                                                                 +===============================+");
                getchar(); 

                fclose(fp);
                return 1;
            }
        }
        else
        {   to_upper_case(product.name);
            if(strcmp(product.name, input) == 0)
            {
                display_product_details(product);
                printf("                                                                                 +===============================+\n");
                printf("                                                                                 |    Press Enter To Go Back     |\n");
                printf("                                                                                 +===============================+");
                getchar();
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);
    system("cls");
    printf("                                                                                    +==============================+\n");
    printf("                                                                                    |      Product Not Found.      |\n");
    printf("                                                                                    +==============================+\n");
    printf("                                                                                         Press Enter To Go Back");
    getchar();
    return 0;
}

int update_product(){

        FILE *fp, *temporary;

            Product product;

            char line[300];
            int id;
            int found = 0;

        fp = fopen("product.txt", "r");

            if(fp == NULL)
            {
                printf("\nUnable To Open Product File.\n");
                printf("Press Enter To Go Back");
                getchar();
                return 0;
            }

            temporary = fopen("temporary.txt", "w");

            if(temporary == NULL)
            {
                fclose(fp);
                printf("\nUnable To Create Temp File.\n");
                printf("Press Enter To Go Back");
                getchar();
                return 0;
            }
    printf("                                                                            +=========================================+\n");
    printf("                                                                            |           Update Product Detail         |\n");
    printf("                                                                            +=========================================+\n");
    printf("                                                                               Enter Product ID To Update : ");
    scanf("%d", &id);
    getchar();

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,
        "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%19[^|]|%f|%d|%d",
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

        if(product.id == id)
        {
            found = 1;

            printf("                                                                               Enter New Product Name : ");
            fgets(product.name,sizeof(product.name),stdin);
            product.name[strcspn(product.name,"\n")] = '\0';
            to_upper_case(product.name);

            printf("                                                                               Enter New Company : ");
            fgets(product.company,sizeof(product.company),stdin);
            product.company[strcspn(product.company,"\n")] = '\0';
            to_upper_case(product.company);

            printf("                                                                               Enter New Category : ");
            fgets(product.category,sizeof(product.category),stdin);
            product.category[strcspn(product.category,"\n")] = '\0';
            to_upper_case(product.category);

            printf("                                                                               Enter New Description : ");
            fgets(product.description,sizeof(product.description),stdin);
            product.description[strcspn(product.description,"\n")] = '\0';

            printf("                                                                               Enter Expiry Date : ");
            fgets(product.expiry_date,sizeof(product.expiry_date),stdin);
            product.expiry_date[strcspn(product.expiry_date,"\n")] = '\0';

            printf("                                                                               Enter Pack Size : ");
            scanf("%d",&product.pack_size);
            getchar();

            printf("                                                                               Enter Price : ");
            scanf("%f",&product.price);
            getchar();

            printf("                                                                               Enter Stock : ");
            scanf("%d",&product.stock);
            getchar();
        }

        fprintf(temporary,
        "%d|%s|%s|%s|%s|%s|%.2f|%d|%d\n",
        product.id,
        product.name,
        product.category,
        product.company,
        product.description,
        product.expiry_date,
        product.price,
        product.pack_size,
        product.stock);
    }

    fclose(fp);
    fclose(temporary);

    remove("product.txt");
    rename("temporary.txt","product.txt");

    if(found==1){
        printf("                                                                            +=========================================+\n\n");
        printf("                                                                            +=========================================+\n");
        printf("                                                                            |      Product Updated Successfully       |\n");
        printf("                                                                            +=========================================+\n");
    }
    else{
                printf("\n                                                                               Product Not Found.\n");
        }

    printf("\n                                                                               Press Enter To Go Back");
    getchar();

    return found;
}


int delete_product(){

    FILE *fp, *temporary;

    Product product;

    char line[300];

    int id;
    int found = 0;

    fp = fopen("product.txt", "r");

    if(fp == NULL)
    {
        printf("\nUnable To Open Product File.\n");
        return 0;
    }

    temporary = fopen("temporary.txt", "w");

    if(temporary == NULL)
    {
        printf("\nUnable To Create Temporary File.\n");
        printf("Press Enter To Go Back");
        getchar();
        fclose(fp);
        return 0;
    }

    printf("                                                                            +=========================================+\n");
    printf("                                                                            |           Delete Any Product            |\n");
    printf("                                                                            +=========================================+\n");
    printf("                                                                               Enter Product ID : ");
    scanf("%d", &id);
    getchar();

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,
        "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%19[^|]|%f|%d|%d",
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

        if(product.id == id)
        {
            found = 1;
            continue;
        }

        fprintf(temporary,
        "%d|%s|%s|%s|%s|%s|%.2f|%d|%d\n",
        product.id,
        product.name,
        product.category,
        product.company,
        product.description,
        product.expiry_date,
        product.price,
        product.pack_size,
        product.stock);
    }

    fclose(fp);
    fclose(temporary);

    remove("product.txt");
    rename("temporary.txt", "product.txt");

    if(found==1)
        {
            printf("                                                                            +=========================================+\n\n");
            printf("                                                                            +=========================================+\n");
            printf("                                                                            |      Product Deleted Successfully       |\n");
            printf("                                                                            +=========================================+\n");
        }
    else
        {
            printf("\nProduct Not Found.\n");
        }

    printf("\n                                                                               Press Enter To Go Back");
    getchar();

    return found;

}

int update_stock(){

 FILE *fp, *temporary;

    Product product;

    char line[300];

    int id;
    int found = 0;

    fp = fopen("product.txt", "r");

    if(fp == NULL)
    {
        printf("\n                                                                            Unable To Open Product File.\n");
        printf("                                                                            Press Enter To Go Back");
        getchar();
        return 0;
    }

    temporary = fopen("temporary.txt", "w");

    if(temporary == NULL)
    {
        printf("\n                                                                            Unable To Create Temporary File.\n");
        fclose(fp);
        return 0;
    }

    printf("                                                                            +=========================================+\n");
    printf("                                                                            |           Update Product Detail         |\n");
    printf("                                                                            +=========================================+\n\n");
    printf("                                                                               Enter Product ID : ");
    scanf("%d", &id);
    getchar();

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,
        "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%19[^|]|%f|%d|%d",
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

        if(product.id == id)
        {
            found = 1;
            printf("                                                                               Current Stock : %d\n", product.stock);
            printf("                                                                               Enter New Stock : ");
            scanf("%d", &product.stock);
            getchar();

        }

        fprintf(temporary,
        "%d|%s|%s|%s|%s|%s|%.2f|%d|%d\n",
        product.id,
        product.name,
        product.category,
        product.company,
        product.description,
        product.expiry_date,
        product.price,
        product.pack_size,
        product.stock);
    }

    fclose(fp);
    fclose(temporary);

    remove("product.txt");
    rename("temporary.txt", "product.txt");

   if(found==1){
        printf("                                                                            +=========================================+\n\n");
        printf("                                                                            +=========================================+\n");
        printf("                                                                            |    Product Stock Updated Successfully   |\n");
        printf("                                                                            +=========================================+\n");
                }
    else{
                printf("\n                                                                            Product Not Found.\n");
        }

    printf("\n                                                                                  Press Enter To Go Back");
    getchar();

    return found;


}


int edit_about_pharmacy(){

    FILE *fp;

    char line[500];

    fp = fopen("about.txt", "w");

    if(fp == NULL)
    {
        printf("\nUnable To Open About Pharmacy File.\n");
        return 0;
    }
    
   

    printf("Write About Pharmacy.\n");
    printf("Type END in a new line to finish.\n");

    while(1)
    {
        fgets(line, sizeof(line), stdin);

        line[strcspn(line, "\n")] = '\0';

        if(strcmp(line, "END") == 0)
            break;

        fprintf(fp, "%s\n", line);
    }

    fclose(fp);

    printf("\nAbout Pharmacy Updated Successfully.\n");

    printf("\nPress Enter To Go Back");
    getchar();

    return 1;

}

int reduce_product_stock()
{
    FILE *fp;
    FILE *temporary;

    Product product;

    char line[300];

    int i;

    fp = fopen("product.txt", "r");

    if(fp == NULL)
    {
        printf("\nError Opening Product File.\n");
        return 0;
    }

    temporary = fopen("temporary.txt", "w");

    if(temporary == NULL)
    {
        fclose(fp);

        printf("Error : %s\n", strerror(errno));
        return 0;
    }

    while(fgets(line, sizeof(line), fp))
    {
        if(sscanf(line,
                  "%d|%29[^|]|%29[^|]|%29[^|]|%49[^|]|%14[^|]|%f|%d|%d",
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

        for(i = 0; i < cart_count; i++)
        {
            if(product.id == cart[i].product.id)
            {
                product.stock -= cart[i].quantity;

                if(product.stock < 0)
                {
                    product.stock = 0;
                }

                break;
            }
        }

        fprintf(temporary,
                "%d|%s|%s|%s|%s|%s|%.2f|%d|%d\n",
                product.id,
                product.name,
                product.category,
                product.company,
                product.description,
                product.expiry_date,
                product.price,
                product.pack_size,
                product.stock);
    }

    fclose(fp);
    fclose(temporary);

    remove("product.txt");
    rename("temporary.txt", "product.txt");

    return 1;
}