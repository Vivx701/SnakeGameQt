
# SnakeGameQt - A Basic Game Development Tutorial with Qt C++

Welcome to the **SnakeGameQt** tutorial! This project is designed to introduce beginners to the fundamentals of game development using Qt C++. By the end of this tutorial, you'll have a fully functional snake game and a better understanding of Qt's capabilities.

![Game Screenshot](.screenshots/game.png)

## Features
- Smooth snake movement with `QTimer`.
- Dynamic food placement.
- Collision detection for game over conditions.
- Simple scoring system.
- Pause and restart functionality.
- Customizable game grid and visuals.

---

## Getting Started

### Prerequisites
1. Install [Qt Framework](https://www.qt.io/download).
2. Set up Qt Creator IDE (recommended for a seamless experience).

### Clone the Repository
```bash
git clone https://github.com/YourUsername/SnakeGameTutorial.git
cd SnakeGameTutorial
```

### Build and Run
1. Open the project in Qt Creator.
2. Configure the build kit (Qt 6.0+ is required).
3. Click the **Run** button to compile and launch the game.

---

## How the Game Works
- **Snake Movement**: Controlled using arrow keys.
  - `↑`: Move Up
  - `↓`: Move Down
  - `←`: Move Left
  - `→`: Move Right
- **Pause/Resume**: Press `P`.
- **Restart**: Press `R`.

The objective is to eat the red apples, grow the snake, and achieve the highest score without colliding with the walls or yourself.

---

## Project Structure
- **`main.cpp`**: Entry point for the application.
- **`snakegame.h/.cpp`**: Core game logic and rendering.
- **`README.md`**: This tutorial document.

---

## Exercises for Beginners
1. Change the snake's appearance using a custom image.
2. Add a feature to increase the snake's speed as the score increases.
3. Implement wrap-around walls (e.g., the snake appears on the opposite side when crossing a boundary).
4. Add sound effects for food collection and game over events.

---

## Contributing
Feel free to fork this repository and submit pull requests. Suggestions and improvements are always welcome!

---

## License
This project is licensed under the GNU General Public License (GPL). See the [LICENSE](./LICENSE) file for details.

---

Happy coding! 🎮
