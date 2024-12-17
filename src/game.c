#include "game.h"
#include "player.h"
#include "room.h"
#include "map.h"
#include "inventory.h"
#include "attacker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>  // Dizin okuma işlemleri için gerekli
#include <sys/stat.h>  // mkdir fonksiyonu için

#define ROWS 5
#define COLS 5

void handle_command(Player *player, Room **current_room, const char *command) {
    if (strcmp(command, "look") == 0) {

        room_info_print(*current_room);

    } else if (strncmp(command, "move", 4) == 0) {
        char direction[10];
        sscanf(command, "move %s", direction);
        if (strcmp(direction, "up") == 0 && (*current_room)->up != NULL) {
            printf("Moving up...\n");
            print_player(player);
            *current_room = (*current_room)->up;
            manage_room(player, *current_room);
            handle_attack(player, *current_room);  // Handle any attacks in the room
        } else if (strcmp(direction, "down") == 0 && (*current_room)->down != NULL) {
            printf("Moving down...\n");
            print_player(player);
            *current_room = (*current_room)->down;
            manage_room(player, *current_room);
            handle_attack(player, *current_room);  // Handle any attacks in the room

        } else if (strcmp(direction, "left") == 0 && (*current_room)->left != NULL) {
            printf("Moving left...\n");
            print_player(player);
            *current_room = (*current_room)->left;
            manage_room(player, *current_room);
            handle_attack(player, *current_room);  // Handle any attacks in the room

        } else if (strcmp(direction, "right") == 0 && (*current_room)->right != NULL) {
            printf("Moving right...\n");
            print_player(player);
            *current_room = (*current_room)->right;
            manage_room(player, *current_room);
            handle_attack(player, *current_room);  // Handle any attacks in the room

        } else {
            printf("You can't move in that direction!\n");
        }
    } else if (strcmp(command, "inventory") == 0) {
        print_inventory(player);
    } else if (strcmp(command, "exit") == 0) {
        printf("Exiting game...\n");
        exit(0);
    }  else if (strcmp(command, "list") == 0) {
        list_saved_games();  // List saved games
    } else if (strncmp(command, "save", 4) == 0) {
        save_game(player);  // Save the game state
    } else if (strncmp(command, "load", 4) == 0) {
    // Kaydedilmiş oyunların listesi
    load_game_from_saved(player);
    }
    else {
        //printf("Invalid command!\n");
    }
}




void list_saved_games() {
    DIR *dir = opendir("savegames");
    struct dirent *entry;
    int count = 1;

    if (dir == NULL) {
        printf("Unable to open savegames directory!\n");
        return;
    }

    printf("Saved Games:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Only regular files
            printf("%d. %s\n", count, entry->d_name);
            count++;
        }
    }

    closedir(dir);
}


void create_savegames_directory() {
    struct stat st = {0};
    if (stat("savegames", &st) == -1) {
        mkdir("savegames", 0700);  // Klasör yoksa oluştur
    }
}

void save_game(Player *player) {
    // player->name ile dosya yolunu oluşturuyoruz (savegames/playername.sav)
    char full_path[150];
    snprintf(full_path, sizeof(full_path), "savegames/%s.sav", player->name);

    // Savegames dizininin var olup olmadığını kontrol et
    if (opendir("savegames") == NULL) {
        printf("Error: 'savegames' directory does not exist. Creating it...\n");
        if (mkdir("savegames", 0777) != 0) {
            printf("Failed to create 'savegames' directory.\n");
            return;
        }
    }

    FILE *file = fopen(full_path, "wb");
    if (file) {
        // Player verilerini dosyaya kaydet
        size_t written_player = fwrite(player, sizeof(Player), 1, file);

        if (written_player == 1) {
            printf("Game saved successfully to %s.\n", full_path);
            
            // Kaydedilen Player verilerini yazdır
            printf("Player data saved:\n");
            printf("  Name: %s\n", player->name);
            printf("  Health: %d\n", player->health);
            printf("  Inventory Size: %d\n", player->inventory_size);
            
            // Envanteri yazdır
            printf("Inventory:\n");
            for (int i = 0; i < player->inventory_size; i++) {
                printf("  Item %d: %s (Power: %d)\n", i + 1, player->inventory[i]->name, player->inventory[i]->power);
            }
        } else {
            printf("Error: Failed to write player data to the file.\n");
        }
        fclose(file);
    } else {
        printf("Failed to save the game. Could not open the file: %s\n", full_path);
    }
}


