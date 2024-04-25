#pragma once

#include "Screen.hpp"
#include "Cursor.hpp"
#include "ContentBuffer.hpp"

class Editor {
	private:
		static const int FOOTER_HEIGHT = 2;

		Screen screen;
		Cursor cursor;
		ContentBuffer contentBuffer;
		int firstLine;

		void update();
		int getLeftPadding();
		std::pair<int, int> printContent();

		bool escaping;
		bool inputHandler(int input);
		void repairCursor();
		void arrowUp();
		void arrowDown();
		void arrowLeft();
		void arrowRight();

	public:
		Editor();
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};