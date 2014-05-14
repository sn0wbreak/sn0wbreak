#!/bin/bash
cud=`dirname $0`
device=`$cud/info.sh device`
version=`$cud/info.sh iOS`
buildid=`$cud/info.sh build`
echo -n "$device"
echo -n "_"
echo -n "$version"
echo -n "_"
echo -n "$buildid.plist"
