#include <Editor.hpp>
#include <ContentBuffer.hpp>
#include <iostream>

int main(int argc, char **argv) {

	Editor editor;

	if (argc == 2) {
		try {
			ContentBuffer contentBuffer(argv[1]);
			editor = Editor(contentBuffer);
		} catch (ContentBuffer::ImpossibleToOpenFileException &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}

	editor.init();
	editor.routine();
    
    return 0;
}