#!/bin/sh

VERSION_FILE=cloudless/version.hpp

if [ ! -f $VERSION_FILE ]; then
    echo "version.sh: error: $VERSION_FILE does not exist" 1>&2
    exit 1
fi

MAJOR=`egrep '^#define +CLOUDLESS_VERSION_MAJOR +[0-9]+$' $VERSION_FILE`
MINOR=`egrep '^#define +CLOUDLESS_VERSION_MINOR +[0-9]+$' $VERSION_FILE`
PATCH=`egrep '^#define +CLOUDLESS_VERSION_PATCH +[0-9]+$' $VERSION_FILE`

if [ -z "$MAJOR" -o -z "$MINOR" -o -z "$PATCH" ]; then
    echo "version.sh: error: could not extract version from $VERSION_FILE" 1>&2
    exit 1
fi

MAJOR=`echo $MAJOR | awk '{ print $3 }'`
MINOR=`echo $MINOR | awk '{ print $3 }'`
PATCH=`echo $PATCH | awk '{ print $3 }'`

echo -n $MAJOR.$MINOR.$PATCH
