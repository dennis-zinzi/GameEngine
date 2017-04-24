#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::vector;
using std::cout;
using std::endl;

#define FILE_PATH "../Assets/Files/"

class FileReader{
	public:
		FileReader();

		//void ReadFile(string filename);
		vector<vector<string>> ReadObjectInfo(string filename);
};