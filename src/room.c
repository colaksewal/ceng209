#include "room.h"
#include "inventory.h"
#include "attacker.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_room(Room *room, const char *description, int is_dark) {
    room->description = strdup(description);  // Oda açıklamasını kopyala
    room->up = NULL;                          // Oda yönleri başlangıçta boş
    room->down = NULL;
    room->left = NULL;
    room->right = NULL;
    room->is_dark = is_dark;  // Odanın karanlık olup olmadığını belirle

    // Eşyaları başlangıçta boş bırak
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++) {
        room->items[i] = NULL;
    }
}

void connect_rooms(Room *room1, Room *room2, const char *direction) {
    if (strcmp(direction, "up") == 0) {
        room1->up = room2;
        room2->down = room1;
    } else if (strcmp(direction, "down") == 0) {
        room1->down = room2;
        room2->up = room1;
    } else if (strcmp(direction, "left") == 0) {
        room1->left = room2;
        room2->right = room1;
    } else if (strcmp(direction, "right") == 0) {
        room1->right = room2;
        room2->left = room1;
    }
}

void add_item_to_room(Room *room, Item *item) {
    if (!room) {
        printf("Oda mevcut değil!\n");
        return;
    }

    // Oda dolu mu kontrol et
    int empty_slot = -1;
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++) {
        if (!room->items[i]) {
            empty_slot = i;
            break;
        }
    }

    if (empty_slot == -1) {
        printf("Oda dolu, yeni eşya eklenemez!\n");
        return;
    }

    // Eşyayı odaya ekle
    room->items[empty_slot] = item;
}

// Adding attackers to rooms
void add_attacker_to_room(Room *room, Attacker *attacker) {
    for (int i = 0; i < MAX_ATTACKERS_PER_ROOM; i++) {
        if (room->attackers[i] == NULL) {
            room->attackers[i] = attacker;
            break;
        }
    }
}



void room_info_print(Room *current_room) {
    if (current_room == NULL) {
        printf("No valid room found!\n");
        return;
    }

    // Print the room description
    printf("Room description: %s\n", current_room->description);

    // Check if the room is dark
    if (current_room->is_dark) {
        printf("The room is dark. Visual information is limited due to lack of light.\n");
    } else {
        // Print the directions to exit the room
        printf("Exits from the room: ");
        if (current_room->up) printf("Up ");
        if (current_room->down) printf("Down ");
        if (current_room->left) printf("Left ");
        if (current_room->right) printf("Right ");
        printf("\n");
    }

    // Print the items in the room
    printf("Items in the room:\n");
    int has_items = 0;
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++) {
        if (current_room->items[i] != NULL) {
            printf("- %s\n", current_room->items[i]->name);
            has_items = 1;
        }
    }
    if (!has_items) {
        printf("There are no items in this room.\n");
    }

    // Print the attackers in the room
    printf("Attackers in the room:\n");
    int has_attackers = 0;
    for (int i = 0; i < MAX_ATTACKERS_PER_ROOM; i++) {
        if (current_room->attackers[i] != NULL) {
            printf("- %s\n", current_room->attackers[i]->name);
            has_attackers = 1;
        }
    }
    if (!has_attackers) {
        printf("There are no attackers in this room.\n");
    }
}