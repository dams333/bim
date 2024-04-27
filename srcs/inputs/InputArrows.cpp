#include "Editor.hpp"

void Editor::arrowUp() {
	if (this->cursor.getLine() == this->firstLine) {
		if (this->firstLine > 0) {
			this->firstLine--;
		}
	}

	if (this->cursor.getLine() > 0) {
		this->cursor.setLine(this->cursor.getLine() - 1);
	}
	this->repairCursor();
}

void Editor::arrowDown() {
	if (this->cursor.getLine() == this->lastPrintedLine) {
		if (this->lastPrintedLine < this->contentBuffer.getLineCount() - 1) {
			if (this->lastUsedScreenLine >= this->screen.getHeight() - Editor::FOOTER_HEIGHT - 1) {
				this->firstLine++;
			}
		}
	}

	if (this->cursor.getLine() < this->contentBuffer.getLineCount() - 1) {
		this->cursor.setLine(this->cursor.getLine() + 1);
	}
	this->repairCursor();
}

void Editor::arrowLeft() {
	if (this->cursor.getPos() > 0) {
		this->cursor.setPos(this->cursor.getPos() - 1);
	}
	this->repairCursor();
}

void Editor::arrowRight() {
	int lineLength = this->contentBuffer.getLine(this->cursor.getLine()).length();
	if (this->cursor.getPos() < lineLength) {
		this->cursor.setPos(this->cursor.getPos() + 1);
	}
	this->repairCursor();
}