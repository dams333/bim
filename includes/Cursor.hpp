#pragma once

class Cursor {
	private:
		int x;
		int y;

	public:
		Cursor();
		~Cursor();
		Cursor(Cursor const &src);

		Cursor &operator=(Cursor const &rhs);

		int getX() const;
		int getY() const;

		void setX(int x);
		void setY(int y);
};