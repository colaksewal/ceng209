#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "inventory.h"


// Oyuncuyu başlatma
void init_player(Player *player) {
    player->health = 100;
    player->strenght = 40;
    player->inventory_size = 0;
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        player->inventory[i] = NULL;
    }
    strcpy(player->name, "user"); // Varsayılan kullanıcı adı
}

// Envanteri kontrol et
int is_inventory_full(Player *player) {
    return player->inventory_size >= MAX_INVENTORY_SIZE;  // Envanter dolu mu?
}

// Envantere öğe ekleme
void add_to_inventory(Player *player, Item *item) {
    if (player->inventory_size < MAX_INVENTORY_SIZE) {
        player->inventory[player->inventory_size] = item;
        player->inventory_size++;
    } else {
        printf("Inventory is full!\n");
    }
}

// Envanteri yazdırma
void print_inventory(Player *player) {
    printf("Inventory:\n");
    for (int i = 0; i < player->inventory_size; i++) {
        printf("  %s (Power: %d)\n", player->inventory[i]->name, player->inventory[i]->power);
    }
}

// Oyuncu bilgilerini yazdırma
void print_player(Player *player) {
    printf("Player Info:\n");
    printf("NAme: %s\n", player->name);
    printf("Health %d\n", player->health);
    printf("Strength %d\n", player->strenght);
    printf("Inventory Size %d/%d\n", player->inventory_size, MAX_INVENTORY_SIZE);
    print_inventory(player);  // Envanteri yazdır
}

void set_playername(Player *player) {
    char response[3];

    // İsim girme isteği
    printf("Do you want to enter your name? (y/n): ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = 0; // Sonundaki yeni satırı temizle

    if (response[0] == 'y' || response[0] == 'Y') {
        // İsim girme işlemi
        printf("Enter your name: ");
        fgets(player->name, sizeof(player->name), stdin);
        player->name[strcspn(player->name, "\n")] = 0; // Sonundaki yeni satırı temizle
        printf("Hello, %s! Let's begin your adventure!\n", player->name);
    } else {
        // Varsayılan isim
        strcpy(player->name, "user");
        printf("Hello, %s! Let's begin your adventure!\n", player->name);
    }
}