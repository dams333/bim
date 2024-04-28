#include "File.hpp"

File::File(): isDefined(false), path("") {
}

File::File(std::string path): isDefined(true), path(path) {
}

File::~File() {
}

File::File(File const &src) {
	*this = src;
}

File &File::operator=(File const &rhs) {
	this->isDefined = rhs.isDefined;
	this->path = rhs.path;
	return *this;
}

std::string File::getPath() const {
	return this->path;
}

bool File::isFileDefined() const {
	return this->isDefined;
}

void File::setPath(std::string path) {
	this->path = path;
	this->isDefined = true;
}