/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CEventManager_
#define _hrengin_CEventManager_

#include <vector>

#include <hrengin/common/time.h>
#include <hrengin/game/IEventManager.h>
#include <hrengin/game/IThinking.h>

namespace hrengin {
class CEventManager : public IEventManager {
private:
	std::vector<Event> events_;
public:
	virtual u32 addEvent(Event event)
	{
		events_.push_back(event);
		return events_.size()-1;
	};
	virtual void removeEvent(u32 eventId)
	{

	};
	virtual void advance()
	{
		u32 time = hrengin::getTime();
		for(std::vector<Event>::iterator event = events_.begin(); event != events_.end(); ++event) {
			if((*event).nextFire <= time) {
				(*event).owner->think(time);
				(*event).nextFire =  time + (*event).period;
			}
		}
	};
};

} // namespace hrengin

#endif//_hrengin_CEventManager_
