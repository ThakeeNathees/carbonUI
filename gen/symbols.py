
## TODO: restructure this into key value to map for generating

REPLACE = [ ## replace order is important

	## flags
	('ImGuiCol', '$flag_ImGuiCol$'),
	('ImGuiCond', '$flag_ImGuiCond$'),
	('ImGuiDataType', '$flag_ImGuiDataType$'),
	('ImGuiDir', '$flag_ImGuiDir$'),
	('ImGuiKey', '$flag_ImGuiKey$'),
	('ImGuiNavInput', '$flag_ImGuiNavInput$'),
	('ImGuiMouseButton', '$flag_ImGuiMouseButton$'),
	('ImGuiMouseCursor', '$flag_ImGuiMouseCursor$'),
	('ImGuiStyleVar', '$flag_ImGuiStyleVar$'),
	('ImDrawCornerFlags', '$flag_ImDrawCornerFlags$'),
	('ImDrawListFlags', '$flag_ImDrawListFlags$'),
	('ImFontAtlasFlags', '$flag_ImFontAtlasFlags$'),
	('ImGuiBackendFlags', '$flag_ImGuiBackendFlags$'),
	('ImGuiColorEditFlags', '$flag_ImGuiColorEditFlags$'),
	('ImGuiConfigFlags', '$flag_ImGuiConfigFlags$'),
	('ImGuiComboFlags', '$flag_ImGuiComboFlags$'),
	('ImGuiDockNodeFlags', '$flag_ImGuiDockNodeFlags$'),
	('ImGuiDragDropFlags', '$flag_ImGuiDragDropFlags$'),
	('ImGuiFocusedFlags', '$flag_ImGuiFocusedFlags$'),
	('ImGuiHoveredFlags', '$flag_ImGuiHoveredFlags$'),
	('ImGuiInputTextFlags', '$flag_ImGuiInputTextFlags$'),
	('ImGuiKeyModFlags', '$flag_ImGuiKeyModFlags$'),
	('ImGuiSelectableFlags', '$flag_ImGuiSelectableFlags$'),
	('ImGuiTabBarFlags', '$flag_ImGuiTabBarFlags$'),
	('ImGuiTabItemFlags', '$flag_ImGuiTabItemFlags$'),
	('ImGuiTreeNodeFlags', '$flag_ImGuiTreeNodeFlags$'),
	('ImGuiViewportFlags', '$flag_ImGuiViewportFlags$'),
	('ImGuiWindowFlags', '$flag_ImGuiWindowFlags$'),

	## other
	('IMGUI_API', ''),
	('ImGuiID', '$im_id$'),

	## default values
	('ImVec2(0,0)', '$vec2_0$'),
	('ImVec2(0, 0)', '$vec2_0$'),
	('ImVec2(1,1)', '$vec2_1$'),
	('ImVec2(1, 1)', '$vec2_1$'),
	('ImVec2(-1,0)', '$vec2_-1,0$'),
	('ImVec4(0,0,0,0)', '$vec4_0$'),
	('ImVec4(1,1,1,1)', '$vec4_1$'),

	## types
	('const char*', '$const_char*$'),
	('float col[3]', '$float_col3$ col'),
	('float col[4]', '$float_col4$ col'),

	('float v[2]', '$float_v2$ v'),
	('float v[3]', '$float_v3$ v'),
	('float v[4]', '$float_v4$ v'),

	('int v[2]', '$int_v2$ v'),
	('int v[3]', '$int_v3$ v'),
	('int v[4]', '$int_v4$ v'),

	('const ImVec2&', '$const_vec2&$'),
	('ImVec2&', '$vec2&$'),
	('ImVec2', '$vec2$'),

	('const ImVec4&', '$const_vec4&$'),
	('ImVec4&', '$vec4&$'),
	('ImVec4', '$vec4$'),
]

