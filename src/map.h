#ifndef MAP_H
#define MAP_H

#include "room.h"
#include "inventory.h"

#define MAX_MAP_SIZE 9

typedef struct {
    Room *rooms[MAX_MAP_SIZE][MAX_MAP_SIZE]; // Harita 2D grid
    int width;
    int height;
} Map;

void init_map(Map *map, int width, int height);
void add_room_to_map(Map *map, int x, int y, const char *description, int is_dark);
void connect_rooms_on_map(Map *map, int x1, int y1, int x2, int y2, const char *direction);
void print_map(const Map *map);
void free_map(Map *map);

#endif // MAP_H
