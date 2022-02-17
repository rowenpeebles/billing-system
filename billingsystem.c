/* A restaurant biling system that takes user input
 * for information regarding food/drink items. Calculates 
 * total bill price adding discounts and displays an 
 * invoice within the terminal.
 *
 * Users can then search for receipts via the GUI by 
 * customer name and the receipt/s are displayed. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to generate bill header
void generateBillHeader(char name[50], char date[30]);

// Function to generate bill body
void generateBillBody(char item[30], int qty, float price);

// Function to generate bill footer
void generateBillFooter(float total);

// Creating the struct 'items' adding variables
struct items
{
    char item[20];
    float price;
    int qty;
};

// Creating the struct 'orders' adding variables
struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;

    struct items itm[50];
};

int main()
{
    int opt, n;
    struct orders ord;
    struct orders order;
    float total;
    char name[50], filename[50];
    char saveBill = 'y', contFlag = 'y';
    FILE *fp;

    // Displaying user dashboard
    while (contFlag == 'y'){
    system("clear");
    float total = 0;
    int invoiceFound = 0;
    printf("\n\n");
    printf("\t==========    RESTAURANTX     ==========");
    printf("\n\n\t1.Generate An Invoice");
    printf("\n\n\t2.Show All Invoices");
    printf("\n\n\t3.Search For An Invoice");
    printf("\n\n\t4.Exit System");
    printf("\n\n\t========================================\n");


    // Prompting user to select an operation
    printf("\n\n\tSelect An Operation:\t");
    scanf("%d", &opt);
    fgetc(stdin);

    // Conditional switch-case statement for operation 1
    switch (opt)
    {
        case 1:
        system("clear");
        printf("\n\n");
        printf("\t==========    NEW INVOICE     ==========");
        printf("\n\n\tName of Customer:\t");
        fgets(ord.customer, 50, stdin);
        ord.customer[strlen(ord.customer) - 1] = 0;
        strcpy(ord.date, __DATE__);
        printf("\n\tNumber of Items:\t");
        scanf("%d", &n);
        ord.numOfItems = n;

        for (int i = 0; i < n; ++i)
        {
            fgetc(stdin);
            printf("\n\t========================================");
            printf("\n\n\tName of Item %d: \t", i + 1);
            fgets(ord.itm[i].item, 20, stdin);
            ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
            printf("\n\tQuantity:\t\t");
            scanf("%d", &ord.itm[i].qty);
            printf("\n\tUnit Price:\t\t");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        system("clear");

        generateBillHeader(ord.customer, ord.date);

        for (int i = 0; i < ord.numOfItems; ++i)
        {
            generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }

        generateBillFooter(total);

        printf("\n\tSave This Invoice? [y/n]: ");
        scanf("%s", &saveBill);

        if (saveBill == 'y')
        {
            fp = fopen("RestaurantBill.txt", "a+");
            fwrite(&ord, sizeof(struct orders), 1, fp);

            if (fwrite != 0)
            {
                printf("\n\tSuccessfully Saved...\n");
            }

            else
            {
                printf("\n\tError, File Not Saved...");
            }

            fclose(fp);
        }

        break;

        // Conditional switch-case statement for operation 2
        case 2:
        system("clear");
        fp = fopen("RestaurantBill.txt", "r");
        printf("\n ******* Your Previous Invoices *******\n");

        while (fread(&order, sizeof(struct orders), 1, fp))
        {
            float tot = 0;
            generateBillHeader(order.customer, order.date);

            for (int i = 0; i < order.numOfItems; ++i)
            {
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }

            generateBillFooter(tot);
        }

        fclose(fp);
        break;

        // Conditional switch-case statement for operation 3
        case 3:
        system("clear");
        printf("\n\n\t  ==========    SEARCH NAME     ==========");
        printf("\n\n\tEnter The Name Of The Customer:\t");
        //fgetc(stdin);
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = 0;
        system("clear");
        
        fp = fopen("RestaurantBill.txt", "r");
        printf("\n\t******* Invoices Of %s *******\n", name);

        while (fread(&order, sizeof(struct orders), 1, fp))
        {
            float tot = 0;

            if (!strcmp(order.customer, name))
            {
                generateBillHeader(order.customer, order.date);

                for (int i = 0; i < order.numOfItems; ++i)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }

                generateBillFooter(tot);
                invoiceFound = 1;
            }
        }

        if (!invoiceFound)
        {
            printf("\n\tNo Invoice Found For %s..\n", name);
        }

        fclose(fp);
        break;

        // Conditional switch-case statement for operation 4
        case 4:
        printf("\n\tProgram Closed..\n\n");
        exit(0);
        break;

        // Conditional switch-case statement for default case
        default:
        printf("\tSorry, Invalid Option Selected");
        break;
    }

    printf("\n\tPerform Another Operation? [y/n]: ");
    scanf("%s", &contFlag);

    }

    printf("\n\tProgram Closed..\n\n");
    printf("\n\n");

    return 0;
}


// Function to generate bill header
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");

    printf("\t==========    RESTAURANTX     ==========");
    printf("\n\n\tDate: %s", date);
    printf("\n\tInvoice To: %s", name);
    printf("\n");
    printf("\t----------------------------------------");
    printf("\n\tItems\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n\t----------------------------------------");
    printf("\n");
}

// Function to generate bill body
void generateBillBody(char item[30], int qty, float price)
{
    printf("\t%s\t", item);
    printf("\t%d\t", qty);
    printf("\t%.2f", qty * price);
    printf("\n");
}

// Function to generate bill footer
void generateBillFooter(float total)
{
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;

    printf("\t----------------------------------------\n");
    printf("\tSub Total\t\t\t%.2f", total);
    printf("\n\tDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t\t-------");
    printf("\n\tNet Total\t\t\t%.2f", netTotal);
    printf("\n\tCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n\tSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n\t----------------------------------------");
    printf("\n\tGrand Total\t\t\t%.2f", grandTotal);
    printf("\n\t----------------------------------------\n");
}
