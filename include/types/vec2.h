#pragma once

#include "gl_api.h"
#include "carbon.h"
using namespace carbon;


// Vec2 //////////////////////////

class Vec2 : public Object {
	REGISTER_CLASS(Vec2, Object) {
		BIND_STATIC_FUNC("Vec2", &Vec2::_Vec2, PARAMS("self", "x", "y"), DEFVALUES(0.f, 0.f));
	}

public:
	Vec2(float x = 0.f, float y = 0.f);
	Vec2(const ImVec2& imvec);
	static void _Vec2(ptr<Object> _self, float x = 0.f, float y = 0.f);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;
	void* get_data() override;

	operator ImVec2& ();
	ImVec2 _data;
};

// Vec2i //////////////////////////

class Vec2i : public Object {
	REGISTER_CLASS(Vec2i, Object) {
		BIND_STATIC_FUNC("Vec2i", &Vec2i::_Vec2i, PARAMS("self", "x", "y"), DEFVALUES(0, 0));
	}

public:
	Vec2i(int x = 0, int y = 0);
	Vec2i(int v[2]);
	static void _Vec2i(ptr<Object> _self, int x = 0, int y = 0);

	var get_member(const String& p_name) override;
	void set_member(const String& p_name, var& value) override;

	void* get_data() override;

	int _data[2];
};
