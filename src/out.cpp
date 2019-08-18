#include "POR.hpp"

std::ostream & operator<<(std::ostream & stream, POR::Face const &a){
	int len = 0;
	int depth = a.getAvailableIndices();
	std::cout << "\tIndex depth: ";
	if(depth & HAS_VERT_INDEX) std::cout 		<< " VERTEX_INDEX ";
	if(depth & HAS_TEXT_INDEX) std::cout 		<< " TEXTURE_INDEX ";
	if(depth & HAS_VERT_NORM_INDEX) std::cout 	<< " NORMAL_INDEX ";
	std::cout << std::endl;

	if(depth & HAS_VERT_INDEX){
		const int * vin = a.getVertexIndices(&len);
		std::cout << "\t\t" << len << " : VERTEX_INDEX: ";
		for(int i = 0; i < len; i++)
			std::cout << vin[i] << (i != len - 1? " ": "");
		std::cout << std::endl;
	}
	if(depth & HAS_TEXT_INDEX){
		int * tin = a.getTextureIndices(&len);
		std::cout << "\t\t" << len << " : TEXTURE_INDEX: ";
		for(int i = 0; i < len; i++)
			std::cout << tin[i] << (i != len - 1? " ": "");
		std::cout << std::endl;
	}
	if(depth & HAS_VERT_NORM_INDEX){
		int * nin = a.getVertexNormalIndices(&len);
		std::cout << "\t\t" << len << " : VERTEX_NORMAL_INDEX: ";
		for(int i = 0; i < len; i++)
			std::cout << nin[i] << (i != len - 1? " ": "");
		std::cout << std::endl;
	}
	return stream;
}

std::ostream & operator<<(std::ostream & stream, POR::Polygon const &a){
	stream << "Polygon: " << a.getFilename() << std::endl;
	stream << "Verteces: \n";
	int len;
	float *items = a.toArray(&len);
	std::string fstring = (a.getVertexSize() == 1?"%d" : (a.getVertexSize() == 2? "%d, %d" : (a.getVertexSize() == 3? "%d, %d, %d" : "%d, %d, %d, %d")));
	for(int i = 0; i < len; i+=a.getVertexSize()){
		stream << "\t" << (int)(i / a.getVertexSize()) << " : [";
		for(int x = 0; x < a.getVertexSize(); x++){
			if(x != 0) stream << ", ";
			stream << std::to_string(items[i + x]);
		}
		stream << "]\n";
	}
	std::vector<POR::Face*> faces = a.getFaces();
	if(!faces.empty()){
	std::cout << "Faces: " << faces.size() << std::endl;
	for(int x = 0; x < faces.size(); x++)
		stream << faces[x];
	}
	const int* pgInd = a.getVertexOrder(&len);
	if(len){
		std::cout << len << " : Polygon indecies: ";
		for(int x = 0; x < len; x++)
			std::cout << pgInd[x] << " ";
		std::cout << std::endl;
	}
	return stream;
}

std::ostream & operator<<(std::ostream & stream, POR::Polygon const *a){
	stream << *a;
	return stream;
}

std::ostream & operator<<(std::ostream & stream, POR::Face const *a){
	stream << *a;
	return stream;
}