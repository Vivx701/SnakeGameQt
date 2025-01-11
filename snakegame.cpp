#include "snakegame.h"
#include <QPixmap>
#include <QPainterPath>

// Constructor: Initializes the game and sets up the UI.
SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent), isGameOver(false), isPaused(false), dir(RIGHT), score(0) {
    setFixedSize(GRID_SIZE * MAX_X, GRID_SIZE * MAX_Y + BANNER_HEIGHT);// Set game window size.
    setStyleSheet("background-color: black;");         // Set background color.
    snakeBody.load(":/images/Images/snakebody.png");
    startGame(); // Start the game.
}

// Destructor: Cleans up resources.
SnakeGame::~SnakeGame() {
    if (gameTimer)
        delete gameTimer;
}

// Initializes or restarts the game.
void SnakeGame::startGame() {
    snake.clear();
    snake.append(QPoint(5, 5)); // Initial snake position.
    dir = RIGHT;               // Default direction.
    isGameOver = false;
    isPaused = false;
    score = 0;                 // Reset score.
    placeFood(); // Place the first food.

    // Initialize the game timer and connect it to the moveSnake() function.
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &SnakeGame::moveSnake);
    gameTimer->start(DELAY);
}

// Toggles the pause state of the game.
void SnakeGame::pauseGame() {
    isPaused = !isPaused;
    if (isPaused) {
        gameTimer->stop(); // Stop the timer if paused.
    } else {
        gameTimer->start(DELAY); // Resume the timer if unpaused.
    }
}

// Ends the game and stops the timer.
void SnakeGame::gameOver() {
    isGameOver = true;
    gameTimer->stop();
}

// Moves the snake in the current direction.
void SnakeGame::moveSnake() {
    if (isGameOver || isPaused)
        return;

    QPoint head = snake.front(); // Get the current head position.

    // Update the head position based on the direction.
    switch (dir) {
    case UP:
    {
        head.ry() -= 1;
    }break;
    case DOWN:
    {
        head.ry() += 1;
    }break;
    case LEFT:
    {
        head.rx() -= 1;
    }break;
    case RIGHT:{
        head.rx() += 1;
    }break;
    }

    snake.push_front(head); // Add the new head position to the snake.

    // Check if the snake eats the food.
    if (head == food) {
        score++;   // Increment the score.
        placeFood(); // Place new food.
    } else {
        snake.pop_back(); // Remove the tail if no food is eaten.
    }

    checkCollision(); // Check for collisions.
    update();         // Repaint the game.
}

// Checks if the snake collides with walls or itself.
void SnakeGame::checkCollision() {
    QPoint head = snake.front();

    // Check collision with walls.
    if (head.x() < 0 || head.x() >= MAX_X || head.y() < 0 || head.y() >= MAX_Y) {
        gameOver();
    }

    // Check collision with itself.
    for (int i = 1; i < snake.size(); ++i) {
        if (head == snake[i]) {
            gameOver();
            break;
        }
    }
}

// Places food at a random position on the grid.
void SnakeGame::placeFood() {
    int x = qrand() % MAX_X;
    int y = qrand() % MAX_Y;
    food = QPoint(x, y);

    // Ensure the food doesn't overlap with the snake.
    while (snake.contains(food)) {
        x = qrand() % MAX_X;
        y = qrand() % MAX_Y;
        food = QPoint(x, y);
    }
}

// Paint event to draw the game.
void SnakeGame::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    if (isGameOver) {
        drawGameOver(painter); // Draw "Game Over" screen.
        return;
    }

    drawGame(painter); // Draw the game elements.
}

// Draws the game elements (snake, food, and score).
void SnakeGame::drawGame(QPainter &painter) {

    drawSnake(painter);
    painter.setBrush(Qt::red); // Set brush for food.
    drawApple(painter, food.x(), food.y(), GRID_SIZE);

    // Draw the score at the top-left corner.
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    drawBanner(painter);

}

// Draws the "Game Over" screen.
void SnakeGame::drawGameOver(QPainter &painter) {
    // Draw a semi-transparent overlay for the game over screen
    painter.setBrush(Qt::Dense5Pattern);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    // Set text color
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(30);
    painter.setFont(font);
    painter.setPen(QColor(255, 0, 0)); // Bright red for "Game Over"

    // Draw "Game Over" message
    QString gameOverText = "GAME OVER";
    int textWidth = painter.fontMetrics().horizontalAdvance(gameOverText);
    painter.drawText((width() - textWidth) / 2, height() / 2 - 30, gameOverText);

    // Draw score message
    painter.setPen(QColor(255, 255, 0)); // Yellow for the score
    QString scoreText = QString("SCORE: %1").arg(score);
    textWidth = painter.fontMetrics().horizontalAdvance(scoreText);
    painter.drawText((width() - textWidth) / 2, height() / 2, scoreText);

    // Draw restart instruction
    painter.setPen(QColor(255, 255, 255)); // White for the restart instructions
    QString restartText = "PRESS R TO RESTART";
    textWidth = painter.fontMetrics().horizontalAdvance(restartText);
    painter.drawText((width() - textWidth) / 2, height() / 2 + 30, restartText);
}


