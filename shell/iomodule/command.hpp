#pragma once

#include <string>
#include <map>
#include <array>

#include "../shell.hpp"

namespace io {

	const std::map< std::string, std::string > definedCommands = { { "exit", "Exits the shell, shutting down the OS. Takes no arguments." },{ "echo", "Echos your arguments back at you." },
																	{ "who", "Tells you who you are. Takes no arguments." },{ "help", "Displays all inbuilt commands and their description. Takes no arguments." },
																	{"cow", "Shows an ASCII cow. Takes no arguments."}, {"add", "Adds the arguments together."}, {"sub", "Subtracts argument 2 from argument 1. Takes 0, 1 or 2 arguments."},
																	{"mult", "Multiplies all arguments."}, {"div", "Divides argument 1 by argument 2. Takes 0, 1 or 2 arguments."},
																	{"addusr", "Adds a new user to the system"}, {"login", "Takes you to the login screen."}, {"remusr", "Removes a user. Takes one argument."} };
	// in the map, the first string denotes commands while the second their description

	class Command {
	private:
		// format is command and args
		std::string commd;
		std::string* args;
		unsigned int numArgs;
		Shell shell;

	public:
		Command() {}

		// parameterized constructor
		Command(std::string, Shell);

		std::string getCommd();

		std::string execute();

		bool getLoginFlag();

		Shell getShell();
	};

	Command parse(std::string line, Shell shell);

	// command definitions
	std::string echo(std::string strToEcho);
	void exit();
	std::string who(Shell& shell);
	std::string help();
	std::string cow();

	std::string addusr(Shell* shell);
	std::string login(Shell& shell);
	std::string remusr(Shell& shell, std::string username);

	// arithmetic commands
	std::string add(std::string*, int);
	std::string subtract(std::string*, int);
	std::string multiply(std::string*, int);
	std::string divide(std::string*, int);
}