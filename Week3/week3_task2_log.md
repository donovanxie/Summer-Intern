# Week 3 Task 2 Process Log

## Step 1. Build Linux Kernel 6.12.34 using Vexpress_defconfig

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/linux-6.12.34$ make vexpress_defconfig
```
    
    note:   here I have exported 
            ARCH=arm
            CROSS_COMPILE=arm-linux-gnueabihf-
            in bashrc.

## Step 2. Build U-Boot 2025.004

listed out all the avaliable config files, decided to fo with vexpress_ca9x4_defconfig as per instructions in CSDN.

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/u-boot-2025.04$ ls configs | grep vexpress
vexpress_aemv8a_juno_defconfig
vexpress_aemv8a_semi_defconfig
vexpress_aemv8r_defconfig
vexpress_ca9x4_defconfig
vexpress_fvp_defconfig
```

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/u-boot-2025.04$ make vexpress_ca9x4_defconfig
#
# configuration written to .config
#
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/u-boot-2025.04$ make all
```

## Step 3. Build Busybox 1.36.0

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/busybox-1_36_0$ make defconfig

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/busybox-1_36_0$ make

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU/busybox-1_36_0$ make install

```

## Step 4. Prepard the Root file system

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ mkdir -p rootfs/{dev,etc/init.d,lib}

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo cp /home/fxie/Desktop/SummerIntern_QEMU/busybox-1_36_0/_install/* -r rootfs/

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo cp -P /usr/arm-linux-gnueabihf/lib/* rootfs/lib/

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mknod rootfs/dev/tty1 c 4 1

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mknod rootfs/dev/tty2 c 4 2

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mknod rootfs/dev/tty3 c 4 3

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mknod rootfs/dev/tty4 c 4 4

```
After finish doing the busybox, it is now the time to prepare the QEMU images

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ qemu-img create -f raw disk.img 512M
Formatting 'disk.img', fmt=raw size=536870912
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ mkfs -t ext4 ./disk.img
mke2fs 1.47.0 (5-Feb-2023)
丢弃设备块： 完成                            
创建含有 131072 个块（每块 4k）和 32768 个 inode 的文件系统
文件系统 UUID：6574c2bb-6b9b-47c9-9fbc-742252b5f2e7
超级块的备份存储于下列块： 
	32768, 98304

正在分配组表： 完成                            
正在写入 inode表： 完成                            
创建日志（4096 个块）： 完成
写入超级块和文件系统账户统计信息： 已完成
```
Now we need to create a disk image for the qemu and mount it under my host pc under tmpfs, so the qemu environment can have a shared working directory with my host PC
```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ mkdir tmpfs
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mount -o loop ./disk.img tmpfs/

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo cp -r rootfs/* tmpfs/
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo umount tmpfs

fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ file disk.img
disk.img: Linux rev 1.0 ext4 filesystem data, UUID=6574c2bb-6b9b-47c9-9fbc-742252b5f2e7 (extents) (64bit) (large files) (huge files)

```
now it is time to run the virtual ARM in QEMU

```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ qemu-system-arm -M vexpress-a9 -m 512M -kernel /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/zImage -dtb /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb -nographic -append "root=/dev/mmcblk0 rw console=ttyAMA0" -sd disk.img

```

here is the Linux sucessfully booted up using QEMU
```bash
WARNING: Image format was not specified for 'disk.img' and probing guessed raw.
         Automatically detecting the format is dangerous for raw images, write operations on block 0 will be restricted.
         Specify the 'raw' format explicitly to remove the restrictions.
Booting Linux on physical CPU 0x0
Linux version 6.12.34 (fxie@fxie-Z790-AORUS-ELITE-AX) (arm-xilinx-linux-gnueabi-gcc.real (GCC) 13.3.0, GNU ld (GNU Binutils) 2.42.0.20240216) #1 SMP Wed Jun 25 15:58:05 PDT 2025
CPU: ARMv7 Processor [410fc090] revision 0 (ARMv7), cr=10c5387d
CPU: PIPT / VIPT nonaliasing data cache, VIPT nonaliasing instruction cache
OF: fdt: Machine model: V2P-CA9
Memory policy: Data cache writeback
cma: Reserved 16 MiB at 0x7f000000 on node -1
Zone ranges:
  Normal   [mem 0x0000000060000000-0x000000007fffffff]
Movable zone start for each node
Early memory node ranges
  node   0: [mem 0x0000000060000000-0x000000007fffffff]
Initmem setup node 0 [mem 0x0000000060000000-0x000000007fffffff]
Reserved memory: created DMA memory pool at 0x4c000000, size 8 MiB
OF: reserved mem: initialized node vram@4c000000, compatible id shared-dma-pool
OF: reserved mem: 0x4c000000..0x4c7fffff (8192 KiB) nomap non-reusable vram@4c000000
CPU: All CPU(s) started in SVC mode.
percpu: Embedded 17 pages/cpu s39244 r8192 d22196 u69632
Kernel command line: root=/dev/mmcblk0 rw console=ttyAMA0
printk: log_buf_len individual max cpu contribution: 4096 bytes
printk: log_buf_len total cpu_extra contributions: 12288 bytes
printk: log_buf_len min size: 16384 bytes
printk: log_buf_len: 32768 bytes
printk: early log buf free: 14928(91%)
Dentry cache hash table entries: 65536 (order: 6, 262144 bytes, linear)
Inode-cache hash table entries: 32768 (order: 5, 131072 bytes, linear)
Built 1 zonelists, mobility grouping on.  Total pages: 131072
mem auto-init: stack:all(zero), heap alloc:off, heap free:off
SLUB: HWalign=64, Order=0-3, MinObjects=0, CPUs=4, Nodes=1
rcu: Hierarchical RCU implementation.
rcu: 	RCU event tracing is enabled.
rcu: 	RCU restricting CPUs from NR_CPUS=8 to nr_cpu_ids=4.
rcu: RCU calculated value of scheduler-enlistment delay is 10 jiffies.
rcu: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=4
NR_IRQS: 16, nr_irqs: 16, preallocated irqs: 16
GIC CPU mask not found - kernel will fail to boot.
GIC CPU mask not found - kernel will fail to boot.
L2C: platform modifies aux control register: 0x02020000 -> 0x02420000
L2C: DT/platform modifies aux control register: 0x02020000 -> 0x02420000
L2C-310 enabling early BRESP for Cortex-A9
L2C-310 full line of zeros enabled for Cortex-A9
L2C-310 dynamic clock gating disabled, standby mode disabled
L2C-310 cache controller enabled, 8 ways, 128 kB
L2C-310: CACHE_ID 0x410000c8, AUX_CTRL 0x46420001
rcu: srcu_init: Setting srcu_struct sizes based on contention.
sched_clock: 32 bits at 24MHz, resolution 41ns, wraps every 89478484971ns
clocksource: arm,sp804: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 1911260446275 ns
smp_twd: clock not found -2
Console: colour dummy device 80x30
Calibrating local timer... 95.62MHz.
Calibrating delay loop... 2419.91 BogoMIPS (lpj=12099584)
CPU: Testing write buffer coherency: ok
CPU0: Spectre v2: using BPIALL workaround
pid_max: default: 32768 minimum: 301
Mount-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes, linear)
CPU0: thread -1, cpu 0, socket 0, mpidr 80000000
Setting up static identity map for 0x60100000 - 0x60100060
rcu: Hierarchical SRCU implementation.
rcu: 	Max phase no-delay instances is 1000.
Timer migration: 1 hierarchy levels; 8 children per group; 1 crossnode level
smp: Bringing up secondary CPUs ...
smp: Brought up 1 node, 1 CPU
SMP: Total of 1 processors activated (2419.91 BogoMIPS).
CPU: All CPU(s) started in SVC mode.
Memory: 486344K/524288K available (9216K kernel code, 752K rwdata, 2152K rodata, 1024K init, 193K bss, 19308K reserved, 16384K cma-reserved)
devtmpfs: initialized
VFP support v0.3: implementor 41 architecture 3 part 30 variant 9 rev 0
clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns
futex hash table entries: 1024 (order: 4, 65536 bytes, linear)
NET: Registered PF_NETLINK/PF_ROUTE protocol family
DMA: preallocated 256 KiB pool for atomic coherent allocations
cpuidle: using governor ladder
hw-breakpoint: debug architecture 0x4 unsupported.
Serial: AMBA PL011 UART driver
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /clcd@10020000
/clcd@10020000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
SCSI subsystem initialized
usbcore: registered new interface driver usbfs
usbcore: registered new interface driver hub
usbcore: registered new device driver usb
/clcd@10020000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/clcd@1f000
/bus@40000000/motherboard-bus@40000000/iofpga@7,00000000/i2c@16000/dvi-transmitter@39: Fixed dependency cycle(s) with /clcd@10020000
pps_core: LinuxPPS API ver. 1 registered
pps_core: Software ver. 5.3.6 - Copyright 2005-2007 Rodolfo Giometti <giometti@linux.it>
PTP clock support registered
Advanced Linux Sound Architecture Driver Initialized.
clocksource: Switched to clocksource arm,sp804
NET: Registered PF_INET protocol family
IP idents hash table entries: 8192 (order: 4, 65536 bytes, linear)
tcp_listen_portaddr_hash hash table entries: 512 (order: 0, 4096 bytes, linear)
Table-perturb hash table entries: 65536 (order: 6, 262144 bytes, linear)
TCP established hash table entries: 4096 (order: 2, 16384 bytes, linear)
TCP bind hash table entries: 4096 (order: 4, 65536 bytes, linear)
TCP: Hash tables configured (established 4096 bind 4096)
UDP hash table entries: 256 (order: 1, 8192 bytes, linear)
UDP-Lite hash table entries: 256 (order: 1, 8192 bytes, linear)
NET: Registered PF_UNIX/PF_LOCAL protocol family
RPC: Registered named UNIX socket transport module.
RPC: Registered udp transport module.
RPC: Registered tcp transport module.
RPC: Registered tcp-with-tls transport module.
RPC: Registered tcp NFSv4.1 backchannel transport module.
workingset: timestamp_bits=30 max_order=17 bucket_order=0
squashfs: version 4.0 (2009/01/31) Phillip Lougher
jffs2: version 2.2. (NAND) © 2001-2006 Red Hat, Inc.
9p: Installing v9fs 9p2000 file system support
io scheduler mq-deadline registered
io scheduler kyber registered
io scheduler bfq registered
ledtrig-cpu: registered to indicate activity on CPUs
sii902x 0-0060: supply iovcc not found, using dummy regulator
sii902x 0-0060: supply cvcc12 not found, using dummy regulator
simple-pm-bus bus@40000000:motherboard-bus@40000000:iofpga@7,00000000: Failed to create device link (0x180) with dcc:clock-controller-2
simple-pm-bus bus@40000000:motherboard-bus@40000000:iofpga@7,00000000: Failed to create device link (0x180) with dcc:clock-controller-2
physmap-flash 40000000.flash: physmap platform flash device: [mem 0x40000000-0x43ffffff]
40000000.flash: Found 2 x16 devices at 0x0 in 32-bit bank. Manufacturer ID 0x000000 Chip ID 0x000000
Intel/Sharp Extended Query Table at 0x0031
Using buffer write method
physmap-flash 40000000.flash: physmap platform flash device: [mem 0x44000000-0x47ffffff]
40000000.flash: Found 2 x16 devices at 0x0 in 32-bit bank. Manufacturer ID 0x000000 Chip ID 0x000000
Intel/Sharp Extended Query Table at 0x0031
Using buffer write method
Concatenating MTD devices:
(0): "40000000.flash"
(1): "40000000.flash"
into device "40000000.flash"
physmap-flash 48000000.psram: physmap platform flash device: [mem 0x48000000-0x49ffffff]
smsc911x 4e000000.ethernet eth0: MAC Address: 52:54:00:12:34:56
isp1760 4f000000.usb: isp1760 bus width: 32, oc: digital
isp1760 4f000000.usb: NXP ISP1760 USB Host Controller
isp1760 4f000000.usb: new USB bus registered, assigned bus number 1
isp1760 4f000000.usb: Scratch test failed. 0x00000000
isp1760 4f000000.usb: can't setup: -19
isp1760 4f000000.usb: USB bus 1 deregistered
usbcore: registered new interface driver usb-storage
rtc-pl031 10017000.rtc: registered as rtc0
rtc-pl031 10017000.rtc: setting system clock to 2025-06-26T06:15:13 UTC (1750918513)
mmci-pl18x 10005000.mmci: Got CD GPIO
mmci-pl18x 10005000.mmci: Got WP GPIO
usbcore: registered new interface driver usbhid
usbhid: USB HID core driver
mmci-pl18x 10005000.mmci: mmc0: PL181 manf 41 rev0 at 0x10005000 irq 31,32 (pio)
hw perfevents: enabled with armv7_cortex_a9 PMU driver, 7 (8000003f) counters available
aaci-pl041 10004000.aaci: ARM AC'97 Interface PL041 rev0 at 0x10004000, irq 37
aaci-pl041 10004000.aaci: FIFO 512 entries
NET: Registered PF_PACKET protocol family
9pnet: Installing 9P2000 support
Registering SWP/SWPB emulation handler
10009000.serial: ttyAMA0 at MMIO 0x10009000 (irq = 38, base_baud = 0) is a PL011 rev1
printk: legacy console [ttyAMA0] enabled
1000a000.serial: ttyAMA1 at MMIO 0x1000a000 (irq = 39, base_baud = 0) is a PL011 rev1
1000b000.serial: ttyAMA2 at MMIO 0x1000b000 (irq = 40, base_baud = 0) is a PL011 rev1
1000c000.serial: ttyAMA3 at MMIO 0x1000c000 (irq = 41, base_baud = 0) is a PL011 rev1
drm-clcd-pl111 1001f000.clcd: assigned reserved memory node vram@4c000000
drm-clcd-pl111 1001f000.clcd: using device-specific reserved memory
drm-clcd-pl111 1001f000.clcd: core tile graphics present
drm-clcd-pl111 1001f000.clcd: this device will be deactivated
drm-clcd-pl111 1001f000.clcd: Versatile Express init failed - -19
mmc0: new SD card at address 4567
mmcblk0: mmc0:4567 QEMU! 512 MiB
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
input: AT Raw Set 2 keyboard as /devices/platform/bus@40000000/bus@40000000:motherboard-bus@40000000/bus@40000000:motherboard-bus@40000000:iofpga@7,00000000/10006000.kmi/serio0/input/input0
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
clk: Disabling unused clocks
ALSA device list:
  #0: ARM AC'97 Interface PL041 rev0 at 0x10004000, irq 37
input: ImExPS/2 Generic Explorer Mouse as /devices/platform/bus@40000000/bus@40000000:motherboard-bus@40000000/bus@40000000:motherboard-bus@40000000:iofpga@7,00000000/10007000.kmi/serio1/input/input2
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
EXT4-fs (mmcblk0): mounted filesystem 6574c2bb-6b9b-47c9-9fbc-742252b5f2e7 r/w with ordered data mode. Quota mode: disabled.
VFS: Mounted root (ext4 filesystem) on device 179:0.
Freeing unused kernel image (initmem) memory: 1024K
Run /sbin/init as init process
random: crng init done
can't run '/etc/init.d/rcS': No such file or directory

Please press Enter to activate this console. 
~ # drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
amba 100e0000.memory-controller: deferred probe pending: (reason unknown)
amba 100e1000.memory-controller: deferred probe pending: (reason unknown)
amba 100e5000.watchdog: deferred probe pending: (reason unknown)
i2c 0-0039: deferred probe pending: sii902x: Failed to find remote bridge
amba 1000f000.wdt: deferred probe pending: (reason unknown)
amba 10020000.clcd: deferred probe pending: (reason unknown)

~ # 
~ # uname -a
Linux (none) 6.12.34 #1 SMP Wed Jun 25 15:58:05 PDT 2025 armv7l GNU/Linux
~ # ls
bin         etc         linuxrc     sbin
dev         lib         lost+found  usr

```

## Step 5. Cross Compile a test program to run

it is now a good time to write a test program to see if the linux is working fine using QEMU

here is the code:

```c
#include <stdio.h>

int main(){
        for(int i = 0; i < 11; i++){
        
        printf("Hello, this is test %d\n", i);
        }

        return 0;
}

```
create a C program and cross compile it for ARM
```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ touch hello_test.c
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ nano hello_test.c
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ arm-linux-gnueabihf-gcc -o test hello_test.c 
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ file test
test: ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=7bb64ba773030c6bdb38ae8f8d05ac08fdd4d1cc, for GNU/Linux 5.15.0, with debug_info, not stripped
```
Kill QEMU, then copy the cross compiled file into its folder
```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ killall qemu-system-arm 
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo mount -o loop ./disk.img tmpfs/
[sudo] fxie 的密码： 
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ cp test tmpfs/
cp: 无法创建普通文件 'tmpfs/test': 权限不够
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo cp test tmpfs/
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ sudo umount tmpfs

```
here is the result:
```bash
~ # ls
bin         etc         linuxrc     sbin        usr
dev         lib         lost+found  test
~ # ./test
Hello, this is test 0
Hello, this is test 1
Hello, this is test 2
Hello, this is test 3
Hello, this is test 4
Hello, this is test 5
Hello, this is test 6
Hello, this is test 7
Hello, this is test 8
Hello, this is test 9
Hello, this is test 10
~ # 

```