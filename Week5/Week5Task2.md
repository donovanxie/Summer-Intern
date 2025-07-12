# Week 5 Task 2
# ARM Linux Boot Walk‑Through (QEMU vexpress‑a9, Linux 6.12.34)

## 0  Boot parameters

```bash
qemu-system-arm -M vexpress-a9 -m 512M -kernel /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/zImage -dtb /home/fxie/Desktop/SummerIntern_QEMU/linux-6.12.34/arch/arm/boot/dts/arm/vexpress-v2p-ca9.dtb -nographic -append "root=/dev/mmcblk0 rw console=ttyAMA0" -sd disk.img
```
- zImage: self‑extracting kernel placed at 0x6000_0000 by QEMU.
- DTB: hardware description handed in r2.
- cmdline: root device + serial console.



---

## 1  From reset to `start_kernel()`

| Stage                             | PC / Function                     | Source file              | Log evidence                        |
| --------------------------------- | --------------------------------- | ------------------------ | ----------------------------------- |
| ROM‑loader → QEMU boots `zImage`  | `arch/arm/boot/compressed/head.S` | –                        | (implicit)                          |
| Self‑extract, jump to real kernel | `__enter_kernel`                  | `arch/arm/kernel/head.S` | –                                   |
| C entry‑point                     | `start_kernel()`                  | `init/main.c`    | `Booting Linux on physical CPU 0x0` |

---

## 2  `start_kernel()` early setup (generic)

| Line in log                       | Function path                                                           |
| --------------------------------- | ----------------------------------------------------------------------- |
| `printk: log_buf_len…`            | `pr_early()` → ring‑buffer size print inside **kernel/printk/printk.c** |
| `OF: fdt: Machine model: V2P‑CA9` | `early_init_fdt_scan()` → **drivers/of/fdt.c**                          |
| `Zone ranges:` … `Initmem setup`  | `mm_init()` → **mm/mm\_init.c** → buddy + memblock                      |
| `RCU restricting CPUs…`           | `rcu_init()` → **kernel/rcu/tree.c**                                    |
| `sched_clock: 32 bits at 24 MHz`  | `sched_clock_register()` via **drivers/clocksource/arm\_sp804.c**       |
| `Calibrating delay loop…`         | `calibrate_delay()` → **kernel/time/timer.c**                           |

---

## 3  Architecture‑specific setup

| Log                                 | Source                                                                        |
| ----------------------------------- | ----------------------------------------------------------------------------- |
| `CPU: ARMv7 Processor [410fc090]`   | `setup_arch()` → **arch/arm/kernel/setup.c** prints CPU ID                    |
| `L2C-310 cache controller enabled…` | `l2x0_of_init()` → **drivers/cache/l2x0.c**                                   |
| `smp: Bringing up secondary CPUs…`  | `smp_init_cpus()` + `boot_secondary()` → **arch/arm/mach‑vexpress/platsmp.c** |

---

## 4  Initcall walk (drivers & subsystems)

The kernel now iterates **link‑ordered initcall levels**:

```
init/main.c   kernel_init_freeable()
  ↳ do_basic_setup()
      ↳ do_initcalls()           ← loops over __initcall sections
```

### Selected examples

| Order macro       | Function (file)                                             | Log snippet                                      |
| ----------------- | ----------------------------------------------------------- | ------------------------------------------------ |
| `core_initcall`   | `vexpress_init()` (`arch/arm/mach‑vexpress/core.c`)         | none (silent)                                    |
| `device_initcall` | `amba_init()` (`drivers/amba/bus.c`)                        | `Serial: AMBA PL011 UART driver`                 |
| `device_initcall` | `demo_char_init()` (`drivers/misc/demo_char/simple_char.c`) | `demo_char: loaded  major=250 minor=0, buf=1024` |

`module_init()` expands to `device_initcall()` when `CONFIG_DEMO_CHAR=y`, so your driver banner appears here automatically.

---

## 5  Mounting the root filesystem

| Step                                     | Code                             | Log                                      |
| ---------------------------------------- | -------------------------------- | ---------------------------------------- |
| Parse `root=` cmdline                    | `fs/namespace.c` `get_fs_type()` | (silent)                                 |
| `prepare_namespace()` mounts ext4 on `/` | `init/do_mounts.c`               | `EXT4-fs (mmcblk0): mounted filesystem…` |

---

## 6  Starting user space

```text
VFS: Mounted root (ext4 filesystem) on device 179:0.
Run /sbin/init as init process
```

Path:

```
rest_init()           init/main.c
  ↳ kernel_init()     init/main.c
      ↳ run_init_process("/sbin/init")
```

Failure to find BusyBox rcS script is printed in **init/noinitramfs.c**.

---