int load_game(const char *filepath, Player *player) {
    char full_path[150];
    snprintf(full_path, sizeof(full_path), "savegames/%s", filepath);
    printf("Attempting to load game from: %s\n", full_path);

    FILE *file = fopen(full_path, "rb");
    if (file) {
        fread(player, sizeof(Player), 1, file);

        // Envanteri yükle
        for (int i = 0; i < player->inventory_size; i++) {
            player->inventory[i] = malloc(sizeof(Item)); // Envanterdeki her item için bellek ayırıyoruz
            fread(player->inventory[i], sizeof(Item), 1, file);
        }

        fclose(file);
        printf("Game loaded successfully from %s.\n", full_path);

        // Yüklenen Player verilerini yazdır
        printf("Player data loaded:\n");
        printf("  Name: %s\n", player->name);
        printf("  Health: %d\n", player->health);
        printf("  Inventory Size: %d\n", player->inventory_size);

        // Envanteri yazdır
        printf("Inventory:\n");
        for (int i = 0; i < player->inventory_size; i++) {
            printf("  Item %d: %s (Power: %d)\n", i + 1, player->inventory[i]->name, player->inventory[i]->power);
        }

        return 1;  // Başarılı yükleme
    } else {
        printf("Failed to load the game. File might not exist: %s\n", full_path);
        return 0;  // Başarısız yükleme
    }
}

void load_game_from_saved(void *player) {
    // Kaydedilmiş oyunların listesi
    list_saved_games();
    printf("Enter the number of the saved game to load: ");

    int choice;
    if (scanf("%d", &choice) != 1) {  // Kullanıcı girişini kontrol et
        printf("Invalid input! Please enter a valid number.\n");
        while (getchar() != '\n');  // Girdi tamponunu temizle
        return;
    }

    // Savegames dizinini açmaya çalış
    DIR *dir = opendir("savegames");
    if (dir == NULL) {
        printf("Error: Unable to open savegames directory!\n");
        return;
    }

    struct dirent *entry;
    int count = 1;
    char filename[256];
    int file_found = 0;  // Seçilen dosyanın bulunup bulunmadığını izlemek için bayrak

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Sadece düzenli dosyaları kontrol et
            if (count == choice) {
                file_found = 1;
                snprintf(filename, sizeof(filename), "%s", entry->d_name);  // Dosya adını al

                // Oyunu yükle ve sonucu kontrol et
                if (!load_game(filename, player)) {
                    printf("Error: Failed to load the game '%s'.\n", filename);
                } else {
                    printf("Game '%s' loaded successfully!\n", filename);
                }
                break;
            }
            count++;
        }
    }

    // Eğer dosya bulunamadıysa, kullanıcıyı bilgilendir
    if (!file_found) {
        printf("Error: Invalid choice. No such saved game exists.\n");
    }

    closedir(dir);  // Dizin kapat
}






void show_instructions() {
    printf("Here are the available commands:\n");
    printf("- 'look' : Look around the current room.\n");
    printf("- 'move <direction>' : Move to a different room. Directions: up, down, left, right.\n");
    printf("- 'pickup <item>' : Pick up an item and add it to your inventory.\n");
    printf("- 'inventory' : View the items you have picked up.\n");
    printf("- 'exit' : Exit the game.\n");
    printf("\nUse these commands to navigate and interact with the world.\n");
    printf("Good luck!\n");
}



