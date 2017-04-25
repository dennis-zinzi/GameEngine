#include "FileReader.h"

FileReader::FileReader(){
}

vector<string> FileReader::ReadFile(string filename){
	string filePath = FILE_PATH + filename;
	ifstream file(filePath);

	//Check file exists
	if(!file.good()){
		cout << "Error: file " << filename << " not found, check name" << endl;
	}

	vector<string> fileData;

	for(string line; getline(file, line);){
		//If line starts with # then it's a comment, so ignore it
		if(line.at(0) == '#'){
			continue;
		}

		//Else store line containing data in vector
		fileData.push_back(line);
	}

	return fileData;
}


vector<vector<string>> FileReader::ReadObjectInfo(string filename){
	string filePath = FILE_PATH + filename;

	//Vector representing a list of renderobjects
	vector<vector<string>> fullData;

	ifstream file(filePath);

	//Check file exists
	if(!file.good()){
		cout << "Error: file " << filename << " not found, check name" << endl;
		return fullData;
	}

	for(string line; getline(file, line);){
		//If line starts with # then it's a comment, so ignore it
		if(line.at(0) == '#'){
			continue;
		}

		istringstream iss(line);

		vector<string> data;
		string value;

		//Split each line up by "tab" key
		while(getline(iss, value, '\t')){
			data.push_back(value);
		}

		//Store object detatils in list
		fullData.push_back(data);
	}

	return fullData;
}


/**
 * Gets vector list of files in given directory
 * Adapted from http://forums.devarticles.com/c-c-help-52/c-opening-all-txt-files-in-a-folder-one-by-150745.html
 */
vector<string> FileReader::GetDirFiles(string directory, string fileextension){
	string searchPattern = "*." + fileextension;
	string fullSearchPath = directory + searchPattern;

	WIN32_FIND_DATA FindData;
	HANDLE hFind;

	hFind = FindFirstFile(fullSearchPath.c_str(), &FindData);

	if(hFind == INVALID_HANDLE_VALUE){
		cout << "Error searching directory: " << fullSearchPath.c_str() << endl;
		return vector<string>();
	}

	vector<string> files;

	do{
		string filePath = directory + FindData.cFileName;
		ifstream in(filePath.c_str());
		if(in){
			files.push_back(FindData.cFileName);
		}
		else{
			cout << "Problem opening file " << FindData.cFileName << endl;
		}
	}
	while(FindNextFile(hFind, &FindData) > 0);

	if(GetLastError() != ERROR_NO_MORE_FILES){
		cout << "Something went wrong during searching" << endl;
	}

	return files;
}
