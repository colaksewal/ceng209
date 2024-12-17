// inventory.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "room.h"

// Öğeyi başlat
void init_item(Item *item, const char *name, int points) {
    item->name = malloc(strlen(name) + 1); // Ad için bellek ayır
    if (item->name == NULL) {
        fprintf(stderr, "Memory allocation failed for item name.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(item->name, name);
    item->power = points;
}

// Envanteri başlat
void init_inventory(Inventory *inventory) {
    inventory->item_count = 0;
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        inventory->items[i] = NULL;
    }
}

// Envantere öğe ekle
int add_item_to_inventory(Inventory *inventory, Item *item) {
    if (inventory->item_count >= MAX_INVENTORY_SIZE) {
        printf("Envanter dolu! Yeni öğe eklenemedi.\n");
        return 0;
    }

    // Yeni öğe oluştur
    Item *new_item = malloc(sizeof(Item));
    if (!new_item) {
        printf("Hata: Bellek tahsis edilemedi.\n");
        return 0;
    }

    // Öğeyi kopyala
    new_item->name = malloc(strlen(item->name) + 1);
    if (!new_item->name) {
        printf("Hata: Bellek tahsis edilemedi.\n");
        free(new_item); // Belleği serbest bırak
        return 0;
    }
    strcpy(new_item->name, item->name);
    new_item->power = item->power;

    // Öğeyi envantere ekle
    inventory->items[inventory->item_count] = new_item;
    inventory->item_count++;
    return 1;
}

// Envanterden öğe kaldır
void remove_item_from_inventory(Inventory *inventory, const char *item_name) {
    int found = 0;
    for (int i = 0; i < inventory->item_count; i++) {
        if (strcmp(inventory->items[i]->name, item_name) == 0) {
            // Öğeyi serbest bırak
            free(inventory->items[i]->name);
            free(inventory->items[i]);
            inventory->items[i] = inventory->items[inventory->item_count - 1];
            inventory->item_count--;
            found = 1;
            printf("%s envanterden çıkarıldı.\n", item_name);
            break;
        }
    }
    if (!found) {
        printf("%s envanterde bulunamadı.\n", item_name);
    }
}

// Envanteri listele
void list_inventory(Inventory *inventory) {
    if (inventory->item_count == 0) {
        printf("Envanter boş.\n");
        return;
    }
    printf("Envanterdeki öğeler:\n");
    for (int i = 0; i < inventory->item_count; i++) {
        printf("%d. %s (%d puan)\n", i + 1, inventory->items[i]->name, inventory->items[i]->power);
    }
}

// Envanteri serbest bırak
void free_inventory(Inventory *inventory) {
    for (int i = 0; i < inventory->item_count; i++) {
        free(inventory->items[i]->name); // Ad için ayrılan belleği serbest bırak
        free(inventory->items[i]);       // Öğenin kendisini serbest bırak
    }
}
