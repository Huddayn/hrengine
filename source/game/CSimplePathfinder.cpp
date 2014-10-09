/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include "CSimplePathfinder.h"

namespace hrengin {
namespace ai {

HR_GAME_API IBasePathfinder* createSimplePathfinder()
{
	return new CSimplePathfinder;
}

} // namespace ai
} // namespace hrengin
