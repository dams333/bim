#include "Editor.hpp"

Editor::Editor() {
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
	return *this;
}

void Editor::init() {
	this->screen.init();
}

void Editor::update() {
	this->screen.clear();

	this->screen.print(1, 1, "Width: %d", this->screen.getWidth());
	this->screen.print(1, 2, "Height: %d", this->screen.getHeight());

	this->screen.setCursor(this->cursor.getX(), this->cursor.getY());

	this->screen.update();
}

void Editor::routine() {
	while (true) {
		int c = this->screen.getInput();
		if (c == KEY_RESIZE) {
			this->screen.resize();
		}
		if (c == 113) { // Q
			break;
		}
		if (c == 68 && this->cursor.getX() > 0) { // Left
			this->cursor.setX(this->cursor.getX() - 1);
		}
		if (c == 67 && this->cursor.getX() < this->screen.getWidth() - 1) { // Right
			this->cursor.setX(this->cursor.getX() + 1);
		}
		if (c == 65 && this->cursor.getY() > 0) { // Up
			this->cursor.setY(this->cursor.getY() - 1);
		}
		if (c == 66 && this->cursor.getY() < this->screen.getHeight() - 1) { // Down
			this->cursor.setY(this->cursor.getY() + 1);
		}
		this->update();
	}
}