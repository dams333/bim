#include "ContentBuffer.hpp"

ContentBuffer::ContentBuffer(): hasChanged(false) {
	this->buffer.push_back("");
}

ContentBuffer::ContentBuffer(std::string filename): hasChanged(false) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			this->buffer.push_back(line);
		}
	}
	if (this->buffer.size() == 0) {
		this->buffer.push_back("");
	}
}

ContentBuffer::~ContentBuffer() {
}

ContentBuffer::ContentBuffer(ContentBuffer const &src) {
	*this = src;
}

ContentBuffer &ContentBuffer::operator=(ContentBuffer const &rhs) {
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
	this->hasChanged = true;
}

void ContentBuffer::append(int index, int position, char c) {
	this->buffer[index].insert(this->buffer[index].begin() + position, c);
	this->hasChanged = true;
}

void ContentBuffer::erase(int index, int position) {
	this->buffer[index].erase(this->buffer[index].begin() + position);
	this->hasChanged = true;
}

std::string ContentBuffer::getContent() {
	std::string content;
	for (std::string line : this->buffer) {
		content += line + "\n";
	}
	return content;
}

bool ContentBuffer::getHasChanged() {
	return this->hasChanged;
}

void ContentBuffer::save() {
	this->hasChanged = false;
}