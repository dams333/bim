#pragma once

#include <Screen.hpp>
#include <Cursor.hpp>

class Editor {
	private:
		Screen screen;
		Cursor cursor;

		void update();

	public:
		Editor();
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};