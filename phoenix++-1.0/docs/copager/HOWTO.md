How to run Phoenix-copager

## preparations
1. setting vm as in scripts/run\_qemu.sh(ubuntu1604, 2G ram with 4 cpus)

## swap on NVMe
Original contents from [here](https://wiki.archlinux.org/index.php/swap#Automated)
1. make swap partition
```
sudo mkswap /dev/nvme0n1
```
2. enable the device for paging
```
sudo swapon /dev/nvme0n1
```
3. check current swap
```
lifeng@node0:~$ swapon --show
NAME         TYPE      SIZE USED PRIO
/dev/sda5    partition   2G   0B   -1
/dev/nvme0n1 partition   8G   0B   -2
```
4. disable the other swap areas(if any)
```
sudo swapoff /dev/sda5
```
5. set swapiness
```shell
# you can also change this in /etc/sysctl.d/99-sysctl.conf
sysctl vm.swappiness=1
```
