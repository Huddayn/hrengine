/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Irrlicht/IGUIElement.h>

#include <hrengin/common/nowide.h>

#include "CGUITextBox.h"

namespace hrengin {
namespace gui {

CGUITextBox::CGUITextBox(irr::gui::IGUIElement* elem)
	: irrElement_(elem)
{
	elem->grab();
}

CGUITextBox::~CGUITextBox()
{
	irrElement_->drop();
}

u32 CGUITextBox::getId() const
{
	return irrElement_->getID();
}

u32 CGUITextBox::getParentId() const
{
	return irrElement_->getParent()->getID();
}

std::string CGUITextBox::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}

void CGUITextBox::setText(std::string text)
{
	irrElement_->setText(locale::widen(text).c_str());
}

} // namespace gui
} // namespace hrengin
