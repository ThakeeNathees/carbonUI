
#include "types/vec4.h"


// Color ///////////////////////////////////////////////////

Color::Color(float r, float g, float b, float a) : _data(r, g, b, a) {}
Color::Color(const ImColor& imcolor) : _data(imcolor) {}

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


// Vec4 ///////////////////////////////////////////////////

Vec4::Vec4(float x, float y, float z, float w)
	:_data(ImVec4(x, y, z, w)) {}
Vec4::Vec4(const ImVec4& imvec) : _data(imvec) {}

void Vec4::_Vec4(ptr<Object> _self, float x, float y, float z, float w) {
	Vec4* vec4 = ptrcast<Vec4>(_self).get();
	vec4->_data = ImVec4(x, y, z, w);
}

var Vec4::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash: return _data.x;
		case "y"_hash: return _data.y;
		case "z"_hash: return _data.z;
		case "w"_hash: return _data.w;
	}
	return Super::get_member(p_name);
}
void Vec4::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash: _data.x = value; return;
		case "y"_hash: _data.y = value; return;
		case "z"_hash: _data.z = value; return;
		case "w"_hash: _data.w = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec4::get_data() {
	return (void*)&_data;
}

Vec4::operator ImVec4& () {
	return _data;
}

// Vec4i ///////////////////////////////////////////////////


Vec4i::Vec4i(int x, int y, int z, int w) {
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
	_data[3] = w;
}
Vec4i::Vec4i(int v[4]) {
	_data[0] = v[0];
	_data[1] = v[1];
	_data[2] = v[2];
	_data[3] = v[3];
}

void Vec4i::_Vec4i(ptr<Object> _self, int x, int y, int z, int w) {
	Vec4i* vec4 = ptrcast<Vec4i>(_self).get();
	vec4->_data[0] = x;
	vec4->_data[1] = y;
	vec4->_data[2] = z;
	vec4->_data[3] = w;
}

var Vec4i::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash: return _data[0];
		case "y"_hash: return _data[1];
		case "z"_hash: return _data[2];
		case "w"_hash: return _data[3];
	}
	return Super::get_member(p_name);
}
void Vec4i::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash: _data[0] = value; return;
		case "y"_hash: _data[1] = value; return;
		case "z"_hash: _data[2] = value; return;
		case "w"_hash: _data[3] = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec4i::get_data() {
	return (void*)_data;
}
