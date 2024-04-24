#pragma once

class Cursor {
	private:
		int line;
		int pos;

	public:
		Cursor();
		~Cursor();
		Cursor(Cursor const &src);

		Cursor &operator=(Cursor const &rhs);

		int getLine() const;
		int getPos() const;

		void setLine(int line);
		void setPos(int pos);
};