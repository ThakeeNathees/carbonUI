
#include "types/vec3.h"

Vec3::Vec3(float x, float y, float z) {
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
}
Vec3::Vec3(float v[3]) {
	_data[0] = v[0];
	_data[1] = v[1];
	_data[2] = v[2];
}

void Vec3::_Vec3(ptr<Object> _self, float x, float y, float z) {
	Vec3* vec4 = ptrcast<Vec3>(_self).get();
	vec4->_data[0] = x;
	vec4->_data[1] = y;
	vec4->_data[2] = z;
}

var Vec3::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash: return _data[0];
		case "y"_hash: return _data[1];
		case "z"_hash: return _data[2];
		case "w"_hash: return _data[3];
	}
	return Super::get_member(p_name);
}
void Vec3::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash: _data[0] = value; return;
		case "y"_hash: _data[1] = value; return;
		case "z"_hash: _data[2] = value; return;
		case "w"_hash: _data[3] = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec3::get_data() {
	return (void*)_data;
}

// Vec3i ///////////////////////////////////////


Vec3i::Vec3i(int x, int y, int z) {
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
}
Vec3i::Vec3i(int v[3]) {
	_data[0] = v[0];
	_data[1] = v[1];
	_data[2] = v[2];
}

void Vec3i::_Vec3i(ptr<Object> _self, int x, int y, int z) {
	Vec3i* vec4 = ptrcast<Vec3i>(_self).get();
	vec4->_data[0] = x;
	vec4->_data[1] = y;
	vec4->_data[2] = z;
}

var Vec3i::get_member(const String& p_name) {
	switch (p_name.const_hash()) {
		case "x"_hash: return _data[0];
		case "y"_hash: return _data[1];
		case "z"_hash: return _data[2];
		case "w"_hash: return _data[3];
	}
	return Super::get_member(p_name);
}
void Vec3i::set_member(const String& p_name, var& value) {
	switch (p_name.const_hash()) {
		case "x"_hash: _data[0] = value; return;
		case "y"_hash: _data[1] = value; return;
		case "z"_hash: _data[2] = value; return;
		case "w"_hash: _data[3] = value; return;
	}
	Super::set_member(p_name, value);
}

void* Vec3i::get_data() {
	return (void*)_data;
}
