#pragma once

#include "glfw_imgui.h"

// Vec3 //////////////////////////

class Vec3 : public Object {
	REGISTER_CLASS(Vec3, Object) {
		BIND_STATIC_FUNC("Vec3", &Vec3::_Vec3, PARAMS("self", "x", "y", "z"), DEFVALUES(nullptr, 0.f, 0.f, 0.f));
	}

public:
	Vec3(float x = 0.f, float y = 0.f, float z = 0.f);
	Vec3(float v[3]);
	static void _Vec3(ptr<Object> _self, float x = 0.f, float y = 0.f, float z = 0.f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;

	void* get_data() override;

	float _data[3];
};

// Vec3i ////////////////////////


class Vec3i : public Object {
	REGISTER_CLASS(Vec3i, Object) {
		BIND_STATIC_FUNC("Vec3i", &Vec3i::_Vec3i, PARAMS("self", "x", "y", "z"), DEFVALUES(nullptr, 0.f, 0.f, 0.f));
	}

public:
	Vec3i(int x = 0.f, int y = 0.f, int z = 0.f);
	Vec3i(int v[3]);
	static void _Vec3i(ptr<Object> _self, int x = 0.f, int y = 0.f, int z = 0.f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;

	void* get_data() override;

	int _data[3];
};

