#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>
class fileSystem
{
public:
	fileSystem(const fileSystem& obj) = delete;
	static fileSystem* getFileSystem();

private:
	fileSystem();
	static fileSystem* fSystem;
	//std::unordered_map<std::string, std::string> parameters; // make a hashmap for the input and output to read from and get information from
};