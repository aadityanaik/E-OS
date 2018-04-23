#include "command.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <conio.h>
#include <cctype>
#include "../shell.hpp"
#include "../../processmanagement/processmanagement.hpp"

namespace io {
	Command::Command(std::string line, Shell callShell) {
		shell = callShell;
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

	bool Command::getLoginFlag() {
		return shell.getNewLoginFlag();
	}

	std::string Command::getCommd() {
		return commd;
	}

	Shell Command::getShell() {
		return shell;
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
		else if (commd == "login") {
			if (numArgs > 0) {
				return "\'login\': too many arguments.";
			}
			return login(shell);
		}
		else if (commd == "addusr") {
			if (numArgs > 0) {
				return "\'addusr\': too many arguments.";
			}
			return addusr(&shell);
		}
		else if (commd == "remusr") {
			if (numArgs == 0) {
				return "\'remusr\': needs user name as argument.";
			}
			else if (numArgs > 1) {
				return "\'remusr\': too many arguments.";
			}
			return remusr(shell, args[0]);
		}
		else if (commd == "chpass") {
			if (numArgs == 0) {
				return chpass(shell);
			}
			else {
				return "\'chpass\': too many arguments.";
			}
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
			else if (commd == "write") {
				commdCode = 4;
			}
			else if (commd == "append") {
				commdCode = 5;
			}
			else if (commd == "rm") {
				commdCode = 6;
			}
			else if (commd == "addprc") {
				commdCode = 7;
			}
			else if (commd == "delprc") {
				commdCode = 8;
			}
			else if (commd == "pat") {
				commdCode = 9;
			}
			else {
				return "\'" + commd + "\': no such command";
			}

			return createProcess(commdCode, args, numArgs);
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
			return std::to_string(std::stod(args[0]));
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
			return std::to_string(std::stod(args[0]));
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

	std::string login(Shell& shell) {
		shell.setNewLoginFlag(true);
		return "";
	}

	std::string addusr(Shell* shell) {
		std::string username = "";
		char c;
		while (true) {
			std::cout << "\rNew Username- " << username;
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if(username.size() > 0)
				username.pop_back();
			}
			else {
				username.push_back(c);
			}
		}

		if (shell->getUserPasswordMap()[username] != "") {
			return "User " + username + " already exists.";
		}

		std::string passwd, confPasswd;
		while (true) {
			std::cout << "\rPassword- " << std::string(passwd.length(), '*');
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (passwd.size() > 0)
				passwd.pop_back();
			}
			else {
				passwd.push_back(c);
			}
		}

		while (true) {
			std::cout << "\rConfirm Password- " << std::string(confPasswd.length(), '*');
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (confPasswd.size() > 0)
				confPasswd.pop_back();
			}
			else {
				confPasswd.push_back(c);
			}
		}

		if (passwd == confPasswd) {
			shell->addUser(username, passwd);
			return "User " + username + " added.";
		}
		else {
			return "Passwords do not match";
		}
	}

	std::string remusr(Shell& shell, std::string username) {
		if (username == "root") {
			return "Cannot remove root.";
		}
		if (shell.getUserName() == "root") {
			if (shell.getUserPasswordMap()[username] != "") {
				shell.removeusr(username);
				return "Removed " + username;
			}
		}
		else {
			return "Must be root to remove user.";
		}
	}

	std::string chpass(Shell& shell) {
		std::string username = "";
		char c;
		while (true) {
			std::cout << "\rUsername- " << username;
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (username.size() > 0)
					username.pop_back();
			}
			else {
				username.push_back(c);
			}
		}

		if (shell.getUserPasswordMap()[username] == "") {
			return "User " + username + " does not exist.";
		}

		std::string passwd, confPasswd, oldPasswd;
		while (true) {
			std::cout << "\rOld Password- " << std::string(oldPasswd.length(), '*');
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (oldPasswd.size() > 0)
					oldPasswd.pop_back();
			}
			else {
				oldPasswd.push_back(c);
			}
		}

		if (shell.getUserPasswordMap()[username] != oldPasswd) {
			return "Old password does not match";
		}

		while (true) {
			std::cout << "\rNew Password- " << std::string(passwd.length(), '*');
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (passwd.size() > 0)
					passwd.pop_back();
			}
			else {
				passwd.push_back(c);
			}
		}

		while (true) {
			std::cout << "\rConfirm Password- " << std::string(confPasswd.length(), '*');
			c = _getch();
			if ((int)c == 13 || std::isspace(c)) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
				if (confPasswd.size() > 0)
					confPasswd.pop_back();
			}
			else {
				confPasswd.push_back(c);
			}
		}

		if (passwd == confPasswd) {
			shell.changePass(username, passwd);
			return "User " + username + "'s password changed.";
		}
		else {
			return "Did not change password";
		}
	}
}