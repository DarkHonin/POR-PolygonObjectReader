#ifndef _POR_H_
#define _POR_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/glm.hpp>
#include <vector>


#define POR_VERSION_MAJOR 1
#define POR_VERSION_MINOR 0

namespace POR{
	#define HAS_VERT_INDEX 		0x01
	#define HAS_TEXT_INDEX 		0x02
	#define HAS_VERT_NORM_INDEX 0x04

	enum IndexType{
		vertex, tcoor, normal
	};

	class Face{
		public:
			Face();
			Face(Face const &o);
			~Face();

			int 		getAvailableIndices() const;
			const int	*getVertexIndices(int *len) const;
			int 		*getTextureIndices(int *len) const;
			int 		*getVertexNormalIndices(int *len) const;
			void 		addIndex(int v, IndexType t);
		private:
			std::vector<int>		_vertex_indices;
			std::vector<int>		_texture_coordinate_indices;
			std::vector<int>		_vertex_normal_indices;
	};

	class Polygon{
		public:
			Polygon(std::string filename);
			~Polygon();

			std::string 			getFilename() const;
			void 					addVertex(glm::vec4  vert);
			void 					addVertex(glm::vec3  vert);
			void 					addVertex(glm::vec2  vert);
			void 					addVertex(glm::vec1  vert);
			void					pushIndex(int x);
			void 					addFace(Face *f);

			std::vector<Face *>		getFaces() const;
			const int				getVertexSize() const;
			float 					*toArray(int *len) const;
			const	int				*getVertexOrder(int *len) const;
			

		private:
			int 					_vertex_size;
			std::string 			_filename;
			std::vector<glm::vec4> 	_vertices;
			std::vector<Face *>		_faces;
			std::vector<int>		_vertex_order;
			
	};
	class FileProfile{
		public:
			virtual void parseLine(std::string line, Polygon & p) = 0;
	};

	class Reader{
		public:
			Reader(std::string filePath);
			~Reader();

			Polygon * read();

		private:
			FileProfile			*_profile;
			const std::string 	_filePath;
			FILE 				*_file;

	};
};

std::ostream & operator<<(std::ostream & stream, POR::Polygon const &a);
std::ostream & operator<<(std::ostream & stream, POR::Polygon const *a);
std::ostream & operator<<(std::ostream & stream, POR::Face const &a);
std::ostream & operator<<(std::ostream & stream, POR::Face const *a);


#endif