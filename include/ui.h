#pragma once

#include "glfw_imgui.h"
#include "types.h"

class ui : public Object {
	REGISTER_CLASS(ui, Object) {
		BIND_ENUM("WindowFlags", {
			{ "None", ImGuiWindowFlags_None },
			{ "NoTitleBar", ImGuiWindowFlags_NoTitleBar },
			{ "NoResize", ImGuiWindowFlags_NoResize },
			{ "NoMove", ImGuiWindowFlags_NoMove },
			{ "NoScrollbar", ImGuiWindowFlags_NoScrollbar },
			{ "NoScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse },
			{ "NoCollapse", ImGuiWindowFlags_NoCollapse },
			{ "AlwaysAutoResize", ImGuiWindowFlags_AlwaysAutoResize },
			{ "NoBackground", ImGuiWindowFlags_NoBackground },
			{ "NoSavedSettings", ImGuiWindowFlags_NoSavedSettings },
			{ "NoMouseInputs", ImGuiWindowFlags_NoMouseInputs },
			{ "MenuBar", ImGuiWindowFlags_MenuBar },
			{ "HorizontalScrollbar", ImGuiWindowFlags_HorizontalScrollbar },
			{ "NoFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing },
			{ "NoBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus },
			{ "AlwaysVerticalScrollbar", ImGuiWindowFlags_AlwaysVerticalScrollbar },
			{ "AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar },
			{ "AlwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding },
			{ "NoNavInputs", ImGuiWindowFlags_NoNavInputs },
			{ "NoNavFocus", ImGuiWindowFlags_NoNavFocus },
			{ "UnsavedDocument", ImGuiWindowFlags_UnsavedDocument },
			{ "NoDocking", ImGuiWindowFlags_NoDocking },

			{ "NoNav", ImGuiWindowFlags_NoNav },
			{ "NoDecoration", ImGuiWindowFlags_NoDecoration },
			{ "NoInputs", ImGuiWindowFlags_NoInputs },

		});

		BIND_ENUM("Cond", {
			{ "Always", ImGuiCond_Always },
			{ "Once", ImGuiCond_Once },
			{ "FirstUseEver", ImGuiCond_FirstUseEver },
			{ "Appearing", ImGuiCond_Appearing },
		});

		BIND_STATIC_FUNC("Begin",       &ui::Begin,       PARAMS("title", "open", "flags"),                     DEFVALUES(nullptr, ImGuiWindowFlags_None));
		BIND_STATIC_FUNC("End",         &ui::End);

		// TODO: BeginChild, EndChild
		// TODO: Windows Utilities

		BIND_STATIC_FUNC("SetNextWindowPos", &ui::SetNextWindowPos, PARAMS("pos", "cond", "pivot"), DEFVALUES(0, newptr<Vec2>(0.f, 0.f)));
		//SetNextWindowPos(const var & pos, int cond = 0, const var & pivot = newptr<Vec2>(0, 0));

		// ---------------------
		BIND_STATIC_FUNC("CheckBox",    ui::CheckBox,    PARAMS("label", "value"));
		BIND_STATIC_FUNC("Text",        ui::Text,        PARAMS("text"));
		BIND_STATIC_FUNC("SliderFloat", ui::SliderFloat, PARAMS("text", "value", "min", "max", "fmt", "power"), DEFVALUES("%.3f", 1.0f));
		BIND_STATIC_FUNC("ColorEdit3",  ui::ColorEdit3,  PARAMS("label", "color"));
		BIND_STATIC_FUNC("InputText",   ui::InputText,   PARAMS("label", "buff"));

	}

public:

	static void Text(const String& text);
	static bool CheckBox(const String& label, bool& v);
	static bool SliderFloat(const String& label, double& v, float min, float max, const String& fmt = "%.3f", float power = 1.0f);
	static bool ColorEdit3(const String& label, var& color);
	static bool InputText(const String& label, String& buff);

	static bool Begin(const String& title, var& open, int window_flags);
	static void End();

	static void SetNextWindowPos(const var& pos, int cond = 0, const var& pivot = newptr<Vec2>(0, 0));
	//static void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
	//static void SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL);
	//static void SetNextWindowContentSize(const ImVec2& size);
	//static void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
	//static void SetNextWindowFocus();
	//static void SetNextWindowBgAlpha(float alpha);
	//static void SetNextWindowViewport(ImGuiID viewport_id);
	//static void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
	//static void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
	//static void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
	//static void SetWindowFocus();
	//static void SetWindowFontScale(float scale);
	//static void SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);
	//static void SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);
	//static void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);
	//static void SetWindowFocus(const char* name);

};
