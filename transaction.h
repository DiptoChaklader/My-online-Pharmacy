#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "deliveryman.h"
#include "product.h"


typedef struct
{
    Product product;
    int quantity;
} Cart;


extern int cart_count;
extern Cart cart[100];

typedef struct
{
    char district[30];
    char area[50];
    char house[100];
} Deliveryinfo;

int add_to_cart(Product product);
int view_cart();
int update_cart_quantity();
int remove_cart_item();
int clear_cart();

int checkout();
int generate_order_id();
int receipt(Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total, char payment_method[]);
int save_order(int order_id, Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total, char payment_method[], Deliveryman deliveryman);
int view_order_history();

int payment(Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total);
int cash_on_delivery(Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total, char payment_method[]);
int bkash_payment(Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total, char payment_method[]);
int nagad_payment(Deliveryinfo delivery, float item_total, float delivery_charge, float grand_total, char payment_method[]);



#endif