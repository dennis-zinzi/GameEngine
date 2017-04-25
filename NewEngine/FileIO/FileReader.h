#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>

using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::vector;
using std::cout;
using std::endl;

#define FILE_PATH "../Assets/Files/"
#define AUDIO_PATH "../Assets/Sounds/"

class FileReader{
	public:
		FileReader();

		vector<string> ReadFile(string filename);
		vector<vector<string>> ReadObjectInfo(string filename);

		vector<string> GetDirFiles(string directory, string fileextension);
};