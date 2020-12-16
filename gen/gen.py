
import decl_parser
from symbols import SYMBOLS

BIND_CLASS = 'ui'
WRITE_TO_HEADER = 'ui.gen.h'
WRITE_TO_CPP = 'ui.gen.cpp'
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

def main():
	generate_header()
	generate_cpp()

def generate_header():
	## decl : list of [Comment] and [Decl]
	global DECLS
	DECLS = decl_parser.parse();

	bindings_str = '\n' ## string of bindings
	decls_str = '\n'    ## string of declarations
	for decl in DECLS:
		## add and skip [Comment]
		if type(decl) == decl_parser.Comment:
			bindings_str += decl.comment + '\n'
			continue

		## map ret
		ret_key = decl.ret.strip()
		if ret_key[0] == '$':
			if ret_key == '$im_id$'            : ret_key = SYMBOLS[ret_key][0]
			elif ret_key.startswith('$flag_')  : ret_key = SYMBOLS[ret_key][0]
			elif ret_key.startswith('$v@')     : ret_key = SYMBOLS[ret_key+' v'][1]
			elif ret_key.startswith('$col@')   : ret_key = SYMBOLS[ret_key+' col'][1]
			else                               : ret_key = SYMBOLS[ret_key][1]
		decl.ret_mapped = ret_key
		#print(decl.func)

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
				if param_key == '$im_id$'           : param_key = SYMBOLS[param_key][0]
				elif param_key.startswith('$flag_') : param_key = SYMBOLS[param_key][0]
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

		impl_str = f'{decl.ret_mapped} {BIND_CLASS}::{decl.func}('
		for i in range(len(decl.params)):
			if (i != 0):
				impl_str += f', '
				
			impl_str += f'{decl.params[i].dtype_mapped} {decl.params[i].name}'

			if i == len(decl.params) - 1:
				impl_str += ')'
		
		impl_str += ') {\n'

		#if decl.ret_mapped  == 'void':
		impl_str +=  f'\treturn ImGui::{decl.func}('
		for i in range(len(decl.params)):
			if i != 0: impl_str += ', '
			param_key = decl.params[i].dtype
			param_arg = decl.params[i].name
			if param_key[0] == '$':
				if param_key == '$im_id$'           : pass
				elif param_key.startswith('$flag_') : pass
				elif param_key.startswith('$v@')    : param_arg = SYMBOLS[param_key+' v'][2](param_arg)
				elif param_key.startswith('$col@')  : param_arg = SYMBOLS[param_key+' col'][2](param_arg)
				else                                : param_arg = SYMBOLS[param_key][2](param_arg)
			impl_str += f'{param_arg}'
		impl_str += ');\n}'

		implementation += impl_str + '\n\n'

	write(
		CPP_TEMPLATE % (implementation), WRITE_TO_CPP )

	pass


def write(text, to):
	with open(to, 'w') as file:
		file.write(text)

if __name__ == '__main__':
	main()