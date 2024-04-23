#include "Screen.hpp"

Screen::Screen() {
	this->width = 0;
	this->height = 0;
	this->win = NULL;
}

Screen::~Screen() {
	if (this->win != NULL) {
		this->terminate();
	}
}

Screen::Screen(Screen const &src) {
	*this = src;
}

Screen &Screen::operator=(Screen const &rhs) {
	if (this != &rhs) {
		*this = rhs;
	}
	this->width = rhs.width;
	this->height = rhs.height;
	this->win = rhs.win;
	return *this;
}

int Screen::getWidth() const {
	return this->width;
}

int Screen::getHeight() const {
	return this->height;
}

void Screen::init() {
	if (this->win != NULL) {
		throw std::runtime_error("Screen already initialized");
	}
	initscr();
	noecho();
	curs_set(2);
	keypad(stdscr, TRUE);
	refresh();
	getmaxyx(stdscr, this->height, this->width);
	this->win = newwin(this->height, this->width, 0, 0);
	if (this->win == NULL) {
		throw std::runtime_error("Failed to create window");
	}
	refresh();
}

void Screen::update() {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	wrefresh(this->win);
}

void Screen::terminate() {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	delwin(this->win);
	endwin();

	this->width = 0;
	this->height = 0;
	this->win = NULL;
}

void Screen::clear() {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	wclear(this->win);
}

void Screen::setCursor(int x, int y) {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	wmove(this->win, y, x);
}

void Screen::print(int x, int y, char c) {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	mvwaddch(this->win, y, x, c);
}

void Screen::print(int x, int y, char const *format, ...) {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}
	
	va_list args;
	va_start(args, format);
	va_list args_copy;
	va_copy(args_copy, args);
	int len = vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);
	if (len < 0) {
		throw std::runtime_error("Failed to format string");
	}
	char buffer[len + 1];
	vsnprintf(buffer, len + 1, format, args);
	mvwprintw(this->win, y, x, buffer);
	va_end(args);
}

int Screen::getInput() {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	return wgetch(this->win);
}

void Screen::resize() {
	if (this->win == NULL) {
		throw std::runtime_error("Screen not initialized");
	}

	getmaxyx(stdscr, this->height, this->width);
	wresize(this->win, this->height, this->width);
}