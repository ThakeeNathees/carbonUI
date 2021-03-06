
#include "cbui.h"

#ifdef APIENTRY
	#undef APIENTRY
#endif

#define INCLUDE_CRASH_HANDLER_MAIN
#define CRASH_HANDLER_IMPLEMENTATION
#include "crash_handler.h"

// Or should use a config file?
#define ENTRY_SCRIPT "main.cb"
#define LOOP_FN "process"
#define INIT_FN "init"

ptr<uiWindow> ui::_window = nullptr;
void (*ui::_ReloadScriptFn)();
void (*ui::_SetConsoleVisible)(bool);
bool (*ui::_IsConsoleVisible)();

void set_console_visible(bool visible) {
#ifdef PLATFORM_WINDOWS
	if (visible) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	} else {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
#else
	// TODO: also for is visible()
#endif
}

bool is_console_visible() {
#ifdef PLATFORM_WINDOWS
	return IsWindowVisible(GetConsoleWindow()) != FALSE;
#endif
	return true;
}

void reload_script() {
	ui::_window->_reload = true;
}

inline int compile_script() {
	try {
		ui::_window->_script = Compiler::singleton()->compile(ENTRY_SCRIPT, false);
		ui::_window->_fn = ui::_window->_script->get_function(LOOP_FN);
		ui::_window->_init = ui::_window->_script->get_function(INIT_FN);
	} catch (Throwable& err) {
		set_console_visible(true);
		err.console_log();
		return 1;
	}
	return 0;
}

int mainloop() {
	// call initialize() function in script for title, etc.
	ui::_window = newptr<uiWindow>("Window Title");
	ui::_ReloadScriptFn = &reload_script;
	ui::_SetConsoleVisible = &set_console_visible;
	ui::_IsConsoleVisible = &is_console_visible;

	if (ui::_window->Initialize() != 0) {
		set_console_visible(true);
		fprintf(stderr, "initialize doesn't returned 0");
		return 1;
	}
	
	if (compile_script() != 0) return 1;

	stdvec<var*> args;
	if (ui::_window->_init != nullptr) { // script initialization
		VM::singleton()->call_function(ui::_window->_init.get(), ui::_window->_script.get(), nullptr, args);
	}

	while (!ui::_window->ShouldClose()) {
		ui::_window->PollEvents();
		
		ui::_window->NewFrame();
		/* ------------------------------------------ */
		try {
			VM::singleton()->call_function(ui::_window->_fn.get(), ui::_window->_script.get(), nullptr, args);
			if (ui::_window->_reload) {
				compile_script();
				ui::_window->_reload = false;
			}
		} catch (Throwable& err) {
			set_console_visible(true);
			err.console_log();
			return 1;
		}
		
		/* ------------------------------------------ */
		ui::_window->DrawFrame();
		ui::_window->SwapBuffer();
	}
		
	ui::_window->Cleanup();
	return 0;
}

int _main(int argc, char** argv) {

	carbon_initialize();
	register_ui();

	int exit_code = mainloop();

	carbon_cleanup();

	return exit_code;
}

// tmp //////////////////////
//void text_edit_init(TextEditor& editor);
//void text_edit_draw(TextEditor& editor);
void text_edit_init(TextEditor& editor) {
	auto lang = TextEditor::LanguageDefinition::CPlusPlus();
	
	// set your own known preprocessor symbols...
	static const char* ppnames[] = { "NULL", "PM_REMOVE",
		"ZeroMemory", "DXGI_SWAP_EFFECT_DISCARD", "D3D_FEATURE_LEVEL", "D3D_DRIVER_TYPE_HARDWARE", "WINAPI","D3D11_SDK_VERSION", "assert" };
	// ... and their corresponding values
	static const char* ppvalues[] = {
		"#define NULL ((void*)0)",
		"#define PM_REMOVE (0x0001)",
		"Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
		"enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
		"enum D3D_FEATURE_LEVEL",
		"enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
		"#define WINAPI __stdcall",
		"#define D3D11_SDK_VERSION (7)",
		" #define assert(expression) (void)(                                                  \n"
		"    (!!(expression)) ||                                                              \n"
		"    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
		" )"
	};
	
	for (int i = 0; i < sizeof(ppnames) / sizeof(ppnames[0]); ++i) {
		TextEditor::Identifier id;
		id.mDeclaration = ppvalues[i];
		lang.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
	}
	
	// set your own identifiers
	static const char* identifiers[] = {
		"HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor" };
	static const char* idecls[] =
	{
		"typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
		"typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
		"ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
		"ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
		"IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor" };
	for (int i = 0; i < sizeof(identifiers) / sizeof(identifiers[0]); ++i) {
		TextEditor::Identifier id;
		id.mDeclaration = std::string(idecls[i]);
		lang.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
	}
	editor.SetLanguageDefinition(lang);
	//editor.SetPalette(TextEditor::GetLightPalette());
	
	// error markers
	TextEditor::ErrorMarkers markers;
	markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
	markers.insert(std::make_pair<int, std::string>(41, "Another example error"));
	editor.SetErrorMarkers(markers);
	
	// "breakpoint" markers
	TextEditor::Breakpoints bpts;
	bpts.insert(24);
	bpts.insert(47);
	editor.SetBreakpoints(bpts);
	
	static const char* fileToEdit = "src/main.cpp";
	//	static const char* fileToEdit = "test.cpp";
	
	{
		std::ifstream t(fileToEdit);
		if (t.good()) {
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.SetText(str);
		}
	}
}


void text_edit_draw(TextEditor& editor) {

	auto cpos = editor.GetCursorPosition();
	ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Save")) {
				auto textToSave = editor.GetText();
				/// save text....
			}
			if (ImGui::MenuItem("Quit", "Alt-F4"))
				; // BREAK
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			bool ro = editor.IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				editor.SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
				editor.Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
				editor.Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
				editor.Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
				editor.Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
				editor.Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				editor.Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			if (ImGui::MenuItem("Dark palette"))
				editor.SetPalette(TextEditor::GetDarkPalette());
			if (ImGui::MenuItem("Light palette"))
				editor.SetPalette(TextEditor::GetLightPalette());
			if (ImGui::MenuItem("Retro blue palette"))
				editor.SetPalette(TextEditor::GetRetroBluePalette());
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
		editor.IsOverwrite() ? "Ovr" : "Ins",
		editor.CanUndo() ? "*" : " ",
		editor.GetLanguageDefinition().mName.c_str(), "src/main.cpp");

	editor.Render("TextEditor");
	ImGui::End();
}
