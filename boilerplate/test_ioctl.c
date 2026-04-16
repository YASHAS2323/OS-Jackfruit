#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "monitor_ioctl.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <PID> <Soft Limit Bytes> <Hard Limit Bytes>\n", argv[0]);
        return 1;
    }

    int fd = open("/dev/container_monitor", O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    struct monitor_request req;
    req.pid = atoi(argv[1]);
    strncpy(req.container_id, "test-container", sizeof(req.container_id) - 1);
    req.container_id[sizeof(req.container_id) - 1] = '\0';
    req.soft_limit_bytes = atol(argv[2]);
    req.hard_limit_bytes = atol(argv[3]);

    if (ioctl(fd, MONITOR_REGISTER, &req) < 0) {
        perror("IOCTL Failed");
    } else {
        printf("Successfully registered PID %d to kernel monitor.\n", req.pid);
    }

    close(fd);
    return 0;
}
