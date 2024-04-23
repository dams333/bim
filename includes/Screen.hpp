#pragma once

#include <ncurses.h>
#include <cstdarg>
#include <stdexcept>

class Screen {
	private:
		WINDOW *win;
		int width;
		int height;

	public:
		Screen();
		~Screen();
		Screen(Screen const &src);

		Screen &operator=(Screen const &rhs);

		int getWidth() const;
		int getHeight() const;
		
		void init();
		void update();
		void terminate();

		void clear();
		void setCursor(int x, int y);
		void print(int x, int y, char c);
		void print(int x, int y, char const *format, ...);

		int getInput();

		void resize();
};