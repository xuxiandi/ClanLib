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
**    Kenneth Gangstoe
*/

#include "GUI/precomp.h"
#include "API/GUI/Components/savefiledialog.h"
#include "filedialog_impl.h"

namespace clan
{

/////////////////////////////////////////////////////////////////////////////
// SaveFileDialog Construction:

SaveFileDialog::SaveFileDialog(GUIComponent *owner)
: impl(new FileDialog_Impl)
{
	impl->owner = owner;
}

SaveFileDialog::~SaveFileDialog()
{
}

/////////////////////////////////////////////////////////////////////////////
// SaveFileDialog Attributes:

std::string SaveFileDialog::get_filename() const
{
	return impl->get_filename();
}

/////////////////////////////////////////////////////////////////////////////
// SaveFileDialog Operations:

void SaveFileDialog::set_filename(const std::string &filename)
{
	impl->set_filename(filename);
}

void SaveFileDialog::add_filter(const std::string &filter_description, const std::string &filter_extension, bool is_default)
{
	impl->add_filter(filter_description, filter_extension, is_default);
}

void SaveFileDialog::clear_filters()
{
	impl->clear_filters();
}

void SaveFileDialog::set_filter_index(int filter_index)
{
	impl->set_filter_index(filter_index);
}

void SaveFileDialog::set_initial_directory(const std::string &path)
{
	impl->initial_directory = path;
}

void SaveFileDialog::set_title(const std::string &title)
{
	impl->title = title;
}

bool SaveFileDialog::show()
{
	return impl->show(true);
}

}
