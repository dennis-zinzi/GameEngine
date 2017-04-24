#include "DataLoader.h"

DataLoader::DataLoader(GraphicsRenderer &renderer, PhysicsManager &physics, FileReader &reader){
	this->renderer = &renderer;
	this->physics = &physics;
	this->reader = &reader;
}


void DataLoader::LoadRadWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("sample_radius_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[0] == "Sphere"){
			shape = Shape::Sphere;
		}
		else if(data[0] == "Cylinder"){
			shape = Shape::Cylinder;
		}
		else if(data[0] == "Cone"){
			shape = Shape::Cone;
		}

		new GameObject(*renderer, *physics, shape, stof(data[1]), stof(data[2]), stof(data[3]), stof(data[4]), stof(data[5]),
			stof(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9]), stoi(data[10]));
	}
}

void DataLoader::LoadFlatWorldObjects(){
	vector<vector<string>> allData = reader->ReadObjectInfo("sample_flat_objects.txt");
	for(auto data : allData){
		Shape shape;

		if(data[0] == "Plane"){
			shape = Shape::Plane;
		}
		else if(data[0] == "Box"){
			shape = Shape::Box;
		}

		new GameObject(*renderer, *physics, shape, stof(data[1]), stof(data[2]), stof(data[3]), stof(data[4]),
			stof(data[5]), stof(data[6]), stof(data[7]),
			stoi(data[8]), stoi(data[9]), stoi(data[10]), stoi(data[11]));
	}
}