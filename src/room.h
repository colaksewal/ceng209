#ifndef ROOM_H
#define ROOM_H

#include "inventory.h"
#include "attacker.h"
#include "player.h"

#define MAX_ROOMS 100
#define MAX_ITEMS_PER_ROOM 10  // Oda başına en fazla 10 eşya
#define MAX_ATTACKERS_PER_ROOM 3 


typedef struct Room {
    char *description;
    struct Room *up;
    struct Room *down;
    struct Room *left;
    struct Room *right;
    int is_dark;  // Odanın karanlık olup olmadığını belirler
    Item *items[MAX_ITEMS_PER_ROOM];  // Odadaki eşyalar
    Attacker *attackers[MAX_ATTACKERS_PER_ROOM];  // Array to hold attackers in the room

} Room;

void init_room(Room *room, const char *description, int is_dark);
void connect_rooms(Room *room1, Room *room2, const char *direction);
void add_item_to_room(Room *room, Item *item);
void add_attacker_to_room(Room *room, Attacker *attacker);
void room_info_print(Room *current_room) ;

#endif
