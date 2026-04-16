#ifndef MONITOR_IOCTL_H
#define MONITOR_IOCTL_H

#include <linux/types.h>

#define CONTAINER_MON_MAGIC 0xCF


struct container_info_t{

  pid_t pid;
  uint64_t soft_mib;
  uint64_t hard_mib;
};

#define IOCTL_REGISTER_PID _IOW(CONTAINER_MON_MAGIC,1,struct container_info_t)
#define IOCTL_REGISTER_PID _IOW(CONTAINER_MON_MAGIC,2,struct container_info_t)
#endif
