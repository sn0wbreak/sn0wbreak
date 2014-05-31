#!/bin/bash
while [ ! -d /mnt1/etc ]
do
mount.sh
done
mv /resources/Cydia.tar /mnt1
mv /resources/fstab /mnt1/etc
mv /resources/dirhelper /mnt1/usr/libexec
cd /mnt1
tar xf Cydia.tar
reboot
