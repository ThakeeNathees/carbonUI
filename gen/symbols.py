
## TODO: restructure this into key value to map for generating

from collections import OrderedDict

SYMBOLS = OrderedDict()
	
## flags
## KEY : [IMGUI_SUMBOL]
SYMBOLS['$flag_XXXXXXXXorEditFlags$'  ] = ['ImGuiColorEditFlags'] ## <- this should be above ImGuiCol flag
SYMBOLS['$flag_ImGuiCol$'             ] = ['ImGuiCol']
SYMBOLS['$flag_ImGuiCond$'            ] = ['ImGuiCond']
SYMBOLS['$flag_ImGuiDataType$'        ] = ['ImGuiDataType']
SYMBOLS['$flag_ImGuiDir$'             ] = ['ImGuiDir']
SYMBOLS['$flag_ImGuiKey$'             ] = ['ImGuiKey']
SYMBOLS['$flag_ImGuiNavInput$'        ] = ['ImGuiNavInput']
SYMBOLS['$flag_ImGuiMouseButton$'     ] = ['ImGuiMouseButton']
SYMBOLS['$flag_ImGuiMouseCursor$'     ] = ['ImGuiMouseCursor']
SYMBOLS['$flag_ImGuiStyleVar$'        ] = ['ImGuiStyleVar']
SYMBOLS['$flag_ImDrawCornerFlags$'    ] = ['ImDrawCornerFlags']
SYMBOLS['$flag_ImDrawListFlags$'      ] = ['ImDrawListFlags']
SYMBOLS['$flag_ImFontAtlasFlags$'     ] = ['ImFontAtlasFlags']
SYMBOLS['$flag_ImGuiBackendFlags$'    ] = ['ImGuiBackendFlags']
SYMBOLS['$flag_ImGuiConfigFlags$'     ] = ['ImGuiConfigFlags']
SYMBOLS['$flag_ImGuiComboFlags$'      ] = ['ImGuiComboFlags']
SYMBOLS['$flag_ImGuiDockNodeFlags$'   ] = ['ImGuiDockNodeFlags']
SYMBOLS['$flag_ImGuiDragDropFlags$'   ] = ['ImGuiDragDropFlags']
SYMBOLS['$flag_ImGuiFocusedFlags$'    ] = ['ImGuiFocusedFlags']
SYMBOLS['$flag_ImGuiHoveredFlags$'    ] = ['ImGuiHoveredFlags']
SYMBOLS['$flag_ImGuiInputTextFlags$'  ] = ['ImGuiInputTextFlags']
SYMBOLS['$flag_ImGuiKeyModFlags$'     ] = ['ImGuiKeyModFlags']
SYMBOLS['$flag_ImGuiSelectableFlags$' ] = ['ImGuiSelectableFlags']
SYMBOLS['$flag_ImGuiTabBarFlags$'     ] = ['ImGuiTabBarFlags']
SYMBOLS['$flag_ImGuiTabItemFlags$'    ] = ['ImGuiTabItemFlags']
SYMBOLS['$flag_ImGuiTreeNodeFlags$'   ] = ['ImGuiTreeNodeFlags']
SYMBOLS['$flag_ImGuiViewportFlags$'   ] = ['ImGuiViewportFlags']
SYMBOLS['$flag_ImGuiWindowFlags$'     ] = ['ImGuiWindowFlags']

## other
SYMBOLS[''                            ] = ['IMGUI_API']
SYMBOLS['$im_id$'                     ] = ['ImGuiID']

## -------------------------------------------------------------------------

## default values
## KEY                    = [IMGUI_SUMBOL      ,  VAR_VERSION             ]
SYMBOLS['$vec2_0$'      ] = ['ImVec2(0,0)'     ,  'newptr<Vec2>(0,0)'     ]
SYMBOLS['$vec2_0_$'     ] = ['ImVec2(0, 0)'    ,  'newptr<Vec2>(0,0)'     ]
SYMBOLS['$vec2_1$'      ] = ['ImVec2(1,1)'     ,  'newptr<Vec2>(1,1)'     ]
SYMBOLS['$vec2_1_$'     ] = ['ImVec2(1, 1)'    ,  'newptr<Vec2>(1,1)'     ]
SYMBOLS['$vec2_-10$'    ] = ['ImVec2(-1,0)'    ,  'newptr<Vec2>(-1,0)'    ]
SYMBOLS['$vec4_0$'      ] = ['ImVec4(0,0,0,0)' ,  'newptr<Vec4>(0,0,0,0)' ]
SYMBOLS['$vec4_1$'      ] = ['ImVec4(1,1,1,1)' ,  'newptr<Vec4>(1,1,1,1)' ]

