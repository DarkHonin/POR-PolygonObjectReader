#ifndef _WFOBJ_H_
#define _WFOBJ_H_

#include "POR.hpp"

namespace POR{
	class WFObjProfile : public FileProfile{
		public:
			int parseLine(std::string line);
	};
};

#endif