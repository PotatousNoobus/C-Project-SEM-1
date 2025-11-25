
# Supermarket Inventory Management System


This report details the design and implementation of a terminal-based inventory management system written in C. The system utilizes dynamic data structures to provide
efficient, real-time stock tracking for store managers and administrative staff.

## Executive Summary
**Project Title**: Supermarket Management System (SMS)

**Target Audience**: Store Managers and Inventory Clerks

**Objective**: To develop a lightweight, terminal-based application that allows store managers to maintain real-time control over inventory levels, reducing the administrative
burden of manual tracking and preventing stock inefficiencies.

The system serves two distinct roles: the Administrator (Store Manager) who maintains
the database, and the Customer who depletes stock through purchases.

## Problem Statement

In a busy retail environment, manual inventory tracking leads to errors, "stockouts"
(running out of products), and data inconsistencies. A store manager needs a digital
solution that is:

• **Persistent**: Data must survive after the computer is turned off.

• **Dynamic**: The system must handle an arbitrary number of products without predefined limits.

• **Fast**: Operations like looking up a price or updating stock must be immediate.

## System Architecture & Design

The core of this project relies on a Singly Linked List data structure. Unlike a standard
array, which requires a fixed size (e.g., products[100]), a linked list allows the inventory
to grow or shrink dynamically as the store adds or removes items.

## Data Structure Design

The fundamental unit of data is the product node, defined in the header file. The node
structure contains:

• **ID (Unique Identifier)**: Auto-generated integer for distinct tracking.

• **Name**: Character string (up to 100 chars).

• **Price**: Floating point value.

• **Quantity**: Integer representing current stock.

• **Next Pointer**: A reference to the next product in the chain

## Memory Management
The system uses dynamic memory allocation (malloc) to create nodes only when needed.

• **Creation**: Memory is allocated for exactly one node when a product is added.

• **Deletion**: Memory is explicitly released (free) when a product is removed to
prevent leaks.

## Data Persistence (File I/O)

To ensure the store manager’s work is saved, the system implements binary file serialization.

• **Loading**: On startup, the system checks for supermarket.dat, reads data blockby-block, and reconstructs the linked list in RAM.

• **Saving**: Upon exit, the system traverses the linked list and writes the raw memory
of the structures to the disk.

## Functional Modules

The application is split into modular functions (Create, Read, Update, Delete) to maintain
clean logic.

## Administrative Functions

1. Add New Product (create): The system auto-generates a unique ID and links
the new node to the head of the list.
2. Display Inventory (display): Iterates through the linked list and prints a formatted table, providing a snapshot of current stock.4. 
3. Update Product (update_product): Allows the manager to modify details of an
existing item, essential for correcting errors or price adjustments.
4. Delete Product (delete_product): Removes an item entirely. Logic handles
pointer re-linking to ensure the chain remains unbroken.

## Operational Functions

• Purchase (customer): Simulates a point-of-sale transaction. It validates if requested_qty
≤ current_stock. If valid, it deducts the stock and calculates the total cost.

## Building and Running

1. Save all the files in the same directory
2. Open terminal and type gcc main.c crud.c -o supermarket 
3. Now type ./supermarket.exe to run the executable.

## Technical Analysis

### Complexity

The choice of a Linked List implies specific performance characteristics:

• **Insertion**: O(1) (Constant time) - Adding items is instant.

• **Search/Update/Delete**: O(n) (Linear time) - The system must traverse the list
to find a specific ID.

## Future Recommendations

To further assist the store manager, future versions could include:

• **Low Stock Alerts**: Automatically flag items where quantity < 10.

• **Revenue Tracking**: Keep a running total of sales made in the customer function.

• **Sorting**: Implementing Merge Sort to view items alphabetically or by ID.





