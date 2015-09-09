/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_drawer_
#define _awrts_gui_drawer_
#include <awengine/gui/Visitor.h>

namespace awrts {
namespace gui {
//! Drawing visitor. Used for rendering GUI.
class Drawer : public Visitor {
public:
	virtual ~Drawer();

	virtual void visit(Element* element);
	virtual void visit(Canvas* element);
	virtual void visit(Window* element);
	virtual void visit(Widget* element);
};

} // namespace gui
} // namespace awrts
#endif //_awrts_gui_drawer_
