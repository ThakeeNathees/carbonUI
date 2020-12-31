#pragma once

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

#include "TextEditor.h"

class uiWindow : public Object {
	REGISTER_CLASS(uiWindow, Object) {
		// construct by ui.Window()
		//BIND_STATIC_FUNC("uiWindow", &uiWindow::_uiWindow, PARAMS("self", "title", "size"), DEFVALUES(newptr<Vec2i>(1280, 720)));
		BIND_METHOD("Initialize", &uiWindow::Initialize);
		BIND_METHOD("Cleanup", &uiWindow::Cleanup);
		BIND_METHOD("NewFrame", &uiWindow::NewFrame);
		BIND_METHOD("DrawFrame", &uiWindow::DrawFrame);
		BIND_METHOD("SwapBuffer", &uiWindow::SwapBuffer);
		BIND_METHOD("ShouldClose", &uiWindow::ShouldClose);
		BIND_METHOD("PollEvents", &uiWindow::PollEvents);
		BIND_METHOD("Clear", &uiWindow::Clear, PARAMS("color"), DEFVALUES(newptr<Color>(0.f, 0.f, 0.f, 1.f)));
	}

	uiWindow(const String& title = "", ptr<Vec2i> size = newptr<Vec2i>(1280, 720));
	static void _uiWindow(ptr<uiWindow> self, const String& title, ptr<Vec2i> size);

	int Initialize();
	void Cleanup();

	void NewFrame();
	void DrawFrame();
	void SwapBuffer();

	bool ShouldClose();
	void PollEvents();

	void Clear(ptr<Color> col);

private:
	friend class ui;
	ptr<Vec2i> size;
	String title = "Carbon UI";
	GLFWwindow* _window = nullptr;

};

class uiTextEditor : public Object {
	REGISTER_CLASS(uiTextEditor, Object) {
		BIND_METHOD("SetText", &uiTextEditor::SetText, PARAMS("text"));
		BIND_METHOD("GetText", &uiTextEditor::GetText);
		BIND_METHOD("Render", &uiTextEditor::Render);
	}

	uiTextEditor();

	// FIXME: bind all methods
	void SetText(const String& text);
	String GetText();
	void Render();

private:
	TextEditor editor;
};