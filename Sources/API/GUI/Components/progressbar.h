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
**    Kenneth Gangstoe
**    Harry Storbacka
*/


#pragma once

#include "../api_gui.h"
#include "../gui_component.h"

namespace clan
{
/// \addtogroup clanGUI_Components clanGUI Components
/// \{

class ProgressBar_Impl;

/// \brief Progress bar component.
class CL_API_GUI ProgressBar : public GUIComponent
{
/// \name Construction
/// \{

public:

	/// \brief Constructs a ProgressBar
	///
	/// \param parent = GUIComponent
	ProgressBar(GUIComponent *parent);

	virtual ~ProgressBar();

/// \}
/// \name Attributes
/// \{

public:
	using GUIComponent::get_named_item;

	/// \brief Find the child ProgressBar with the specified component ID name.
	///
	/// If it was not found, an exception is thrown.
	static ProgressBar *get_named_item(GUIComponent *reference_component, const std::string &id);

	/// \brief Get Min
	///
	/// \return min
	int get_min() const;

	/// \brief Get Max
	///
	/// \return max
	int get_max() const;

	/// \brief Get Step size
	///
	/// \return step_size
	int get_step_size() const;

	/// \brief Get Position
	///
	/// \return position
	int get_position() const;

	/// \brief Is Marquee mode
	///
	/// \return true = marquee_mode
	bool is_marquee_mode() const;

	/// \brief Get Marquee animation speed
	///
	/// \return marquee_animation_speed
	int get_marquee_animation_speed() const;

	/// \brief Get Marquee box width
	///
	/// \return marquee_box_width
	int get_marquee_box_width() const;

	/// \brief Get Marquee step size
	///
	/// \return marquee_step_size
	int get_marquee_step_size() const;

/// \}
/// \name Operations
/// \{

public:

	/// \brief Set min
	///
	/// \param progress_min = value
	void set_min(int progress_min);

	/// \brief Set max
	///
	/// \param progress_max = value
	void set_max(int progress_max);

	/// \brief Set range
	///
	/// \param progress_min = value
	/// \param progress_max = value
	void set_range(int progress_min, int progress_max);

	/// \brief Set step size
	///
	/// \param size = value
	void set_step_size(int size);

	/// \brief Set position
	///
	/// \param pos = value
	void set_position(int pos);

	/// \brief Advance position
	///
	/// \param pos = value
	void advance_position(int pos);

	/// \brief Step position
	void step_position();

	/// \brief Set marquee mode
	///
	/// \param enable = bool
	void set_marquee_mode(bool enable);

	/// \brief Set marquee animation speed
	///
	/// \param milliseconds = value
	void set_marquee_animation_speed(int milliseconds);

	/// \brief Set marquee box width
	///
	/// \param width = value
	void set_marquee_box_width(int width);
	
	/// \brief Set marquee step size
	///
	/// \param size = value
	void set_marquee_step_size(int size);

/// \}
/// \name Implementation
/// \{

private:
	std::shared_ptr<ProgressBar_Impl> impl;
/// \}
};

}

/// \}
