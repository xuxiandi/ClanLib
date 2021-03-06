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

#include "css_select_node.h"

namespace clan
{
/// \addtogroup clanCSSLayout_Document clanCSSLayout Document
/// \{

class CL_API_CSSLAYOUT DomSelectNode : public CSSSelectNode
{
public:
	DomSelectNode(const DomElement &element);
	bool parent();
	bool prev_sibling();
	void push();
	void pop();

	std::string name();
	std::string lang();
	std::string id();
	std::vector<std::string> element_classes();
	std::vector<std::string> pseudo_classes();
	std::string get_attribute_value(const std::string &name, bool &out_found);
	int child_index();

private:
	DomElement dom_element;
	DomElement pos;
	bool is_modified;
	std::vector<DomElement> saved_elements;
};

/// \}
}
