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
#include "API/CSSLayout/PropertyValues/css_value_z_index.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"

namespace clan
{

CSSValueZIndex::CSSValueZIndex()
: type(type_auto), value(0)
{
}

std::string CSSValueZIndex::get_name() const
{
	return "z-index";
}
std::unique_ptr<CSSPropertyValue> CSSValueZIndex::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValueZIndex (*this));
}


void CSSValueZIndex::apply(CSSComputedValuesUpdater *updater)
{
	updater->get_misc_reset().z_index = *this;
}

void CSSValueZIndex::compute(const CSSValueZIndex *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
		{
			type = parent->type;
			value = parent->value;
		}
		else
		{
			type = type_auto;
		}
	}
}

std::string CSSValueZIndex::to_string() const
{
	switch (type)
	{
	default:
	case type_auto:
		return "auto";
	case type_integer:
		return StringHelp::int_to_text(value);
	case type_inherit:
		return "inherit";
	}
}

}
