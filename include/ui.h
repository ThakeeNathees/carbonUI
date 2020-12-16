#pragma once

#include "glfw_imgui.h"

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

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

		/* METHODS */
		BIND_STATIC_FUNC("Begin",       &ui::Begin,       PARAMS("title", "open", "flags"),                     DEFVALUES(nullptr, ImGuiWindowFlags_None));
		BIND_STATIC_FUNC("End",         &ui::End);

		// TODO: BeginChild, EndChild
		// TODO: Windows Utilities

		BIND_STATIC_FUNC("SetNextWindowPos",         &ui::SetNextWindowPos,         PARAMS("pos", "cond", "pivot"), DEFVALUES(0, newptr<Vec2>(0.f, 0.f)));
		BIND_STATIC_FUNC("SetNextWindowSize",        &ui::SetNextWindowSize,        PARAMS("size", "cond"),         DEFVALUES(0));
		//SetNextWindowSizeConstraints
		BIND_STATIC_FUNC("SetNextWindowContentSize", &ui::SetNextWindowContentSize, PARAMS("size"));

		// -- TEMP --------------------
		BIND_STATIC_FUNC("CheckBox",    ui::CheckBox,    PARAMS("label", "value"));
		BIND_STATIC_FUNC("Text",        ui::Text,        PARAMS("text"));
		BIND_STATIC_FUNC("SliderFloat", ui::SliderFloat, PARAMS("text", "value", "min", "max", "fmt", "power"), DEFVALUES("%.3f", 1.0f));
		BIND_STATIC_FUNC("ColorEdit3",  ui::ColorEdit3,  PARAMS("label", "color"));
		BIND_STATIC_FUNC("InputText",   ui::InputText,   PARAMS("label", "buff"));
		BIND_STATIC_FUNC("GetMousePos", ui::GetMousePos);

	}

