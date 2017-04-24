#pragma once

#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

class JSONReader{
	public:
		JSONReader();

		void ReadJSON(string filename);

};