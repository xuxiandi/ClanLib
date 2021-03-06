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
#include "API/CSSLayout/PropertyValues/css_value_border_image_slice.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"

namespace clan
{

CSSValueBorderImageSlice::CSSValueBorderImageSlice()
: type(type_values),
  value_top(value_type_percentage), value_right(value_type_percentage), value_bottom(value_type_percentage), value_left(value_type_percentage),
  number_top(0.0f), number_right(0.0f), number_bottom(0.0f), number_left(0.0f),
  percentage_top(100.0f), percentage_right(100.0f), percentage_bottom(100.0f), percentage_left(100.0f),
  fill_center(false)
{
}

std::string CSSValueBorderImageSlice::get_name() const
{
	return "border-image-slice";
}
std::unique_ptr<CSSPropertyValue> CSSValueBorderImageSlice::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValueBorderImageSlice (*this));
}


void CSSValueBorderImageSlice::apply(CSSComputedValuesUpdater *updater)
{
	updater->get_border().border_image_slice = *this;
}

void CSSValueBorderImageSlice::compute(const CSSValueBorderImageSlice *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
		{
			type = parent->type;
			value_top = parent->value_top;
			value_right = parent->value_right;
			value_bottom = parent->value_bottom;
			value_left = parent->value_left;
			number_top = parent->number_top;
			number_right = parent->number_right;
			number_bottom = parent->number_bottom;
			number_left = parent->number_left;
			percentage_top = parent->percentage_top;
			percentage_right = parent->percentage_right;
			percentage_bottom = parent->percentage_bottom;
			percentage_left = parent->percentage_left;
			fill_center = parent->fill_center;
		}
		else
		{
			type = type_values;
			value_top = value_type_percentage;
			value_right = value_type_percentage;
			value_bottom = value_type_percentage;
			value_left = value_type_percentage;
			number_top = 0.0f;
			number_right = 0.0f;
			number_bottom = 0.0f;
			number_left = 0.0f;
			percentage_top = 100.0f;
			percentage_right = 100.0f;
			percentage_bottom = 100.0f;
			percentage_left = 100.0f;
			fill_center = false;
		}
	}
}

std::string CSSValueBorderImageSlice::to_string() const
{
	if (type == type_inherit)
		return "inherit";

	std::string s;

	switch (value_top)
	{
	default:
	case value_type_percentage:
		s += StringHelp::float_to_text(percentage_top) + "%";
		break;
	case value_type_number:
		s += StringHelp::float_to_text(number_top);
		break;
	}

	s += " ";

	switch (value_right)
	{
	default:
	case value_type_percentage:
		s += StringHelp::float_to_text(percentage_right) + "%";
		break;
	case value_type_number:
		s += StringHelp::float_to_text(number_right);
		break;
	}

	s += " ";

	switch (value_bottom)
	{
	default:
	case value_type_percentage:
		s += StringHelp::float_to_text(percentage_bottom) + "%";
		break;
	case value_type_number:
		s += StringHelp::float_to_text(number_bottom);
		break;
	}

	s += " ";

	switch (value_left)
	{
	default:
	case value_type_percentage:
		s += StringHelp::float_to_text(percentage_left) + "%";
		break;
	case value_type_number:
		s += StringHelp::float_to_text(number_left);
		break;
	}

	return s;
}

}
