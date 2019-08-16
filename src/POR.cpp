#include "POR.hpp"
#include "wfobj.profile.hpp"
using namespace POR;

Reader::Reader(std::string path) : _filePath(path){
	std::string ext = std::string(std::strrchr(path.c_str(), '.'));
	if(ext.empty()){
		std::cerr << "Invalid file extention" << std::endl;
		return;
	}
	if(ext == ".obj")
		_profile = new WFObjProfile();
	else{
		std::cerr << "Invalid file extention" << std::endl;
		return;
	}
	std::cout << "File found" << std::endl;
}

Reader::~Reader(){}


Polygon * Reader::read(){
	std::cout << "Reading..." << std::endl;
	std::string filename = std::strrchr(_filePath.c_str(), '/')+1;
	Polygon * ret = new Polygon(filename);
	std::fstream file(_filePath);
	char line[255];
	if(!file.is_open()){
		std::cerr << "Could not open file: " << _filePath << std::endl;
	}
	while(file.getline(line, 255)){
		_profile->parseLine(line, *ret);
	}
	std::cout << "Read: " << ret << std::endl;
	return ret;
}