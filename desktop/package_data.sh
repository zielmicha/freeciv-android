#!/bin/bash
tar -czvf dist/data.tgz -C .. data fonts
md5sum dist/data.tgz > dist/version
