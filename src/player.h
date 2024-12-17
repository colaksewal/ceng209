#ifndef PLAYER_H
#define PLAYER_H


#include "inventory.h"  // Inventory dosyasını dahil et

// Player yapısı: Oyuncuyu temsil eder
typedef struct {
    char name[100];       // Oyuncunun adı
    int health;           // Oyuncunun mevcut sağlığı
    int strenght; 
    int inventory_size;   // Envanterdeki öğe sayısı
    Item *inventory[MAX_INVENTORY_SIZE]; // Oyuncunun envanteri (Item türünde)
} Player;

// Fonksiyon prototipleri
void init_player(Player *player);
void set_playername(Player *player);
void print_inventory(Player *player);
void add_to_inventory(Player *player, Item *item);
int is_inventory_full(Player *player);
void print_player(Player *player);

#endif // PLAYER_H
