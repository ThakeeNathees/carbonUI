#pragma once

#include "internal.h"
#include "gl_api.h"
#include "glfw_imgui.h"

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"
#include "ui.h"

#include "../gen/ui.gen.h"

inline void register_cbimgui() {
	NativeClasses::singleton()->register_class<Vec2>();
	NativeClasses::singleton()->register_class<Vec2i>();
	NativeClasses::singleton()->register_class<Vec3>();
	NativeClasses::singleton()->register_class<Vec3i>();
	NativeClasses::singleton()->register_class<Vec4>();
	NativeClasses::singleton()->register_class<Vec4i>();
	NativeClasses::singleton()->register_class<Color>();

	NativeClasses::singleton()->register_class<ui>();
	NativeClasses::singleton()->register_class<ui2>();
}