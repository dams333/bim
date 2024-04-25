#include "Editor.hpp"

void Editor::repairCursor() {
	int lineLength = this->contentBuffer.getLine(this->cursor.getLine()).length();
	if (this->cursor.getPos() > lineLength) {
		this->cursor.setPos(lineLength);
	}

	//TODO: replace detection by on screen pos (too long line => 1 line in buffer = 2 lines on screen)
	if (this->cursor.getLine() < this->firstLine) {
		this->firstLine = this->cursor.getLine();
	} else if (this->cursor.getLine() >= this->firstLine + this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
		this->firstLine = this->cursor.getLine() - this->screen.getHeight() + Editor::FOOTER_HEIGHT + 1;
	}
}

bool Editor::inputHandler(int input) {
	if (input == 27) {
		this->escaping = true;
		return false;
	}
	if (this->escaping && input == 91) {
		return false;
	}
	
	if (this->escaping) {
		if (input == 68) {
			this->arrowLeft();
		} else if (input == 67) {
			this->arrowRight();
		} else if (input == 65) {
			this->arrowUp();
		} else if (input == 66) {
			this->arrowDown();
		}
	} else {
		if (input == KEY_RESIZE) {
			this->screen.resize();
		} else if (input == 113) { // Q
			return true;
		} else if (input == 10) { // Enter
			this->contentBuffer.newLine(this->cursor.getLine());
			this->cursor.setLine(this->cursor.getLine() + 1);
			this->cursor.setPos(0);
			this->repairCursor();
		} else if (input == 127) { // Backspace
		} else { // char
			this->contentBuffer.append(this->cursor.getLine(), this->cursor.getPos(), input);
			this->cursor.setPos(this->cursor.getPos() + 1);
		}
	}

	this->escaping = false;
	return false;
}