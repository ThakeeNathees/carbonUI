
#include "types/vec2.h"

// Vec2 ///////////////////////////////////////////////////

Vec2::Vec2(float x, float y) :_data(x, y) { }
Vec2::Vec2(const ImVec2& imvec) : _data(imvec) {}

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

// Vec2i ///////////////////////////////////////////////////

Vec2i::Vec2i(int x, int y) { _data[0] = x, _data[1] = y; }
Vec2i::Vec2i(int v[2]) { _data[0] = v[0], _data[1] = v[1]; }

void Vec2i::_Vec2i(ptr<Object> _self, int x, int y) {
	Vec2i* vec2 = ptrcast<Vec2i>(_self).get();
	vec2->_data[0] = x;
	vec2->_data[1] = y;
}

var Vec2i::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash:
		case "w"_hash: return _data[0];
		case "y"_hash:
		case "h"_hash: return _data[1];
	}
	return Super::get_member(p_name);
}

void Vec2i::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash:
		case "w"_hash:
			_data[0] = value; return;
		case "y"_hash:
		case "h"_hash:
			_data[1] = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec2i::get_data() {
	return (void*)_data;
}
