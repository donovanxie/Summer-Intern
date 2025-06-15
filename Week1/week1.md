# Week 1 Task

## Nand flash和NOR flash的区别
nand flash 和 nor flash的最大区别在于其内部晶体管的连接方式不一样。在nor flash中，每一个晶体管的两端都分别连接上bit lane和source lane，这个并联特性使得nor flash具有真正的随机读取性，并且读取速度比nand flash快许多。

而在nand flash中，各个晶体管之间直接串联在一起 （通常是8个一组串联），这使得nand flash的随机读取性差于nor flash，在nand flash中进行读取时，通常需要读取整个page，把整个page的信息保存到一个buffer里面再进行传输，这一特性使得nand flash的读取速度比起nor flash来说会较为缓慢。

nor flash的真随机读取特性使得nor flash更适合代码执行，但是并联的连接方式使得nor flash的尺寸以及造价显著高于nand flash。nand flash的串联特性可以节省许多空间，但代价为读取速度慢以及I/O映射更为复杂，nand flash中的代码执行为读取内容去RAM，再在RAM里面执行，这和nor flash的原生代码直接执行有着本质的区别。由于nand flash避不开良品率的问题，nand flash通常有着98%的良品率，但是这剩下的2%使得nand flash需要内置ECC。

在内容擦除方面，nand flash的优势才真正被体现出来，nand flash的擦除工作非常简单，而在nor flash中，每一个bit必须先被写为0才能被擦除，互联网资料显示，nand flash擦除一个128kb区块需要大约3.5毫秒，而nor flash需要520毫秒，两者速度相差近150倍。

在可靠性方面，正如之前提及的那样，nand flash绕不开良率问题，尽管出厂时坏块会随机散布，但随着nand flash的读写次数增加，在其整个生命周期中，坏块会越来越多，因此坏块处理与纠错代码ECC是nand flash的必备功能，而nor flash在出厂时几乎没有坏块，并且在nor flash的整个生命周期里坏块的累计率也非常低，这使得在数据保存的可靠性方面，nor flash强于nand flash。

## CPU、MCU、SOC之间的区别
CPU指的是现代台式机和笔记本电脑使用的中央处理器，CPU往往具有更多的核心数量，更大的体积与功耗，更高的造价，以及更强大的性能。

MCU指的是微控制器，也就是常说的单片机，MCU集成了中央处理器，RAM，ROM，Timer和各种I/O接口用于连接外设。MCU的处理性能较弱，造价低，功耗少，实际使用场景中更注重实时性，ARM Cortex-Mx系列就是典型代表。

SoC则是集成了所有现代计算机系统部件在一个单独的芯片上，SoC包含了中央处理器，RAM，ROM，I/O控制器，GPU，DSP，WiFi等等，甚至个别型号还包含了AI加速单元。SoC的价格和性能会强于MCU，一个MCU通常只能运行一些特定的实时性任务，最多会运行一个RTOS进行实时的任务调度和中断处理，而SoC可以运行真正的系统，典型的应用为Linux。

## 什么是交叉编译
交叉编译指的是代码的编译与运行是分别在不同的平台上进行的，在我的日常工作中，典型的应用是在Ubuntu主机上，也就是Host上面使用arm-linux-gnueabihf-gcc工具链编译代码，输出的可执行文件在target上执行，在我的例子里就是可执行文件在BeagleBone Black上运行。

## 什么是冯诺依曼结构和哈弗结构
冯诺依曼结构的处理器使用同一个存储器，经由同一个总线进行传输，这意味着冯诺依曼结构下，程序空间和数据空间是一体的，冯诺依曼结构要求处理器必须有一个存储器，一个控制器，一个运算器和输入输出设备。

而哈佛结构最大的特点是他是一种将程序指令存储器和数据存储器分开的结构。这使得哈佛结构的处理器在执行命令时，可以预先读取下一条指令，同时，这种分开的结构也使指令和数据拥有不同的宽度成为可能。
<div align=center>
<img src="https://pica.zhimg.com/70/v2-3333594d99b4c825d99737d7d771b99c_1440w.avis?source=172ae18b&biz_tag=Post">
</div>

## ARM分哪些异常等级?
ARMv8下存在4个异常等级，EL0-3。

EL0通常指的user space，用户的大多数应用都运行在EL0下，类似于浏览器，Linux shell，任何非信任的无法进行直接硬件访问的程序都运行在EL0级别，在这个级别也被称为non-privileged。

EL1是一个privileged level，Linux 内核通常运行在EL1下，在EL1下可以进行内存映射，中断处理，任务调度。

EL2在官方文档中被描述为Hypervisor，通常应用于虚拟机，例如虚拟机中的系统需要访问sandbox以外的东西，例如page table，这时候hypervisor会介入。

EL3为最高级别，官方文档描述为Secure monitor。EL3决定核心在secure和non-secure之间切换，在ARM下也称为TrustZone split。芯片被点亮后第一个运行的firmware往往是EL3级别，可以启动ROM，也可以进行固件更新。

<div align=center>
<img src="https://documentation-service.arm.com/static/67ac57fb091bfc3e0a9479d7?token=">
</div>