## types
# KEY                      = [IMGUI_SYMBOL,         VAR_VERSION,          PARAM_CAST_TO_IMGUI                                         ]
SYMBOLS['$const_cXXX*$'  ] = ['const char* const', 'const String&',       lambda param : f'{param}.c_str()'              ]
SYMBOLS['$const_cXXX*_$' ] = ['const char*',       'const String&',       lambda param : f'{param}.c_str()'              ]
SYMBOLS['$bXXl*$'        ] = ['bool*',             'var&/*bool*/',        lambda param : f'&({param}.operator bool&())'  ]
SYMBOLS['$iXt*$'         ] = ['int*',              'var&/*int*/',         lambda param : f'&({param}.operator int&())'   ]
SYMBOLS['$const_flXXt*$' ] = ['const float*',      'var&/*float*/',       lambda param : f'&({param}.operator float&())' ]
SYMBOLS['$flXXt*$'       ] = ['float*',            'var&/*float*/',       lambda param : f'&({param}.operator float&())' ]

## casting to color is for better error message
SYMBOLS['$col@float_col3$ col' ] = ['float col[3]', 'var&/*Color*/',      lambda param : f'(float*){param}.cast_to<Color>()->get_data()'   ]
SYMBOLS['$col@float_col4$ col' ] = ['float col[4]', 'var&/*Color*/',      lambda param : f'(float*){param}.cast_to<Color>()->get_data()'   ]

## need to add the v@ by the user
SYMBOLS['$v@float_v2$ v' ] = ['float v[2]',       'var&/*Vec2*/',         lambda param : f'(float*){param}.get_data()'  ]
SYMBOLS['$v@float_v3$ v' ] = ['float v[3]',       'var&/*Vec3*/',         lambda param : f'(float*){param}.get_data()'  ]
SYMBOLS['$v@float_v4$ v' ] = ['float v[4]',       'var&/*Vec4*/',         lambda param : f'(float*){param}.get_data()'  ]

SYMBOLS['$v@int_v2$ v'   ] = ['int v[2]',         'var&/*Vec2i*/',        lambda param : f'(int*){param}.get_data()'    ]
SYMBOLS['$v@int_v3$ v'   ] = ['int v[3]',         'var&/*Vec3i*/',        lambda param : f'(int*){param}.get_data()'    ]
SYMBOLS['$v@int_v4$ v'   ] = ['int v[4]',         'var&/*Vec4i*/',        lambda param : f'(int*){param}.get_data()'    ]

SYMBOLS['$const_vec2&$'  ] = ['const ImVec2&',     'var&/*Vec2*/',        lambda param : f'*{param}.cast_to<Vec2>()'    ]
SYMBOLS['$const_vec2*$'  ] = ['const ImVec2*',     'var&/*Vec2*/',        lambda param : f'&{param}.cast_to<Vec2>()->operator ImVec2&()'    ]
SYMBOLS['$vec2&$'        ] = ['ImVec2&',           'var&/*Vec2*/',        lambda param : f'*{param}.cast_to<Vec2>()'    ]
SYMBOLS['$vec2$'         ] = ['ImVec2',            'var/*Vec2*/',         lambda param : f'*{param}.cast_to<Vec2>()'    ]

SYMBOLS['$const_vec4&$'  ] = ['const ImVec4&',     'var&/*Vec4*/',        lambda param : f'*{param}.cast_to<Vec4>()'     ]
SYMBOLS['$const_vec4*$'  ] = ['const ImVec4*',     'var&/*Vec4*/',        lambda param : f'&*{param}.cast_to<Vec4>()->operator ImVec4&()'     ]
SYMBOLS['$vec4&$'        ] = ['ImVec4&',           'var&/*Vec4*/',        lambda param : f'*{param}.cast_to<Vec4>()'     ]
SYMBOLS['$vec4$'         ] = ['ImVec4',            'var/*Vec4*/',         lambda param : f'*{param}.cast_to<Vec4>()'     ]


