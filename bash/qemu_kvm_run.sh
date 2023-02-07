#!/bin/bash
## help to run the Fedora Cloud image

## meta-data
cat > meta-data <<EOF
instance-id: fedora_cloud
local-hostname: fedora
EOF

## user-data
cat > user-data <<EOF
#cloud-config
# Set the default user
system_info:
  default_user:
    name: fedora

# Unlock the default user
chpasswd:
  list: |
     fedora:fedora
  expire: False

# Other settings
resize_rootfs: True
ssh_pwauth: True
timezone: Asia/Shanghai

# Add any ssh public keys
ssh_authorized_keys:
 - ssh-rsa blahblah...
EOF

## generate seed.iso
genisoimage -output fedora-seed.iso -volid cidata -joliet -rock user-data meta-data

## run qemu-kvm
/usr/bin/qemu-kvm \
        -name fedora-cloud \
        -cpu host \
        -smp 2 \
        -m 4096 \
        -drive file=./Fedora-Cloud-Base-37-1.7.x86_64.qcow2,if=none,id=drive-virtio-disk0,format=qcow2 \
        -cdrom fedora-seed.iso \
        -device virtio-blk-pci,scsi=off,bus=pci.0,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 \
        -nographic -serial mon:stdio \
        -device virtio-net-pci,netdev=user.0 -netdev user,id=user.0,hostfwd=tcp::2222-:22

## ssh the instance
# ssh fedora@localhost -p2222
