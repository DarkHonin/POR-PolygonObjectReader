#ifndef _POR_H_
#define _POR_H_

#include "POR.cfg.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <glm/glm.hpp>

#define ATTRIBUTE_VERTEX	0x0001
#define ATTRIBUTE_FACE 		0x0002

namespace POR{
	class FileProfile{
		public:
			virtual int parseLine(std::string line) = 0;
	};

	class Reader{
		public:
			Reader(std::string filePath);
			~Reader();

		private:
			FileProfile			*_profile;
			const std::string 	_filePath;
			FILE 				*_file;

	};
};


#endif