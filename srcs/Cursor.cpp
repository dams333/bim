#include "Cursor.hpp"

Cursor::Cursor() : line(0), pos(0) {
}

Cursor::~Cursor() {
}

Cursor::Cursor(Cursor const &src) {
	*this = src;
}

Cursor &Cursor::operator=(Cursor const &rhs) {
	this->line = rhs.line;
	this->pos = rhs.pos;
	return *this;
}

int Cursor::getLine() const {
	return this->line;
}

int Cursor::getPos() const {
	return this->pos;
}

void Cursor::setLine(int line) {
	this->line = line;
}

void Cursor::setPos(int pos) {
	this->pos = pos;
}