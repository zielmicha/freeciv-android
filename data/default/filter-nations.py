import os
import sys
out = open('nations.ruleset', 'w')
for line in open('nations.ruleset-'):
	if line.startswith('*include "nation'):
		name = line.split('"')[1]
		if os.path.exists('../' + name):
			out.write(line)
	else:
		out.write(line)
