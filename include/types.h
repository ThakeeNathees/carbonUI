#pragma once

#include "glfw_imgui.h"

class Vec2 : public Object {
	REGISTER_CLASS(Vec2, Object) {
		BIND_STATIC_FUNC("Vec", &Vec2::_Vec2,
			PARAMS("self", "x", "y"), DEFVALUES(nullptr, 0.f, 0.f));
	}

public:
	Vec2(float x = 0.f, float y = 0.f);
	static void _Vec2(ptr<Object> _self, float x = 0.f, float y = 0.f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;
	void* get_data() override;

	operator ImVec2& ();

	ImVec2 _data;
};


class Color : public Object {
	REGISTER_CLASS(Color, Object) {
		BIND_STATIC_FUNC("Color", &Color::_Color,
			PARAMS("self", "r", "g", "b", "a"), DEFVALUES(nullptr, 0.f, 0.f, 0.f, 1.f));
	}

public:
	Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.0f);
	static void _Color(ptr<Object> _self, float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.0f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;
	void* get_data() override;

	ImColor _data;
};




