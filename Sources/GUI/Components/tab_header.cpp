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
**    Harry Storbacka
*/

#include "GUI/precomp.h"
#include "API/GUI/gui_component.h"
#include "API/GUI/gui_message.h"
#include "API/GUI/gui_message_input.h"
#include "API/GUI/gui_message_pointer.h"
#include "API/GUI/gui_message_focus_change.h"
#include "API/GUI/gui_theme_part.h"
#include "API/GUI/gui_theme_part_property.h"
#include "API/GUI/gui_component_description.h"
#include "API/GUI/Components/tab_page.h"
#include "API/Display/Font/font.h"
#include "API/Display/Window/input_event.h"
#include "API/Display/Window/keys.h"
#include "API/Core/Text/string_help.h"
#include "../gui_css_strings.h"
#include "API/Display/2D/canvas.h"
#include "tab_header.h"

namespace clan
{

/////////////////////////////////////////////////////////////////////////////
// TabHeader_Impl Class:

class TabHeader_Impl
{
public:
	TabHeader_Impl() : first_tab_x_offset(0), selected_page(-1)
	{
		prop_first_tab_x_offset = GUIThemePartProperty(CssStr::first_tab_x_offset, "0");
	}

	void on_process_message(GUIMessage &msg);
	void on_render(Canvas &canvas, const Rect &update_rect);
	void on_style_changed();
	void unselect_all();
	void select_page(int index);

	struct Handle
	{
		TabPage *tab_page;
		std::string label;
		GUIThemePart part;
		Rect rect;
	};

	void update_handle_rects();

