#pragma once

#include <map>

#include "Screen.hpp"
#include "Cursor.hpp"
#include "ContentBuffer.hpp"

class Editor {
	private:
		typedef enum {
			VISUAL,
			INSERT,
		} Mode;
		static const int FOOTER_HEIGHT = 2;

		Screen screen;
		Cursor cursor;
		ContentBuffer contentBuffer;
		int firstLine;
		int lastPrintedLine;
		int lastUsedScreenLine;
		Editor::Mode mode;

		void update();
		int getLeftPadding();
		std::pair<int, int> printContent();

		bool inputHandler(int input);
		void repairCursor();
		void arrowUp();
		void arrowDown();
		void arrowLeft();
		void arrowRight();
		void enter();
		void erase();
		void addChar(int input);

	public:
		Editor();
		Editor(ContentBuffer const contentBuffer);
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};