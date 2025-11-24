#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void menu() {
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
}

int main(void) {
    int choice;
    int c;

    loadDatabase();

    while (1) {
        menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number (0 - 5).\n");

            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        while ((c = getchar()) != '\n' && c != EOF);

        if (choice < 0 || choice > 5) {
            printf("Invalid input. Please enter a number (0 - 5).\n");
            continue;
        }

        if (choice == 0) {
            saveDatabase();
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
