#!/bin/bash
#
#Runs QEMU with the specified BIOS image
#
#

if [ $# -ne 1 ]; then
	echo "You must inform the ovmf image name to run, usage:"
	echo "$0 <ovmf firmware image name>"
	exit 1
fi

FIRMWARE="-drive file=$1,format=raw,if=pflash"
DRIVE="-drive file=fat:rw:hda"
NETWORK="-net nic -net user"
MACHINE="-m 1G"

qemu-system-x86_64 $MACHINE $FIRMWARE $DRIVE $NETWORK
