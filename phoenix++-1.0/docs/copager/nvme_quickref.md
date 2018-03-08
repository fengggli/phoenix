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
	```
	feng@node0:~$ sudo fio -filename=/dev/nvme0n1 -direct=1 -rw=write -bs=1m -size=100G -numjobs=4 -runtime=10 -group_reporting -name=test_read
	test_read: (g=0): rw=write, bs=1M-1M/1M-1M/1M-1M, ioengine=sync, iodepth=1
	...
	fio-2.2.10
	Starting 4 processes 
	Jobs: 4 (f=4): [W(4)] [100.0% done] [0KB/185.0MB/0KB /s] [0/185/0 iops] [eta 00m:00s]
	test_read: (groupid=0, jobs=4): err= 0: pid=1850: Wed Mar  7 21:19:43 2018
	  write: io=4427.0MB, bw=450263KB/s, iops=439, runt= 10068msec
		clat (usec): min=306, max=2518.4K, avg=9070.67, stdev=75598.77
		 lat (usec): min=319, max=2518.5K, avg=9088.44, stdev=75599.70
		clat percentiles (usec):
		 |  1.00th=[  366],  5.00th=[  382], 10.00th=[  390], 20.00th=[  438],
		 | 30.00th=[  572], 40.00th=[  580], 50.00th=[  596], 60.00th=[  700],
		 | 70.00th=[  900], 80.00th=[ 1224], 90.00th=[24192], 95.00th=[47872],
		 | 99.00th=[94720], 99.50th=[108032], 99.90th=[230400], 99.95th=[2473984],
		 | 99.99th=[2506752]
		bw (KB  /s): min= 1502, max=1262051, per=32.21%, avg=145019.25, stdev=229379.22
		lat (usec) : 500=22.84%, 750=40.09%, 1000=10.26%
		lat (msec) : 2=11.84%, 4=0.09%, 10=0.36%, 20=1.11%, 50=9.92%
		lat (msec) : 100=2.82%, 250=0.59%, >=2000=0.09%
	  cpu          : usr=0.31%, sys=0.49%, ctx=4434, majf=0, minf=41
	  IO depths    : 1=100.0%, 2=0.0%, 4=0.0%, 8=0.0%, 16=0.0%, 32=0.0%, >=64=0.0%
		 submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
		 complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
		 issued    : total=r=0/w=4427/d=0, short=r=0/w=0/d=0, drop=r=0/w=0/d=0
		 latency   : target=0, window=0, percentile=100.00%, depth=1

	Run status group 0 (all jobs):
	  WRITE: io=4427.0MB, aggrb=450263KB/s, minb=450263KB/s, maxb=450263KB/s, mint=10068msec, maxt=10068msec

	Disk stats (read/write):
	  nvme0n1: ios=42/4417, merge=0/0, ticks=0/38812, in_queue=38984, util=99.07%
	```

