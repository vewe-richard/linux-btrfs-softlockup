#!/bin/bash
set -e
make -C /lib/modules/`uname -r`/build M=$(pwd) modules
sudo umount /dev/loop0
sudo rmmod btrfs
sudo insmod ./btrfs.ko
sudo mkfs.btrfs -f /dev/loop0
sudo mount /dev/loop0 /home/ec2-user/linux/mountpoint/
sudo chown ec2-user:ec2-user -R ../../mountpoint/
touch ../../mountpoint/run-parts
echo "first read"
../../readbash ../../mountpoint/run-parts
exit
echo "second read"
../../readbash ../../mountpoint/run-parts
