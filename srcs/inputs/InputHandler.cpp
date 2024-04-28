#include "Editor.hpp"

void Editor::repairCursor() {
	int lineLength = this->contentBuffer.getLine(this->cursor.getLine()).length();
	if (this->cursor.getPos() > lineLength) {
		this->cursor.setPos(lineLength);
	}
}

void Editor::inputHandler(int input) {	
	if (input == KEY_LEFT) {
		this->arrowLeft();
	} else if (input == KEY_RIGHT) {
		this->arrowRight();
	} else if (input == KEY_UP) {
		this->arrowUp();
	} else if (input == KEY_DOWN) {
		this->arrowDown();
	} else if (input == KEY_RESIZE) {
		this->screen.resize();
	} else {
		if (this->mode == Editor::Mode::INSERT) {
			if (input == 27) { // Escape
				this->mode = Editor::Mode::VISUAL;
			} else if (input == 10) { // Enter
				this->enter();
			} else if (input == 127) { // Backspace
				this->erase();
			} else { // char
				this->addChar(input);
			}
		} else if (this->mode == Editor::Mode::VISUAL) {
			if (this->command.length() == 0) {
				if (input == 105) { // i
					this->mode = Editor::Mode::INSERT;
				} else if (input == 58) { // :
					this->command = ":";
				}
			} else {
				if (input == 10) { // Enter
					this->handleCommand();
					this->command = "";
				} else if (input == 27) { // Escape
					this->command = "";
				} else if (input == 127) { // Backspace
					this->command = this->command.substr(0, this->command.length() - 1);
				} else {
					this->command += input;
				}
			}
		}

	}
}