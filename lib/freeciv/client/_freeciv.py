# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
import os

if os.environ.get('RPC'):
    import clientrpc as client
else:
    import clientnative as client

for name in ['get_overview_size', 'register',
             'const', 'callback', 'func', 'run',
             'server_side']:
    globals()[name] = getattr(client, name)
