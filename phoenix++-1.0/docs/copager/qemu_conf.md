Configuration for QEMU

## what's new
0. now use qemu-nvme, see scripts/run\_qemu.sh for more detail
0. the default qemu (v2.5) in ubuntu, I cannot set physical/logical block size from 512 to 4k for -drive=nvme
1. 2.11 has better support for better nvme, but 4k block still doesn't work
3. I also want to have it installed in non-root

## install
how to build qemu, go to official page
```shell
## configure
# prerequisite
sudo apt-get install git libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev

# virfs suport
sudo apt-get install libcap-dev libattr1-dev

# for stock version:
./configure --enable-virtfs --prefix=/home/lifeng/software/install/

# for qemu-nvme
./configure --enable-virtfs --extra-cflags=-w --enable-linux-aio --target-list=x86_64-softmmu --enable-kvm --prefix=/home/lifeng/software/install-qemu-nvme/ &>config.lifen.log

make -j4
make install
```

## Configuration
0. use SandyBridge

## deprecated:
1. I use libvirt to hypervise qemu/kvm, the configuration file is in docs/copager/ubuntu1604\_libvirt.xml
2. I haven't sucessed to use 4k block size for qemu, descripted [here](https://stackoverflow.com/questions/49157684/setting-4k-block-size-for-nvme-in-qemu)




