#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "iomodule\input.hpp"

using namespace io;

int main() {
	HANDLE handleSTDIN = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(handleSTDIN, &mode);
	SetConsoleMode(handleSTDIN, mode & (~ENABLE_ECHO_INPUT));

	char c;

	Buffer buffer(20);

	while(true) {
		std::cout << "\r>>> " << buffer.getContents();;
		c = _getch();
		buffer.accept(c);
		if ((int)c == 13) {
			std::cout << '\n';
			break;
		} else if((int) c == 8) {
			std::cout << " \b";
		}
	}
	getchar();
}