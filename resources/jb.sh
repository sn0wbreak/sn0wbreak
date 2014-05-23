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
executecmd "while [ ! -d /mnt1/etc ]; do mount.sh; done"
echo " [OK]"
echo -n "Copying tar binray..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/tar root@localhost:/bin/
echo " [OK]"
echo -n "Copying basic cydia bundle from p0sixspwn, 1/2..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/mnt1.tar root@localhost:/mnt1/
echo " [OK]"
echo -n "Copying basic cydia bundle from p0sixspwn, 2/2..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/mnt2.tar root@localhost:/mnt12
echo " [OK]"
echo -n "Copying ssh..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/ssh.tar root@localhost:/mnt1/
echo " [OK]"
echo -n "Uploading fstab..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/fstab root@localhost:/mnt1/etc/
echo " [OK]"
echo -n "Extracting bundles..."
executecmd "cd /mnt1 && tar xvf mnt1.tar && tar xvf ssh.tar && cd /mnt2 && tar xvf mnt2.tar"
echo " [OK]"
echo -n "Removing old bundles..."
executecmd "rm -rf /mnt1/mnt1.tar /mnt1/ssh.tar /mnt2/mnt2.tar"
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
