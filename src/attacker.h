// attacker.h
#ifndef ATTACKER_H
#define ATTACKER_H

#include "player.h"

typedef struct {
    char name[50];  // Takım adı
    int score;      // Takım puanı
} Attacker;

void init_attacker(Attacker *attacker, const char *name, int score);
void attack_player(Player *player, Attacker *attacker);

#endif
