#!/bin/bash
cud=`dirname $0`
sbd="$HOME/.sn0wbreak"
function executecmd()
{
$sbd/sshpass -p alpine ssh root@localhost -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -p 2022 $@
}
echo -n "Waiting for ssh_rd... "
executecmd echo " [OK]"
echo -n "Copying basic cydia bundle from p0sixspwn..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/Cydia.tar root@localhost:/mnt1/
echo " [OK]"
echo -n "Extracting bundle..."
executecmd cd /mnt1 && echo tar xf cydia.tar
echo " [OK]"
echo -n "Removing bundle archive..."
executecmd rm -rf /mnt1/Cydia.tar
echo " [OK]"
echo -n "Creating temporary directory..."
executecmd mkdir /tmp
echo " [OK]"
echo "Copying semitether & depencies..."
$sbd/sshpass -p alpine scp -q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -P 2022 $sbd/stether.tar root@localhost:/tmp/
echo " [OK]"
echo -n "Extracting semitether & depencies..."
executecmd cd /tmp && tar xf stether.tar && rm stether.tar
echo " [OK]"
echo -n "Moving files to their places..."
executecmd mv /tmp/dirhelper /mnt1/usr/libexec && mv /tmp/mount /mnt1/sbin && mv /tmp/mount_hfs /mnt1/sbin
echo " [OK]"
echo -n "Creating /etc/rc.d..."
executecmd mkdir /mnt1/etc/rc.d
echo " [OK]"
echo -n "Setting nvram variables and rebooting..."
executecmd nvram auto-boot=true
reboot_bak
echo " [OK]"
killall java
echo "Done"
