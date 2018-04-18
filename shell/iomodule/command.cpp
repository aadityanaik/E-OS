#include "command.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "../shell.hpp"

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

	std::string Command::execute() {
		std::string string = "";

		return string;
	}

	Command parse(std::string line) {
		return Command(line);
	}

	std::string echo(std::string strToEcho) {
		return strToEcho;
	}

	void exit() {
		std::exit(0);
	}

	std::string who(Shell& shell) {
		return shell.getUserName();
	}

	std::string help() {
		std::string commandList = "";
		for (std::pair< std::string, std::array<int, 2> > pair : definedCommands) {
			commandList += pair.first + "\n";
		}

		return commandList;
	}
}