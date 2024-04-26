#include "Editor.hpp"

void Editor::enter() {
	int lineLength = this->contentBuffer.getLine(this->cursor.getLine()).length();
	if (this->cursor.getPos() < lineLength) {
		std::string line = this->contentBuffer.getLine(this->cursor.getLine()).substr(this->cursor.getPos());
		this->contentBuffer.setLine(this->cursor.getLine(), this->contentBuffer.getLine(this->cursor.getLine()).substr(0, this->cursor.getPos()));
		this->contentBuffer.newLine(this->cursor.getLine());
		this->contentBuffer.setLine(this->cursor.getLine() + 1, line);
	} else {
		this->contentBuffer.newLine(this->cursor.getLine());
	}
	this->cursor.setLine(this->cursor.getLine() + 1);
	this->cursor.setPos(0);
	this->repairCursor();
}

void Editor::erase() {
	if (this->cursor.getPos() > 0) {
		this->contentBuffer.setLine(this->cursor.getLine(), this->contentBuffer.getLine(this->cursor.getLine()).substr(0, this->cursor.getPos() - 1) + this->contentBuffer.getLine(this->cursor.getLine()).substr(this->cursor.getPos()));
		this->cursor.setPos(this->cursor.getPos() - 1);
	} else if (this->cursor.getLine() > 0) {
		int lineLength = this->contentBuffer.getLine(this->cursor.getLine() - 1).length();
		this->contentBuffer.setLine(this->cursor.getLine() - 1, this->contentBuffer.getLine(this->cursor.getLine() - 1) + this->contentBuffer.getLine(this->cursor.getLine()));
		this->contentBuffer.removeLine(this->cursor.getLine());
		this->cursor.setLine(this->cursor.getLine() - 1);
		this->cursor.setPos(lineLength);
	}
}

void Editor::addChar(int input) {
	this->contentBuffer.append(this->cursor.getLine(), this->cursor.getPos(), input);
	this->cursor.setPos(this->cursor.getPos() + 1);
}