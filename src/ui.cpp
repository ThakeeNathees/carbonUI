
#include "ui.h"

void ui::Text(const String& text) { ImGui::Text(text.c_str()); }

bool ui::CheckBox(const String& label, bool& v) {
	return ImGui::Checkbox(label.c_str(), &v);
}

bool ui::SliderFloat(const String& label, double& v, float min, float max, const String& fmt, float power) {
	static float _v = 0;
	_v = (float)v;
	ImGui::SliderFloat(label.c_str(), &_v, min, max, fmt.c_str(), power);
	return v = (double)_v;
}

bool ui::ColorEdit3(const String& label, var& color) {
	return ImGui::ColorEdit3(label.c_str(), (float*)color.cast_to<Color>()->get_data());
}

bool ui::InputText(const String& label, String& buff) {
	return ImGui::InputText(label.c_str(), &buff.operator std::string & ());
}

ptr<Vec2> ui::GetMousePos() {
	return newptr<Vec2>(ImGui::GetMousePos());
}
// ------------------------------------------------------------------------------------------------------

bool ui::Begin(const String& title, var& open, int window_flags) {
	static bool _open = true; static bool* _popen = &_open;
	if (open.get_type() != var::_NULL) _open = open.operator bool(), _popen = &_open;
	else _popen = NULL;
	bool ret = ImGui::Begin(title.c_str(), &(open.operator bool&()), (ImGuiWindowFlags)window_flags);
	if (open.get_type() == var::BOOL) open = _open;
	return ret;
}
void ui::End() {
	ImGui::End();
}


void ui::SetNextWindowPos(const var& pos, int cond, const var& pivot) {
	ImGui::SetNextWindowPos(*pos.cast_to<Vec2>(), cond, *pivot.cast_to<Vec2>());
}

void ui::SetNextWindowSize(const var& size, ImGuiCond cond) {
	ImGui::SetNextWindowSize(*size.cast_to<Vec2>(), cond);
}

void ui::SetNextWindowContentSize(const var& size) {
	ImGui::SetNextWindowContentSize(*size.cast_to<Vec2>());
}