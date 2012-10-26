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

#include "test.h"

// This is the Program class that is called by Application
class Program
{
public:
	static int main(const std::vector<std::string> &args)
	{
		SetupCore setup_core;
		SetupDisplay setup_display;
		SetupGL setup_gl;

		// Start the Application
		TestApp app;
		int retval = app.main(args);
		return retval;
	}
};

// Instantiate Application, informing it where the Program is located
Application app(&Program::main);

int TestApp::main(const std::vector<std::string> &args)
{
	// Create a console window for text-output if not available
	ConsoleWindow console("Console");

	try
	{
		DisplayWindowDescription desc;
		desc.set_size(Size(800,600), true);
		desc.set_title("Image clipboard test");
		DisplayWindow window(desc);
		
		PixelBuffer to_clipboard = ImageProviderFactory::load("copy.png");
		window.set_clipboard_image(to_clipboard);

/*		while (!window.get_ic().get_keyboard().get_keycode(KEY_ESCAPE))
		{
			window.get_gc().clear(Colorf::gray70);
			window.flip();
			KeepAlive::process();
			System::sleep(50);
		}*/

/*		// Save to file
		PNGProvider::save(to_clipboard, "copy2.png");

		// Save to IODevice_Memory memory buffer
		DataBuffer data(1024*8); // 8 kb
		IODevice_Memory mem(data);
		PNGProvider::save(to_clipboard, mem);
		File file("copy3.png", File::create_always);
		DataBuffer mem_data = mem.get_data();
		file.write(mem_data.get_data(), mem_data.get_size());
*/	

	
 		PixelBuffer from_clipboard;
		if (window.is_clipboard_image_available())
		{
			from_clipboard = window.get_clipboard_image();
			PNGProvider::save(from_clipboard, "from_clipboard.png");
		} 

		if (!from_clipboard.is_null())
		{
			Texture tex(window.get_gc(), from_clipboard.get_size());
			tex.set_image(from_clipboard);
			tex.set_min_filter(cl_filter_nearest);
			tex.set_mag_filter(cl_filter_nearest);

			while (!window.get_ic().get_keyboard().get_keycode(KEY_ESCAPE))
			{
				window.get_gc().clear(Colorf::gray30);

				if (!from_clipboard.is_null())
				{
					Draw::texture(window.get_gc(), Rect(0,0,tex.get_width(), tex.get_height()));
				}

				window.flip();
				KeepAlive::process();
				System::sleep(50);
			}
		}
	}
	catch(Exception error)
	{
		Console::write_line("Exception caught:");
		Console::write_line(error.message);

		console.display_close_message();
		return -1;
	}

	return 0;
}




