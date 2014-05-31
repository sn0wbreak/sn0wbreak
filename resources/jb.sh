#!/bin/bash
cud=`dirname $0`
sbd="$HOME/.sn0wbreak"
echo "Please identify your device first and then enter DFU Mode. Press Enter to continue..."
read NULL
echo "Starting ssh_rd..."
java -jar $sbd/ssh_rd.jar > /tmp/rd.log 2>> /tmp/rd.log &
echo "Waiting for ssh_rd..."
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
executecmd echo "Done"
echo "Mounting rootfs..."
executecmd "while [ ! -d /mnt1/etc ]; do mount.sh; done"
echo "Done"
echo -n "Copying tar binary..."
transferfile $sbd/tar /bin
echo "Done"
echo -n "Copying cp binary..."
transferfile $sbd/cp /bin
echo "Done"
echo -n "Copying basic cydia bundle..."
transferfile $sbd/Cydia.tar /mnt1
echo "Done"
#echo -n "Copying ssh..."
#transferfile $sbd/ssh.tar /mnt1
#echo " [OK]"
echo -n "Uploading fstab..."
transferfile $sbd/fstab /mnt1/etc
echo "Done"
echo -n "Extracting bundle..."
executecmd "cd /mnt1 && tar xvf Cydia.tar"
echo "Done"
echo -n "Cleaning up..."
executecmd "rm -rf /mnt1/Cydia.tar /mnt2/mobile/Library/Caches/com.apple.mobile.installation.plist"
echo "Done"
echo -n "Moving dpkg structure to user partition..."
executecmd "mv /mnt1/var/* /mnt2"
echo "Done"
echo "Applying Semi-Tether..."
transferfile $sbd/dirhelper /mnt1/usr/libexec
echo "Done"
echo -n "Setting nvram variables and rebooting..."
executecmd nvram auto-boot=true
executecmd reboot_bak
echo "Done"
php $cud/sshkiller.php
echo "Done, please put your device into DFU mode again and then press Enter to continue..."
echo > $sbd/jbd
read NULL
$cud/info --boot
