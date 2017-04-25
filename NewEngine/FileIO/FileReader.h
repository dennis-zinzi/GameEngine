/**
 * Main class responsible for reading resources from files/directories
 * @author: Dennis Zinzi (130301136)
 */
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

		//Reads single file, and stores contents line-by-line in string vector
		vector<string> ReadFile(string filename);

		//Reads file representing RenderObjects,
		//and stores object details on single line in string vector
		vector<vector<string>> ReadObjectInfo(string filename);

		//Stores filename of every file within given directory with specified file extension
		vector<string> GetDirFiles(string directory, string fileextension);
};