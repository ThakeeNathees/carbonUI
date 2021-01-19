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

#define UI_REGISTER_EXTRA 																				      \
	BIND_STATIC_FUNC("DockSpace", &imgui_dockspace, PARAMS("flags"), DEFVALUES(ImGuiDockNodeFlags_None));     \
	BIND_STATIC_FUNC("Window", &ui::newWindow, PARAMS("title", "size"), DEFVALUES(newptr<Vec2i>(1280, 720))); \
	BIND_STATIC_FUNC("TextEditor", &ui::newTextEditor);														  \
	/* */																								      \
	BIND_STATIC_FUNC("InputText", &ui::InputText, PARAMS("label", "buffer", "flags", DEFVALUES(0)));		  \

#define UI_METHODS_EXTRA                                                                                      \
	static ptr<uiWindow> newWindow(const String& title, ptr<Vec2i> size = newptr<Vec2i>(1280, 720)) {	      \
		return newptr<uiWindow>(title, size);                                                                 \
	}																									      \
	static ptr<uiTextEditor> newTextEditor() {															      \
		return newptr<uiTextEditor>();                                                       			      \
	}																									      \
	/* */																								      \
	static bool InputText(const String& label, String& buff, ImGuiInputTextFlags flags = 0) {				  \
		if (buff.size() == 0) {																				  \
			buff = (var(String(" "))*1024).operator String&();												  \
			buff[0] = '\0';																					  \
		}																									  \
		return ImGui::InputText(label.c_str(), (char*)buff.get_data(), buff.size(), flags);					  \
	}																									      \


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
	NativeClasses::singleton()->register_class<uiTextEditor>();

}