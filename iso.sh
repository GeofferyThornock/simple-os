#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/primusOS.kernel isodir/boot/primusOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "myos" {
	multiboot /boot/primusOS.kernel
}
EOF
grub-mkrescue -o primusOS.iso isodir
