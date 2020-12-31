#include "cls_bind.h"

uiWindow::uiWindow(const String& title, ptr<Vec2i> size)
	:size(size), title(title) {}

void uiWindow::_uiWindow(ptr<uiWindow> self, const String& title, ptr<Vec2i> size) {
	self->size = size;
	self->title = title;
}

void uiWindow::Cleanup() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(_window);
	glfwTerminate();
}

int uiWindow::Initialize() {
	glfwSetErrorCallback([](int error, const char* description) {
		fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	_window = glfwCreateWindow(size->_data[0], size->_data[1], title.c_str(), NULL, NULL);
	if (_window == NULL) return -1;
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1); // Enable vsync

	bool err = gladLoadGL() == 0;
	if (err) {
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return -1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core"/*glsl_version*/);

	return 0;
}

void uiWindow::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void uiWindow::DrawFrame() {
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	// The actual draw call of the ImGui frame
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void uiWindow::SwapBuffer() {
	glfwSwapBuffers(_window);
}

bool uiWindow::ShouldClose() {
	return glfwWindowShouldClose(_window);
}

void uiWindow::PollEvents() {
	glfwPollEvents();
}

void uiWindow::Clear(ptr<Color> col) {
	glClearColor(col->r(), col->g(), col->b(), col->a()); glClear(GL_COLOR_BUFFER_BIT);
}

// -- TEXT EDITOR --------------------------------------------------

uiTextEditor::uiTextEditor() {
}

void uiTextEditor::SetText(const String& text) {
	editor.SetText(text.operator const std::string &());
}

String uiTextEditor::GetText() {
	return editor.GetText();
}

void uiTextEditor::Render() {
	editor.Render("TextEditor");
}
