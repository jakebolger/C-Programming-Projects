#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

//Billing System in C.
//Author Jake Bolger
//06/07/2018
//

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numofItems;
    struct items itm[50];
};
//functions to generate bills
//
void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
        printf("\t   ADV. Billing System");
        printf("\n\t -----------------");
        printf("\nDate:%s", date);
        printf("\nInvoice ToL %s", name);
        printf("\n");
        printf("--------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n------------------------------------");
        printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t", item);
        printf("%d\t\t", qty);
        printf("%.2f\t\t", qty * price);
        printf("\n");
}



void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;
    printf("-------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("CGST @9%s\t\t\t%.2f", "%", cgst);
    printf("SGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n-------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n-------------------------------------\n");
}

//CGST = Central Goods And Service Tax
//SGST = State Goods And Service Tax
//

int main(){
    
    int opt, n;
    char saveBill = 'y', contFlag='y';
    struct orders ord;
    struct orders order;
    char name[50];
    FILE *fp;
    //dashboard
    //
    while(contFlag == 'y'){
        system("cls");
        float total = 0;
        int invoiceFound = 0;
    printf("\t===========ADV. Billing System==============");
    printf("\n\nPlease select your prefered operation");
    printf("\n1. Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nYour Choice");
    scanf("%d", &opt);
    fgetc(stdin);

    switch(opt){
        case 1:
        system("cls");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        strcpy(ord.date, __DATE__);
        printf("\nPlease enter the nnumber of items:\t");
        scanf("%d", &n);
        ord.numofItems = n;

        for(int i =0; i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t", i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("\nPlease enter the quantitiy:\t");
            scanf("%d", &ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHeader(ord.customer,ord.date);
        for(int i = 0; i< ord.numofItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty, ord.itm[i].price);


        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s", &saveBill);

        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.dat", "a+");
            fwrite(&ord, sizeof(struct orders), 1, fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);

        }
        break;

        case 2:
        system("cls");
        fp = fopen("RestaurantBill.dat", "r");
        printf("\n ******YOUR PREVIOUS INVOICES******\n");
        while(fread(&order,sizeof(struct orders), 1, fp)){
            float tot = 0;
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i<order.numofItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;

            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("\nEnter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("cls");
        fp = fopen("RestaurantBill.dat", "r");
        printf("\t ******Invoice of %s******", name);
        while(fread(&order,sizeof(struct orders), 1, fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
                generateBillHeader(order.customer, order.date);
            for(int i = 0; i<order.numofItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;

            }
            generateBillFooter(tot);
            invoiceFound = 1;
            }
            
        }
        if(!invoiceFound){
            printf("sorry the invouice for %s doesnt exits. ", name);
        }
        fclose(fp);
        break;

    case 4:
    printf("\n\t\t Exited:");
    exit(0);
    break;

    default:
    printf("Sorry invalid option");
    break;

    
    }
    //printf("\nYou have chosen %d", opt);
    printf("\nDo you want to perform anbother operation?[y/n] \t");
    scanf("%s", &contFlag);
    }
    printf("\n\t\t Exited:");
    printf("\n\n");

    return 0;
}


