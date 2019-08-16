#include "wfobj.profile.hpp"

int main(){
	POR::Reader reader("tests/files/wfobj.test1.obj");
	std::cout << reader.read();
	return 1;
}