void SnakeGame::drawApple(QPainter &painter, int x, int y, int gridSize) {
    // Enable anti-aliasing for smooth edges
    painter.setRenderHint(QPainter::Antialiasing);

    // --- Apple Body ---
    // Create a radial gradient for the apple body
    QRadialGradient gradient(x * gridSize + gridSize / 2, y * gridSize + gridSize / 2, gridSize / 2);
    gradient.setColorAt(0.0, QColor(255, 80, 80));  // Light red in the center
    gradient.setColorAt(0.8, QColor(255, 0, 0));    // Bright red in the middle
    gradient.setColorAt(1.0, QColor(180, 0, 0));    // Dark red at the edges

    // Set the gradient as the brush and draw the apple
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen); // No border
    painter.drawEllipse(x * gridSize, y * gridSize, gridSize, gridSize);

    // Optional: Add a subtle border around the apple (uncomment if needed)
    // painter.setPen(QPen(Qt::black, 1)); // 1-pixel black border
    // painter.drawEllipse(x * gridSize, y * gridSize, gridSize, gridSize);

    // --- Apple Stem ---
    // Draw a small brown rectangle for the stem
    painter.setBrush(QColor(139, 69, 19)); // Brown color
    QRectF stemRect(x * gridSize + gridSize * 0.4, y * gridSize - gridSize * 0.1, gridSize * 0.2, gridSize * 0.4);
    painter.drawRoundedRect(stemRect, gridSize * 0.1, gridSize * 0.1);

    // --- Apple Leaf ---
    // Draw a green leaf using a Bézier curve
    QPainterPath leafPath;
    leafPath.moveTo(x * gridSize + gridSize * 0.5, y * gridSize); // Start at the top center of the apple
    leafPath.cubicTo(
                x * gridSize + gridSize * 0.3, y * gridSize - gridSize * 0.3, // Control point 1
                x * gridSize + gridSize * 0.1, y * gridSize - gridSize * 0.1, // Control point 2
                x * gridSize + gridSize * 0.3, y * gridSize + gridSize * 0.1  // End point
                );
    painter.setBrush(QColor(34, 139, 34)); // Green color
    painter.drawPath(leafPath);
}

void SnakeGame::drawSnake(QPainter &painter) {
    // Enable anti-aliasing for smoother edges
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the head of the snake
    QPoint head = snake.front();
    painter.setBrush(Qt::green); // Green color for the head
    painter.setPen(Qt::NoPen);   // No border for the head
    painter.drawRoundedRect(
                head.x() * GRID_SIZE, head.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE, 10, 10);

    // Draw the body of the snake
    painter.setBrush(Qt::darkGreen); // Darker green for the body
    for (int i = 1; i < snake.size() - 1; ++i) {
        QPoint bodySegment = snake[i];
        painter.drawRoundedRect(
                    bodySegment.x() * GRID_SIZE, bodySegment.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE, 10, 10);
    }

    // Draw the tail of the snake
    QPoint tail = snake.back();
    painter.setBrush(Qt::green); // Same color as the head for simplicity
    painter.drawRoundedRect(
                tail.x() * GRID_SIZE, tail.y() * GRID_SIZE, GRID_SIZE, GRID_SIZE, 10, 10);
}

void SnakeGame::drawBanner(QPainter &painter) {
    // Draw the banner background
    painter.setBrush(QColor(50, 50, 50)); // Dark gray
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width(), BANNER_HEIGHT);

    // Set text color
    painter.setPen(QColor(255, 255, 0)); // Bright yellow

    // Draw the score in the center of the banner
    QString scoreText = QString("SCORE: %1").arg(score);
    int textWidth = painter.fontMetrics().horizontalAdvance(scoreText);
    painter.drawText((width() - textWidth) / 2, 25, scoreText); // Centered
}




// Handles keyboard input to control the snake.
void SnakeGame::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        if (dir != DOWN) dir = UP; // Prevent reverse direction.
        break;
    case Qt::Key_Down:
        if (dir != UP) dir = DOWN; // Prevent reverse direction.
        break;
    case Qt::Key_Left:
        if (dir != RIGHT) dir = LEFT; // Prevent reverse direction.
        break;
    case Qt::Key_Right:
        if (dir != LEFT) dir = RIGHT; // Prevent reverse direction.
        break;
    case Qt::Key_P:
        pauseGame(); // Pause or resume the game.
        break;
    case Qt::Key_R:
        startGame(); // Restart the game.
        break;
    }
}
