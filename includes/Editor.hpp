#pragma once

#include <map>

#include "Screen.hpp"
#include "Cursor.hpp"
#include "ContentBuffer.hpp"
#include "File.hpp"
#include "EditorConfig.hpp"

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
		File file;
		std::string command;
		bool running;
		std::string message;

		void update();
		int getLeftPadding();
		std::pair<int, int> printContent();

		void inputHandler(int input);
		void repairCursor();
		void arrowUp();
		void arrowDown();
		void arrowLeft();
		void arrowRight();
		void enter();
		void erase();
		void addChar(int input);
		void save();
		void quit(bool force);

		void handleCommand();

		std::string getLineOnScreen(int index);
		int getCursorPosOnScreen();

	public:
		Editor();
		Editor(std::string path);
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};