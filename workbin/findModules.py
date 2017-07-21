#! /usr/bin/env python
from modulefinder import ModuleFinder
import sys

finder = ModuleFinder()
finder.run_script(sys.argv[1])

finder.report();

sys.exit(0);

print 'Loaded modules:'
for name, mod in finder.modules.iteritems():
    print '%s: ' % name,
    print ','.join(mod.globalnames.keys()[:3])

print '-'*50
print 'Modules not imported:'
print '\n'.join(finder.badmodules.iterkeys())
