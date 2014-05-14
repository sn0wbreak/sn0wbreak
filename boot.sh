#!/bin/bash
cud=$(dirname $0)
sbd="$HOME/.sn0wbreak"
device=$($cud/info.sh device)
if [[ $device != iPhone3,* ]]
  then
  echo "Your device isn't an iPhone 4"
  exit 1
fi
/os/bin/opensn0w_cli -p /os/bundles/`$cud/bootplist.sh`
