#pragma once

#include <string>
#include <map>

#include "iomodule\input.hpp"

class Shell {
private:
	std::string user, password;
	io::Buffer buffer;
	bool newLogin;

	std::map<std::string, std::string> userpasswd;

public:
	Shell();

	Shell(int bufferSize);

	void setUserNameFromBuffer();

	void setPasswordFromBuffer();

	void accept(char a);

	std::string getBufferContents();

	std::string getUserName();

	void setNewLoginFlag(bool);

	void clearBfr();

	bool login();

	bool getNewLoginFlag();

	void addUser(std::string, std::string);

	void setUserPasswordMap(std::map<std::string, std::string> userpassword);

	std::map<std::string, std::string> getUserPasswordMap();

	void removeusr(std::string user);
};