public:

	// -- TEMP -----------------------
	static void Text(const String& text);
	static bool CheckBox(const String& label, bool& v);
	static bool SliderFloat(const String& label, double& v, float min, float max, const String& fmt = "%.3f", float power = 1.0f);
	static bool ColorEdit3(const String& label, var& color);
	static bool InputText(const String& label, String& buff);
	static ptr<Vec2> GetMousePos();
	// -------------------------------

	static bool Begin(const String& title, var& open, int window_flags);
	static void End();


	/* NextWindow */
	static void SetNextWindowPos(const var& pos, int cond = 0, const var& pivot = newptr<Vec2>(0, 0));
	static void SetNextWindowSize(const var& size, ImGuiCond cond = 0);
	//static void SetNextWindowSizeConstraints(const var& size_min, const var& size_max, ImGuiSizeCallback custom_callback = NULL, void* custom_callback_data = NULL);
	static void SetNextWindowContentSize(const var& size);
	static void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
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


	/* Windows Scrolling */
	//float GetScrollX();
	//float GetScrollY();
	//float GetScrollMaxX();
	//float GetScrollMaxY();
	//void  SetScrollX(float scroll_x);
	//void  SetScrollY(float scroll_y);
	//void  SetScrollHereX(float center_x_ratio = 0.5f);
	//void  SetScrollHereY(float center_y_ratio = 0.5f);
	//void  SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
	//void  SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);


	/* Parameters stacks (shared) */
	//void          PushFont(ImFont* font);
	//void          PopFont();
	//void          PushStyleColor(ImGuiCol idx, ImU32 col);
	//void          PushStyleColor(ImGuiCol idx, const ImVec4& col);
	//void          PopStyleColor(int count = 1);
	//void          PushStyleVar(ImGuiStyleVar idx, float val);
	//void          PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
	//void          PopStyleVar(int count = 1);
	//const ImVec4& GetStyleColorVec4(ImGuiCol idx);
	//ImFont*       GetFont();
	//float         GetFontSize();
	//ImVec2        GetFontTexUvWhitePixel();
	//ImU32         GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
	//ImU32         GetColorU32(const ImVec4& col);
	//ImU32         GetColorU32(ImU32 col);


	/* Parameters stacks (current window) */
	// void  PushItemWidth(float item_width);
	// void  PopItemWidth();
	// void  SetNextItemWidth(float item_width);
	// float CalcItemWidth();
	// void  PushTextWrapPos(float wrap_local_pos_x = 0.0f);
	// void  PopTextWrapPos();
	// void  PushAllowKeyboardFocus(bool allow_keyboard_focus);
	// void  PopAllowKeyboardFocus();
	// void  PushButtonRepeat(bool repeat);
	// void  PopButtonRepeat();

	/* Cursor / Layout */
	// void   Separator();
	// void   SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);
	// void   NewLine();
	// void   Spacing();
	// void   Dummy(const ImVec2& size);
	// void   Indent(float indent_w = 0.0f);
	// void   Unindent(float indent_w = 0.0f);
	// void   BeginGroup();
	// void   EndGroup();
	// ImVec2 GetCursorPos();
	// float  GetCursorPosX();
	// float  GetCursorPosY();
	// void   SetCursorPos(const ImVec2& local_pos);
	// void   SetCursorPosX(float local_x);
	// void   SetCursorPosY(float local_y);
	// ImVec2 GetCursorStartPos();
	// ImVec2 GetCursorScreenPos();
	// void   SetCursorScreenPos(const ImVec2& pos);
	// void   AlignTextToFramePadding();
	// float  GetTextLineHeight();
	// float  GetTextLineHeightWithSpacing();
	// float  GetFrameHeight();
	// float  GetFrameHeightWithSpacing();

	/* ID stack/scopes */
	// void    PushID(const char* str_id);
	// void    PushID(const char* str_id_begin, const char* str_id_end);
	// void    PushID(const void* ptr_id);
	// void    PushID(int int_id);
	// void    PopID();
	// ImGuiID GetID(const char* str_id);
	// ImGuiID GetID(const char* str_id_begin, const char* str_id_end);
	// ImGuiID GetID(const void* ptr_id);


	/* Widgets: Text */
	// void TextUnformatted(const char* text, const char* text_end = NULL);
	// void Text(const char* fmt, ...)                                      IM_FMTARGS(1);
	// void TextV(const char* fmt, va_list args)                            IM_FMTLIST(1);
	// void TextColored(const ImVec4& col, const char* fmt, ...)            IM_FMTARGS(2);
	// void TextColoredV(const ImVec4& col, const char* fmt, va_list args)  IM_FMTLIST(2);
	// void TextDisabled(const char* fmt, ...)                              IM_FMTARGS(1);
	// void TextDisabledV(const char* fmt, va_list args)                    IM_FMTLIST(1);
	// void TextWrapped(const char* fmt, ...)                               IM_FMTARGS(1);
	// void TextWrappedV(const char* fmt, va_list args)                     IM_FMTLIST(1);
	// void LabelText(const char* label, const char* fmt, ...)              IM_FMTARGS(2);
	// void LabelTextV(const char* label, const char* fmt, va_list args)    IM_FMTLIST(2);
	// void BulletText(const char* fmt, ...)                                IM_FMTARGS(1);
	// void BulletTextV(const char* fmt, va_list args);


	/* Widgets: Main */
	// bool Button(const char* label, const ImVec2& size = ImVec2(0,0));
	// bool SmallButton(const char* label);
	// bool InvisibleButton(const char* str_id, const ImVec2& size);
	// bool ArrowButton(const char* str_id, ImGuiDir dir);
	// void Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_col = ImVec4(1,1,1,1), const ImVec4& border_col = ImVec4(0,0,0,0));
	// bool ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0),  const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1));
	// bool Checkbox(const char* label, bool* v);
	// bool CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
	// bool RadioButton(const char* label, bool active);
	// bool RadioButton(const char* label, int* v, int v_button);
	// void ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1,0), const char* overlay = NULL);
	// void Bullet();

	/* Widgets: Combo Box */
	// bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
	// void EndCombo(); // only call EndCombo() if BeginCombo() returns true!
	// bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
	// bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);
	// bool Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

	 // TODO:


};
