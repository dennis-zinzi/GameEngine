#include "FileReader.h"

FileReader::FileReader(){
}

//void FileReader::ReadFile(string filename){
//	string filePath = FILE_PATH + filename;
//	ifstream file(filePath);
//
//	if(!file.good()){
//		cout << "Error: file " << filename << " not found, check name" << endl;
//	}
//
//	for(string line; getline(file, line);){
//		cout << line << endl;
//	}
//}


vector<vector<string>> FileReader::ReadObjectInfo(string filename){
	string filePath = FILE_PATH + filename;

	vector<vector<string>> fullData;

	ifstream file(filePath);

	if(!file.good()){
		cout << "Error: file " << filename << " not found, check name" << endl;
	}

	for(string line; getline(file, line);){
		//If line starts with # then it's a comment, so ignore it
		if(line.at(0) == '#'){
			continue;
		}

		istringstream iss(line);

		vector<string> data;
		string value;

		while(getline(iss, value, '\t')){
			data.push_back(value);
		}

		fullData.push_back(data);
		//cout << line << endl;
	}

	return fullData;
}
