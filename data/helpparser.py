import pprint
f = open('helpdata.txt')
def read_prop():
	while True:
		line = f.readline()
		if line[0:1] == '[': return None,None
		if not line: return None,None
		if '=' in line: break
	k, rest = line.split('=',1)
	bcount = rest.count('(') - rest.count(')')
	data = rest
	while bcount:
		rest = f.readline()
		if not rest: break
		data += rest
		bcount += rest.count('(') - rest.count(')')
	return k.strip(), data

l = []

while True:
	data = {}
	while True:
		k, v = read_prop()
		if not k: break
		data[k] = v
	if not data:
		break
	l.append(data)

def strip(s):
	return s.strip().strip('_').strip('(').strip(')').strip('"')

for d in l:
	if 'name' not in d: continue
	print '=== %s' % strip(d['name']) 
	#print repr(d['text'])
	for para in d['text'].split('),'):
		u = strip(para)
		u = ''.join( o.rstrip('\\') for o in u.splitlines() )
		u = u.replace('\\n', '\n')
		print u
		print
