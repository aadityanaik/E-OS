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
		Buffer(int size) {
			BUFFER_SIZE = size;
			occupied = 0;
			x = new char[size];
			x[occupied] = '\0';
		}

		// will be called when the buffer needs to accept a character
		void accept(char a) {
			if (occupied < BUFFER_SIZE - 1) {
				if ((int)a != 8) {
					x[occupied] = a;
					occupied++;
					x[occupied] = '\0';
				} else if((int) a == 13) {
					// if a is enter, do nothing
				}
			}
			
			if((int) a == 8) {
				// if a is backspace, go back by 1
				if (occupied > 0) {
					occupied--;
					x[occupied] = '\0';
				}
			}
		}

		std::string getContents() {
			return std::string(x);
		}
	};
}