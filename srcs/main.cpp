#include "Screen.hpp"

int main() {
	Screen screen;
	screen.init();
	screen.print(0, 0, "Width: %d", screen.getWidth());
	screen.print(0, 1, "Height: %d", screen.getHeight());
	screen.print(0, 2, "Hello, World!");
	screen.update();
    getch(); // Wait for any user input
    screen.terminate();
    
    return 0;
}