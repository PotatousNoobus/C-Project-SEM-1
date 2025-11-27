#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


typedef struct product Product;

Product *product_lis_head = NULL;

void load_dbfile() {
    FILE *file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        printf("Database file doesnt exist. Starting with a new one.\n");
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

void create() {
    Product *new_node = malloc(sizeof(Product));


    printf("Enter product name: ");
    scanf("%[^\n]", new_node->name);
    while (getchar() != '\n');

    printf("Enter the product ID: ");
    scanf("%d", &new_node->id);

    printf("Enter price: ");
    scanf("%f", &new_node->price);

    printf("Enter quantity in stock: ");
    scanf("%d", &new_node->quantity);
    while (getchar() != '\n');

    new_node->next = NULL;

    if (product_lis_head==NULL || new_node->price<product_lis_head->price) {
        new_node->next = product_lis_head;
        product_lis_head = new_node;
    }
    else {
        Product *current = product_lis_head;
        while (current->next != NULL && current->next->price <new_node->price) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    printf("Product added successfully.\n");
}

void display() {
    Product *current = product_lis_head;
    int found = 0;

    printf("\n--- SUPERMARKET INVENTORY ---\n");
    printf("****************************************************\n");

    while (current != NULL) {
        printf("| %d   |%s         %f | %d |\n",current->id,current->name,current->price,current->quantity);
        found = 1;
        current = current->next;
    }
    printf("****************************************************\n");
    if (found==0) {
        printf("No products available.\n");
    }
}

void update_product() {

    char name[30];

    printf("Enter the product name to be updated: ");
    scanf("%s",name);
    while (getchar() != '\n');

    Product *curr = product_lis_head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("Found product: %s ID: %d Quantity: %d Price: %f.\n", curr->name,curr->id,curr->quantity,curr->price);

            printf("Enter a new name: ");
            scanf("%[^\n]", curr->name);
            while (getchar() != '\n');

            printf("Enter the product ID: ");
            scanf("%d",&curr->id);

            printf("Enter the new price: ");
            scanf("%f", &curr->price);

            printf("Enter the new quantity: ");
            scanf("%d", &curr->quantity);
            while (getchar() != '\n');

            printf("Product was updated successfully.\n");
            return;
        }
        curr = curr->next;
    }

    printf("A product with such a name does not exist.\n");
}

void delete_product() {

    char name[30];
    printf("Enter product name to delete: ");
    scanf("%s", name);
    while (getchar() != '\n');

    Product *current = product_lis_head;
    Product *prev = NULL;


    if (current != NULL && strcmp(current->name, name) == 0) {
        product_lis_head = current->next;
        free(current);
        printf("Product deleted successfully.\n");
        return;
    }

    while (current != NULL && strcmp(current->name, name) != 0) {
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
    int amt;
    char name[30];

    display();

    printf("Enter product name to purchase: ");
    scanf("%s", name);

    Product *current = product_lis_head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {

            printf("Enter quantity to buy (in stock: %d): ", current->quantity);
            scanf("%d", &amt);
            while (getchar() != '\n');

            if (amt <= 0 || amt>current->quantity) {
                printf("Invalid quantity.\n");
                return;
            }

            current->quantity -= amt;

            printf("Purchase successful! Total bill amount: %.2f\n",
                   current->price * amt);
            return;
        }
        current = current->next;
    }

    printf("Error: Product %s was not found.\n", name);
}

void save_dbfile() {

    FILE *file = fopen(DB_FILE, "wb");
    if (file == NULL) {
        printf("Error: Could not open database file.\n");
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


