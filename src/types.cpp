
#include "types.h"

// Vec2 ///////////////////////////////////////////////////

Vec2::Vec2(float x, float y) :_data(x, y) { }

void Vec2::_Vec2(ptr<Object> _self, float x, float y) {
	Vec2* vec2 = ptrcast<Vec2>(_self).get();
	vec2->_data = ImVec2(x, y);
}

var Vec2::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash:
		case "w"_hash:
			return _data.x;
		case "y"_hash:
		case "h"_hash:
			return _data.y;
	}
	return Super::get_member(p_name);
}

void Vec2::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash:
		case "w"_hash:
			_data.x = value; return;
		case "y"_hash:
		case "h"_hash:
			_data.y = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec2::get_data() {
	return (void*)&_data;
}

Vec2::operator ImVec2& () {
	return _data;
}

// Color ///////////////////////////////////////////////////

Color::Color(float r, float g, float b, float a) : _data(r, g, b, a) {}

void Color::_Color(ptr<Object> _self, float r, float g, float b, float a) {
	Color* color = ptrcast<Color>(_self).get();
	color->_data = ImColor(r, g, b, a);
}

var Color::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "r"_hash: return _data.Value.x;
		case "g"_hash: return _data.Value.y;
		case "b"_hash: return _data.Value.z;
		case "a"_hash: return _data.Value.w;
	}
	return Super::get_member(p_name);
}

void Color::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "r"_hash: _data.Value.x = value; return;
		case "g"_hash: _data.Value.y = value; return;
		case "b"_hash: _data.Value.z = value; return;
		case "a"_hash: _data.Value.w = value; return;
	}
	Super::set_member(p_name, value);
}

void* Color::get_data() { return (float*)&_data.Value; }
