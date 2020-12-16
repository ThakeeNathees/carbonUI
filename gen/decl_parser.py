
import re

import symbols

PATTERN_DECLARATION = '''(?P<ret>.*?)\ (?P<func>[a-zA-Z_][a-zA-Z_\d]*)\((?P<params>.*[,\)])?;'''
REPLACE = symbols.REPLACE

class Comment:
	def __init__(self, comment):
		self.comment = comment

class Decl:
	def __init__(self, ret, func, params):
		self.ret = ret;
		self.func = func;
		self.params = params ## list of Param

	def __str__(self):
		return f'{self.ret} {self.func} {self.params}'

class Param:
	def __init__(self, dtype, name, default):
		self.dtype = dtype;
		self.name = name;
		self.default = default

	def __repr__(self):
		return self.__str__();
	def __str__(self):
		return f'{self.name} {self.dtype} = {self.default}'

def parse():
	SOURCE = [] ## list of lines(str) and [Comment] for grouping
	with open('source.txt', 'r') as file:
		group_comment = ''

		for line in file.readlines():

			if line.strip().startswith('//'):
				group_comment += '\n\t\t' + line.strip()
			else:
				## remove trailing comments (they are evil for the regex)
				line = re.sub('\s*//.*', '', line)

				if group_comment:
					SOURCE.append(Comment(group_comment))
					group_comment = ''

				## skip func(...) and func(va_list) <-- can't bind those
				## TODO: find a way to bind them (maybe)
				if 'IM_FMTARGS' in line or 'IM_FMTLIST' in line:
					continue
				SOURCE.append(line.strip())
	
	for i in range(len(SOURCE)):
		if type(SOURCE[i]) == Comment: continue
		for replace in REPLACE:
			SOURCE[i] = SOURCE[i].replace(replace[0], replace[1])

	
	data = [] ## list of [Decl] and [Comment]
	
	for i in range(len(SOURCE)):

		## add and skip comment
		if type(SOURCE[i]) == Comment:
			data.append(SOURCE[i])
			continue

		## build [Decl] from string using regex
		for match in re.finditer(PATTERN_DECLARATION, SOURCE[i], re.VERBOSE):
			groupdict = match.groupdict()
			decl = Decl(groupdict['ret'], groupdict['func'], [])

			for param_str in groupdict['params'][:-1].split(','):
				if not param_str : continue
				param = Param(None, None, None)
				if '=' in param_str:
					param.default = param_str.split('=')[1].strip()
					param_str = param_str.split('=')[0]
				param.dtype = ' '.join(param_str.split()[:-1])
				param.name = param_str.split()[-1]
				decl.params.append(param)

			data.append(decl)

	return data

	