void use_item(Player *player, int item_index) {
    if (item_index < 0 || item_index >= player->inventory_size) {
        printf("Invalid item index!\n");
        return;
    }

    Item *item = player->inventory[item_index];
    printf("You use %s!\n", item->name);
    player->health += item->power;
    printf("Your health is now: %d\n", player->health);

    // Öğeyi envanterden kaldır (shift items)
    for (int i = item_index; i < player->inventory_size - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventory_size--;  // Envanter boyutunu küçült
    printf("%s has been removed from your inventory.\n", item->name);
}

void handle_attack(Player *player, Room *room) {
    for (int i = 0; i < MAX_ATTACKERS_PER_ROOM; i++) {
        if (room->attackers[i] != NULL) {

            // Eğer oyuncunun envanterinde item varsa, kullanmak isteyip istemediğini sor
            if (player->inventory_size > 0) {
                printf("Would you like to use an item? (y/n): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    print_inventory(player);
                    printf("Choose an item to use (1-%d): ", player->inventory_size);
                    int item_choice;
                    scanf("%d", &item_choice);
                    use_item(player, item_choice - 1);
                }
            }

            // Düşmanla karşılaşma ve hasar verme
            printf("You encounter %s!\n", room->attackers[i]->name);
            printf("It deals %d damage to you!\n", room->attackers[i]->score);
            player->health -= room->attackers[i]->score;
            printf("Your current health: %d\n", player->health);

            // Eğer oyuncunun sağlığı 0 veya daha azsa, oyun bitiyor
            if (player->health <= 0) {
                printf("You have been defeated!\n");
                exit(0); // Oyun biter
            }
        }
    }
}


void manage_room(Player *player, Room *room) {
    char command[20];

    // Eğer oda karanlıksa, oyuncuya seçenek sunulur
    if (room->is_dark) {
          printf("This room is dark, you can't see clearly around you.\n");
    printf("Would you like to spend 20 points to light up the room? (y/n): Your strength is being reduced.\n");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Yeni satırı temizle
        
        if (command[0] == 'y' || command[0] == 'Y') {
            if (player->strenght >= 20) {
                player->strenght -= 20;
                room->is_dark = 0;
                printf("The room has been lit! Remaining points:  %d\n", player->strenght);
            } else {
                printf("You don't have enough points! Your current points: %d\n", player->strenght);
                return;
            }
        } else {
            printf("The room remains dark, you cannot perform any other actions.\n");
            return;
        }
    }

    // Oda açıklamasını ve içeriğini göster
    printf("Room Description: %s\n", room->description);

    printf("Items in the room:\n");  
    int has_items = 0;
    for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++) {
        if (room->items[i] != NULL) {
            printf("- %s : %d power\n", room->items[i]->name, room->items[i]->power);
            has_items = 1;
        }
    }
    if (!has_items) {
        printf("Items in the room:\n");  
    }

    printf("Enemies in the room\n");
    int has_attackers = 0;
    for (int i = 0; i < MAX_ATTACKERS_PER_ROOM; i++) {
        if (room->attackers[i] != NULL) {
            printf("- %s : %d damage\n", room->attackers[i]->name, room->attackers[i]->score);
            has_attackers = 1;
        }
    }
    if (!has_attackers) {
        printf("Enemies in the room Yok.\n");
    }

    // Kullanıcı komutları beklenir
    while (1) {

        
        printf("\nEnter  (inventory, pickup <item>, continue game): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Yeni satırı temizle
        
        if(has_attackers && (!strncmp(command, "pickup", 6) == 0 )){
            printf("\nEnter (attack): ");
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = 0; 
            break;
        }


        if (strncmp(command, "inventory", 9) == 0) {
            printf("Envanteriniz:\n");
            if (player->inventory_size == 0) {
                printf("- Envanteriniz boş.\n");
            } else {
                for (int i = 0; i < player->inventory_size; i++) {
                    printf("- %s : %d power\n", player->inventory[i]->name, player->inventory[i]->power);
                }
            }
        } else if (strncmp(command, "pickup", 6) == 0) {
            char *item_name = command + 7; // Komuttan sonra gelen öğe adı
            int found = 0;
            for (int i = 0; i < MAX_ITEMS_PER_ROOM; i++) {
                if (room->items[i] != NULL && strcmp(room->items[i]->name, item_name) == 0) {
                    found = 1;
                    if (is_inventory_full(player)) {
                        printf("Your inventory is full! You cannot buy any more items.\n");
                    } else {
                        add_to_inventory(player, room->items[i]);
                        printf("%s add inventory.\n", room->items[i]->name);
                        room->items[i] = NULL; // Oda içindeki öğe kaldırıldı
                    }
                    break;
                }
            }
            if (!found) {
                printf("No item found with this name.\n");
            }
        } else if (strncmp(command, "continue game", 14) == 0) {
            printf("Continue.\n");
            break;
        } else {
            printf("Invalid command. Available commands: look, pickup <item>, exit.\n");
        }
    }
}


void run_game() {

    // Örnek veri yazma
Item test_item = {"Sword", 10};  // Örnek bir item
FILE *file = fopen("savegames/user45.sav", "wb");
if (file == NULL) {
    perror("Dosya açılmadı");
    exit(1);
}
fwrite(&test_item, sizeof(Item), 1, file);
fclose(file);


    Player player;
    Map game_map;
    Room *current_room;
    char command[100];

    // Initialize player and map
    init_player(&player);
    init_map(&game_map, ROWS, COLS);

    // 5x5 matris için odaları ve bağlantıları ekle
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS ;x++) {
            char description[50];
            
            snprintf(description, sizeof(description), "Room (%d, %d)", x, y);
            // 0 veya 1 atıyacak isDark için
            int is_dark = rand() % 2;  // 0 veya 1 alır
            add_room_to_map(&game_map, x, y, description, is_dark);

            // Bağlantılar kur (sağ ve aşağı bağlantılar)
            if (x > 0) {
                connect_rooms_on_map(&game_map, x - 1, y, x, y, "right");
            }
            if (y > 0) {
                connect_rooms_on_map(&game_map, x, y - 1, x, y, "down");
            }
        }
    }

    current_room = game_map.rooms[0][0];

    Item items[] = {
    {"Star Ball", 100},
    {"Moon Glow", 150},
    {"Nebula Dust", 200},
    {"Black Hole Energy", 300},
    {"Asteroid Ore", 250},
    {"Supernova", 350},
    {"Sun Crystal", 40},
    {"Planet Dust", 50},
    {"Quasar Glow", 500},
    {"Milky Way Glow", 60},
    {"Galaxy Core", 450},
    {"Comet Tail", 550},
    {"Meteorite Shard", 65},
    {"Solar Wind", 70},
    {"Void Energy", 75}
};

    // Odalara öğeleri ekle
    add_item_to_room(game_map.rooms[0][1], &items[0]);
    add_item_to_room(game_map.rooms[1][1], &items[1]);
    add_item_to_room(game_map.rooms[2][2], &items[2]);
    add_item_to_room(game_map.rooms[3][3], &items[3]);
    add_item_to_room(game_map.rooms[4][4], &items[4]);
    add_item_to_room(game_map.rooms[0][1], &items[5]);
    add_item_to_room(game_map.rooms[1][0], &items[6]);
    add_item_to_room(game_map.rooms[2][1], &items[7]);
    add_item_to_room(game_map.rooms[3][2], &items[8]);
    add_item_to_room(game_map.rooms[4][3], &items[9]);
    add_item_to_room(game_map.rooms[0][2], &items[10]);
    add_item_to_room(game_map.rooms[1][3], &items[11]);
    add_item_to_room(game_map.rooms[2][4], &items[12]);
    add_item_to_room(game_map.rooms[3][0], &items[13]);
    add_item_to_room(game_map.rooms[4][1], &items[14]);



        Attacker attackers[] = {
        {"Orion Team Star", 50},
        {"Big Bear Team", 60},
        {"Lion Team Star", 70},
        {"Scorpion Team", 80},
        {"King Team", 90},
        {"Bull Team", 40},
        {"Sail Team", 120},
        {"Musical Team", 150},
        {"Sailing Team", 200},
        {"Eagle Team", 110},
        {"Shadow Team", 130},
        {"Phoenix Team", 180},
        {"Dragon Team", 160},
        {"Titan Team", 210},
        {"Thunder Team", 220}
    };

    // Adding attackers to rooms
    add_attacker_to_room(game_map.rooms[0][1], &attackers[0]);  // Orion Team Star
    add_attacker_to_room(game_map.rooms[1][1], &attackers[1]);  // Big Bear Team
    add_attacker_to_room(game_map.rooms[2][2], &attackers[2]);  // Lion Team Star
    add_attacker_to_room(game_map.rooms[3][3], &attackers[3]);  // Scorpion Team
    add_attacker_to_room(game_map.rooms[4][4], &attackers[4]);  // King Team
    add_attacker_to_room(game_map.rooms[0][1], &attackers[5]);  // Bull Team
    add_attacker_to_room(game_map.rooms[1][2], &attackers[6]);  // Sail Team
    add_attacker_to_room(game_map.rooms[2][3], &attackers[7]);  // Musical Team
    add_attacker_to_room(game_map.rooms[3][0], &attackers[8]);  // Sailing Team
    add_attacker_to_room(game_map.rooms[4][2], &attackers[9]);  // Eagle Team
    add_attacker_to_room(game_map.rooms[0][2], &attackers[10]); // Shadow Team
    add_attacker_to_room(game_map.rooms[1][3], &attackers[11]); // Phoenix Team
    add_attacker_to_room(game_map.rooms[2][4], &attackers[12]); // Dragon Team
    add_attacker_to_room(game_map.rooms[3][4], &attackers[13]); // Titan Team
    add_attacker_to_room(game_map.rooms[4][0], &attackers[14]); // Thunder Team

    

    printf("Do you want to start a new game or continue a saved game? (new/continue): ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Yeni satır karakterini temizle

    if (strcmp(command, "new") == 0) {
        // Yeni oyun başlat
        set_playername(&player);
        printf("Welcome to the game, %s!\n", player.name);
    } else if (strcmp(command, "continue") == 0) {
        // Kaydeden oyundan devam et
        load_game_from_saved(&player);
    } else {
        printf("Invalid option, starting a new game by default.\n");
        set_playername(&player);
    }



    show_instructions();
    // Game loop
    while (1) {
        printf("\nCurrent room: %s\n", current_room->description);
        printf("You can move:");
        if (current_room->up) printf(" up");
        if (current_room->down) printf(" down");
        if (current_room->left) printf(" left");
        if (current_room->right) printf(" right");
        printf(".\n");

        if (player.health >= 500) {
            printf("\nCongratulations! You reached 500 points. You win the game!\n");
            break; // Exit the loop to end the game
        }

        printf("\nEnter command: ");
        fgets(command, 100, stdin);
        command[strcspn(command, "\n")] = 0; 
        handle_command(&player, &current_room, command);
        
    }
}
