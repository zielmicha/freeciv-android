#!/bin/bash
make -C .. data/techtree.index
tar -czvf dist/data.tgz -C .. data fonts
md5sum dist/data.tgz > dist/version
