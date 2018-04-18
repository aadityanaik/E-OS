#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "iomodule\input.hpp"
#include "iomodule\command.hpp"
#include "shell.hpp"

int main() {
	std::string EXIT_STR = "exit";

	HANDLE handleSTDIN = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handleSTDIN, &mode);
	SetConsoleMode(handleSTDIN, mode & (~ENABLE_ECHO_INPUT));

	char c = '\0';

	Shell shell;

	// Getting the user name
	while(true) {
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
			std::cout << "\r>>> Password- " << std::string(shell.getBufferContents().length(), '*');
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

		if (!shell.login()) {
			std::cout << "BOOOOOOO\n";
		}
		else {
			break;
		}
	}

	std::cout << "Welcome, " << shell.getUserName() << "\n";

	while (true) {
		while (true) {
			std::cout << "\r>>> " << shell.getBufferContents();
			c = _getch();
			shell.accept(c);
			if ((int)c == 13) {
				std::cout << "\n" << io::parse(shell.getBufferContents()).getString() << "\n";
				break;
			}
			if ((int)c == 8) {
				std::cout << "\b \b";
			}
		}

		if (!shell.getBufferContents().compare("exit")) {
			break;
		}
		else {
			shell.clearBfr();
		}
	}
}