
#include <Irrlicht/Irrlicht.h>

#include "CVideoManager.h"

#include "CInputManager.h"


namespace hrengin {
namespace gui {

HRENGINGRAPHICS_API IInputManager& getInputManager()
{
	static CInputManager singleton;
	return singleton;
}

CInputManager::CInputManager()
{
	graphics::getLocalManager().GetDevice()->setEventReceiver(this);
}

bool CInputManager::OnEvent(const irr::SEvent& event)
{
	for(std::vector<IControllable*>::iterator it = mReceivers.begin(); it != mReceivers.end(); ++it) {
		if((*it)->IsEnabled()) {
			(*it)->ReceiveInput(event);
		}
	}

	return false;
}


irr::gui::ICursorControl* CInputManager::GetCursorControl()
{
	return CursorControl;
}

bool CInputManager::RegisterReceiver(IControllable& receiver)
{
	mReceivers.push_back(&receiver);
	return true;
}

bool CInputManager::UnregisterReceiver(IControllable& receiver)
{
	//remove from mReceivers
	return true;
}

} // namespace io
} // namespace hrengin