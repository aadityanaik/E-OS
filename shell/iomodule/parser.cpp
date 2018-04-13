#include "parser.hpp"

#include <sstream>

namespace io {
	Command::Command(std::string line) {
		std::stringstream lineStream(line);

		unsigned int countArgs = 0;
		for (char c : line) {
			if (isspace(c)) {
				countArgs++;
			}
		}

		numArgs = countArgs;

		args = new std::string[numArgs];

		lineStream >> commd;

		int i = 0;

		while (lineStream >> args[i]) {
			i++;
			if (i >= numArgs) {
				break;
			}
		}
	}

	std::string Command::getString() {
		std::string string = "";
		string += "Command- " + commd + "\nArgs- ";
		for (int i = 0; i < numArgs; i++) {
			string += args[i] + " ";
		}

		return string;
	}

	Command parse(std::string line) {
		return Command(line);
	}
}