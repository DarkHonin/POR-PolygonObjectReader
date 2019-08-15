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


}

Reader::~Reader(){}