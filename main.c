#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void menu() {
    
}

int main(void) {
    int choice;

    load_dbfile();

    while (1) {

    printf("\n===================================\n");
    printf("  SUPERMARKET MANAGEMENT SYSTEM \n");
    printf("===================================\n");
    printf("1. Add New Product (admin)\n");
    printf("2. Display All Products\n");
    printf("3. Update Product (admin)\n");
    printf("4. Delete Product (admin)\n");
    printf("************************************\n");
    printf("5. Purchase (Customer)\n");
    printf("0. Exit\n");
    printf("===================================\n");
    printf("===================================\n");
    printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number (0 - 5).\n");

            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (choice < 0 || choice > 5) {
            printf("Invalid input. Please enter a number (0 - 5).\n");
            continue;
        }

        if (choice == 0) {
            save_dbfile();
            free_memory();
            printf("Thank you for shopping with us. See you soon !!\n");
            break;
        }

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
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

