```bash
~ # ls
bin             lib             sbin
dev             linuxrc         simple_char.ko
etc             lost+found      usr
~ # insmod simple_char.ko 
simple_char: loading out-of-tree module taints kernel.
char_dev_driver loaded major: 248 minor: 0
~ # ls
bin             lib             sbin
dev             linuxrc         simple_char.ko
etc             lost+found      usr
~ # cd dev
/dev # ls
char_dev_driver  ptypf            tty38            ttyp1
console          random           tty39            ttyp2
cpu_dma_latency  rtc0             tty4             ttyp3
full             snd              tty40            ttyp4
gpiochip0        tty              tty41            ttyp5
gpiochip1        tty0             tty42            ttyp6
gpiochip2        tty1             tty43            ttyp7
gpiochip3        tty10            tty44            ttyp8
hwrng            tty11            tty45            ttyp9
input            tty12            tty46            ttypa
kmsg             tty13            tty47            ttypb
mem              tty14            tty48            ttypc
mmcblk0          tty15            tty49            ttypd
mtd0             tty16            tty5             ttype
mtd0ro           tty17            tty50            ttypf
mtd1             tty18            tty51            ubi_ctrl
mtd1ro           tty19            tty52            urandom
mtdblock0        tty2             tty53            usbmon0
mtdblock1        tty20            tty54            vcs
null             tty21            tty55            vcs1
port             tty22            tty56            vcs2
ptmx             tty23            tty57            vcs3
ptyp0            tty24            tty58            vcs4
ptyp1            tty25            tty59            vcsa
ptyp2            tty26            tty6             vcsa1
ptyp3            tty27            tty60            vcsa2
ptyp4            tty28            tty61            vcsa3
ptyp5            tty29            tty62            vcsa4
ptyp6            tty3             tty63            vcsu
ptyp7            tty30            tty7             vcsu1
ptyp8            tty31            tty8             vcsu2
ptyp9            tty32            tty9             vcsu3
ptypa            tty33            ttyAMA0          vcsu4
ptypb            tty34            ttyAMA1          zero
ptypc            tty35            ttyAMA2
ptypd            tty36            ttyAMA3
ptype            tty37            ttyp0
/dev # cat char_dev_driver 
/dev # echo "this is user space" > char_dev_driver 
/dev # cat char_dev_driver 
this is user space
/dev # echo "this is user space, hello kernel" > char_dev_driver 
/dev # cat char_dev_driver 
this is user space, hello kernel
/dev # 


```