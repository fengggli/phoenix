Configuration for QEMU

## what's new
0. the default qemu (v2.5) in ubuntu, I cannot set physical/logical block size from 512 to 4k for -drive=nvme
1. 2.11 has better support for better nvme
3. I also want to have it installed in non-root

## install

```shell
./configure --prefix=/home/lifeng/software
sudo apt-get install zlib1g-dev
# error: ERROR: glib-2.22 gthread-2.0 is required to compile QEMU
```
