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

#include "../CSSDocument/css_property_value.h"

namespace clan
{
/// \addtogroup clanCSSLayout_PropertyValues clanCSSLayout Property Values
/// \{

class CSSValueContent : public CSSPropertyValue
{
public:
	CSSValueContent();
	void compute(const CSSValueContent *parent, CSSResourceCache *layout, float em_size, float ex_size, bool before_or_after_pseudo_element);
	std::string to_string() const;
	void apply(CSSComputedValuesUpdater *updater);
	std::string get_name() const;
	std::unique_ptr<CSSPropertyValue> clone() const;

	enum Type
	{
		type_normal,
		type_none,
		type_string,
		type_uri,
		type_counter,
		type_attr,
		type_open_quote,
		type_close_quote,
		type_no_open_quote,
		type_no_close_quote,
		type_inherit
	};
	Type type;
	std::string str;
};

/// \}
}
