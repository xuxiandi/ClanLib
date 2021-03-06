/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#pragma once

#include "gui_css_display_visitor.h"

namespace clan
{

class GUILayoutNormalFlow : public GUICSSDisplayVisitor
{
public:
	void flex_horizontal_node(GUIComponent_Impl *node);
	void flex_vertical_node(GUIComponent_Impl *node);

private:
	void find_preferred_width(GUIComponent_Impl *node);
	void find_preferred_height(GUIComponent_Impl *node);
	CSSUsedValue align_vertical(GUIComponent_Impl *node, GUIComponent *child);
	CSSUsedValue align_horizontal(GUIComponent_Impl *node, GUIComponent *child);
	void set_horizontal_geometry(GUIComponent_Impl *node);
	void set_vertical_geometry(GUIComponent_Impl *node);
	void set_child_geometry(GUIComponent_Impl *node, GUIComponent *child, CSSUsedValue x, CSSUsedValue y);
};

}
