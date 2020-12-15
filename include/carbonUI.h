#pragma once

#include "internal.h"
#include "gl_api.h"
#include "glfw_imgui.h"

#include "types.h"
#include "ui.h"

inline void register_cbimgui() {
	NativeClasses::singleton()->register_class<Vec2>();
	NativeClasses::singleton()->register_class<Color>();

	NativeClasses::singleton()->register_class<ui>();
}