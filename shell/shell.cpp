#include "shell.hpp"

#include <iostream>
#include <fstream>

using namespace io;

Shell::Shell() {
	newLogin = false;
	setUsernamePasswordMap();
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
	saveUserPasswordMap();
}

std::map<std::string, std::string> Shell::getUserPasswordMap() {
	return userpasswd;
}

void Shell::removeusr(std::string user) {
	userpasswd.erase(user);
}

void Shell::setUsernamePasswordMap() {
	userpasswd.clear();
	std::ifstream passFile("passwd");

	std::string name, passwd;

	if (passFile.is_open()) {
		while (!passFile.eof()) {
			passFile >> name >> password;
			userpasswd.insert(std::pair<std::string, std::string>(name, password));
		}
	}
	else {
		std::ofstream passFileSave("passwd");
		userpasswd.insert(std::pair<std::string, std::string>("root", "password"));
		passFileSave << "root password\n";
		passFileSave.close();
	}

	passFile.close();
}

void Shell::saveUserPasswordMap() {
	std::ofstream passFile("passwd");
	if (passFile.is_open()) {
		for (std::pair<std::string, std::string> upmap : userpasswd) {
			passFile << upmap.first << " " << upmap.second << "\n";
		}
	}
}