#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_INVENTORY_SIZE 1

// Item yapısı: Oyuncunun envanterindeki her öğe
typedef struct {
    char *name;    // Öğenin adı
    int power;     // Öğenin gücü
} Item;

// Inventory yapısı: Envanteri temsil eder
typedef struct {
    Item *items[MAX_INVENTORY_SIZE];  // Envanterdeki öğeler
    int item_count;  // Envanterdeki öğe sayısı
} Inventory;

// Fonksiyon prototipleri
void init_inventory(Inventory *inventory);
int add_item_to_inventory(Inventory *inventory, Item *item);
void remove_item_from_inventory(Inventory *inventory, const char *item_name);
void list_inventory(Inventory *inventory);
void free_inventory(Inventory *inventory);

#endif // INVENTORY_H
