#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>

// The SnakeGame class represents the main game logic and UI for the Snake game.
class SnakeGame : public QWidget {
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    void paintEvent(QPaintEvent *event) override;      // Handles painting.
    void keyPressEvent(QKeyEvent *event) override;    // Handles keyboard input.

private:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    static const int GRID_SIZE = 20;
    static const int MAX_X = 40;
    static const int MAX_Y = 30;
    static const int DELAY = 100;
    static const int BANNER_HEIGHT = 40;

    QTimer *gameTimer;  // Timer for game updates.
    bool isGameOver;    // Indicates if the game is over.
    bool isPaused;      // Indicates if the game is paused.
    int score;          // Tracks the player's score.

    QVector<QPoint> snake; // Snake segments.
    QPoint food;           // Food position.
    Direction dir;         // Current movement direction.

    void startGame();      // Initializes or restarts the game.
    void pauseGame();      // Pauses or resumes the game.
    void gameOver();       // Ends the game.
    void moveSnake();      // Moves the snake.
    void checkCollision(); // Checks collisions.
    void placeFood();      // Places food at a random location.
    void drawGame(QPainter &painter);      // Draws the game.
    void drawGameOver(QPainter &painter); // Draws the game over screen.
    void drawApple(QPainter &painter, int x, int y, int gridSize);
    void drawSnake(QPainter &painter);
    void drawBanner(QPainter &painter);
};

#endif // SNAKEGAME_H
