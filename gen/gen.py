
import decl_parser

BIND_CLASS = 'ui'
WRITE_TO = 'ui.gen.h'
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
// TODO:
};
'''

def main():
	## decl : list of [Comment] and [Decl]
	decls = decl_parser.parse();

	decls_str = '\n' ## string of decl bindings
	for decl in decls:
		
		## add and skip [Comment]
		if type(decl) == decl_parser.Comment:
			decls_str += decl.comment + '\n'
			continue

		decl_str = f'\t\tBIND_STATIC_FUNC("{decl.func}", &{BIND_CLASS}::{decl.func}'

		## params
		for i in range(len(decl.params)):
			if (i == 0):
				decl_str += f', PARAMS("{decl.params[i].name}"'
			else:
				decl_str += f', "{decl.params[i].name}"'

			if i == len(decl.params) - 1:
				decl_str += ')'

		## default values
		first_default = True
		for i in range(len(decl.params)):
			if decl.params[i].default == None: continue
			if first_default:
				first_default = False
				decl_str += f', DEFVALUES({decl.params[i].default}'
			else:
				decl_str += f', {decl.params[i].default}'

			if i == len(decl.params) - 1:
				decl_str += ')'

		decl_str += ');'
		decls_str += decl_str + '\n'

	write(
		BIND_TEMPLATE % (BIND_CLASS, BIND_CLASS, decls_str),
		WRITE_TO)



def write(text, to):
	with open(to, 'w') as file:
		file.write(text)

if __name__ == '__main__':
	main()