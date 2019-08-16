#ifndef _WFOBJ_H_
#define _WFOBJ_H_

#include "POR.hpp"

namespace POR{
	class WFObjProfile : public FileProfile{
		public:
			void parseLine(std::string line, Polygon & p);
	};
};

#endif