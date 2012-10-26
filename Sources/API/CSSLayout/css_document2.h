/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
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

#include "api_csslayout.h"

namespace clan
{

class CSSProperty2;
class CSSSelectNode2;
class CSSPropertyList2;
class CSSDocument2_Impl;

class CL_API_CSSLAYOUT CSSDocument2
{
public:
	CSSDocument2();
	~CSSDocument2();

	void add_sheet(const std::string &filename, const std::string &base_uri = std::string());
	void add_sheet(IODevice &iodevice, const std::string &base_uri = std::string());
	CSSPropertyList2 select(const DomElement &node, const std::string &pseudo_element = std::string());
	CSSPropertyList2 select(CSSSelectNode2 *node, const std::string &pseudo_element = std::string());
	static CSSPropertyList2 get_style_properties(const std::string &style_string, const std::string &base_uri = std::string());

private:
	std::shared_ptr<CSSDocument2_Impl> impl;
};

}
