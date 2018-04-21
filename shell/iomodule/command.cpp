#include "command.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "../shell.hpp"

namespace io {
	Command::Command(std::string line, Shell callShell) {
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

		shell = callShell;
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
		if (commd == "echo") {
			std::string strToEcho = "";
			for (int i = 0; i < numArgs; i++) {
				strToEcho += args[i] + " ";
			}

			return echo(strToEcho);
		}
		else if (commd == "exit") {
			exit();
			return "";
		}
		else if (commd == "who") {
			if (numArgs > 0) {
				return "\'who\': Too many arguments";
			}
			return who(shell);
		}
		else if (commd == "help") {
			return help();
		}
		else if (commd == "cow") {
			if (numArgs > 0) {
				return "\'who\': Too many arguments";
			}
			else {
				return cow();
			}
		}
		else {
			return "\'" + commd + "\': no such command";
		}
	}

	Command parse(std::string line, Shell shell) {
		return Command(line, shell);
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
		for (std::pair< std::string, std::string > pair : definedCommands) {
			commandList += pair.first + "-  " + pair.second + "\n";
		}
		return commandList;
	}

	std::string cow() {
		std::string cowString = "^__^\n(oo)\_______\n(__)\       )\\ / \\\n   ||----w |\n   ||     ||";
		return cowString;
	}
}