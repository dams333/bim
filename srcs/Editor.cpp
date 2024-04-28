#include "Editor.hpp"

Editor::Editor(): firstLine(0), lastPrintedLine(0), lastUsedScreenLine(0), mode(Editor::Mode::VISUAL) {
}

Editor::Editor(ContentBuffer const contentBuffer): firstLine(0), lastPrintedLine(0), lastUsedScreenLine(0), mode(Editor::Mode::VISUAL) {
	this->contentBuffer = contentBuffer;
}

Editor::~Editor() {
}

Editor::Editor(Editor const &src) {
	*this = src;
}

Editor &Editor::operator=(Editor const &rhs) {
	this->screen = rhs.screen;
	this->cursor = rhs.cursor;
	this->firstLine = rhs.firstLine;
	this->contentBuffer = rhs.contentBuffer;
	this->mode = rhs.mode;
	this->lastPrintedLine = rhs.lastPrintedLine;
	this->lastUsedScreenLine = rhs.lastUsedScreenLine;
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
	std::map<int, std::string> res;
	int screenLine = 0;
	for (int line = this->firstLine; line < this->contentBuffer.getLineCount(); line++) {
		if (screenLine >= this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
			break;
		}

		this->lastPrintedLine = line;
		this->lastUsedScreenLine = screenLine;

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
		int firstLineOnScreen = screenLine;
		while (!lineContent.empty()) {
			size_t sizeToPrint = this->screen.getWidth() - leftPadding;
			if (sizeToPrint > lineContent.length()) {
				sizeToPrint = lineContent.length();
			}
			int lastPos = posInLine + sizeToPrint;
			if (line == this->cursor.getLine() && posInLine <= this->cursor.getPos() && this->cursor.getPos() <= lastPos) {
				int cursorPosOnScreen = leftPadding + this->cursor.getPos() - posInLine;
				int cursorLineOnScreen = screenLine;
				if (cursorPosOnScreen >= this->screen.getWidth()) {
					cursorPosOnScreen = leftPadding;
					cursorLineOnScreen++;
				}
				if (cursorLineOnScreen >= this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
					this->firstLine++;
					this->screen.clear();
					return this->printContent();
				}
				cursorOnScreen = std::make_pair(cursorPosOnScreen, cursorLineOnScreen);
			}
			res[screenLine] = lineContent.substr(0, sizeToPrint);
			lineContent = lineContent.substr(sizeToPrint);
			this->lastUsedScreenLine = screenLine;
			screenLine++;
			posInLine += sizeToPrint;

			if (screenLine >= this->screen.getHeight() - Editor::FOOTER_HEIGHT) {
				if (!lineContent.empty()) {
					if (line == this->cursor.getLine()) {
						this->firstLine++;
						this->screen.clear();
						return this->printContent();
					}
					for (int i = firstLineOnScreen; i < screenLine; i++) {
						res[i] = "...";
					}
					std::string clearLine = std::string(this->screen.getWidth(), ' ');
					this->screen.print(0, firstLineOnScreen, clearLine.c_str());
					this->lastPrintedLine = line - 1;
				}
				break;
			}
		}
	}

	for (auto it = res.begin(); it != res.end(); it++) {
		this->screen.printLiteral(leftPadding, it->first, it->second);
	}

	return cursorOnScreen;
}

void Editor::update() {
	this->screen.clear();

	auto cursorOnScreen = this->printContent();

	this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT, "------");
	if (this->mode == Editor::Mode::INSERT) {
		this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT + 1, "INSERT");
	} else {
		this->screen.print(0, this->screen.getHeight() - Editor::FOOTER_HEIGHT + 1, "VISUAL");
	}

	this->screen.setCursor(cursorOnScreen.first, cursorOnScreen.second);

	this->screen.update();
}

void Editor::routine() {
	this->update();
	while (true) {
		int c = this->screen.getInput();
		if (this->inputHandler(c))
			break;
		this->update();
	}
}