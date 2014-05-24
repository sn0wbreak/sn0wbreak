#!/bin/bash
cud=`dirname $0`
sbd="$HOME/.sn0wbreak"
echo "Please make sure your device is connected and in DFU mode, if you haven't done it yet, please identify your device first, before entering DFU mode. Press enter to continue..."
read NULL
echo "Starting ssh_rd..."
java -jar $sbd/ssh_rd.jar > /tmp/rd.log 2>> /tmp/rd.log &
echo "I'll wait 30 seconds now for ssh_rd..."
sleep 30
function executecmd()
{
$sbd/sshpass -p alpine ssh root@localhost -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -p 2022 $@
}
function transferfile()
{
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $1 root@localhost:$2
}
echo -n "Waiting for ssh_rd... "
executecmd echo " [OK]"
echo "Mounting fs..."
executecmd "while [ ! -d /mnt1/etc ]; do mount.sh; done"
echo " [OK]"
echo -n "Copying tar binary..."
transferfile $sbd/tar /bin
echo " [OK]"
echo -n "Copying cp binary..."
transferfile $sbd/cp /bin
echo " [OK]"
echo -n "Copying basic cydia bundle from p0sixspwn..."
transferfile $sbd/Cydia.tar /mnt1
echo " [OK]"
#echo -n "Copying ssh..."
#transferfile $sbd/ssh.tar /mnt1
#echo " [OK]"
echo -n "Uploading fstab..."
transferfile $sbd/fstab /mnt1/etc
echo " [OK]"
echo -n "Extracting bundle..."
executecmd "cd /mnt1 && tar xvf Cydia.tar"
echo " [OK]"
echo -n "Cleaning up..."
executecmd "rm -rf /mnt1/Cydia.tar /mnt2/mobile/Library/Caches/com.apple.mobile.installation.plist"
echo " [OK]"
echo -n "Moving dpkg structure to user partition..."
executecmd "mv /mnt1/var/* /mnt2"
echo " [OK]"
echo "Applying semitether..."
transferfile $sbd/dirhelper /mnt1/usr/libexec
echo " [OK]"
echo -n "Setting nvram variables and rebooting..."
executecmd nvram auto-boot=true
executecmd reboot_bak
echo " [OK]"
php $cud/sshkiller.php
echo "Done, please put your device into DFU mode again, we'll now boot it for the first time, press enter to continue..."
echo > $sbd/jbd
read NULL
$cud/boot.sh
