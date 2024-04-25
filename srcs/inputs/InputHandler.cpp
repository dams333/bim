#include "Editor.hpp"

bool Editor::inputHandler(int input) {
	if (input == KEY_RESIZE) {
		this->screen.resize();
	} else if (input == 113) { // Q
		return true;
	} else if (input == 68) { // Left
	} else if (input == 67) { // Right
	} else if (input == 65) { // Up
	} else if (input == 66) { // Down
	} else if (input == 10) { // Enter
		this->contentBuffer.newLine(this->cursor.getLine());
		//todo: replace detection by real position of cursor on screen (problem with line on multiple lines)
		if (this->cursor.getLine() == this->firstLine + this->screen.getHeight() - Editor::FOOTER_HEIGHT - 1) {
			this->firstLine++;
		}
		this->cursor.setLine(this->cursor.getLine() + 1);
		this->cursor.setPos(0);
	} else if (input == 127) { // Backspace
	} else { // char
		this->contentBuffer.append(this->cursor.getLine(), this->cursor.getPos(), input);
		this->cursor.setPos(this->cursor.getPos() + 1);
	}
	return false;
}