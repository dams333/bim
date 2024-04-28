#pragma once

#include <vector>
#include <string>
#include <fstream>

class ContentBuffer {
	private:
		std::vector<std::string> buffer;

	public:
		ContentBuffer();
		ContentBuffer(std::string filename);
		~ContentBuffer();
		ContentBuffer(ContentBuffer const &src);

		ContentBuffer &operator=(ContentBuffer const &rhs);

		void newLine(int previousIndex);
		void removeLine(int index);
		int getLineCount();
		std::string getLine(int index);
		void setLine(int index, std::string line);
		void append(int index, int position, char c);
		void erase(int index, int position);
		std::string getContent();

		class ImpossibleToOpenFileException: public std::exception {
			public:
				virtual const char *what() const throw() {
					return "Impossible to open file";
				}
		};
};