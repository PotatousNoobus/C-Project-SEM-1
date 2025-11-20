#ifndef DATA_H
#define DATA_H

// This is the name of the file we'll use as our "database"
#define DB_FILE "supermarket.dat"

// This is our main data structure.
// Each "Product" in the store will have these properties.
struct Product {
    int id;            // Unique ID (e.g., 101)
    char category[20];
    char name[100];    // Product name (e.g., "Apple", "Milk")
    float price;       // Price (e.g., 1.50)
    int quantity;      // How many are in stock
    struct Product *next;
};



/**
 * @brief Loads the database from DB_FILE into the linked list in memory.
 * This should be called once when the program starts.
 */
void loadDatabase();

/**
 * @brief Saves the entire in-memory linked list back to DB_FILE.
 * This should be called once when the program exits.
 */
void saveDatabase();

/**
 * @brief Frees all allocated memory for the linked list.
 * This is called just before the program exits.
 */
void freeList();

// --- Core App Functions (Implementations will change) ---

/**
 * @brief Gets user input and adds a new product to the linked list.
 */
void createProduct();

/**
 * @brief Reads all products from the linked list and prints them.
 */
void displayAllProducts();

/**
 * @brief Asks for a Product ID, then finds it in the list to update.
 */
void updateProduct();

/**
 * @brief Asks for a Product ID and removes that product from the linked list.
 */
void deleteProduct();

/**
 * @brief Asks for a Product ID and a quantity to "buy",
 * then reduces the stock of that item in the list.
 */
void customerPurchase();

/**
 * @brief A helper function to get the next available ID from the list.
 */
int getNextId();

#endif // DATA_H