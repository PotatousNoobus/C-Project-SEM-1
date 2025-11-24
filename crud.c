#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


typedef struct product Product;

Product *product_lis_head = NULL;

void loadDatabase() {
    FILE *file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        printf("Database file not found. Starting with an empty list.\n");
        return;
    }

    Product tempProduct;

    while (fread(&tempProduct, sizeof(Product), 1, file) == 1) {
        Product *newNode = (Product *)malloc(sizeof(Product));
        if (newNode == NULL) {
            printf("Error: Out of memory during database load.\n");
            fclose(file);
            return;
        }

        *newNode = tempProduct;
        newNode->next = NULL;

        if (product_lis_head == NULL) {

            product_lis_head = newNode;
        }
        else {

            Product *current = product_lis_head;
            while (current->next != NULL) {
                current = current->next;
            }
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
        fwrite(current, sizeof(Product), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Database saved successfully.\n");
}


void free_memory() {
    Product *current = product_lis_head;
    Product *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
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

    newNode->next = NULL;
    newNode->id = getNextId();

    printf("Enter product name: ");
    scanf("%[^\n]", newNode->name);
    while (getchar() != '\n');  // clear buffer

    printf("Enter price: ");
    scanf("%f", &newNode->price);

    printf("Enter quantity in stock: ");
    scanf("%d", &newNode->quantity);
    while (getchar() != '\n');  // clear buffer


    newNode->next = product_lis_head;
    product_lis_head = newNode;

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
        printf("| %d | %s     | %f | %d |\n",
               current->id,
               current->name,
               current->price,
               current->quantity);
        found = 1;
        current = current->next;
    }
    printf("****************************************************\n");
    if (!found) {
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
            printf("Found product: %s.\n", curr->name);

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

    printf("A product with ID %d does not exist.\n", id);
}

void delete_product() {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Product *current = product_lis_head;
    Product *prev = NULL;


    if (current != NULL && current->id == id) {
        product_lis_head = current->next;
        free(current);
        printf("Product deleted successfully.\n");
        return;
    }

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }


    if (current == NULL) {
        printf("Product not found.\n");
        return;
    }

    prev->next = current->next;
    free(current);
    printf("Product deleted successfully.\n");
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
            while (getchar() != '\n');

            if (amount <= 0 || amount > current->quantity) {
                printf("Invalid quantity.\n");
                return;
            }

            current->quantity -= amount;

            printf("Purchase successful! Total bill amount: $%.2f\n",
                   current->price * amount);
            return;
        }
        current = current->next;
    }

    printf("Error: Product ID %d was not found.\n", id);
}
