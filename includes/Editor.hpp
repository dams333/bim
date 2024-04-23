#pragma once

#include "Screen.hpp"
#include "Cursor.hpp"
#include "ContentBuffer.hpp"

class Editor {
	private:
		Screen screen;
		Cursor cursor;
		ContentBuffer contentBuffer;
		int firstLine;

		void update();

	public:
		Editor();
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};