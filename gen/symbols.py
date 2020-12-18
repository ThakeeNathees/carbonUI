
## TODO: some const char* could be NULL => can't cast to const String&

from collections import OrderedDict

SYMBOLS = OrderedDict()

## just reomve these symbols
SYMBOLS['$@CLEAN@$'] = [
	'IMGUI_API',
	'IM_FMTARGS(1)', 'IM_FMTARGS(2)', 'IM_FMTARGS(3)', ', ...' ]
	
## flags
## KEY : [IMGUI_SUMBOL]
SYMBOLS['$flag_XXXXXXXXorEditFlags$'  ] = ['ImGuiColorEditFlags'  ] ## <- this should be above ImGuiCol flag
SYMBOLS['$flag_ImGuiCol$'             ] = ['ImGuiCol'             ]
SYMBOLS['$flag_ImGuiCond$'            ] = ['ImGuiCond'            ]
SYMBOLS['$flag_ImGuiDataType$'        ] = ['ImGuiDataType'        ]
SYMBOLS['$flag_ImGuiDir$'             ] = ['ImGuiDir'             ]
SYMBOLS['$flag_ImGuiKey$'             ] = ['ImGuiKey'             ]
SYMBOLS['$flag_ImGuiNavInput$'        ] = ['ImGuiNavInput'        ]
SYMBOLS['$flag_ImGuiMouseButton$'     ] = ['ImGuiMouseButton'     ]
SYMBOLS['$flag_ImGuiMouseCursor$'     ] = ['ImGuiMouseCursor'     ]
SYMBOLS['$flag_ImGuiStyleVar$'        ] = ['ImGuiStyleVar'        ]
SYMBOLS['$flag_ImDrawCornerFlags$'    ] = ['ImDrawCornerFlags'    ]
SYMBOLS['$flag_ImDrawListFlags$'      ] = ['ImDrawListFlags'      ]
SYMBOLS['$flag_ImFontAtlasFlags$'     ] = ['ImFontAtlasFlags'     ]
SYMBOLS['$flag_ImGuiBackendFlags$'    ] = ['ImGuiBackendFlags'    ]
SYMBOLS['$flag_ImGuiConfigFlags$'     ] = ['ImGuiConfigFlags'     ]
SYMBOLS['$flag_ImGuiComboFlags$'      ] = ['ImGuiComboFlags'      ]
SYMBOLS['$flag_ImGuiDockNodeFlags$'   ] = ['ImGuiDockNodeFlags'   ]
SYMBOLS['$flag_ImGuiDragDropFlags$'   ] = ['ImGuiDragDropFlags'   ]
SYMBOLS['$flag_ImGuiFocusedFlags$'    ] = ['ImGuiFocusedFlags'    ]
SYMBOLS['$flag_ImGuiHoveredFlags$'    ] = ['ImGuiHoveredFlags'    ]
SYMBOLS['$flag_ImGuiInputTextFlags$'  ] = ['ImGuiInputTextFlags'  ]
SYMBOLS['$flag_ImGuiKeyModFlags$'     ] = ['ImGuiKeyModFlags'     ]
SYMBOLS['$flag_ImGuiSelectableFlags$' ] = ['ImGuiSelectableFlags' ]
SYMBOLS['$flag_ImGuiTabBarFlags$'     ] = ['ImGuiTabBarFlags'     ]
SYMBOLS['$flag_ImGuiTabItemFlags$'    ] = ['ImGuiTabItemFlags'    ]
SYMBOLS['$flag_ImGuiTreeNodeFlags$'   ] = ['ImGuiTreeNodeFlags'   ]
SYMBOLS['$flag_ImGuiViewportFlags$'   ] = ['ImGuiViewportFlags'   ]
SYMBOLS['$flag_ImGuiWindowFlags$'     ] = ['ImGuiWindowFlags'     ]

SYMBOLS['$im_id$'                     ] = ['ImGuiID',    'int',  lambda param: f'{param}'] ## <-- FIXME: unsigned int incompatable	(implement uint in var)
SYMBOLS['$im_u32$'                    ] = ['ImU32',      'int',  lambda param: f'{param}'] ## <-- FIXME: unsigned int incompatable (implement uint in var)

## -----------------------------------------------------------------------------------------------------------------------------------

## DEFAULT:    KEY          = [IMGUI_SUMBOL,       VAR_VERSION                                                                            ]
SYMBOLS['$NXLL$'          ] = ['NULL',             'nullptr'                                                                              ]
SYMBOLS['$vec2_0$'        ] = ['ImVec2(0,0)',      'newptr<Vec2>(0.f,0.f)'                                                                ]
SYMBOLS['$vec2_0_$'       ] = ['ImVec2(0, 0)',     'newptr<Vec2>(0.f,0.f)'                                                                ]
SYMBOLS['$vec2_1$'        ] = ['ImVec2(1,1)',      'newptr<Vec2>(1.f,1.f)'                                                                ]
SYMBOLS['$vec2_1_$'       ] = ['ImVec2(1, 1)',     'newptr<Vec2>(1.f,1.f)'                                                                ]
SYMBOLS['$vec2_n10$'      ] = ['ImVec2(-1,0)',     'newptr<Vec2>(-1.f,0.f)'                                                               ]
SYMBOLS['$vec4_0$'        ] = ['ImVec4(0,0,0,0)',  'newptr<Vec4>(0.f,0.f,0.f,0.f)'                                                        ]
SYMBOLS['$vec4_1$'        ] = ['ImVec4(1,1,1,1)',  'newptr<Vec4>(1.f,1.f,1.f,1.f)'                                                        ]


