#include "ContentBuffer.hpp"

ContentBuffer::ContentBuffer() {
	this->buffer.push_back("");
}

ContentBuffer::~ContentBuffer() {
}

ContentBuffer::ContentBuffer(ContentBuffer const &src) {
	*this = src;
}

ContentBuffer &ContentBuffer::operator=(ContentBuffer const &rhs) {
	if (this != &rhs) {
		*this = rhs;
	}
	this->buffer = rhs.buffer;
	return *this;
}

void ContentBuffer::newLine(int previousIndex) {
	this->buffer.insert(this->buffer.begin() + previousIndex + 1, "");
}

void ContentBuffer::removeLine(int index) {
	this->buffer.erase(this->buffer.begin() + index);
}

int ContentBuffer::getLineCount() {
	return this->buffer.size();
}

std::string ContentBuffer::getLine(int index) {
	return this->buffer[index];
}

void ContentBuffer::setLine(int index, std::string line) {
	this->buffer[index] = line;
}

void ContentBuffer::append(int index, int position, char c) {
	this->buffer[index].insert(this->buffer[index].begin() + position, c);
}

void ContentBuffer::erase(int index, int position) {
	this->buffer[index].erase(this->buffer[index].begin() + position);
}