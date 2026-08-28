#ifndef DELIVERYMAN_H
#define DELIVERYMAN_H

typedef struct
{
    int id;
    char name[30];
    char phone[15];
    char pasword[20];
} Deliveryman;


int delivery_man_login();
Deliveryman assign_delivery_man();
int delivery_man_menu();
int view_assigned_orders();
int update_order_status();
int delivery_man_logout();



#endif