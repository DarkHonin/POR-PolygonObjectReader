#include "wfobj.profile.hpp"
#include <sstream>
#include <regex>
#include <algorithm> 
#include <cctype>
#include <cstring>
#include <locale>

using namespace POR;

glm::vec1 v1(float *e){ return glm::vec1(*e); }
glm::vec2 v2(float *e){ return glm::vec2(*e, *(e+1)); }
glm::vec3 v3(float *e){ return glm::vec3(*e, *(e+1), *(e+2)); }
glm::vec4 v4(float *e){ return glm::vec4(*e, *(e+1), *(e+2), *(e+3)); }


void addVec(char *str, Polygon & p){
	std::vector<float> store;
	float value;
	int rd = 0;
	std::stringstream ss(str);

	while(ss.rdbuf()->in_avail()) {
		ss >> value;
		store.push_back(value);		
	}
	float primVec[store.size()];
	for(int x = 0; x < store.size(); x++) primVec[x] = store[x];
	switch(store.size()){
		case 1:
			p.addVertex(v1(primVec));
			return;
		case 2:
			p.addVertex(v2(primVec));
			return;
		case 3:
			p.addVertex(v3(primVec));
			return;
		case 4:
			p.addVertex(v4(primVec));
			return;
		case 0:
		default: return;
	}
}

void readFace(char *str, Polygon &p){
	std::string _str(str);
	std::regex rex("(\\d)((\\/)?\\d?)((\\/)?\\d?)", std::regex::ECMAScript);
	std::sregex_iterator it(_str.begin(), _str.end(), rex);
	std::sregex_iterator et = std::sregex_iterator();
	Face *face = new Face();
	for(std::sregex_iterator q = it; q != et; ++q){
		std::string match = (*q).str();
		std::stringstream ss(match);
		double type = 0;
		char m;
		int v;
		while(ss.rdbuf()->in_avail()){
			if(ss.peek() != '/'){
				ss >> v;
				face->addIndex(v, (IndexType)type);
			}else{
				ss >> m;
				type++;
			}
		}
	}
	p.addFace(face);
}

void WFObjProfile::parseLine(std::string line, Polygon & p){
	char *str = (char *)line.c_str();
	char raw_flag[255];
	std::sscanf(str, "%s", raw_flag);
	str += strlen(raw_flag);
	std::string flag(raw_flag);
	if(flag == "v")					addVec(str, p);
	else if(flag == "f")			readFace(str+1, p);	
}