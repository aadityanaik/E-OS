#pragma once
#include <string>

namespace io {
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
	};

	Command parse(std::string line);
}