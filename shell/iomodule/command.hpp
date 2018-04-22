#pragma once

#include <string>
#include <map>
#include <array>

#include "../shell.hpp"

namespace io {

	const std::map< std::string, std::string > definedCommands = { { "exit", "Exits the shell, shutting down the OS" },{ "echo", "Echos your arguments back at you" },
																	{ "who", "Tells you who you are" },{ "help", "Displays all inbuilt commands and their description" },
																	{"cow", "Shows an ASCII cow"}, {"add", "Adds the arguments together"}, {"sub", "Subtracts argument 2 from argument 1"},
																	{"mult", "Multiplies all arguments"}, {"div", "Divides argument 1 by argument 2"} };
	// in the map, the first string denotes commands while the second their description

	class Command {
	private:
		// format is command and args
		std::string commd;
		std::string* args;
		unsigned int numArgs;
		Shell shell;

	public:
		// parameterized constructor
		Command(std::string, Shell);

		std::string getString();

		std::string execute();
	};

	Command parse(std::string line, Shell shell);

	// command definitions
	std::string echo(std::string strToEcho);
	void exit();
	std::string who(Shell& shell);
	std::string help();
	std::string cow();

	// arithmetic commands
	std::string add(std::string*, int);
	std::string subtract(std::string*, int);
	std::string multiply(std::string*, int);
	std::string divide(std::string*, int);
}