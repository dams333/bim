#pragma once

#include <vector>
#include <string>

class ContentBuffer {
	private:
		std::vector<std::string> buffer;

	public:
		ContentBuffer();
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
};