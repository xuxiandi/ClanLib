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
#include "API/CSSLayout/PropertyValues/css_value_padding_width.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"
#include "../css_resource_cache.h"

namespace clan
{

CSSValuePaddingWidth::CSSValuePaddingWidth()
: value_type(left_value), type(type_length), length(0, CSSLength::type_px), percentage(0.0f)
{
}

CSSValuePaddingWidth::CSSValuePaddingWidth(ValueType value_type, const CSSValuePaddingWidth &value)
: value_type(value_type), type(value.type), length(value.length), percentage(value.percentage)
{
}

std::string CSSValuePaddingWidth::get_name() const
{
	switch (value_type)
	{
		case left_value: return "padding-left";
		case top_value: return "padding-top";
		case right_value: return "padding-right";
		case bottom_value: return "padding-bottom";
	}
	return "";
}
std::unique_ptr<CSSPropertyValue> CSSValuePaddingWidth::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValuePaddingWidth (*this));
}


void CSSValuePaddingWidth::apply(CSSComputedValuesUpdater *updater)
{
	switch (value_type)
	{
		case left_value: updater->get_padding().padding_width_left = *this; break;
		case top_value: updater->get_padding().padding_width_top = *this; break;
		case right_value: updater->get_padding().padding_width_right = *this; break;
		case bottom_value: updater->get_padding().padding_width_bottom = *this; break;
	}

}

void CSSValuePaddingWidth::compute(const CSSValuePaddingWidth *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
		{
			type = parent->type;
			length = parent->length;
			percentage = parent->percentage;
		}
		else
		{
			type = type_length;
			length = CSSLength(0.0f, CSSLength::type_px);
		}
	}

	if (type == type_length)
		length = layout->compute_length(length, em_size, ex_size);
}

std::string CSSValuePaddingWidth::to_string() const
{
	switch (type)
	{
	default:
	case type_length:
		return length.to_string();
	case type_percentage:
		return StringHelp::float_to_text(percentage) + "%";
	case type_inherit:
		return "inherit";
	}
}

}
