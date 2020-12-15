#pragma once

#include "internal.h"
#include "gl_api.h"

class Glfw_ImGui {
public:

	// TODO: window title and dimension hardcoded.
	static int initialize();
	static void cleanup();

	static void new_frame();
	static void draw_frame();
	static void clear();

	static GLFWwindow* get_window();

private:
	static GLFWwindow* window;
};
