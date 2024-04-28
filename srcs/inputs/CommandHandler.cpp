#include "Editor.hpp"

void Editor::handleCommand() {
	if (this->command == ":w") {
		this->save();
	} else if (this->command == ":q") {
		this->quit(false);
	} else if (this->command == ":q!") {
		this->quit(true);
	} else if (this->command == ":wq") {
		this->save();
		this->quit(false);
	} else if (this->command == ":x") {
		this->save();
		this->quit(false);
	} else {
		this->message = "Command not found";
	}
}