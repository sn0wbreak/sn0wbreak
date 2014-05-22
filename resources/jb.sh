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
echo -n "Waiting for ssh_rd... "
executecmd echo " [OK]"
echo "Mounting fs..."
executecmd "mount.sh"
echo " [ OK]"
echo -n "Copying tar binray..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/tar root@localhost:/bin/
echo " [OK]"
echo -n "Copying basic cydia bundle from p0sixspwn..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/Cydia.tar root@localhost:/mnt1/
echo " [OK]"
echo -n "Extracting bundle..."
executecmd "cd /mnt1 && tar xf Cydia.tar"
echo " [OK]"
echo -n "Removing bundle archive..."
executecmd rm -rf /mnt1/Cydia.tar
echo " [OK]"
echo -n "Creating temporary directory..."
executecmd mkdir /tmp
echo " [OK]"
echo "Applying semitether..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/dirhelper root@localhost:/mnt1/usr/libexec
echo " [OK]"
echo -n "Setting nvram variables and rebooting..."
executecmd nvram auto-boot=true
executecmd reboot_bak
echo " [OK]"
php $cud/sshkiller.php
echo "Done, please put your device into DFU mode again, we'll now boot it for the first time, press enter to continue..."
read NULL
$cud/boot.sh
