#pragma once
#include <string>

namespace io {
	class Buffer {
		// buffer will be an independent array of characters
		// size will be dictated by the constructor
	private:
		char* x;
		int occupied;
		int BUFFER_SIZE;

	public:
		// Parameterized constructor
		Buffer(int size);

		// will be called when the buffer needs to accept a character
		void accept(char a);

		std::string getContents();

		// to clear the buffer completely
		void clear();
	};
}