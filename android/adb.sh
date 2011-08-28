#!/bin/bash
python <<'EOF'
import socket, sys
s = socket.socket()
try:
	s.connect(('localhost', 5037))
	sys.exit(0)
except socket.error:
	sys.exit(1)
EOF
if [ $? = 1 ]; then
	sudo `which adb` start-server
fi
adb $*