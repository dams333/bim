#include "Editor.hpp"

Editor::Editor(): firstLine(0) {
}

Editor::~Editor() {
}

Editor::Editor(Editor const &src) {
	*this = src;
}

Editor &Editor::operator=(Editor const &rhs) {
	if (this != &rhs) {
		*this = rhs;
	}
	this->screen = rhs.screen;
	this->cursor = rhs.cursor;
	this->firstLine = rhs.firstLine;
	this->contentBuffer = rhs.contentBuffer;
	return *this;
}

void Editor::init() {
	this->screen.init();
}

void Editor::update() {
	this->screen.clear();

	for (int i = 0; i < this->screen.getHeight(); i++) {
		int line = i + this->firstLine;
		if (line >= this->contentBuffer.getLineCount()) {
			break;
		}
		this->screen.print(0, i, this->contentBuffer.getLine(line).c_str());
	}

	this->screen.setCursor(this->cursor.getX(), this->cursor.getY());

	this->screen.update();
}

#include <iostream>

void Editor::routine() {
	while (true) {
		int c = this->screen.getInput();
		std::cerr << c << std::endl;
		if (c == KEY_RESIZE) {
			this->screen.resize();
		} else if (c == 113) { // Q
			break;
		} else if (c == 68) { // Left
			if (this->cursor.getX() > 0)
				this->cursor.setX(this->cursor.getX() - 1);
		} else if (c == 67) { // Right
			if (this->cursor.getX() < this->screen.getWidth() - 1)
				this->cursor.setX(this->cursor.getX() + 1);
		} else if (c == 65) { // Up
			if (this->cursor.getY() > 0)
				this->cursor.setY(this->cursor.getY() - 1);
		} else if (c == 66) { // Down
			if (this->cursor.getY() < this->screen.getHeight() - 1 && this->cursor.getY() < this->contentBuffer.getLineCount() - 1)
				this->cursor.setY(this->cursor.getY() + 1);
		} else if (c == 10) { // Enter
			if (this->cursor.getY() == this->screen.getHeight() - 1) {
				this->firstLine++;
			}
			this->contentBuffer.newLine(this->cursor.getY() + this->firstLine);
			this->cursor.setX(0);
			this->cursor.setY(this->cursor.getY() + 1);
		} else if (c == 127) { // Backspace
			if (this->cursor.getX() > 0) {
				this->contentBuffer.erase(this->cursor.getY() + this->firstLine, this->cursor.getX() - 1);
				this->cursor.setX(this->cursor.getX() - 1);
			}
		} else if (isprint(c) && c != 27 && c != 91) {
			this->contentBuffer.append(this->cursor.getY() + this->firstLine, this->cursor.getX(), c);
			this->cursor.setX(this->cursor.getX() + 1);
		}

		int currentLineLength = this->contentBuffer.getLine(this->cursor.getY() + this->firstLine).length();
		if (this->cursor.getX() > currentLineLength) {
			this->cursor.setX(currentLineLength);
		}

		this->update();
	}
}