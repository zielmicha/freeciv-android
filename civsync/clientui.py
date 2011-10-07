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

import sys
import thread
import os
import urllib
import socket, httplib
import time

def wait_for_close():
    while True:
        if sys.stdin.readline().strip() == 'close':
            print 'exit!'
            os._exit(0)

thread.start_new_thread(wait_for_close, ())

url = sys.argv[1]

while True:
    try:
        urllib.urlopen(url)
    except (socket.error, httplib.InvalidURL, IOError):
        print 'retry...'
        time.sleep(0.5)
    else:
        break


from PyQt4 import QtWebKit, QtCore, QtGui

app = QtGui.QApplication([])
view = QtWebKit.QWebView()
view.setUrl(QtCore.QUrl(url))
view.setWindowTitle('freeciv sync')
view.setSizeIncrement(600, 400)
view.show()
app.exec_()