#include <stdio.h>
#include <stdlib.h>
#include "data.h"

// Function to display the main menu
void showMenu() {
    printf("\n===================================\n");
    printf("  Supermarket Management System\n");
    printf("===================================\n");
    printf("1. Add New Product\n");
    printf("2. Display All Products\n");
    printf("3. Update Product\n");
    printf("4. Delete Product\n");
    printf("-----------------------------------\n");
    printf("5. Make a Purchase (Customer)\n");
    printf("-----------------------------------\n");
    printf("0. Save & Exit\n"); // Changed text
    printf("===================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    // --- NEW ---
    // Load the database from file into our list when program starts
    loadDatabase();

    do {
        showMenu();

        // Validate input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear the invalid input from the buffer
            while (getchar() != '\n');
            continue; // Go back to the start of the loop
        }

        // Clear the newline character left by scanf
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
                // --- NEW ---
                // Save the list back to file, then free memory
                saveDatabase();
                freeList();
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}