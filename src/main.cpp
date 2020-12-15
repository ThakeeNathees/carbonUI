
#include "carbonUI.h"

void imgui_demo(); // tmp

int mainloop(int argc, char** argv) {

	carbon_initialize();
	if (Glfw_ImGui::initialize() != 0) return 1;

	register_cbimgui();

	ptr<Bytecode> bytecode;
	CarbonFunction* fn;
	stdvec<var*> args;
	try {
		bytecode = Compiler::singleton()->compile("bin/main.cb");
		fn = bytecode->get_function("draw").get();
	} catch (Throwable& err) {
		err.console_log();
		return -1;
	}

	while (!glfwWindowShouldClose(Glfw_ImGui::get_window())) {
		glfwPollEvents();
		
		Glfw_ImGui::new_frame();
		/* ------------------------------------------ */
		//imgui_dockspace();
		imgui_demo();
		//ImGui::ShowDemoWindow();

		try {
			VM::singleton()->call_function(fn, bytecode.get(), nullptr, args);
		} catch (Throwable& err) {
			err.console_log();
			return -1;
		}

		/* ------------------------------------------ */
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		Glfw_ImGui::draw_frame();
		glfwSwapBuffers(Glfw_ImGui::get_window());
	}

	Glfw_ImGui::cleanup();
	carbon_cleanup();

	return 0;

}


// tmp //////////////////////

void imgui_demo() {
	// Our state
	static bool show_demo_window = true;
	static bool show_another_window = false;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                           // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");                // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);       // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color);  // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                             // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window) {
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}