## TYPES : _p = pointe, _r = reference
# KEY                       = [IMGUI_SYMBOL,         VAR_VERSION,          PARAM_CAST_TO_IMGUI                                            ]
SYMBOLS['$const_cXXX_p$'  ] = ['const char* const', 'const String&',      lambda param : f'{param}.c_str()'                               ]
SYMBOLS['$const_cXXX_p_$' ] = ['const char*',       'const String&',      lambda param : f'{param}.c_str()'                               ]
#SYMBOLS['$bXXl_p$'       ] = ['bool*',             'var&/*bool*/',       lambda param : f'{param}.operator bool*()'                      ]
SYMBOLS['$uiXt_p$'        ] = ['unsigned int*',     'int64_t*',           lambda param : f'(unsigned int*){param}'                        ] ## FIXME:
SYMBOLS['$uiXt$'          ] = ['unsigned int',      'int',                lambda param : f'{param}'                                       ] ## FIXME:
SYMBOLS['$iXt_p$'         ] = ['int*',              'int64_t*',           lambda param : f'(int*){param}'                                 ] ## FIXME:
SYMBOLS['$const_flXXt_p$' ] = ['const float*',      'const double*',      lambda param : f'(const float*){param}'                         ] ## FIXME:
SYMBOLS['$flXXt_p$'       ] = ['float*',            'double*',            lambda param : f'(float*){param}'                               ] ## FIXME:
SYMBOLS['$flXXt_r$'       ] = ['float&',            'double&',            lambda param : f'*(float*)&({param})'                           ] ## FIXME:

## need to add the ' col' by the user (casting to color is for better error message)
SYMBOLS['$col@float_col3$ col' ] = ['float col[3]', 'ptr<Color>',      lambda param : f'(float*){param}->get_data()'                      ]
SYMBOLS['$col@float_col4$ col' ] = ['float col[4]', 'ptr<Color>',      lambda param : f'(float*){param}->get_data()'                      ]

## need to add the ' v' by the user
SYMBOLS['$v@float_v2$ v'  ] = ['float v[2]',       'ptr<Vec2>',        lambda param : f'(float*){param}->get_data()'                      ]
SYMBOLS['$v@float_v3$ v'  ] = ['float v[3]',       'ptr<Vec3>',        lambda param : f'(float*){param}->get_data()'                      ]
SYMBOLS['$v@float_v4$ v'  ] = ['float v[4]',       'ptr<Vec4>',        lambda param : f'(float*){param}->get_data()'                      ]

## need to add the ' v' by the user
SYMBOLS['$v@int_v2$ v'    ] = ['int v[2]',         'ptr<Vec2i>',       lambda param : f'(int*){param}->get_data()'                        ]
SYMBOLS['$v@int_v3$ v'    ] = ['int v[3]',         'ptr<Vec3i>',       lambda param : f'(int*){param}->get_data()'                        ]
SYMBOLS['$v@int_v4$ v'    ] = ['int v[4]',         'ptr<Vec4i>',       lambda param : f'(int*){param}->get_data()'                        ]

SYMBOLS['$const_vec2_r$'  ] = ['const ImVec2&',    'ptr<Vec2>',         lambda param : f'*{param}'                                        ]
SYMBOLS['$const_vec2_p$'  ] = ['const ImVec2*',    'ptr<Vec2>',         lambda param : f'&{param}->operator ImVec2&()'                    ]
SYMBOLS['$vec2_r$'        ] = ['ImVec2&',          'ptr<Vec2>',         lambda param : f'*{param}'                                        ]
SYMBOLS['$vec2$'          ] = ['ImVec2',           'ptr<Vec2>',         lambda param : f'*{param}',         lambda ret : f'newptr<Vec2>({ret})'  ]

SYMBOLS['$const_vec4_r$'  ] = ['const ImVec4&',    'ptr<Vec4>',        lambda param : f'*{param}',          lambda ret : f'newptr<Vec4>({ret})'  ]
SYMBOLS['$const_vec4_p$'  ] = ['const ImVec4*',    'ptr<Vec4>',        lambda param : f'&{param}->operator ImVec4&()'  ]
SYMBOLS['$vec4&$'         ] = ['ImVec4&',          'ptr<Vec4>',        lambda param : f'*{param}',          lambda ret : f'newptr<Vec4>({ret})'  ]
SYMBOLS['$vec4$'          ] = ['ImVec4',           'ptr<Vec4>',        lambda param : f'*{param}',          lambda ret : f'newptr<Vec4>({ret})'  ]


