#include "POR.hpp"

using namespace POR;

Polygon::Polygon(std::string filename) : _filename(filename), _vertex_size(0){}

Polygon::~Polygon(){};

std::string Polygon::getFilename() const {
	return _filename;
}

float * Polygon::toArray(int *len) const {
	*len = _vertices.size() * _vertex_size;
	float * ret = new float[*len];
	float * pos = ret;
	for(std::vector<glm::vec4>::const_iterator b = _vertices.begin(); b != _vertices.end(); b++, pos+=_vertex_size){
		for(int q = 0; q < _vertex_size; q++)
			*(pos + q) = (*b)[q];
	}
	return ret;
}

void 					Polygon::addFace(Face *f){_faces.push_back(f);}
std::vector<Face *> 	Polygon::getFaces() const {return _faces;}


const int Polygon::getVertexSize() const{
	return _vertex_size;
}

void Polygon::addVertex(glm::vec4  vert){
	if(_vertex_size < 4) _vertex_size = 4;
	_vertices.push_back(vert);
}
void Polygon::addVertex(glm::vec3  vert){
	if(_vertex_size < 3) _vertex_size = 3;
	_vertices.push_back(glm::vec4(vert, 0));
}
void Polygon::addVertex(glm::vec2  vert){
	if(_vertex_size < 2) _vertex_size = 2;
	_vertices.push_back(glm::vec4(vert, 0, 0));
}
void Polygon::addVertex(glm::vec1  vert){
	if(_vertex_size < 1) _vertex_size = 1;
	_vertices.push_back(glm::vec4(vert, 0, 0, 0));
}

void 	Polygon::pushIndex(int x){ _vertex_order.push_back(x); }
const int *	Polygon::getVertexOrder(int *len) const{
	*len = _vertex_order.size();
	return _vertex_order.data();
}

Face::Face(){}
Face::Face(Face const & o){
	for(int x = 0; x < o._vertex_indices.size(); x++) _vertex_indices.push_back(o._vertex_indices[x]);
	for(int x = 0; x < o._texture_coordinate_indices.size(); x++) _texture_coordinate_indices.push_back(o._texture_coordinate_indices[x]);
	for(int x = 0; x < o._vertex_normal_indices.size(); x++) _vertex_normal_indices.push_back(o._vertex_normal_indices[x]);
	std::cout << "Copied" << std::endl;
}
Face::~Face(){}

void Face::addIndex(int v, IndexType t){
	switch(t){
		case vertex:	_vertex_indices.push_back(v); break;
		case tcoor:		_texture_coordinate_indices.push_back(v); break;
		case normal:	_vertex_normal_indices.push_back(v); break;
	}
}

int 	Face::getAvailableIndices() const{
	return 	(!_vertex_indices.empty()				? 	HAS_VERT_INDEX : 0x00)	|
			(!_texture_coordinate_indices.empty()	? 	HAS_TEXT_INDEX : 0x00)	|
			(!_vertex_normal_indices.empty()		? 	HAS_VERT_NORM_INDEX : 0x00)	;
}
const int 		*Face::getVertexIndices(int *len) const{
	*len = _vertex_indices.size();
	return _vertex_indices.data();
}
int 		*Face::getTextureIndices(int *len) const{
	*len = _texture_coordinate_indices.size();
	int *ret = new int[*len];
	for(int x = 0; x < *len; x++)	ret[x] = _texture_coordinate_indices[x];
	return ret;
}
int 		*Face::getVertexNormalIndices(int *len) const{
	*len = _vertex_normal_indices.size();
	int *ret = new int[*len];
	for(int x = 0; x < *len; x++)	ret[x] = _vertex_normal_indices[x];
	return ret;
}