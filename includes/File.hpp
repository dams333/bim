#pragma once

#include <string>

class File {
	private:
		bool isDefined;
		std::string path;

	public:
		File();
		File(std::string path);
		~File();
		File(File const &src);
		
		File &operator=(File const &rhs);

		std::string getPath() const;
		bool isFileDefined() const;

		void setPath(std::string path);
};