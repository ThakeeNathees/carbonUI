#pragma once

#include <stdio.h>
#include <iostream>

#include "carbon.h"
using namespace carbon;

#include "gl_api.h"
#include "TextEditor.h"

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

#include "cls_bind.h"

//#define UI_METHODS_EXTRA

//#define UI_REGISTER_EXTRA                                      \
//	BIND_STATIC_FUNC("initialize", &ui::initialize);           \
//	BIND_STATIC_FUNC("cleanup", &ui::cleanup);		           \
//	BIND_STATIC_FUNC("new_frame", &ui::new_frame);	           \
//	BIND_STATIC_FUNC("draw_frame", &ui::draw_frame);           \
//	BIND_STATIC_FUNC("clear", &ui::clear, PARAMS("color"));    \

#include "ui.gen.h"

inline void register_ui() {
	NativeClasses::singleton()->register_class<Vec2>();
	NativeClasses::singleton()->register_class<Vec2i>();
	NativeClasses::singleton()->register_class<Vec3>();
	NativeClasses::singleton()->register_class<Vec3i>();
	NativeClasses::singleton()->register_class<Vec4>();
	NativeClasses::singleton()->register_class<Vec4i>();
	NativeClasses::singleton()->register_class<Color>();

	NativeClasses::singleton()->register_class<ui>();
	NativeClasses::singleton()->register_class<uiWindow>();
}