#pragma once

#include "glfw_imgui.h"

// Color /////////////////////////

class Color : public Object {
	REGISTER_CLASS(Color, Object) {
		BIND_STATIC_FUNC("Color", &Color::_Color,
			PARAMS("self", "r", "g", "b", "a"), DEFVALUES(nullptr, 0.f, 0.f, 0.f, 1.f));
	}

public:
	Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.0f);
	Color(const ImColor& imcolor);
	static void _Color(ptr<Object> _self, float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.0f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;
	void* get_data() override;

	ImColor _data;
};


// Vec4 //////////////////////////

class Vec4 : public Object {
	REGISTER_CLASS(Vec4, Object) {
		BIND_STATIC_FUNC("Vec", &Vec4::_Vec4,
			PARAMS("self", "x", "y", "z", "w"), DEFVALUES(nullptr, 0.f, 0.f, 0.f, 0.f));
	}

public:
	Vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);
	Vec4(const ImVec4& imvec);
	static void _Vec4(ptr<Object> _self, float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;
	void* get_data() override;

	operator ImVec4& ();
	ImVec4 _data;
};

// Vec4i //////////////////////////

class Vec4i : public Object {
	REGISTER_CLASS(Vec4i, Object) {
		BIND_STATIC_FUNC("Vec4i", &Vec4i::_Vec4i, PARAMS("self", "x", "y", "z", "w"), DEFVALUES(nullptr, 0, 0, 0, 0));
	}

public:
	Vec4i(int x = 0, int y = 0, int z = 0, int w = 0);
	Vec4i(int v[4]);
	static void _Vec4i(ptr<Object> _self, int x = 0, int y = 0, int z = 0, int w = 0);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;

	void* get_data() override;

	int _data[2];
};
