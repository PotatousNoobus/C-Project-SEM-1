#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// --- Global Variable ---
// This is the "head" of our linked list. It's the entry point.
// It's defined here in the .c file.
typedef struct product Product;

Product *product_lis_head = NULL;

void loadDatabase() {
    FILE *file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        printf("Database file not found. Starting with an empty list.\n");
        return;
    }

    Product tempProduct;
    // Read one product at a time from the file
    while (fread(&tempProduct, sizeof(Product), 1, file)) {
        // For each product, allocate memory for a new list node
        Product *newNode = (Product *)malloc(sizeof(Product));
        if (newNode == NULL) {
            printf("Error: Out of memory during database load.\n");
            fclose(file);
            return;
        }


        *newNode = tempProduct;
        // IMPORTANT: The 'next' pointer read from the file is garbage.
        // We must set it to NULL.
        newNode->next = NULL;

        // Add the new node to the end of our list
        if (product_lis_head == NULL) {
            // List is empty, this is the first node
            product_lis_head = newNode;
        } else {
            // Find the end of the list
            Product *current = product_lis_head;
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

    Product *current = product_lis_head;
    while (current != NULL) {
        // Write the *entire* product struct to the file.
        // The 'next' pointer is also written, but it's okay.
        // Our loadDatabase() function knows to ignore it.
        fwrite(current, sizeof(Product), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Database saved successfully.\n");
}

void freeList() {
    Product *current = product_lis_head;
    Product *temp;

    while (current != NULL) {
        temp = current;          // Remember the current node
        current = current->next; // Move to the next node
        free(temp);              // Free the one we remembered
    }
    product_lis_head = NULL;
    printf("Memory freed.\n");
}

int getNextId() {
    int last_id = 0;
    Product *current = product_lis_head;

    while (current != NULL) {
        if (current->id > last_id) {
            last_id = current->id;
        }
        current = current->next;
    }
    return last_id + 1;
}

void create() {

    Product *newNode = (Product *)malloc(sizeof(Product));
    if (newNode == NULL) {
        printf("Malloc failed.\n");
        return;
    }
    newNode->id = getNextId();
    printf("Enter product name: ");
    scanf("%[^\n]", newNode->name);
    while (getchar() != '\n');
    //fgets(newNode->name, 100, stdin);
    //newNode->name[strcspn(newNode->name, "\n")] = 0;

    printf("Enter price: ");
    scanf("%f", &newNode->price);

    printf("Enter quantity in stock: ");
    scanf("%d", &newNode->quantity);
    while (getchar() != '\n');
    if (product_lis_head == NULL){
        product_lis_head = newNode;
    }
    else {
        newNode->next = product_lis_head;
    }

    printf("Product added successfully.\n");
}

void display() {
    Product *current = product_lis_head;
    int found = 0;

    printf("\n--- SUPERMARKET INVENTORY ---\n");
    printf("----------------------------------------------------\n");
    printf("| ID   | Name                 | Price    | Stock   |\n");
    printf("----------------------------------------------------\n");

    while (current != NULL) {
        printf("| %d | %s | %f | %d |\n",current->id,current->name,current->price,current->quantity);
        found = 1;
        current = current->next; // Move to the next item
    }
    printf("****************************************************\n");
    if (found==0) {
        printf("No products available.\n");
    }
}

void update_product() {
    int id;
    printf("Enter product ID to update: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Product *curr = product_lis_head;
    while (curr != NULL) {
        if (curr->id == id) {
            printf("Found product: %s.\n",curr->name);

            printf("Enter a new name: ");
            scanf("%[^\n]", curr->name);
            while (getchar() != '\n');

            printf("Enter the new price: ");
            scanf("%f", &curr->price);

            printf("Enter the new quantity: ");
            scanf("%d", &curr->quantity);
            while (getchar() != '\n'); // Clear buffer

            printf("Product with ID %d was updated successfully.\n", id);
            return;
        }
        curr = curr->next;
    }

    printf("A product with ID %d does not exist.\n",id);
}

void delete_product() {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n'); // Clear buffer

    Product *current = product_lis_head;
    Product *prev = NULL;

    if (current!=NULL && current->id == id) {
        product_lis_head = current->next;
        free(current);
        printf("Product deleted successfully.\n");
        return;
    }
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    if (current==NULL) {
        printf("Product not found.\n");
        return;
    }
    else if (current != NULL) {
        prev->next = current->next;
        free(current);
        printf("Product deleted successfully.\n");
        return;
    }
}

void customer() {
    int id, amount;
    display();
    printf("Enter product ID to purchase: ");
    scanf("%d", &id);

    Product *current = product_lis_head;

    while (current != NULL) {
        if (current->id == id) {

            printf("Enter quantity to buy (in stock: %d): ", current->quantity);
            scanf("%d", &amount);
            while (getchar() != '\n'); // Clear buffer

            if (amount <= 0 || amount > current->quantity ) {
                printf("Invalid quantity.\n");
                return;
            }

            current->quantity -= amount;

            printf("Purchase successful! Total bill amount: $%.2f\n", current->price * amount);
            //printf("Remaining stock for %s: %d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }

    printf("Error: Product ID %d was not found.\n", id);
}