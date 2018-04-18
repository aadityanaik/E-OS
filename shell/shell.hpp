#pragma once

#include <string>
#include <map>

#include "iomodule\input.hpp"

class Shell {
private:
	std::string user, password;
	io::Buffer buffer;

	std::map<std::string, std::string> userpasswd;

public:
	Shell();

	Shell(int bufferSize);

	void setUserNameFromBuffer();

	void setPasswordFromBuffer();

	void accept(char a);

	std::string getBufferContents();

	std::string getUserName();

	void clearBfr();

	bool login();
};

