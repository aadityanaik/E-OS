#include "shell.hpp"

#include <iostream>

using namespace io;

Shell::Shell() {
	userpasswd.insert(std::pair<std::string, std::string>("root", "password"));
}

Shell::Shell(int bufferSize) {
	userpasswd.insert(std::pair<std::string, std::string>("root", "password"));
	buffer = io::Buffer(bufferSize);
}

void Shell::setUserNameFromBuffer() {
	user = buffer.getContents();
}

void Shell::setPasswordFromBuffer() {
	password = buffer.getContents();
}

void Shell::accept(char a) {
	buffer.accept(a);
}

std::string Shell::getBufferContents() {
	return buffer.getContents();
}

std::string Shell::getUserName() {
	return user;
}

void Shell::clearBfr() {
	buffer.clear();
}

bool Shell::login() {
	return (userpasswd[user] == password);
}