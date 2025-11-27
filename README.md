# Supermarket Management System (C-based Inventory CRUD)    
  
This project is a simple Supermarket Management System implemented in C. It uses a singly linked list to manage a dynamic inventory of products and implements basic CRUD operations. The product data is persisted to a binary file (supermarket.dat) so the inventory state is saved between program executions.

------------------
## CRUD FUNCTIONALITY

The CRUD operations, the core logic for managing the product data, are all implemented as separate functions within the crud.c file, which manipulates the in-memory linked list of products.

**Create (C)**: Implemented in the create() function. It allocates memory for a new product node, prompts for details, and adds the node to the linked list.    

**Read (R)**: Implemented in the display() function. This function traverses the linked list, printing the details of every product in the inventory.  

**Update (U)**: Implemented in the update_product() function. It searches the list by ID and modifies the fields (name, price, quantity) of the found node.  

**Delete (D)**: Implemented in the delete_product() function. It searches for the node by ID, unlinks it from the list, and frees the associated memory.

The customer() function is a specialized operation that acts like a combination of a read (to display stock) and an update (to decrement quantity).  

-------------------
## Persistance Implementation

Persistance is achieved by reading from and writing to the binary file supermarket.dat. This ensures that the product data remains available even after the program exits.   

**Load** (Reading from File): The loadDatabase() function handles loading. It is called once at the start of the program in main.c. It reads the product structures from the file and reconstructs the linked list in memory.

**Save** (Writing to File): The saveDatabase() function handles saving. It is called just before the program exits (when the user selects option 0) in main.c. It traverses the current linked list and writes each product structure to the file, overwriting the old data.

----------------------------

**Running the code:**

1. Save Files: Ensure all three files main.c, crud.c, and data.h are saved in the same directory.
2. Compile: Open your terminal or command prompt and use a C compiler (like GCC) to compile the source files into a single executable:  
   Use the command -> gcc main.c crud.c -o supermarket  
This creates an executable file named supermarket.

3. Now type ./supermarket.exe in the terminal to run the executable file  
   The program will start by loading the inventory from supermarket.dat (if it exists).
   
4. Exit & Save: Always choose option 0 (Exit) when finished. This ensures your changes are saved to the supermarket.dat file and memory is properly cleaned up.

   ------------------------------
   ***ENJOY***



