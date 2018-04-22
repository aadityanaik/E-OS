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
		else if (commd == "add") {
			return add(args, numArgs);
		}
		else if (commd == "sub") {
			return subtract(args, numArgs);
		}
		else if (commd == "mult") {
			return multiply(args, numArgs);
		}
		else if (commd == "div") {
			return divide(args, numArgs);
		}
		else {
			// Will require process management module

			int commdCode = 0;
			// denotes the command code

			if (commd == "roundrobin") {
				commdCode = -1;
			}
			else if (commd == "lf") {
				commdCode = 1;
			}
			else if (commd == "fat") {
				commdCode = 2;
			}
			else if (commd == "read") {
				commdCode = 3;
			}
			else if (commd == "append") {
				commdCode = 4;
			}
			else if (commd == "write") {
				commdCode = 5;
			}
			else {
				return "\'" + commd + "\': no such command";
			}

			return "";
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

	std::string add(std::string* args, int numArgs) {
		if (numArgs == 0) {
			return "0";
		}
		else {
			double argDouble = 0;
			double	 sum = 0;
			for (int i = 0; i < numArgs; i++) {
				try {
					argDouble = std::stod(args[i]);
					sum += argDouble;
				}
				catch (...) {
					return "\'" + args[i] + "\': invalid input";
				}
			}

			return std::to_string(sum);
		}
	}

	std::string subtract(std::string* args, int numArgs) {
		if (numArgs == 0) {
			return "0";
		}
		else if (numArgs == 1) {
			return args[0];
		}
		else if (numArgs == 2) {
			std::string s;
			try {
				s = args[0];
				double a = std::stod(s);
				s = args[1];
				double b = std::stod(s);

				return std::to_string(a - b);
			}
			catch (...) {
				return "\'" + s + "\': invalid input";
			}
		}
		else {
			return "\'sub\': too many arguments";
		}
	}

	std::string multiply(std::string* args, int numArgs) {
		if (numArgs == 0) {
			return "0";
		}
		else {
			double argDouble = 0;
			double	 sum = 1;
			for (int i = 0; i < numArgs; i++) {
				try {
					argDouble = std::stod(args[i]);
					sum *= argDouble;
				}
				catch (...) {
					return "\'" + args[i] + "\': invalid input";
				}
			}

			return std::to_string(sum);
		}
	}

	std::string divide(std::string* args, int numArgs) {
		if (numArgs == 0) {
			return "0";
		}
		else if (numArgs == 1) {
			return args[0];
		}
		else if (numArgs == 2) {
			std::string s;
			try {
				s = args[0];
				double a = std::stod(s);
				s = args[1];
				double b = std::stod(s);

				if (b == 0) {
					return "\'div\': cannot divide by 0";
				}

				return std::to_string(a / b);
			}
			catch (...) {
				return "\'" + s + "\': invalid input";
			}
		}
		else {
			return "\'div\': too many arguments";
		}
	}
}