	GUIThemePart part_background;
	GUIThemePartProperty prop_first_tab_x_offset;
	GUIThemePart part_focus;
	std::vector<Handle> tabs;
	Callback_v1<TabPage*> func_page_selected;
	TabHeader *component;
	Colorf text_color;
	int first_tab_x_offset;
	int selected_page;
};

/////////////////////////////////////////////////////////////////////////////
// TabHeader Construction:

TabHeader::TabHeader(GUIComponent *parent)
: GUIComponent(parent), impl(new TabHeader_Impl)
{
	set_type_name(CssStr::Tab::Header::type_name);
	set_focus_policy(focus_local);
	impl->component = this;
	func_process_message().set(impl.get(), &TabHeader_Impl::on_process_message);
	func_render().set(impl.get(), &TabHeader_Impl::on_render);
	func_style_changed().set(impl.get(), &TabHeader_Impl::on_style_changed);
	// todo: enablemode, resize

	impl->on_style_changed();
}

TabHeader::~TabHeader()
{
}

/////////////////////////////////////////////////////////////////////////////
// TabHeader Attributes:

int TabHeader::get_preferred_height() const
{
	return impl->part_background.get_preferred_height();
}

Size TabHeader::get_preferred_size() const
{
	return impl->part_background.get_preferred_size();
}

/////////////////////////////////////////////////////////////////////////////
// TabHeader Operations:

void TabHeader::add_page(TabPage *tab_page, const std::string &label)
{
	TabHeader_Impl::Handle handle;
	handle.part = GUIThemePart(this, CssStr::Tab::Header::part_page);
	handle.tab_page = tab_page;
	handle.label = label;

	handle.part.set_state(CssStr::normal, true);
	handle.part.set_state(CssStr::hot, false);
	handle.part.set_state(CssStr::selected, false);
	impl->tabs.push_back(handle);

	impl->update_handle_rects();

	request_repaint();
}

void TabHeader_Impl::update_handle_rects()
{
	Canvas &canvas = component->get_canvas();

	int last_tab_end_x = first_tab_x_offset;

	std::vector<Handle>::size_type i;
	for (i = 0; i < tabs.size(); ++i)
	{
		int tab_width = tabs[i].part.get_preferred_width();

		// Apply padding-left, padding-right css values:
		Rect render_rect = tabs[i].part.get_render_box(tabs[i].part.get_text_size(canvas, tabs[i].label));

		if (render_rect.get_width() > tab_width)
		{
			tab_width = render_rect.get_width();
		}

		tabs[i].rect = Rect(
			last_tab_end_x, 0,
			last_tab_end_x + tab_width, tabs[i].part.get_preferred_height());

		last_tab_end_x += tab_width;
	}
}

void TabHeader::del_page(TabPage *tab_page)
{
	std::vector<TabHeader_Impl::Handle>::iterator it;
	for (it = impl->tabs.begin(); it != impl->tabs.end(); ++it)
	{
		if ((*it).tab_page == tab_page)
		{
			it = impl->tabs.erase(it);
			break;
		}
	}
	impl->update_handle_rects();
	request_repaint();
}

void TabHeader::page_renamed(TabPage *tab_page)
{
	std::vector<TabHeader_Impl::Handle>::iterator it;
	for (it = impl->tabs.begin(); it != impl->tabs.end(); ++it)
	{
		if ((*it).tab_page == tab_page)
		{
			(*it).label = tab_page->get_label();
			break;
		}
	}

	impl->update_handle_rects();
	request_repaint();
}

void TabHeader::select_page(int index)
{
	impl->select_page(index);
}

/////////////////////////////////////////////////////////////////////////////
// TabHeader Callbacks:

Callback_v1<TabPage*> &TabHeader::func_page_selected()
{
	return impl->func_page_selected;
}

/////////////////////////////////////////////////////////////////////////////
// TabHeader Implementation:

void TabHeader_Impl::on_process_message(GUIMessage &msg)
{
	if(component->is_enabled())
	{
		if (msg.is_type(GUIMessage_Input::get_type_name()))
		{
			GUIMessage_Input input_msg = msg;
			InputEvent e = input_msg.get_event();
			Point pos = e.mouse_pos;

			if (e.type == InputEvent::pressed && e.id == mouse_left)
			{
				std::vector<Handle>::iterator it;
				for (it = tabs.begin(); it != tabs.end(); ++it)
				{
					bool inside = (*it).rect.contains(pos);
					if (inside)
					{
						unselect_all();
						(*it).part.set_state(CssStr::selected, true);
						(*it).part.set_state(CssStr::normal, false);

						component->request_repaint();
						if (!func_page_selected.is_null())
							func_page_selected.invoke((*it).tab_page);
					}
				}
				msg.set_consumed();
			}
			else if (e.type == InputEvent::pointer_moved)
			{
				std::vector<Handle>::iterator it;
				for (it = tabs.begin(); it != tabs.end(); ++it)
				{
					bool inside = (*it).rect.contains(pos);
					if (inside)
					{
						if ((*it).part.get_state(CssStr::selected))
							return;
						(*it).part.set_state(CssStr::hot, true);
						(*it).part.set_state(CssStr::normal, false);
						component->request_repaint();
						msg.set_consumed();
					}
					else if ((*it).part.get_state(CssStr::hot))
					{
						(*it).part.set_state(CssStr::hot, false);
						(*it).part.set_state(CssStr::normal, true);						
						component->request_repaint();
						msg.set_consumed();
					}
				}
			}
			else if (e.type == InputEvent::pressed && e.id == keycode_left)
			{
				int next_page = selected_page - 1;
				if (next_page < 0)
					next_page = tabs.size()-1;

				unselect_all();
				select_page(next_page);

				if (!func_page_selected.is_null())
					func_page_selected.invoke(tabs[next_page].tab_page);

				component->select_page(next_page);
				msg.set_consumed();
			}
			else if (e.type == InputEvent::pressed && e.id == keycode_right)
			{
				int next_page = selected_page + 1;
				if (next_page >= tabs.size())
					next_page = 0;

				unselect_all();
				select_page(next_page);

				if (!func_page_selected.is_null())
					func_page_selected.invoke(tabs[next_page].tab_page);

				component->request_repaint();
				msg.set_consumed();
			}
			else if (e.type == InputEvent::pressed && (e.id == keycode_up || e.id == keycode_down))
			{
				// block focus switching with up/down when in tab header.
				msg.set_consumed();
			}
		}
		else if (msg.is_type(GUIMessage_Pointer::get_type_name()))
		{
			GUIMessage_Pointer pointer = msg;
			if (pointer.get_pointer_type() == GUIMessage_Pointer::pointer_leave)
			{
				std::vector<Handle>::iterator it;
				for (it = tabs.begin(); it != tabs.end(); ++it)
				{
					(*it).part.set_state(CssStr::hot, false);
					(*it).part.set_state(CssStr::normal, true);
				}
				component->request_repaint();
			}
		}
		else if (msg.is_type(GUIMessage_FocusChange::get_type_name()))
		{
			GUIMessage_FocusChange focus_msg = msg;
			if (focus_msg.get_focus_type() == GUIMessage_FocusChange::gained_focus)
			{
				part_background.set_state(CssStr::focused, true);
				component->request_repaint();
			}
			else 
			{
				part_background.set_state(CssStr::focused, false);
				component->request_repaint();
			}
			msg.set_consumed();
		}
	}
}

void TabHeader_Impl::on_render(Canvas &canvas, const Rect &update_rect)
{
	Rect rect = component->get_geometry();
	part_background.render_box(canvas, rect, update_rect);

	std::vector<Handle>::size_type i;
	for (i = 0; i < tabs.size(); i++)
	{
		Handle &handle = tabs[i];
		handle.part.render_box(canvas, handle.rect, update_rect);

		Rect rect_handle_content = handle.part.get_content_box(handle.rect);

		Size text_size = handle.part.get_text_size(canvas, handle.label);
		handle.part.render_text(canvas, handle.label, rect_handle_content, update_rect);

		if (component->has_focus() && i == selected_page)
		{
			Rect focus_rect = handle.rect;
			focus_rect.shrink(2,2,2,2);
			part_focus.render_box(canvas, focus_rect, update_rect);
		}
	}
}

void TabHeader_Impl::on_style_changed()
{
	part_background = GUIThemePart(component);
	part_focus = GUIThemePart(component, CssStr::Tab::Header::part_focus);

	first_tab_x_offset = part_background.get_property_int(prop_first_tab_x_offset);
}

void TabHeader_Impl::unselect_all()
{
	std::vector<Handle>::iterator it;
	for (it = tabs.begin(); it != tabs.end(); ++it)
	{
		(*it).part.set_state(CssStr::selected, false);
		(*it).part.set_state(CssStr::normal, true);
		(*it).part.set_state(CssStr::hot, false);
	}
}

void TabHeader_Impl::select_page(int index)
{
	selected_page = index;

	std::vector<Handle>::size_type i;
	for (i = 0; i < tabs.size(); ++i)
	{
		Handle &handle = tabs[i];
		handle.part.set_state(CssStr::normal, i != index);
		handle.part.set_state(CssStr::hot, false);
		handle.part.set_state(CssStr::selected, i == index);
	}
}

}
