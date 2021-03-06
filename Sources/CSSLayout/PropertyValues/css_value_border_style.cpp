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

#include "CSSLayout/precomp.h"
#include "API/CSSLayout/PropertyValues/css_value_border_style.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"

namespace clan
{

CSSValueBorderStyle::CSSValueBorderStyle()
: type(type_none)
{
}

CSSValueBorderStyle::CSSValueBorderStyle(ValueType value_type, const CSSValueBorderStyle &value)
: value_type(value_type), type(value.type)
{
}

std::string CSSValueBorderStyle::get_name() const
{
	switch (value_type)
	{
		case left_value: return "border-left-style";
		case top_value: return "border-top-style";
		case right_value: return "border-right-style";
		case bottom_value: return "border-bottom-style";
	}
	return "";
}
std::unique_ptr<CSSPropertyValue> CSSValueBorderStyle::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValueBorderStyle (*this));
}


void CSSValueBorderStyle::apply(CSSComputedValuesUpdater *updater)
{
	switch (value_type)
	{
		case left_value: updater->get_border().border_style_left = *this; break;
		case top_value: updater->get_border().border_style_top = *this; break;
		case right_value: updater->get_border().border_style_right = *this; break;
		case bottom_value: updater->get_border().border_style_bottom = *this; break;
	}
}

void CSSValueBorderStyle::compute(const CSSValueBorderStyle *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
			type = parent->type;
		else
			type = type_none;
	}
}

std::string CSSValueBorderStyle::to_string() const
{
	switch (type)
	{
	default:
	case type_none:
		return "none";
	case type_hidden:
		return "hidden";
	case type_dotted:
		return "dotted";
	case type_dashed:
		return "dashed";
	case type_solid:
		return "solid";
	case type_double:
		return "double";
	case type_groove:
		return "groove";
	case type_ridge:
		return "ridge";
	case type_inset:
		return "inset";
	case type_outset:
		return "outset";
	case type_inherit:
		return "inherit";
	}
}

}
