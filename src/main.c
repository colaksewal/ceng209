
#include <stdio.h>
#include "game.h"
#include <stdlib.h> 
#include <time.h>

void display_intro() {
    printf("******************************\n");
    printf("*   Welcome to Space Dungeon!   *\n");
    printf("******************************\n\n");
    printf("While traveling through space, you suddenly crashed into a star!\n");
    printf("One of your spaceship's engines fell onto the Milky Way planet.\n");
    printf("You have landed there and discovered that a new engine costs 500 points!\n");
    printf("But beware! The Milky Way galaxy consists of 25 rooms with dangerous constellations.\n");
    printf("Use light, dust, and other tools to defeat enemies and escape the rooms.\n");
    printf("Are you ready? Let the adventure begin...\n\n");
    printf("The game is starting...\n\n");
}


int main() {
    display_intro();

    printf("Loading**");

    //5 seconds for loading effect
    for (int i = 0; i < 5; i++) {
        printf("*"); 
        fflush(stdout); 
        usleep(1000000); 
    }

    printf("\n\n"); 
    run_game();
    return 0;
}
