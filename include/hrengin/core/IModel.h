/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IModel_
#define _hrengin_IModel_

#include <vector>
#include <hrengin/core/hrenginmodels.h>


namespace hrengin {

class IModel
{
public:
	std::vector<SPrimitive> primitives;
};

}

#endif//_hrengin_IModel_
