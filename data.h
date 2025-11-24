#ifndef DATA_H
#define DATA_H

// This is the name of the file we'll use as our "database"
#define DB_FILE "supermarket.dat"

// This is our main data structure.
// Each "Product" in the store will have these properties.
struct product {
    int id;            // Unique ID (e.g., 101)
    char name[100];    // Product name (e.g., "Apple", "Milk")
    float price;       // Price (e.g., 1.50)
    int quantity;      // How many are in stock
    struct product *next;
};


void loadDatabase();
void saveDatabase();
void free_memory();
void create();
void display();
void update_product();
void delete_product();
void customer();
int getNextId();

#endif