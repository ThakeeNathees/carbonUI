#pragma once

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

class uiWindow : public Object {
	REGISTER_CLASS(uiWindow, Object) {
		BIND_STATIC_FUNC("uiWindow", &uiWindow::_uiWindow, PARAMS("self", "title", "size"), DEFVALUES(newptr<Vec2i>(1280, 720)));
		BIND_METHOD("initialize", &uiWindow::initialize);
		BIND_METHOD("cleanup", &uiWindow::cleanup);
		BIND_METHOD("new_frame", &uiWindow::new_frame);
		BIND_METHOD("draw_frame", &uiWindow::draw_frame);
		BIND_METHOD("swap_buffer", &uiWindow::swap_buffer);
		BIND_METHOD("should_close", &uiWindow::should_close);
		BIND_METHOD("poll_events", &uiWindow::poll_events);
		BIND_METHOD("clear", &uiWindow::clear, PARAMS("color"), DEFVALUES(newptr<Color>(0.f, 0.f, 0.f, 1.f)));
	}

	uiWindow(const String& title = "", ptr<Vec2i> size = newptr<Vec2i>(1280, 720));
	static void _uiWindow(ptr<uiWindow> self, const String& title, ptr<Vec2i> size);

	int initialize();
	void cleanup();

	void new_frame();
	void draw_frame();
	void swap_buffer();

	bool should_close();
	void poll_events();

	void clear(ptr<Color> col);

private:
	friend class ui;
	ptr<Vec2i> size;
	String title = "Carbon UI";
	GLFWwindow* _window = nullptr;

};