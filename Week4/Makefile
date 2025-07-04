obj-m := simple_char.o simple_char_ioctl.o

KDIR ?= /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34
ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabihf-


all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean