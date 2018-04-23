#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "iomodule\input.hpp"
#include "iomodule\command.hpp"
#include "shell.hpp"
#include "../processmanagement/processmanagement.hpp"
#include <fstream>

int main() {
	std::string EXIT_STR = "exit";

	HANDLE handleSTDIN = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handleSTDIN, &mode);
	SetConsoleMode(handleSTDIN, mode & (~ENABLE_ECHO_INPUT));

	char c = '\0';
	std::ifstream fat_file("FAT_TABLE.txt");
	if (!fat_file.good()) {

		std::ofstream fat_table_file("FAT_TABLE.txt");           //FAT_TABLE.csv must exist
		if (fat_table_file.is_open()) {
			fat_table_file << "File Name" << "\t" << "Start" << "\t" << "File Size" << std::endl;
		}
		fat_table_file.close();
	} else {
		initFATTable();
	}

	fat_file.close();

	Shell shell;

	// Getting the user name
	while (true) {
		while (true) {
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
				std::cout << "Wrong credentials.\n";
			}
			else {
				break;
			}
		}

		std::cout << "Welcome, " << shell.getUserName() << "\n";

		while (true) {
			io::Command command;
			while (true) {
				std::cout << "\r>>> " << shell.getBufferContents();
				c = _getch();
				shell.accept(c);
				if ((int)c == 13) {
					command = io::parse(shell.getBufferContents(), shell);
					std::cout << "\n";
					std::cout  << command.execute() << "\n";
					break;
				}
				if ((int)c == 8) {
					std::cout << "\b \b";
				}
			}

			shell.clearBfr();

			if (command.getCommd() == "login") {
				break;
			}
			else if (command.getCommd() == "addusr" || command.getCommd() == "remusr") {
				shell.setUserPasswordMap(command.getShell().getUserPasswordMap());
			}
		}
	}
}