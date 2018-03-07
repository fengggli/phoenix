Configuration for QEMU

## what's new
0. the default qemu (v2.5) in ubuntu, I cannot set physical/logical block size from 512 to 4k for -drive=nvme
1. 2.11 has better support for better nvme
3. I also want to have it installed in non-root

## install

```shell
## configure
./configure --prefix=/home/lifeng/software/install/
sudo apt-get install git libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev
make -j4
make install
```

## Configuration
1. I use libvirt to hypervise qemu/kvm, the configuration file is in docs/copager/ubuntu1604\_libvirt.xml
2. I haven't sucessed to use 4k block size for qemu, descripted [here](https://stackoverflow.com/questions/49157684/setting-4k-block-size-for-nvme-in-qemu)

## useful


