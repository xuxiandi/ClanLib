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
**    Mark Page
*/

#pragma once

enum PerlinDimension
{
	perlin_1d,
	perlin_2d,
	perlin_3d,
	perlin_4d
};

class Options : public GUIComponent
{
public:
	Options(GUIManager &gui, Rect gui_position);
	virtual ~Options();

	TextureFormat sized_format;
	float amplitude;
	int width;
	int height;
	int octaves;
	float start_x;
	float length_x;
	float start_y;
	float length_y;
	float position_z;
	float position_w;
	PerlinDimension dimension;
	bool is_normals_set;

private:
	void checkbox_normals_changed();
	void update_all_slider_text();
	void slider_amplitude_changed();
	void slider_width_changed();
	void slider_height_changed();
	void slider_octaves_changed();
	void slider_start_x_changed();
	void slider_length_x_changed();
	void slider_start_y_changed();
	void slider_length_y_changed();
	void slider_position_z_changed();
	void slider_position_w_changed();
	void checkbox_normal_changed();
	void set_value(Slider *slider, float value, float max_value);
	Label *create_slider_label(Slider *slider);
	void on_format_selected(int value, ComboBox *combo);
	void on_dimension_selected(int value, ComboBox *combo);
	void on_render(GraphicContext &gc, const Rect &update_rect);
	Slider *create_slider(int xpos, int ypos);
	float get_value(Slider *slider, float max_value);

	CheckBox *create_checkbox(int xpos, int ypos, const char *name, bool state);
	ComboBox *create_dimension_combo_box(int xpos, int ypos, PopupMenu &menu, int selected_item);
	void make_dimension_menu(PopupMenu &menu);
	ComboBox *create_format_combo_box(int xpos, int ypos, PopupMenu &menu, int selected_item);
	void make_format_menu(PopupMenu &menu);
	Label *create_combobox_label(ComboBox *combo, const char *text);
private:
	Slider *slider_width;
	Label *label_width;
	Slider *slider_height;
	Label *label_height;
	Slider *slider_start_x;
	Label *label_start_x;
	Slider *slider_start_y;
	Label *label_start_y;
	Slider *slider_length_x;
	Label *label_length_x;
	Slider *slider_length_y;
	Label *label_length_y;
	Slider *slider_position_z;
	Label *label_position_z;
	Slider *slider_position_w;
	Label *label_position_w;
	Slider *slider_octaves;
	Label *label_octaves;
	Slider *slider_amplitude;
	Label *label_amplitude;

	Label *label_format;
	ComboBox *combo_format;
	PopupMenu combo_format_menu;

	Label *label_dimension;
	ComboBox *combo_dimension;
	PopupMenu combo_dimension_menu;

	CheckBox *checkbox_normals;

};

