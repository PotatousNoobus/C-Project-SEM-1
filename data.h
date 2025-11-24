#ifndef DATA_H
#define DATA_H

#define DB_FILE "supermarket.dat"

struct product {
    int id;
    char name[100];
    float price;
    int quantity;
    struct product *next;
};

void load_dbfile();
void create();
void display();
void update_product();
void delete_product();
void customer();
int get_ID();
void save_dbfile();
void free_memory();

#endif
