#!/bin/bash
# use ssh lifeng@locahost -p 2222 to connect
QEMU_EXE="/home/lifeng/software/install/bin/qemu-system-x86_64"
SYSTEM_IMG="/var/lib/libvirt/images/ubuntu1604.qcow2"
NVME_IMG="./nvme_8G.img"
$QEMU_EXE -m 2G \
                   -machine q35 \
                   -hda ${SYSTEM_IMG} \
                   -drive file=${NVME_IMG},format=raw,if=none,id=drv0 \
                   -device nvme,drive=drv0,serial=foo,opt_io_size=4096,min_io_size=4096,logical_block_size=4096,physical_block_size=4096 \
                   -smp 4 \
                   -enable-kvm \
                   -net nic \
                   -net user,hostfwd=tcp::2222-:22

                   #-vga std \
                   #-nographic \
                   #-nographic -serial mon:stdio \
                   #-cpu Broadwell \
                   #-fsdev local,id=mdev,path=/home/lifeng,security_model=none \
                   #-device virtio-9p-pci,fsdev=mdev,mount_tag=host_mount \
                #-append 'root=/dev/sda1 console=ttyS0 default_hugepagesz=1G hugepagesz=1G hugepages=4 hugepagesz=2M hugepages=512 intel_iommu=on iommu=pt vfio_iommu_type1.allow_unsafe_interrupts=1' \


