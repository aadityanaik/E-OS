#include "shell.hpp"

#include <iostream>

using namespace io;

Shell::Shell() {
	newLogin = false;
	userpasswd.insert(std::pair<std::string, std::string>("root", "password"));
}

Shell::Shell(int bufferSize) {
	newLogin = false;
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

void Shell::setNewLoginFlag(bool flag) {
	newLogin = flag;
}

bool Shell::getNewLoginFlag() {
	return newLogin;
}

void Shell::addUser(std::string usrname, std::string passwd) {
	userpasswd.insert(std::pair< std::string, std::string > (usrname, passwd));
}

void Shell::setUserPasswordMap(std::map<std::string, std::string> userpassword) {
	userpasswd = userpassword;
}

std::map<std::string, std::string> Shell::getUserPasswordMap() {
	return userpasswd;
}

void Shell::removeusr(std::string user) {
	userpasswd.erase(user);
}