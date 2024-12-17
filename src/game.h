#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "room.h"
#include "map.h"
#include "inventory.h"


void show_instructions();
void handle_command(Player *player, Room **current_room, const char *command);
void run_game();
void load_game_from_saved(void *player);
void manage_room(Player *player, Room *room);
void handle_attack(Player *player, Room *room);

void list_saved_games() ;

void save_game(Player *player);
int load_game(const char *filepath, Player *player);
void create_savegames_directory();
#endif // GAME_H
