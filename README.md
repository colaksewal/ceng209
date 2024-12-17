
---

# Dungeon Game

**Dungeon Game** is a simple text-based adventure game where the player navigates through rooms, manages their inventory, and faces attackers. The game includes a grid-based map, a player with health and strength attributes, and rooms that can contain items and enemies.

---

## 📂 Project Structure

```
/project-root
|-- src/
|   |-- main.c           # Entry point for the game
|   |-- game.c           # Core game logic (commands, game loop)
|   |-- player.c         # Player management (health, inventory)
|   |-- room.c           # Room creation and navigation
|   |-- map.c            # Map grid logic
|   |-- inventory.c      # Inventory management
|   |-- attacker.c       # Attacker behavior (enemy logic)
|   |-- game.h           # Header for game logic
|   |-- player.h         # Header for player management
|   |-- room.h           # Header for room logic
|   |-- map.h            # Header for map logic
|   |-- inventory.h      # Header for inventory management
|   |-- attacker.h       # Header for attacker behavior
|
|-- Makefile             # Build and clean the project
|-- README.md            # Project documentation
```

---

## 🕹️ How to Play

### Objective:
- Explore the dungeon rooms, collect items, and survive attacks from enemies.
- Use commands to navigate and interact with the game environment.

---

### Commands:

| Command              | Description                                    |
|-----------------------|-----------------------------------------------|
| `move `up` / `down` / `right` / `left` | Move to an adjacent room in the specified direction. |
| `look`               | Show a description of the current room and its contents. |
| `inventory`          | List the player's inventory.                  |
| `attack <enemy>`     | Attack an enemy in the room.                  |
| `save`               | Save the game progress.                       |
| `load`               | Load a previously saved game.                 |

---

## 🛠️ Building and Running the Game

1. Clone the repository:
   ```bash
   git clone <repo-link>
   cd project-root
   ```

2. Build and run the game using `Makefile`:
   ```bash
   make
   ```

   - This compiles all the `.c` files and runs the executable.
   - The executable name is `dungeon_game`.

3. Clean up object files and the executable:
   ```bash
   make clean
   ```

---

## 🧩 Game Components

1. **Player**:
   - Health, strength, and an inventory to carry items.
   - Can pick up items, drop items, and fight attackers.

2. **Room**:
   - Each room has a description and may contain items or attackers.
   - Rooms are connected in a grid-based map (north, south, east, west).

3. **Map**:
   - Represents the dungeon as a 2D grid of rooms.

4. **Inventory**:
   - Manages the player's items with a size limit.

5. **Attacker**:
   - Enemies that can attack the player and reduce health.

6. **Game Logic**:
   - Handles user input, room navigation, inventory management, and combat.

---

## 💾 Saving and Loading

- Use the `save` command to save your progress.
- Use the `load` command to load a previous game.

