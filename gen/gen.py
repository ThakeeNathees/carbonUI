
try:
	from . import decl_parser
	from .symbols import SYMBOLS
except ImportError:
	import decl_parser
	from symbols import SYMBOLS


SOURCE_PATH = 'source.txt'
WRITE_TO_HEADER = 'ui.gen.h'
WRITE_TO_CPP = 'ui.gen.cpp'
BIND_CLASS = 'ui'

BIND_TEMPLATE = '''\
#pragma once

#include "glfw_imgui.h"

#include "types/vec2.h"
#include "types/vec3.h"
#include "types/vec4.h"

class %s : public Object {
	REGISTER_CLASS(%s, Object) {
%s
	}
public:
%s
};
'''

CPP_TEMPLATE = '''\
#include "ui.gen.h" // <-- TODO: use variable

%s

'''
DECLS = None

import os
def generate(source = SOURCE_PATH, header = WRITE_TO_HEADER, cpp = WRITE_TO_CPP):
	global SOURCE_PATH, WRITE_TO_HEADER, WRITE_TO_CPP
	SOURCE_PATH = source
	WRITE_TO_HEADER = header
	WRITE_TO_CPP = cpp
	main()

def main():

	generate_header()
	generate_cpp()

def should_skip(decl):
	## TODO: implement wrappers for the return type first
	if '*' in decl.ret_mapped or '&' in decl.ret_mapped:
		return True

	## TODO: implement wrappers
	for param in decl.params:
		for illegal in [
			'ImTextureID', 'ImGuiWindowClass', 'ImGuiViewport', 'ImGuiStorage', 'ImFont',
		]:
			if illegal in param.dtype:
				return True
	pass

def generate_header():
	## decl : list of [Comment] and [Decl]
	global DECLS
	DECLS = decl_parser.parse(SOURCE_PATH);

	bindings_str = '\n' ## string of bindings
	decls_str = '\n'    ## string of declarations
	for decl in DECLS:
		## add and skip [Comment]
		if type(decl) == decl_parser.Comment:
			bindings_str += decl.comment + '\n'
			continue

		## map ret
		decl.ret = decl.ret.strip()
		ret_key = decl.ret
		if ret_key[0] == '$':
			if ret_key.startswith('$flag_')  : ret_key = SYMBOLS[ret_key][0]
			elif ret_key.startswith('$v@')     : ret_key = SYMBOLS[ret_key+' v'][1]
			elif ret_key.startswith('$col@')   : ret_key = SYMBOLS[ret_key+' col'][1]
			else                               : ret_key = SYMBOLS[ret_key][1]
		decl.ret_mapped = ret_key
		#print(decl.func)

		if (should_skip(decl)):
			continue

		bind_str = f'\t\tBIND_STATIC_FUNC("{decl.func}", &{BIND_CLASS}::{decl.func}'
		decl_str = f'\tstatic {ret_key} {decl.func.strip()}('

		## params
		for i in range(len(decl.params)):
			if (i == 0):
				bind_str += f', PARAMS("{decl.params[i].name}"'
			else:
				bind_str += f', "{decl.params[i].name}"'
				decl_str += f', '

			## map param
			param_key = decl.params[i].dtype
			if param_key[0] == '$':
				#print(param_key)
				if param_key.startswith('$flag_') : param_key = SYMBOLS[param_key][0]
				elif param_key.startswith('$v@')    : param_key = SYMBOLS[param_key+' v'][1]
				elif param_key.startswith('$col@')  : param_key = SYMBOLS[param_key+' col'][1]
				else                                : param_key = SYMBOLS[param_key][1]
			decl.params[i].dtype_mapped = param_key
			decl_str += f'{param_key} {decl.params[i].name}'

			if i == len(decl.params) - 1:
				bind_str += ')'

		## default values
		first_default = True
		for i in range(len(decl.params)):
			if decl.params[i].default == None: continue

			## map values
			decl_key = decl.params[i].default
			if decl_key[0] == '$':
				#if decl_key.startswith('$v@'): decl_key += ' v'
				decl_key = SYMBOLS[decl_key][1]

			if first_default:
				first_default = False
				bind_str += f', DEFVALUES({decl_key}'
			else:
				bind_str += f', {decl_key}'

			if i == len(decl.params) - 1:
				bind_str += ')'

		bind_str += ');'
		decl_str += ');'
		bindings_str += bind_str + '\n'
		decls_str += decl_str + '\n'

	write(
		BIND_TEMPLATE % (BIND_CLASS, BIND_CLASS, bindings_str, decls_str),
		WRITE_TO_HEADER )


def generate_cpp():

	implementation = ''
	for decl in DECLS:

		if type(decl) == decl_parser.Comment:
			## skip [Comment]
			continue

		if should_skip(decl) :
			continue

		ret_mapped = decl.ret_mapped
		if ret_mapped.startswith('var&'):
			ret_mapped = 'var' + ret_mapped[4:]
		impl_str = f'{decl.ret_mapped} {BIND_CLASS}::{decl.func}('
		for i in range(len(decl.params)):
			if (i != 0):
				impl_str += f', '
				
			impl_str += f'{decl.params[i].dtype_mapped} {decl.params[i].name}'

			#if i == len(decl.params) - 1:
			#	impl_str += ')'
		
		impl_str += ') {\n'

		if decl.ret_mapped  != 'void':
			impl_str += '\treturn '
		ret_stmn =  f'ImGui::{decl.func.rstrip("_")}(' ## TODO: overloaded ends with '_'
		for i in range(len(decl.params)):
			if i != 0: ret_stmn += ', '
			param_key = decl.params[i].dtype
			param_arg = decl.params[i].name
			if param_key[0] == '$':
				if param_key.startswith('$flag_') : pass
				elif param_key.startswith('$v@')    : param_arg = SYMBOLS[param_key+' v'][2](param_arg)
				elif param_key.startswith('$col@')  : param_arg = SYMBOLS[param_key+' col'][2](param_arg)
				else                                : param_arg = SYMBOLS[param_key][2](param_arg)
			ret_stmn += f'{param_arg}'
		ret_stmn += ')'

		if decl.ret in SYMBOLS.keys() and SYMBOLS[decl.ret].__len__() >= 4:
			ret_stmn = SYMBOLS[decl.ret.strip()][3](ret_stmn)

		impl_str += '\t' + ret_stmn + ';'
		impl_str += '\n}'

		implementation += impl_str + '\n\n'

	write(
		CPP_TEMPLATE % (implementation), WRITE_TO_CPP )

	pass


def write(text, to):
	with open(to, 'w') as file:
		file.write(text)


import sys
if __name__ == '__main__':
	generate(*sys.argv[1:])