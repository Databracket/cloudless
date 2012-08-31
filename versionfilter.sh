#!/bin/sh

# A script to help Doxygen extract the latest revision
# of a given file from git.

if [ ! -f "$1" ]; then
	exit 1
else
	git log -n1 --format=%H $1
fi
