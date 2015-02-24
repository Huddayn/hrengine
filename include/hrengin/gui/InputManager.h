/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_InputManager_
#define _hrengin_InputManager_

#include <hrengin/common/types.h>

#include <hrengin/gui/gui.h>
#include <hrengin/gui/InputEvent.h>

namespace hrengin {
class UserInputReceiver;
namespace gui {

//! Handles user input and generates input events
class InputManager {
public:
	virtual bool registerReceiver(UserInputReceiver* receiver) = 0;
	virtual bool unregisterReceiver(UserInputReceiver* receiver) = 0;

	#if 0
	virtual void seizeControl(bool seizeCusror, bool seizeKeyboard) = 0;
	#endif
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_InputManager_