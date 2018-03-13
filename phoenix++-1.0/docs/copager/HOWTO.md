How to run Phoenix-copager

# Basic setup
## build Phoenix-copager
Phoenix-copager depends on comanche
Currently pci address of NVme device is hardcoded in PCI_ADDR in allocator/copager/allocator_copager.cc:22, you may want to change it before you build
```shell
mkdir build
cd build

# modify path if needed
cmake -DCOMANCHE_PREFIX:PATH=${HOME}/comanche

```

## prepare dataset
```
# go to project root
cd ../
sh scripts/get_data.sh
```

## prepare comanche
run basic comanche set up, see [here](https://github.com/IBM/comanche/blob/unstable/README.md) for more details.
basically, make sure:
1. xms module is loaded
2. nvme device is attached to VFIO or UIO 
    ```
     sudo ${COMANCHE_HOME}/tools/nvme_setup.sh
    ```
3. hugepages are set:
    ```
     echo 500 > /proc/sys/vm/nr_hugepages
    ```
4. get the pci address
    lspci|grep Non-Volatile

## run test
```
cd test
./kmeans_copager_NVME
```


# Advanced
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
