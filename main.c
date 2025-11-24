#include <stdio.h>
#include <stdlib.h>
#include "data.h"

// Function to display the main menu
void menu() {
    printf("\n===================================\n");
    printf("  SUPERMARKET MANAGEMENT SYSTEM \n");
    printf("===================================\n");
    printf("1. Add New Product (admin)\n");
    printf("2. Display All Products (admin)\n");
    printf("3. Update Product (admin)\n");
    printf("4. Delete Product (admin)\n");
    printf("************************************\n");
    printf("5. Make a Purchase (Customer)\n");
    printf("0. Exit\n");
    printf("===================================\n");
    printf("===================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    loadDatabase();

    scanf("%d",&choice);
    while (choice!=0) {
        menu();

        if (choice!=1 && choice != 0 && choice!=2 && choice!=3 && choice !=4 && choice !=5) {
            printf("Invalid input. Please enter a number (0 - 5).\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                update_product();
                break;
            case 4:
                delete_product();
                break;
            case 5:
                customer();
                break;
            case 0:
                saveDatabase();
                free_memory();

                printf("Thank you for shopping with us. See you soon !!");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        scanf("%d",&choice);
    }



    return 0;
}