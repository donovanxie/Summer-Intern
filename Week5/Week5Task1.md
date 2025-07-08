# Week 5 Task 1

## Build-in with kernel

under Kernel souce folder, make a new folder named demo_char under /drivers/misc
```bash
mkdir -p drivers/misc/demo_char
```

copy the driver code to this folder

```bash
cp /home/fxie/Desktop/Summer-Intern/Week4/simple_char_ioctl.c /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/drivers/misc/demo_char

```

add Kconfig and Makefile for driver code

```bash
nano Kconfig
nano Makefile
```

Kconfig:
```
config DEMO_CHAR
        tristate "Demo resizable buffer char device"
        default n
        help
          Simple teaching driver that provides /dev/demo_char with a
          resizable RAM buffer. Supports read/write and two ioctl
          commands (set/query buffer size).
```
Makefile:
```
obj-y  += simple_char_ioctl.o

```

make a new entry under the misc global Kconfig
at the end of the Kconfig, add this line:
```
source "drivers/misc/demo_char/Kconfig"
```

make an entry under the misc global Makefile, append this line at the end of Makefile:
```
obj-$(CONFIG_DEMO_CHAR) += demo_char/
```
Trun it on in menuconfig and re-compile the kernel
![alt text](image.png)


now the device driver is successfully loaded during kernel boot up 
```bash
fxie@fxie-Z790-AORUS-ELITE-AX:~/Desktop/SummerIntern_QEMU$ qemu-system-arm -M vexpress-a9 -m 512M -kernel /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/zImage -dtb /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb -nographic -append "root=/dev/mmcblk0 rw console=ttyAMA0" -sd disk.img
WARNING: Image format was not specified for 'disk.img' and probing guessed raw.
         Automatically detecting the format is dangerous for raw images, write operations on block 0 will be restricted.
         Specify the 'raw' format explicitly to remove the restrictions.
Booting Linux on physical CPU 0x0
Linux version 6.12.34 (fxie@fxie-Z790-AORUS-ELITE-AX) (arm-xilinx-linux-gnueabi-gcc.real (GCC) 13.3.0, GNU ld (GNU Binutils) 2.42.0.20240216) #5 SMP Tue Jul  8 14:16:37 PDT 2025
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
Calibrating local timer... 95.85MHz.
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
demo_char: loaded  major=250 minor=0, buf=1024
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
rtc-pl031 10017000.rtc: setting system clock to 2025-07-08T21:16:52 UTC (1752009412)
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
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
mmc0: new SD card at address 4567
mmcblk0: mmc0:4567 QEMU! 512 MiB
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
input: AT Raw Set 2 keyboard as /devices/platform/bus@40000000/bus@40000000:motherboard-bus@40000000/bus@40000000:motherboard-bus@40000000:iofpga@7,00000000/10006000.kmi/serio0/input/input0
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
clk: Disabling unused clocks
ALSA device list:
  #0: ARM AC'97 Interface PL041 rev0 at 0x10004000, irq 37
input: ImExPS/2 Generic Explorer Mouse as /devices/platform/bus@40000000/bus@40000000:motherboard-bus@40000000/bus@40000000:motherboard-bus@40000000:iofpga@7,00000000/10007000.kmi/serio1/input/input2
drm-clcd-pl111 10020000.clcd: DVI muxed to daughterboard 1 (core tile) CLCD
drm-clcd-pl111 10020000.clcd: initializing Versatile Express PL111
EXT4-fs (mmcblk0): recovery complete
EXT4-fs (mmcblk0): mounted filesystem 2de30ab9-1dfb-4e8a-b84a-4fca965ab9d4 r/w with ordered data mode. Quota mode: disabled.
VFS: Mounted root (ext4 filesystem) on device 179:0.
devtmpfs: mounted
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

~ # dmesg | grep demo_char
demo_char: loaded  major=250 minor=0, buf=1024
~ # echo "Test from user space" > demo_char
~ # cat demo_char
Test from user space

```
