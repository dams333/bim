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

		// internal variables
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

		// update and display
		void update();
		int getLeftPadding();
		std::pair<int, int> printContent();
		std::string getLineOnScreen(int index);
		int getCursorPosOnScreen();

		// keyboard input handling
		void inputHandler(int input);
		void repairCursor();
		void arrowUp();
		void arrowDown();
		void arrowLeft();
		void arrowRight();
		void enter();
		void erase();
		void addChar(int input);
		
		// commands
		void handleCommand();
		void save();
		void quit(bool force);

	public:
		Editor();
		Editor(std::string path);
		~Editor();
		Editor(Editor const &src);

		Editor &operator=(Editor const &rhs);

		void init();
		void routine();
};