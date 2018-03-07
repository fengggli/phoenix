Reference for nvme device

you should have nvme-cli installed

## list nvme devices
```
sudo nvme list
```

## format
```
sudo nvme format /dev/nvme0n1
```
Notes; if "oacs=0", you cannot use format for your nvme controller

## id-ns and id ctrol
```shell
sudo nvme id-ns /dev/nvme0n1
sudo nvme id-ctrl /dev/nvme0n1
```

## other useful info
1. [openchannel ssd](https://openchannelssd.readthedocs.io/en/latest/)
2. [a better qemu for nvme](https://github.com/OpenChannelSSD/qemu-nvme/)
3. a summary of nvme from [smart tool](https://www.smartmontools.org/wiki/NVMe_Support)

