#include "input.hpp"

namespace io {
	Buffer::Buffer(int size) {
		BUFFER_SIZE = size;
		occupied = 0;
		x = new char[size];
		x[occupied] = '\0';
	}

	// will be called when the buffer needs to accept a character
	void Buffer::accept(char a) {
		if (occupied < BUFFER_SIZE - 1) {
			if ((int)a != 8 && (int)a != 13) {
				x[occupied] = a;
				occupied++;
				x[occupied] = '\0';
			}
			else if ((int)a == 13) {
				// if a is enter, do nothing
			}
		}

		if ((int)a == 8) {
			// if a is backspace, go back by 1
			if (occupied > 0) {
				occupied--;
				x[occupied] = '\0';
			}
		}
	}

	std::string Buffer::getContents() {
		return std::string(x);
	}

	void Buffer::clear() {
		x[0] = '\0';
		occupied = 0;
	}
}