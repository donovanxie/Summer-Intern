#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#define DEVNODE "/dev/demo_char"

/* ---- copy the same ioctl definitions the driver uses ---- */
#define DEMO_IOC_MAGIC      'd'
#define DEMO_IOC_SET_BUFSZ  _IOW(DEMO_IOC_MAGIC, 1, size_t)
#define DEMO_IOC_GET_BUFSZ  _IOR(DEMO_IOC_MAGIC, 2, size_t)

static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    size_t sz;
    int fd = open(DEVNODE, O_RDWR);
    if (fd < 0) die("open");

    if (argc == 2) {
        /* ---------- set new size ---------- */
        sz = strtoul(argv[1], NULL, 0);
        if (ioctl(fd, DEMO_IOC_SET_BUFSZ, &sz) < 0)
            die("ioctl SET_BUFSZ");
        printf("buffer resized to %zu bytes\n", sz);
    }

    /* ---------- always query current size ---------- */
    if (ioctl(fd, DEMO_IOC_GET_BUFSZ, &sz) < 0)
        die("ioctl GET_BUFSZ");
    printf("current size = %zu bytes\n", sz);

    close(fd);
    return 0;
}
