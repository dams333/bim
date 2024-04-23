#include "Cursor.hpp"

Cursor::Cursor() : x(0), y(0) {
}

Cursor::~Cursor() {
}

Cursor::Cursor(Cursor const &src) {
	*this = src;
}

Cursor &Cursor::operator=(Cursor const &rhs) {
	if (this != &rhs) {
		*this = rhs;
	}
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

int Cursor::getX() const {
	return this->x;
}

int Cursor::getY() const {
	return this->y;
}

void Cursor::setX(int x) {
	this->x = x;
}

void Cursor::setY(int y) {
	this->y = y;
}