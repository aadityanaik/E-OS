#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "iomodule\input.hpp"
#include "iomodule\command.hpp"

using namespace io;

class Shell {
private:
	std::string user, password;
	io::Buffer buffer;

	std::map<std::string, std::string> userpasswd = { {"root", "password"} };

public:
	Shell() {}

	Shell(int bufferSize) {
		buffer = io::Buffer(bufferSize);
	}

	void setUserNameFromBuffer() {
		user = buffer.getContents();
	}

	void setPasswordFromBuffer() {
		password = buffer.getContents();
	}

	void accept(char a) {
		buffer.accept(a);
	}

	std::string getBufferContents() {
		return buffer.getContents();
	}

	std::string getUserName() {
		return user;
	}

	void clearBfr() {
		buffer.clear();
	}

	bool login() {
		return (userpasswd[user] == password);
	}
};

int main() {
	std::string EXIT_STR = "exit";

	HANDLE handleSTDIN = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handleSTDIN, &mode);
	SetConsoleMode(handleSTDIN, mode & (~ENABLE_ECHO_INPUT));

	char c = '\0';

	Buffer buffer(20);
	Shell shell;

	// Getting the user name
	do {
		while (true) {
			std::cout << "\r>>> Username- " << shell.getBufferContents();
			c = _getch();
			shell.accept(c);
			if ((int)c == 13) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
			}
		}
		shell.setUserNameFromBuffer();

		shell.clearBfr();

		// Getting the password
		while (true) {
			std::cout << "\r>>> Password- ";
			c = _getch();
			shell.accept(c);
			if ((int)c == 13) {
				std::cout << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
			}
		}
		shell.setPasswordFromBuffer();

		shell.clearBfr();

	} while (shell.login());

	std::cout << "Welcome, " << shell.getUserName() << "\n";

	while (true) {
		while (true) {
			std::cout << "\r>>> " << shell.getBufferContents();
			c = _getch();
			shell.accept(c);
			if ((int)c == 13) {
				std::cout << "\n" << parse(shell.getBufferContents()).getString() << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
			}
		}

		if (!shell.getBufferContents().compare("exit")) {
			break;
		} else {
			shell.clearBfr();
		}
	}
}