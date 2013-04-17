import ConfigParser
config = ConfigParser.RawConfigParser()
config.read('default/techs.ruleset')

def strip_t(text):
    return text.strip(' _()""')

techs = {}

for section in config.sections():
    if section == 'datafile': continue
    name = strip_t(config.get(section, 'name'))
    req = [config.get(section, 'req1'), config.get(section, 'req2')]
    req = [ r for r in [ strip_t(r) for r in req ] if r != 'None' ]
    techs[name] = req

print 'digraph technologies {'
for name, reqs in techs.items():
    for req in reqs:
        print '"%s" -> "%s";' % (req, name)
print '}'
