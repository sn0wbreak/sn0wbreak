#!/bin/bash
if [ ! -d $HOME/.sn0wbreak ]
  then
  mkdir $HOME/.sn0wbreak
  echo "created working directory"
fi
cud=`dirname $0`
sbd="$HOME/.sn0wbreak"
downloaddomain="localhost"
if [ ! -f $sbd/partialzip ]
then
echo "Downloading partialzip..."
curl http://$downloaddomain/pz.zip > $sbd/pz.zip
unzip $sbd/pz.zip -d $sbd
rm -rf $sbd/pz.zip
fi
if [ ! -f /usr/local/Cellar/libimobiledevice/1.1.5_2/lib/libimobiledevice.4.dylib ]
  then
  echo "Didn't find the libimobiledevice library in the excepted place in your system, so we'll have to install it, please enter your password when prompted."
  sudo mkdir -p /usr/local/Cellar/libimobiledevice/1.1.5_2/lib/
$sbd/partialzip http://$downloaddomain/res.zip libimobiledevice.4.dylib $sbd/libimobiledevice.4.dylib
  sudo mv $sbd/libimobiledevice.4.dylib /usr/local/Cellar/libimobiledevice/1.1.5_2/lib/
  echo "Done"
fi
if [ ! -f /usr/local/lib/libplist.1.1.10.dylib ]
then
  echo "Didn't find the libplist library in the excepted place in your system, so we'll have to install it, please enter your password when prompted."
  sudo mkdir -p /usr/local/lib
$sbd/partialzip http://$downloaddomain/res.zip libplist.1.1.10.dylib $sbd/libplist.1.1.10.dylib
  sudo mv $sbd/libplist.1.1.10.dylib /usr/local/lib/
echo "Done"
fi
if [ ! -f /usr/local/lib/libusbmuxd.2.dylib ]
  then
  echo "Didn't find the libusbmuxd library in the excepted place in your system, so we'll have to install it, please enter your password when prompted."
  sudo mkdir -p /usr/local/lib
$sbd/partialzip http://$downloaddomain/res.zip libusbmuxd.2.dylib $sbd/libusbmuxd.2.dylib
  sudo mv $sbd/libusbmuxd.2.dylib /usr/local/lib
  echo "Done"
fi
if [ ! -f /os/bin/opensn0w_cli ]
  then
  echo "Didn't find opensn0w's executable, installing it, please enter your password when prompted."
  sudo mkdir /os/
  $sbd/partialzip http://$downloaddomain/res.zip os.zip $sbd/os.zip
  sudo unzip $sbd/os.zip -d /
  sudo chown -R $USER /os
sudo rm -rf $sbd/os.zip
  echo "Done"
fi
if [ ! -f $sbd/ideviceinfo ]
  then
  echo "Downloading ideviceinfo..."
    $sbd/partialzip http://$downloaddomain/res.zip ideviceinfo $sbd/ideviceinfo
chmod 755 $sbd/ideviceinfo
  echo "Done"
fi
if [ ! -f $sbd/sshpass ]
  then
  echo "Downloading sshpass..."
    $sbd/partialzip http://$downloaddomain/res.zip sshpass $sbd/sshpass
chmod 755 $sbd/sshpass
  echo "Done"
fi
if [ ! -f $sbd/ssh_rd.jar ]
  then
  echo "Downloading ssh_rd..."
    $sbd/partialzip http://$downloaddomain/res.zip ssh_rd.jar $sbd/ssh_rd.jar
  echo "Done"
fi
if [ ! -f $sbd/Cydia.tar ]
  then
  echo "Downloading cydia bundle..."
    $sbd/partialzip http://$downloaddomain/res.zip Cydia.tar $sbd/Cydia.tar
  echo "Done"
fi
if [ ! -f $sbd/stether.tar ]
  then
  echo "Downloading SemiTether bundle..."
    $sbd/partialzip http://$downloaddomain/res.zip stether.tar $sbd/stether.tar
  echo "Done"
fi
if [ ! -f $sbd/tar ]
  then
  echo "Downloading tar binary..."
    $sbd/partialzip http://$downloaddomain/res.zip tar $sbd/tar
    chmod 755 $sbd/tar
    echo "Done"
fi
php $cud/checks.php $sbd
ex=$(echo $?)
if [ $ex == 0 ]
then
$cud/info.sh identify
echo > $sbd/ok
fi
echo "Please press enter"
read NULL
exit $ex
