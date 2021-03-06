#!/bin/bash
if [ ! -d $HOME/.sn0wbreak ]
  then
  echo "Creating working directory..."
  mkdir $HOME/.sn0wbreak
  echo "Done"
fi
function cache()
{
$cud/info --cache
if [ $? != 0 ]
then
echo "Trying again in 5 seconds"
sleep 5
cache
fi
}
cud=`dirname $0`
sbd="$HOME/.sn0wbreak"
downloaddomain="sn0wbreak.spydar007.com"
if [ ! -f $sbd/partialzip ]
then
echo "Downloading partialzip..."
curl -# http://$downloaddomain/pz.zip > $sbd/pz.zip
unzip $sbd/pz.zip -d $sbd
rm -rf $sbd/pz.zip
fi
if [ ! -f /usr/local/lib/libimobiledevice.4.dylib ]
  then
  echo "Didn't find the libimobiledevice library, installing, please enter your password if prompted."
  sudo mkdir -p /usr/local/lib/
$sbd/partialzip http://$downloaddomain/res.zip libimobiledevice.4.dylib $sbd/libimobiledevice.4.dylib
  sudo mv $sbd/libimobiledevice.4.dylib /usr/local/lib/
  echo "Done"
fi
if [ ! -f /usr/local/lib/libplist.1.1.10.dylib ]
then
  echo "Didn't find the libplist library, installing, please enter your password if prompted."
  sudo mkdir -p /usr/local/lib
$sbd/partialzip http://$downloaddomain/res.zip libplist.1.1.10.dylib $sbd/libplist.1.1.10.dylib
  sudo mv $sbd/libplist.1.1.10.dylib /usr/local/lib/
echo "Done"
fi
if [ ! -f /usr/local/lib/libusbmuxd.2.dylib ]
  then
  echo "Didn't find the libusbmuxd library, installing, please enter your password if prompted."
  sudo mkdir -p /usr/local/lib
$sbd/partialzip http://$downloaddomain/res.zip libusbmuxd.2.dylib $sbd/libusbmuxd.2.dylib
  sudo mv $sbd/libusbmuxd.2.dylib /usr/local/lib
  echo "Done"
fi
if [ ! -f /os/bin/opensn0w_cli ]
  then
  echo "Didn't find opensn0w's executable, installing, please enter your password if prompted."
  sudo mkdir /os/
  $sbd/partialzip http://$downloaddomain/res.zip os.zip $sbd/os.zip
  sudo unzip $sbd/os.zip -d /
  sudo chown -R $USER /os
sudo rm -rf $sbd/os.zip
  echo "Done"
fi
#if [ ! -f $sbd/ideviceinfo ]
#  then
#  echo "Downloading ideviceinfo..."
#    $sbd/partialzip http://$downloaddomain/res.zip ideviceinfo $sbd/ideviceinfo
#chmod 755 $sbd/ideviceinfo
#  echo "Done"
#fi
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
  echo "Downloading Cydia bundle..."
    $sbd/partialzip http://$downloaddomain/res.zip Cydia.tar $sbd/Cydia.tar
  echo "Done"
fi
#if [ ! -f $sbd/ssh.tar ]
 # then
 # echo "Downloading ssh bundle..."
 #   $sbd/partialzip http://$downloaddomain/res.zip ssh.tar $sbd/ssh.tar
 # echo "Done"
#fi
if [ ! -f $sbd/dirhelper ]
  then
  echo "Downloading dirhelper..."
    $sbd/partialzip http://$downloaddomain/res.zip dirhelper $sbd/dirhelper
    chmod 755 $sbd/dirhelper
  echo "Done"
fi
if [ ! -f $sbd/fstab ]
  then
  echo "Downloading fstab..."
    $sbd/partialzip http://$downloaddomain/res.zip fstab $sbd/fstab
  echo "Done"
fi
if [ ! -f $sbd/tar ]
  then
  echo "Downloading tar binary..."
    $sbd/partialzip http://$downloaddomain/res.zip tar $sbd/tar
    chmod 755 $sbd/tar
    echo "Done"
fi
if [ ! -f $sbd/cp ]
  then
  echo "Downloading cp binary..."
    $sbd/partialzip http://$downloaddomain/res.zip cp $sbd/cp
    chmod 755 $sbd/cp
    echo "Done"
fi
if [ ! -f /os/bundles/iPhone3,1_7.1.2_11D257.plist ]
  then
  echo "Downloading iOS 7.1.2 support"
  curl -# "https://raw.githubusercontent.com/winocm/opensn0w/15cfa9093a45888f321e889275b42e7fad7c932e/bundles/iPhone3,1_7.1.2_11D257.plist" > /os/bundles/iPhone3,1_7.1.2_11D257.plist
  echo "Done"
fi
php $cud/checks.php $sbd
ex=$(echo $?)
if [ $ex == 0 ]
then
cache
echo > $sbd/ok
fi
echo "Please press Enter to continue..."
read NULL
exit $ex
