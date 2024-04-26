#include "Editor.hpp"

Editor::Editor(): firstLine(0), mode(Editor::Mode::VISUAL) {
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
	this->mode = rhs.mode;
	return *this;
}

void Editor::init() {
	this->screen.init();
}

int Editor::getLeftPadding() {
	return std::to_string(this->contentBuffer.getLineCount()).length() + 1;
}

#include <iostream>

std::pair<int, int> Editor::printContent() {
	int leftPadding = this->getLeftPadding();

	if (leftPadding < 4) {
		leftPadding = 4;
	}

	std::pair<int, int> cursorOnScreen = std::make_pair(-1, -1);
	int screenLine = 0;
	for (int line = this->firstLine; line < this->contentBuffer.getLineCount(); line++) {
		if (screenLine >= this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
			break;
		}

		int numerotationPadding = leftPadding - std::to_string(line + 1).length() - 1;
		this->screen.print(numerotationPadding, screenLine, std::to_string(line + 1).c_str());
		std::string lineContent = this->contentBuffer.getLine(line);
		if (lineContent.empty()) {
			if (line == this->cursor.getLine()) {
				cursorOnScreen = std::make_pair(leftPadding, screenLine);
			}
			screenLine++;
		}
		int posInLine = 0;
		while (!lineContent.empty()) {
			size_t sizeToPrint = this->screen.getWidth() - leftPadding;
			if (sizeToPrint > lineContent.length()) {
				sizeToPrint = lineContent.length();
			}
			int lastPos = posInLine + sizeToPrint;
			if (line == this->cursor.getLine() && posInLine <= this->cursor.getPos() && this->cursor.getPos() <= lastPos) {
				cursorOnScreen = std::make_pair(leftPadding + this->cursor.getPos() - posInLine, screenLine);
			}
			this->screen.print(leftPadding, screenLine, lineContent.substr(0, sizeToPrint).c_str());
			lineContent = lineContent.substr(sizeToPrint);
			screenLine++;
			posInLine += sizeToPrint;

			if (screenLine >= this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
				break;
			}
		}
	}

	return cursorOnScreen;
}

void Editor::update() {
	this->screen.clear();

	auto cursorOnScreen = this->printContent();
	if (cursorOnScreen.first >= this->screen.getWidth()) {
		cursorOnScreen.first = this->screen.getWidth() - 1;
	}

	this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT, "------");
	if (this->mode == Editor::Mode::INSERT) {
		this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT + 1, "INSERT");
	} else {
		this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT + 1, "VISUAL");
	}

	this->screen.setCursor(cursorOnScreen.first, cursorOnScreen.second);

	this->screen.update();
}

#include <iostream>

void Editor::routine() {
	this->update();
	while (true) {
		int c = this->screen.getInput();
		if (this->inputHandler(c))
			break;
		this->update();
	}
}