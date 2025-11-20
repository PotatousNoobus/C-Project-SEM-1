#include <stdio.h>
#include <stdlib.h> // For malloc() and free()
#include <string.h>
#include "data.h"

// --- Global Variable ---
// This is the "head" of our linked list. It's the entry point.
// It's defined here in the .c file.
struct Product *g_productListHead = NULL;


// --- List Management Functions ---

void loadDatabase() {
    FILE *file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        printf("Database file not found. Starting with an empty list.\n");
        return;
    }

    struct Product tempProduct;
    // Read one product at a time from the file
    while (fread(&tempProduct, sizeof(struct Product), 1, file)) {
        // For each product, allocate memory for a new list node
        struct Product *newNode = (struct Product*)malloc(sizeof(struct Product));
        if (newNode == NULL) {
            printf("Error: Out of memory during database load.\n");
            fclose(file);
            return;
        }

        // Copy the data from the file struct into our new node
        *newNode = tempProduct;
        // IMPORTANT: The 'next' pointer read from the file is garbage.
        // We must set it to NULL.
        newNode->next = NULL;

        // Add the new node to the end of our list
        if (g_productListHead == NULL) {
            // List is empty, this is the first node
            g_productListHead = newNode;
        } else {
            // Find the end of the list
            struct Product *current = g_productListHead;
            while (current->next != NULL) {
                current = current->next;
            }
            // Add the new node at the end
            current->next = newNode;
        }
    }

    fclose(file);
    printf("Database loaded successfully into memory.\n");
}

void saveDatabase() {
    // "wb" = write binary. This overwrites the old file.
    FILE *file = fopen(DB_FILE, "wb");
    if (file == NULL) {
        printf("Error: Could not open database file for saving.\n");
        return;
    }

    struct Product *current = g_productListHead;
    while (current != NULL) {
        // Write the *entire* product struct to the file.
        // The 'next' pointer is also written, but it's okay.
        // Our loadDatabase() function knows to ignore it.
        fwrite(current, sizeof(struct Product), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Database saved successfully.\n");
}

void freeList() {
    struct Product *current = g_productListHead;
    struct Product *temp;

    while (current != NULL) {
        temp = current;          // Remember the current node
        current = current->next; // Move to the next node
        free(temp);              // Free the one we remembered
    }
    g_productListHead = NULL;
    printf("All memory freed.\n");
}

// Helper function to get the next available ID *from the list*
int getNextId() {
    int maxId = 0;
    struct Product *current = g_productListHead;

    while (current != NULL) {
        if (current->id > maxId) {
            maxId = current->id;
        }
        current = current->next;
    }
    return maxId + 1;
}

// --- Core App Functions (Linked List) ---

// 1. CREATE
void createProduct() {
    // 1. Allocate memory for the new node
    struct Product *newNode = (struct Product*)malloc(sizeof(struct Product));
    if (newNode == NULL) {
        printf("Error: Out of memory. Cannot add new product.\n");
        return;
    }

    // 2. Get product details from user
    newNode->id = getNextId();
    printf("Adding new product (ID: %d)\n", newNode->id);

    printf("Enter product name: ");
    fgets(newNode->name, 100, stdin);
    newNode->name[strcspn(newNode->name, "\n")] = 0;

    printf("Enter price: ");
    scanf("%f", &newNode->price);

    printf("Enter quantity in stock: ");
    scanf("%d", &newNode->quantity);
    while (getchar() != '\n'); // Clear buffer

    newNode->next = NULL; // This node will be at the end

    // 3. Add the new node to the end of the list
    if (g_productListHead == NULL) {
        // List is empty
        g_productListHead = newNode;
    } else {
        // Find the end
        struct Product *current = g_productListHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; // Link the last node to the new one
    }

    printf("Product added successfully (to memory).\n");
}

// 2. READ (Display All)
void displayAllProducts() {
    struct Product *current = g_productListHead;
    int found = 0;

    printf("\n--- SUPERMARKET INVENTORY (from memory) ---\n");
    printf("----------------------------------------------------\n");
    printf("| ID   | Name                 | Price    | Stock   |\n");
    printf("----------------------------------------------------\n");

    while (current != NULL) {
        printf("| %-4d | %-20s | %-8.2f | %-7d |\n",
               current->id,
               current->name,
               current->price,
               current->quantity);
        found = 1;
        current = current->next; // Move to the next item
    }
    printf("----------------------------------------------------\n");

    if (!found) {
        printf("No products in stock.\n");
    }
}

// 3. UPDATE
void updateProduct() {
    int id;
    printf("\n--- Update Product ---\n");
    printf("Enter product ID to update: ");
    scanf("%d", &id);
    while (getchar() != '\n'); // Clear buffer

    // Find the product in the list
    struct Product *current = g_productListHead;
    while (current != NULL) {
        if (current->id == id) {
            // Found it!
            printf("Found product: %s. Enter new details:\n", current->name);

            printf("Enter new name: ");
            fgets(current->name, 100, stdin);
            current->name[strcspn(current->name, "\n")] = 0;

            printf("Enter new price: ");
            scanf("%f", &current->price);

            printf("Enter new quantity: ");
            scanf("%d", &current->quantity);
            while (getchar() != '\n'); // Clear buffer

            printf("Product ID %d updated successfully.\n", id);
            return;
        }
        current = current->next;
    }

    printf("Error: Product ID %d not found.\n", id);
}

// 4. DELETE
void deleteProduct() {
    int id;
    printf("\n--- Delete Product ---\n");
    printf("Enter product ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n'); // Clear buffer

    struct Product *current = g_productListHead;
    struct Product *previous = NULL;

    // Iterate the list to find the node
    while (current != NULL) {
        if (current->id == id) {
            // Found the node to delete
            if (previous == NULL) {
                // This is the *first* node (the head)
                g_productListHead = current->next;
            } else {
                // This is a node in the middle or end
                previous->next = current->next;
            }

            free(current); // Free the memory!
            printf("Product ID %d deleted successfully.\n", id);
            return;
        }

        // Move to the next node
        previous = current;
        current = current->next;
    }

    printf("Error: Product ID %d not found.\n", id);
}

// 5. CUSTOMER PURCHASE
void customerPurchase() {
    int id, amountToBuy;
    displayAllProducts(); // Show the customer what's available

    printf("\n--- Customer Purchase ---\n");
    printf("Enter product ID to purchase: ");
    scanf("%d", &id);

    // Find the product in the list
    struct Product *current = g_productListHead;
    while (current != NULL) {
        if (current->id == id) {
            // Found the product
            printf("Enter quantity to buy for %s (in stock: %d): ", current->name, current->quantity);
            scanf("%d", &amountToBuy);
            while (getchar() != '\n'); // Clear buffer

            if (amountToBuy <= 0) {
                printf("Invalid quantity.\n");
                return;
            }

            if (amountToBuy > current->quantity) {
                printf("Sorry, not enough stock. Only %d available.\n", current->quantity);
                return;
            }

            // Process the purchase
            current->quantity -= amountToBuy;
            printf("Purchase successful! Total cost: $%.2f\n", current->price * amountToBuy);
            printf("Remaining stock for %s: %d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }

    printf("Error: Product ID %d not found.\n", id);
}