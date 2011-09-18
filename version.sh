#!/bin/sh

if [ ! -f include/cloudless.h ]; then
    echo "version.sh: error: include/cloudless.h does not exist" 1>&2
    exit 1
fi

MAJOR=`egrep '^#define +CLOUDLESS_VERSION_MAJOR +[0-9]+$' include/cloudless.h`
MINOR=`egrep '^#define +CLOUDLESS_VERSION_MINOR +[0-9]+$' include/cloudless.h`
PATCH=`egrep '^#define +CLOUDLESS_VERSION_PATCH +[0-9]+$' include/cloudless.h`

if [ -z "$MAJOR" -o -z "$MINOR" -o -z "$PATCH" ]; then
    echo "version.sh: error: could not extract version from include/cloudless.h" 1>&2
    exit 1
fi

MAJOR=`echo $MAJOR | awk '{ print $3 }'`
MINOR=`echo $MINOR | awk '{ print $3 }'`
PATCH=`echo $PATCH | awk '{ print $3 }'`

echo -n $MAJOR.$MINOR.$PATCH
