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

# emulated device:
see scripts/run\_qemu.h
where open channel qemu-nvme is used, [here](https://github.com/OpenChannelSSD/qemu-nvme)


## use tmpfs( I tried use ramdisk to accerlate emulated nvme,no luck)
```
mkdir /var/ramdisk
mount -t tmpfs none /var/ramdisk -o size=4G
dd if=/dev/zero of=./nvme_4G.ramdisk bs=1024 count=0 seek=4M
```

## other useful info
1. [openchannel ssd](https://openchannelssd.readthedocs.io/en/latest/)
2. [a better qemu for nvme](https://github.com/OpenChannelSSD/qemu-nvme/)
3. a summary of nvme from [smart tool](https://www.smartmontools.org/wiki/NVMe_Support)

## eval
1. device:
	```
	lifeng@node0:~$ sudo fdisk -l
	Disk /dev/nvme0n1: 8 GiB, 8573186048 bytes, 2093063 sectors
	Units: sectors of 1 * 4096 = 4096 bytes
	Sector size (logical/physical): 4096 bytes / 4096 bytes
	I/O size (minimum/optimal): 4096 bytes / 4096 bytes

	```
2. speed:
	4k write 70MB/s with 55us latency:
	```
	feng@node0:~$ sudo fio -filename=/dev/nvme0n1 -direct=1 -rw=write -bs=4k -size=100G -runtime=10 -group_reporting -name=test_write
	[sudo] password for lifeng: 
	test_write: (g=0): rw=write, bs=4K-4K/4K-4K/4K-4K, ioengine=sync, iodepth=1
	fio-2.2.10
	Starting 1 process
	Jobs: 1 (f=1): [W(1)] [100.0% done] [0KB/64972KB/0KB /s] [0/16.3K/0 iops] [eta 00m:00s]
	test_write: (groupid=0, jobs=1): err= 0: pid=1304: Thu Mar  8 16:50:34 2018
	  write: io=663876KB, bw=66381KB/s, iops=16595, runt= 10001msec
		clat (usec): min=47, max=102750, avg=54.94, stdev=252.20
		 lat (usec): min=48, max=102753, avg=56.11, stdev=252.21
		clat percentiles (usec):
		 |  1.00th=[   49],  5.00th=[   50], 10.00th=[   50], 20.00th=[   51],
		 | 30.00th=[   51], 40.00th=[   52], 50.00th=[   53], 60.00th=[   54],
		 | 70.00th=[   55], 80.00th=[   56], 90.00th=[   57], 95.00th=[   61],
		 | 99.00th=[   94], 99.50th=[   98], 99.90th=[  122], 99.95th=[  145],
		 | 99.99th=[  207]
		bw (KB  /s): min=45376, max=69864, per=100.00%, avg=66408.00, stdev=5347.74
		lat (usec) : 50=1.76%, 100=97.96%, 250=0.28%, 500=0.01%, 750=0.01%
		lat (msec) : 250=0.01%
	  cpu          : usr=13.20%, sys=23.72%, ctx=165991, majf=0, minf=12
	  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
		 submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
		 complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
		 issued    : total=r=0/w=165969/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
		 latency   : target=0, window=0, percentile=100.00%, depth=1

	Run status group 0 (all jobs):
	  WRITE: io=663876KB, aggrb=66380KB/s, minb=66380KB/s, maxb=66380KB/s, mint=10001msec, maxt=10001msec

	Disk stats (read/write):
	  nvme0n1: ios=42/164286, merge=0/0, ticks=12/6188, in_queue=6172, util=61.69%
	```

