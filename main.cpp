#include <QApplication>
#include "snakegame.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SnakeGame game; // Create the game instance.
    game.show();    // Show the game window.

    return app.exec(); // Start the Qt event loop.
}
