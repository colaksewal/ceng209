// attacker.c
#include "attacker.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

void init_attacker(Attacker *attacker, const char *name, int score) {
    strncpy(attacker->name, name, sizeof(attacker->name) - 1);
    attacker->score = score;
}

void attack_player(Player *player, Attacker *attacker) {
    printf("Warning! You are attacked by %s (Team: %s, Score: %d)\n", attacker->name, attacker->name, attacker->score);
    player->health -= attacker->score;  // Takım puanına göre oyuncunun canını azaltıyoruz.
    printf("Your health is now: %d\n", player->health);
}
