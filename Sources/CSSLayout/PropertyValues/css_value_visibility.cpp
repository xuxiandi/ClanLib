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
#include "API/CSSLayout/PropertyValues/css_value_visibility.h"
#include "API/CSSLayout/ComputedValues/css_computed_values_updater.h"

namespace clan
{

CSSValueVisibility::CSSValueVisibility()
: type(type_inherit)
{
}

std::string CSSValueVisibility::get_name() const
{
	return "visibility";
}
std::unique_ptr<CSSPropertyValue> CSSValueVisibility::clone() const
{
	return std::unique_ptr<CSSPropertyValue>(new CSSValueVisibility (*this));
}


void CSSValueVisibility::apply(CSSComputedValuesUpdater *updater)
{
	updater->get_misc_inherit().visibility = *this;
}

void CSSValueVisibility::compute(const CSSValueVisibility *parent, CSSResourceCache *layout, float em_size, float ex_size)
{
	if (type == type_inherit)
	{
		if (parent)
			type = parent->type;
		else
			type = type_visible;
	}
}

std::string CSSValueVisibility::to_string() const
{
	switch (type)
	{
	default:
	case type_visible:
		return "visible";
	case type_hidden:
		return "hidden";
	case type_collapse:
		return "collapse";
	case type_inherit:
		return "inherit";
	}
}

}
