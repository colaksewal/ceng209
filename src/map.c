#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "inventory.h"

// Harita başlatma
void init_map(Map *map, int width, int height) {
    if (width > MAX_MAP_SIZE || height > MAX_MAP_SIZE) {
        printf("Harita boyutu maksimum %dx%d olabilir!\n", MAX_MAP_SIZE, MAX_MAP_SIZE);
        exit(1);
    }

    map->width = width;
    map->height = height;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map->rooms[i][j] = NULL;
        }
    }
}

// Haritaya oda ekleme
void add_room_to_map(Map *map, int x, int y, const char *description , int is_dark) {
    if (x >= map->width || y >= map->height || x < 0 || y < 0) {
        printf("Geçersiz koordinatlar!\n");
        return;
    }

    Room *room = malloc(sizeof(Room));
    if (!room) {
        printf("Bellek tahsis edilemedi!\n");
        exit(1);
    }

    init_room(room, description,is_dark);
    map->rooms[y][x] = room;
}

// Odaları bağlama
void connect_rooms_on_map(Map *map, int x1, int y1, int x2, int y2, const char *direction) {
    if (x1 >= map->width || y1 >= map->height || x2 >= map->width || y2 >= map->height ||
        x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) {
        printf("Geçersiz koordinatlar!\n");
        return;
    }

    Room *room1 = map->rooms[y1][x1];
    Room *room2 = map->rooms[y2][x2];

    if (!room1 || !room2) {
        printf("Bağlantı için odalar mevcut değil!\n");
        return;
    }

    connect_rooms(room1, room2, direction);
}

// Haritayı yazdırma
void print_map(const Map *map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->rooms[i][j]) {
                printf("[O]");
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }
}

// Bellekten haritayı temizleme
void free_map(Map *map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->rooms[i][j]) {
                // Oda içerisindeki eşyaları serbest bırak
                for (int k = 0; k < MAX_ITEMS_PER_ROOM; k++) {
                    if (map->rooms[i][j]->items[k]) {
                        free(map->rooms[i][j]->items[k]->name);
                        free(map->rooms[i][j]->items[k]);
                    }
                }
                // Oda açıklamasını ve odayı serbest bırak
                free(map->rooms[i][j]->description);
                free(map->rooms[i][j]);
            }
        }
    }
}
