#pragma once

#include <string>
#include <map>
#include <array>

#include "../shell.hpp"

namespace io {

	const std::map< std::string, std::array<int, 2> > definedCommands = { { "exit", std::array<int, 2>{0, 0} },{ "echo", std::array<int, 2>{-1, 0} },
																	{ "who", std::array<int, 2>{0, 0} },{ "help", std::array<int, 2>{0, 0} } };
	// in the map, the string denotes the commands while the array of integers it is mapped to denotes the number of arguments needed and whether
	// it needs the processor to execute the commands ( 1 if true )

	class Command {
	private:
		// format is command and args
		std::string commd;
		std::string* args;
		unsigned int numArgs;

	public:
		// parameterized constructor
		Command(std::string);

		std::string getString();

		std::string execute();
	};

	Command parse(std::string line);

	// command definitions
	std::string echo(std::string strToEcho);
	void exit();
	std::string who(Shell& shell);
	std::string help();
}